#include "Engine/RenderSystem/AresTerrain.h"
#include "Engine/AresRoot.h"
#include <boost/format.hpp>
#include <Core/AresNumericTools.h>
#include "Engine/RenderSystem/AresRenderable.h"
#include <boost/archive/binary_oarchive.hpp>

using namespace std;

namespace Ares
{
	// ��������Ȩ��
	static float ComputeWeight(float value, float minExtent, float maxExtent)
	{
		// Ȩ�س�ʼΪ��
		float weight = 0.0f;

		if ( value >= minExtent && value <= maxExtent)
		{
			float span = maxExtent - minExtent;
			weight = value - minExtent;

			// convert to a 0-1 range value based on its distance to the midpoint of the range extents
			weight = weight / span;
			weight -= 0.5f;
			weight *= 2.0f;

			// square the result for non-linear falloff
			weight *= weight;

			// invert and bound-check the result
			weight = 1.0f - abs(weight);
			weight = Clamp( weight, 0.0f, 1.0f);

			return weight;
		}

		return weight;
	}

	// ���캯��
	Terrain::Terrain()
		: RenderEntity( ED_Terrain)
	{ 
		Entity::SetStatic(true);

		m_version		= 1;
		m_visible       = true;

		m_material		= RenderMaterialPtr( new_ SuperMaterial);
#ifdef TERRAIN_TESSELLATION
		RenderMethodPtr rMethod = AResSystem.LoadMethod("TerrainDetailTessellection.hlsl");
#else
		RenderMethodPtr rMethod = AResSystem.LoadMethod("TerrainDefault.hlsl");
#endif
		m_material->SetMethod( rMethod);
		m_material->SetRenderQueue( RQ_Terrain);

		ShaderParamPtr tex0    = MakeShaderParam( AResSystem.SyncLoadDDS( "terrain_stone.dds", EAH_GPURead | EAH_Immutable));
		ShaderParamPtr tex1    = MakeShaderParam( AResSystem.SyncLoadDDS( "terrain_stone.dds", EAH_GPURead | EAH_Immutable));
		ShaderParamPtr tex2    = MakeShaderParam( AResSystem.SyncLoadDDS( "terrain_stone.dds", EAH_GPURead | EAH_Immutable));
		ShaderParamPtr tex3    = MakeShaderParam( AResSystem.SyncLoadDDS( "terrain_stone.dds", EAH_GPURead | EAH_Immutable));
		ShaderParamPtr lightmap= MakeShaderParam( AResSystem.SyncLoadDDS( "terrain_stone.dds", EAH_GPURead | EAH_Immutable));
		ShaderParamPtr uvScale = MakeShaderParam( Vector4( 1.f, 1.f, 1.f, 1.f));

		m_material->SetParamRef( "LinearSamp0", tex0);
		m_material->SetParamRef( "LinearSamp1", tex1);
		m_material->SetParamRef( "LinearSamp2", tex2);
		m_material->SetParamRef( "LinearSamp3", tex3);
		m_material->SetParamRef( "LightmapSamp",lightmap);
		m_material->SetParamRef( "G_UVScale",   uvScale);

		// ��̬�󶨲���
		m_material->SetParamAutoBind( "G_WorldViewProj", "SPAB_WorldViewProj");
		m_material->SetParamAutoBind( "G_WorldView",	 "SPAB_WorldView");
		m_material->SetParamAutoBind( "G_World",		 "SPAB_World");
		m_material->SetParamAutoBind( "G_CameraPos",	 "SPAB_CameraPos");

#ifdef TERRAIN_TESSELLATION
		ShaderParamPtr texNH = MakeShaderParam( AResSystem.SyncLoadDDS( "stones_NM_height.dds", EAH_GPURead | EAH_Immutable));
		m_material->SetParamRef( "G_NormalHeightTex", texNH);

		float TessellationFactorEdges = 7.f;
		float TessellationFactorInside= 7.f;
		float DesiredTriangleSize	  = 10.f;

		ShaderParamPtr tesllectionFactor			= MakeShaderParam( Vector4( TessellationFactorEdges, TessellationFactorInside, TessellationFactorEdges/2.f, 1.f/DesiredTriangleSize));
		ShaderParamPtr detailTesllectionHeightScale = MakeShaderParam( Vector4( 8.f, 0.f, 0.f, 0.f));

		m_material->SetParamRef( "G_TessellationFactor", tesllectionFactor);
		m_material->SetParamRef( "G_DetailTessellationHeightScale", detailTesllectionHeightScale);
#endif
	}

	// ��������
	Terrain::~Terrain()
	{

	}

	// ת���߶�ͼΪ��������
	bool Terrain::Build( int width, int height, BYTE shift)
	{
		bool result = false;

		m_tileShift = shift;
		m_iSectorUnits = 1 << shift;
		m_tileVerts = m_iSectorUnits + 1;

		Rect3 worldExtents;
		worldExtents.UnionPoint( 0.f, 0.f, -5.f);
		worldExtents.UnionPoint( static_cast<float>(width), static_cast<float>(height), 5.f);
		SetLocalBounds( worldExtents);
		m_worldExtends = worldExtents;
		m_vWorldSize = m_worldExtends.GetSize();

		// ��ͼ��С��ͬ�������С,�˴�������չ����Ϊ���ε�һ������ĳ�߶�ͼӰ��
		m_iTableWidth  = (WORD)m_worldExtends.GetXSize();
		m_iTableHeight = (WORD)m_worldExtends.GetYSize();

		m_vMapScale.x = m_vWorldSize.x / m_iTableWidth;
		m_vMapScale.y = m_vWorldSize.y / m_iTableHeight;
		m_vMapScale.z = m_vWorldSize.z / 255.0f;

		// Convert the height map to data stored in local tables
		BuildHeightAndNormalTables();

		// �߶�ͼ��ʼ��
		m_heightField.Init( m_iTableWidth, m_iTableHeight);
		m_heightField.SetHollow( m_iTableWidth, m_iTableHeight);

		m_numTileX = m_iTableWidth  >> m_tileShift;
		m_numTileY = m_iTableHeight >> m_tileShift;

		// �����С
		m_tileSize.x = m_vWorldSize.x / m_numTileX;
		m_tileSize.y = m_vWorldSize.y / m_numTileY;

		// �����鹲��Ķ���Buffer ����Buffer����
		BuildIndexBuffer();

		m_tileList.resize( m_numTileX * m_numTileY, s_ptr<TerrainTile>());

		// ������������
		for ( int x=0; x<GetTileNumX(); x++)
		{
			for ( int y=0; y<GetTileNumY(); y++)
				AllocateTile( x, y);
		}

		return result;
	}

	// ��������
	TerrainTilePtr Terrain::AllocateTile( size_t xIdx, size_t yIdx)
	{
		// Terrain tile data
		typedef Vector3 VertexPosition;
		typedef Vector3	VertexNormal;
		typedef DWORD   VertexBlend;
		typedef Vector2 VertexUV;

		A_ASSERT( xIdx<m_numTileX && yIdx<m_numTileY);

		// ��������
		WORD tileIdx = yIdx * m_numTileX + xIdx;

		TerrainTilePtr tTile = MakeSharePtr( new_ TerrainTile(this));

		// ����λ��
		Vector2 tilePos( m_worldExtends.m_min.x + xIdx * m_tileSize.x, m_worldExtends.m_min.y + yIdx * m_tileSize.y);
		
		WORD xHBase = xIdx << m_tileShift;
		WORD yHBase = yIdx << m_tileShift;

		// װ����������
		tTile->m_xVerts = m_tileVerts;
		tTile->m_yVerts = m_tileVerts;
		tTile->m_xIndex = xIdx;
		tTile->m_yIndex = yIdx;
		tTile->m_xHBase = xHBase;
		tTile->m_yHBase = yHBase;

		// ��Ⱦ����
		Renderable tileRenderable;

		RenderLayoutPtr layout = ARenderDevice->CreateRenderLayout();
		layout->SetTopologyType( RenderLayout::TT_TriangleStrip);

		GraphicBufferPtr bufferPosition;
		GraphicBufferPtr bufferNormal;
		GraphicBufferPtr bufferBlend;
		GraphicBufferPtr bufferLightmapUV;
		{
			// position
			Rect3 boundingBox;
			vector<VertexPosition>	  positions( m_tileVerts * m_tileVerts);
			vector<VertexNormal>	  normals( m_tileVerts * m_tileVerts);
			vector<VertexBlend>		  blends( m_tileVerts* m_tileVerts);
			vector<VertexUV>		  lightmapUVs( m_tileVerts * m_tileVerts);
			for (int y=0; y<m_tileVerts; y++)
				for (int x=0; x<m_tileVerts; x++)
				{
					size_t tIndex = y * m_tileVerts + x;

					positions[tIndex]  = Vector3( tilePos.x+x, tilePos.y+y, GetHeight( xHBase+x, yHBase+y));
					normals[tIndex]	   = m_heightField.GetNormalAt( xHBase+x, yHBase+y);
					blends[tIndex]	   = GetTexBlend( xHBase+x, yHBase+y);
					lightmapUVs[tIndex]= Vector2( static_cast<float>(x)/static_cast<float>(m_tileVerts), static_cast<float>(y)/static_cast<float>(m_tileVerts));

					boundingBox.UnionPoint( positions[tIndex]);
				}

			tTile->SetLocalBounds( boundingBox);

			// position
			ElementInitData initVertexPosData;
			initVertexPosData.m_rowPitch     = sizeof(VertexPosition) * positions.size();
			initVertexPosData.m_slicePitch   = 0;
			initVertexPosData.m_data		 = positions.data();
			bufferPosition				     = ARenderDevice->CreateVertexBuffer( BU_Static, EAH_GPURead | EAH_Immutable, &initVertexPosData);

			// normal
			ElementInitData initVertexNData;
			initVertexNData.m_rowPitch   = sizeof(VertexNormal) * normals.size();
			initVertexNData.m_slicePitch = 0;
			initVertexNData.m_data		 = normals.data();
			bufferNormal				 = ARenderDevice->CreateVertexBuffer( BU_Static, EAH_GPURead | EAH_Immutable, &initVertexNData);

			// blend
			ElementInitData initVertexBData;
			initVertexBData.m_rowPitch   = sizeof(VertexBlend) * blends.size();
			initVertexBData.m_slicePitch = 0;
			initVertexBData.m_data		 = blends.data();
			bufferBlend					 = ARenderDevice->CreateVertexBuffer( BU_Static, EAH_GPURead | EAH_Immutable, &initVertexBData);

			// lightmapuv
			ElementInitData initVertexLUVData;
			initVertexLUVData.m_rowPitch    = sizeof(VertexUV) * lightmapUVs.size();
			initVertexLUVData.m_slicePitch  = 0;
			initVertexLUVData.m_data		= lightmapUVs.data();
			bufferLightmapUV				= ARenderDevice->CreateVertexBuffer( BU_Static, EAH_GPURead | EAH_Immutable, &initVertexLUVData);
		}

		layout->BindVertexStream( bufferPosition, TerrainTile::Mapping( TerrainTile::VSF_Position));
		layout->BindVertexStream( bufferNormal, TerrainTile::Mapping( TerrainTile::VSF_Normal));
		layout->BindIndexStream( m_indexBuffer, EF_R16UI);

		tTile->SetVertexGraphicBuffer( TerrainTile::VSF_Position,	bufferPosition);
		tTile->SetVertexGraphicBuffer( TerrainTile::VSF_Normal,		bufferNormal);
		tTile->SetVertexGraphicBuffer( TerrainTile::VSF_Blend,		bufferBlend);
		tTile->SetVertexGraphicBuffer( TerrainTile::VSF_LightmapUV, bufferLightmapUV);
		tTile->SetIndexGraphicsBuffer( m_indexBuffer);

		tileRenderable.SetRenderlayout( layout);
		tileRenderable.SetMaterial( m_material);

		tTile->AddRenderable( tileRenderable);

		m_tileList[tileIdx] = tTile;

		return tTile;
	}

	// ������������
	bool Terrain::BuildIndexBuffer()
	{
		// create single strip grid
		int xStep			   = 1;
		int yStep			   = 1;
		int totalStrips        = m_tileVerts - 1;
		int totalIndexPerStrip = m_tileVerts << 1;

		// the total number of indices is equal
		// to the number of strips times the
		// indices used per strip plus one degenerate
		// triangle between each strip
		int totalIndexes = (totalIndexPerStrip * totalStrips) + (totalStrips<<1) - 2;

		vector<WORD> indexValues( totalIndexes);
		WORD* index = indexValues.data();
		WORD  lineStep = yStep * m_tileVerts;
		WORD  startVert = lineStep * totalStrips;

		for (int j=totalStrips-1; j>=0; j--)
		{
			WORD vert = startVert;

			// create a strip for this row
			for (int k=0; k<m_tileVerts; k++)
			{
				*(index++) = vert;
				*(index++) = vert - lineStep;

				vert += xStep;
			}

			startVert -= lineStep;

			if ( j > 0)
			{
				// ��������ڣ����������ζ���һ��ֱ����
				//  ___
				//    |
				// add a degenerate to attach to the next row
				*(index++) = startVert+lineStep-1; // (vert - xStep) - line_step; // (ע�Ͳ�����ǰ����һ��,���������)
				*(index++) = startVert;
			}
		}

		// ��������
		ElementInitData initIndexData;
		initIndexData.m_rowPitch   = indexValues.size() * NumFormatBytes( EF_R16UI);
		initIndexData.m_slicePitch = 0;
		initIndexData.m_data	   = indexValues.data();
		m_indexBuffer			   = ARenderDevice->CreateIndexBuffer( BU_Static, EAH_GPURead | EAH_Immutable, &initIndexData);

		return true;
	}

	// ʹ�ø߶�ͼ����
	bool Terrain::BuildHeightAndNormalTables()
	{
		UINT32 vertexNum = (m_iTableHeight+1) * (m_iTableWidth+1);

		// Ϊ�߶����ݷ����ڴ�ռ�
		m_blendTable.resize( vertexNum);

		return true;
	}

	// ��������
	void Terrain::DestroyTile( const s_ptr<TerrainTile>& tile)
	{
		std::remove( m_tileList.begin(), m_tileList.end(), tile);
	}

	// ��ȡָ����߶�
	float Terrain::GetHeight( WORD _x, WORD _y, float defaultValue)
	{
		return m_heightField.GetHeightAt( _x, _y);
	}


	// ��ȡָ���������϶�
	DWORD Terrain::GetTexBlend( WORD _x, WORD _y)
	{
		A_ASSERT( _x <= m_iTableWidth && _y<=m_iTableHeight);

		return m_blendTable[ TableIndex(_x, _y)];
	}

	// ����߶�����
	UINT32 Terrain::TableIndex(WORD mapX, WORD mapY)
	{
		// clamp to the table dimensions
		if( mapX > m_iTableWidth) mapX = m_iTableWidth;
		if( mapY > m_iTableHeight)mapY = m_iTableHeight;

		return  mapY*(m_iTableWidth+1) + mapX;
	}

	// ִ�����жԵ��ε��޸�
	bool Terrain::SetHeight( WORD _x, WORD _y, float height)
	{
		UpdateHeightAndNormal( _x,   _y,   &height);
		UpdateHeightAndNormal( _x,   _y+1, NULL);
		UpdateHeightAndNormal( _x,   _y-1, NULL);
		UpdateHeightAndNormal( _x+1, _y,   NULL);
		UpdateHeightAndNormal( _x-1, _y,   NULL);

		return true;
	}

	// ���������϶�
	bool Terrain::SetTexBlend(WORD _x, WORD _y, const STexBlend& texBlend)
	{
		// ���ݺϷ����ж�
		if( _x> m_iTableWidth)  
			return false;

		if( _y > m_iTableHeight)  
			return false;

		m_blendTable[ TableIndex(_x, _y)] = texBlend;

		// ���Ҹı������
		WORD reminderX = _x % m_iSectorUnits;
		WORD reminderY = _y % m_iSectorUnits;
		WORD index = ( _y >> m_tileShift) * m_numTileX + ( _x >> m_tileShift);

		// �������еĵڼ���+1 ����+1
		WORD relaX = reminderX;	
		WORD relaY = reminderY;	

		// �ȸı����½��Ǹ�����
		if ( index >=0 && index < m_numTileY * m_numTileX)
		{
			//m_pSectorArray[index].UpdateHeightNormalAndTexBlend( relaX, relaY, NULL, NULL, &texBlend);
		}

		if ( !reminderX)
		{
			relaX = m_iSectorUnits;
			relaY = reminderY;
			WORD indexX = index - 1;

			if ( indexX >=0 && indexX < m_numTileY * m_numTileX)
			{
				//m_pSectorArray[indexX].UpdateHeightNormalAndTexBlend( relaX, relaY, NULL, NULL, &texBlend);
			}
		}

		if ( !reminderY)
		{
			relaX = reminderX;
			relaY = m_iSectorUnits;
			WORD indexY = index - m_numTileX;

			if ( indexY >=0 && indexY < m_numTileY * m_numTileX)
			{
				//m_pSectorArray[indexY].UpdateHeightNormalAndTexBlend( relaX, relaY, NULL, NULL, &texBlend);
			}
		}

		if ( !reminderX && !reminderY)
		{
			relaX = m_iSectorUnits;
			relaY = m_iSectorUnits;
			WORD indexXY = index - 1 - m_numTileX;

			if ( indexXY >=0 && indexXY < m_numTileY * m_numTileX)
			{
				//m_pSectorArray[indexXY].UpdateHeightNormalAndTexBlend( relaX, relaY, NULL, NULL, &texBlend);
			}
		}

		return true;
	}

	// ָ����߶�
	float Terrain::Height( float x, float y)
	{
		float fMapX = x * (m_iTableWidth - 1);
		float fMapY = y * (m_iTableHeight - 1);

		int iMapX0 = RealToInt32_Chop( fMapX);
		int iMapY0 = RealToInt32_Chop( fMapY);

		fMapX -= iMapX0;
		fMapY -= iMapY0;

		iMapX0 = Clamp( iMapX0, 0, m_iTableWidth - 1);
		iMapY0 = Clamp( iMapY0, 0, m_iTableHeight - 1);

		int iMapX1 = Clamp( iMapX0+1, 0, m_iTableWidth-1);
		int iMapY1 = Clamp( iMapY0+1, 0, m_iTableHeight-1);

		// Read 4 map values
		float h0 = GetHeight( (WORD)iMapX0, (WORD)iMapY0);
		float h1 = GetHeight( (WORD)iMapX1, (WORD)iMapY0);
		float h2 = GetHeight( (WORD)iMapX0, (WORD)iMapY1);
		float h3 = GetHeight( (WORD)iMapX1, (WORD)iMapY1);

		float avgLo = (h1*fMapX) + (h0*(1.0f-fMapX));
		float avgHi = (h3*fMapX) + (h2*(1.0f-fMapX));

		return (avgHi*fMapY) + (avgLo*(1.0f-fMapY));;
	}

	// ����㷨��
	void  Terrain::Normal(Vector3& outNoraml, float x, float y)
	{
		float fMapX = x * (m_iTableWidth-1);
		float fMapY = y * (m_iTableHeight-1);

		int iMapX0 = RealToInt32_Chop(fMapX);
		int iMapY0 =RealToInt32_Chop(fMapY);

		fMapX -= iMapX0;
		fMapY -= iMapY0;

		iMapX0 = Clamp(iMapX0, 0, m_iTableWidth-1);
		iMapY0 = Clamp(iMapY0, 0, m_iTableHeight-1);

		int iMapX1 = Clamp(iMapX0+1, 0, m_iTableWidth-1);
		int iMapY1 = Clamp(iMapY0+1, 0, m_iTableHeight-1);

		// read 4 map values
		const Vector3& h0 = m_heightField.GetNormalAt(iMapX0, iMapY0);
		const Vector3& h1 = m_heightField.GetNormalAt(iMapX1, iMapY0);
		const Vector3& h2 = m_heightField.GetNormalAt(iMapX0, iMapY1);
		const Vector3& h3 = m_heightField.GetNormalAt(iMapX1, iMapY1);

		Vector3 avgLo = (h1*fMapX) + (h0*(1.0f-fMapX));
		Vector3 avgHi = (h3*fMapX) + (h2*(1.0f-fMapX));

		outNoraml = (avgHi*fMapY) + (avgLo*(1.0f-fMapY));
		outNoraml.Normalize();
	}

	// ���¸߶���ʾ
	void Terrain::UpdateHeightAndNormal( WORD _x,WORD _y, float* height)
	{
		// ���ݺϷ����ж�
		if( _x > m_iTableWidth)   return;
		if( _y > m_iTableHeight)  return;

		// ���¸߶�
		if ( height)
			m_heightField.SetHeightAt( _x, _y, *height);

		// ���Ҹı������
		WORD reminderX = _x % m_iSectorUnits;
		WORD reminderY = _y % m_iSectorUnits;
		WORD index = ( _y >> m_tileShift) * m_numTileX + ( _x >> m_tileShift);

		// �ȸı����½��Ǹ�����
		int tileIdxs[4]  = { index, !reminderX ? index - 1 : -1, !reminderY ? index - m_numTileX : -1, (!reminderX && !reminderY) ? index - 1 - m_numTileX : -1};
		for( int i=0; i<4; i++)
		{
			if( tileIdxs[i] >=0 && tileIdxs[i] < (int)(m_numTileY * m_numTileX))
				m_tileList[tileIdxs[i]]->SetDirty( true);
		}
	}

	// �ύ��ȾԪ��
	void Terrain::SubmitRenderElements( RenderElementMgr& renderElementMgr)
	{
		foreach_( s_ptr<TerrainTile>& tile, m_tileList)
		{
			tile->SubmitRenderElements( renderElementMgr);
		}
	}

	// ��ӵ�������Ϣ
	void Terrain::OnAddToScene( Scene* scene)
	{
		RenderEntity::OnAddToScene( scene);

		foreach_( s_ptr<TerrainTile>& tile, m_tileList)
		{
			tile->AutoBindParam();
		}
	}

	// ������ʾ
	void Terrain::UpdateDisplay()
	{
		foreach_( TerrainTilePtr tile, m_tileList)
		{
			if( tile->m_dirtyFlag)
				AllocateTile( tile->m_xIndex, tile->m_yIndex);
		}
	}
}
