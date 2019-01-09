#include "MOLogic.h"
#include "MOLightmapUVBuild.h"
#include "MOMainWindow.h"
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <Engine/RenderSystem/AresModelIDCard.h>

using namespace boost::filesystem;
using namespace QT_UI;

namespace Ares
{
	LightmapUVBuild*	g_lightmapUVBuild = new LightmapUVBuild;

	// �ص�����
	HRESULT CALLBACK UVAtlasCallback( FLOAT fPercentDone, LPVOID lpUserContext)
	{
		boost::format tFormat("%.2f%%");
		tFormat % (fPercentDone*100);

		//AMainWindow->SetLog( tFormat.str().c_str());

		return S_OK;
	}

	// ���캯��
	LightmapUVBuild::LightmapUVBuild()
		: m_device( NULL)
	{
		// ����dx9 device
		CreateNullRefDevice();
	}

	// ָ���ļ�
	void LightmapUVBuild::Open( const char* filePath) 
	{ 
		path tmpPath = path(filePath).replace_extension(".mod_tmp");
		path curPath = path(filePath).replace_extension(".mod");

		if( exists(tmpPath))
			m_filePath = tmpPath;
		else if( exists(curPath))
			m_filePath = curPath;

		Serialization::UnSerializeFromBinaryFile( filePath, m_meshs);
	}

	// ��ԭģ������
	void LightmapUVBuild::Restore()
	{
		try
		{
			path pathFrom = path(MOLogic_ModelEdit->GetResPath()).replace_extension(".mod_tmp");
			path pathTo   = path(MOLogic_ModelEdit->GetResPath()).replace_extension(".mod");

			if( exists( pathFrom))
			{
				copy_file( pathFrom, pathTo);
			}
			else
			{
				// ԭ�����Ѱ���
				MOUI_UVBuild->Warning( "ԭ���ݶ�ʧ,��ԭʧ��!");
			}
		}
		catch (...)
		{
			int a = 10;
		}
	}

	// ִ������( *mod)
	void LightmapUVBuild::Build( const BuildSettings& config)
	{
		m_settings = config;

		// ��
		Open( MOLogic_ModelEdit->GetResPath());

		// ִ�б���
		BackupMod();

		if( IsOrigMod())
		{
			BuildMod();
		}
		else
		{
			// ԭ�����Ѱ���
			MOUI_UVBuild->Warning( "ԭ���ݶ�ʧ,�޷��������ɹ���ͼUV!");
		}
	}

	// ��������
	struct M1Vertex
	{
		Vector3	m_pos;
		Vector2 m_uv;		// diffuse uv
	};

	// ����Mod
	void LightmapUVBuild::BuildMod()
	{
		for( size_t i=0; i<m_meshs.size(); i++)
		{
			const Mesh::IDCard& meshIDCard = *m_meshs[i];
			if( !meshIDCard.m_uvsLightmap.size())
			{
				// 1.����Origin mesh
				ID3DXMesh*		origMesh	 = NULL;
				ID3DXMesh*		resultMesh	 = NULL;
				if( SUCCEEDED( D3DXCreateMeshFVF( meshIDCard.m_faces.size(), meshIDCard.m_positions.size(), D3DXMESH_32BIT, D3DFVF_XYZ | D3DFVF_TEX1, m_device, &origMesh)))
				{
					IDirect3DIndexBuffer9*  indexBuffer;
					IDirect3DVertexBuffer9* vertexBuffer;

					// ��ֵ����
					origMesh->GetIndexBuffer( &indexBuffer);
					origMesh->GetVertexBuffer( &vertexBuffer);

					// ��ֵIndexBuffer
					Int3* faces = NULL;
					indexBuffer->Lock( 0, 0, (void**)&faces, 0);
					std::memcpy( faces, meshIDCard.m_faces.data(), sizeof( Int3)*meshIDCard.m_faces.size());
					indexBuffer->Unlock();

					// ��ֵ����Buffer
					M1Vertex* vertexs = NULL;
					vertexBuffer->Lock( 0, sizeof(M1Vertex)*meshIDCard.m_positions.size(), (void**)&vertexs, 0);
					for ( size_t vIdx=0; vIdx<meshIDCard.m_positions.size(); vIdx++)
					{
						vertexs[vIdx].m_pos = meshIDCard.m_positions[vIdx];
						vertexs[vIdx].m_uv	= meshIDCard.m_uvsDiffuse[vIdx];
					}
					vertexBuffer->Unlock();

					//HRESULT xx = D3DXSaveMeshToXA( "D:\\test.x", origMesh, NULL, NULL, NULL, 0, D3DXF_FILEFORMAT_TEXT);
				}
				else
				{
					return;
				}

				float	stretchOut;
				UINT	numChartOut = 0;
				DWORD*	pAdjacency  = NULL;
				DWORD*	pFalseEdges = NULL;
				FLOAT*	pIMTArray	= NULL;
				LPD3DXBUFFER pFacePartitioning = NULL;
				LPD3DXBUFFER pVertexRemapArray = NULL;
				if( SUCCEEDED(D3DXUVAtlasCreate( origMesh, m_settings.m_maxCharts, m_settings.m_maxStretch, m_settings.m_width, m_settings.m_height, m_settings.m_gutter, m_settings.m_outputTextureIndex,pAdjacency, pFalseEdges, pIMTArray, UVAtlasCallback, 0.2f, NULL, m_settings.m_qualityFlag, &resultMesh, &pFacePartitioning, &pVertexRemapArray, &stretchOut, &numChartOut)))
				{
					vector<Int3>		tIndices;
					vector<Vector2>		tUvs;
					Rect2				tUvRect;
					vector<DWORD>		tFacePartitioning;
					vector<DWORD>		tVertexRemapArray;

					// ��֯���
					OrganizationResult( tIndices, tUvs, tUvRect, tFacePartitioning, tVertexRemapArray, resultMesh, pFacePartitioning, pVertexRemapArray);

					// �޸�M1Mesh
					ModifyMesh( tIndices, tUvs, tUvRect, tFacePartitioning, tVertexRemapArray, *m_meshs[i]);

					// ��ʾ���
					ShowResult( tIndices, tUvs);
					//D3DXSaveMeshToXA( "D:\\result.x", resultMesh, NULL, NULL, NULL, 0, D3DXF_FILEFORMAT_TEXT);
				}

				SAFE_RELEASE( resultMesh);
			}
			else
			{
				// ����(ԭ�����Ѷ�ʧ)

			}
		}
	}

	// ��ʾ���
	void LightmapUVBuild::ShowResult( const vector<Int3>& rIndices, const vector<Vector2>& rUvs)
	{
		// ��ʾ���
		vector<int> lineList;
		for ( size_t ll=0; ll<rIndices.size(); ll++)
		{
			lineList.push_back( rIndices[ll][0]);
			lineList.push_back( rIndices[ll][1]);
			lineList.push_back( rIndices[ll][1]);
			lineList.push_back( rIndices[ll][2]);
			lineList.push_back( rIndices[ll][2]);
			lineList.push_back( rIndices[ll][0]);
		}

		MOLogic_LightmapUVRender->Set( RenderLayout::TT_LineList, rUvs.data(), sizeof(Vector2)*rUvs.size(), lineList.data(), sizeof(int)*lineList.size(), EF_R32UI);
	}

	// ��ȡ���
	void LightmapUVBuild::OrganizationResult( vector<Int3>& rIndices, vector<Vector2>& rUvs, Rect2& rUvRect, vector<DWORD>& rFacePartitioning, vector<DWORD>& rVertexRemapArray, ID3DXMesh* inMesh, LPD3DXBUFFER pFacePartitioning, LPD3DXBUFFER pVertexRemapArray)
	{
		rIndices.clear();
		rUvs.clear();
		rUvRect.Reset();

		IDirect3DIndexBuffer9*  indexBuffer;
		IDirect3DVertexBuffer9* vertexBuffer;

		// ��ֵ����
		inMesh->GetIndexBuffer( &indexBuffer);
		inMesh->GetVertexBuffer( &vertexBuffer);

		// ��ֵIndexBuffer
		Int3* faces = NULL;
		indexBuffer->Lock( 0, 0, (void**)&faces, 0);
		for ( size_t vIdx=0; vIdx<inMesh->GetNumFaces(); vIdx++)
			rIndices.push_back( faces[vIdx]);
		indexBuffer->Unlock();

		// ��ֵ����Buffer
		M1Vertex* vertexs = NULL;
		vertexBuffer->Lock( 0, 0, (void**)&vertexs, 0);
		for ( size_t vIdx=0; vIdx<inMesh->GetNumVertices(); vIdx++)
		{
			rUvs.push_back( vertexs[vIdx].m_uv);

			rUvRect.UnionPoint( vertexs[vIdx].m_uv[0], vertexs[vIdx].m_uv[1]);
		}
		vertexBuffer->Unlock();

		// FacePartitioning and VertexRemapArray
		rFacePartitioning.clear();
		rVertexRemapArray.clear();

		int numFP = pFacePartitioning->GetBufferSize() / sizeof(DWORD);
		int numRA = pVertexRemapArray->GetBufferSize() / sizeof(DWORD);
		DWORD* tFPPointer = (DWORD*)pFacePartitioning->GetBufferPointer();
		DWORD* tVRPointer = (DWORD*)pVertexRemapArray->GetBufferPointer();
		for ( int x=0; x<numFP; x++)	
			rFacePartitioning.push_back( tFPPointer[x]);

		for ( int x=0; x<numRA; x++)
			rVertexRemapArray.push_back( tVRPointer[x]);
	}

	// �޸�Mesh
	void LightmapUVBuild::ModifyMesh( vector<Int3>& rIndices, vector<Vector2>& rUvs, Rect2& rUvRect, vector<DWORD>& rFacePartitioning, vector<DWORD>& rVertexRemapArray, Mesh::IDCard& mesh)
	{
		// ����,�¸��ƵĶ��㱻���õ�ԭ����ĺ�
		for ( size_t i=0; i<mesh.m_positions.size(); i++)
		{
			A_ASSERT( i==rVertexRemapArray[i]);
		}

		// ����m1����
		// 1.���ȸ�����������
		//mesh.m_faces = rIndices;
/*
		// ����ԭUV����
		SM1TexCoord* newDiffuseUVs = new SM1TexCoord[rUvs.size()];
		for ( size_t i=0; i<rVertexRemapArray.size(); i++)
			newDiffuseUVs[i] = mesh.m_pTexCoords[ rVertexRemapArray[i]];	
		SAFE_DELETE_ARRAY( mesh.m_pTexCoords);
		mesh.m_pTexCoords = newDiffuseUVs;
		mesh.m_Header.m_iNumUVs	   = rUvs.size();
		mesh.m_Header.m_iUVOffset  = sizeof( SM1TexCoord) *  rUvs.size();
		mesh.m_texcoordsDiffuse = 

		// ���lightmapuv����
		SAFE_DELETE_ARRAY( mesh.m_lightmapTexCoords);
		mesh.m_Header.m_bLightmapUV		  = true;
		mesh.m_Header.m_iLightmapUVOffset = sizeof( SM1TexCoord) *  rUvs.size();
		mesh.m_Header.m_lightmapAR		  = rUvRect.GetXSize() / rUvRect.GetYSize();
		mesh.m_lightmapTexCoords		  = new SM1TexCoord[rUvs.size()];
		std::memcpy( mesh.m_lightmapTexCoords, rUvs.data(), mesh.m_Header.m_iLightmapUVOffset);


		// ����VertexAppend
		int	 newNumVAppend		= rUvs.size()-mesh.m_Header.m_iNumVerts;
		if( newNumVAppend > 0)
		{
			int* newVertexIdxAppend = new int[rUvs.size()-mesh.m_Header.m_iNumVerts];
			for ( int i=0; i<newNumVAppend; i++)
				newVertexIdxAppend[i] = VertexMapping( rVertexRemapArray[mesh.m_Header.m_iNumVerts+i], mesh);

			SAFE_DELETE_ARRAY( mesh.m_pVertexIdxAppend);
			mesh.m_pVertexIdxAppend		   = newVertexIdxAppend;
			mesh.m_Header.m_iNumVAppend    = newNumVAppend;
			mesh.m_Header.m_iVAppendOffset = sizeof(int) * newNumVAppend;
		}*/
	}

	// ��ȡUV��Ӧ
	int LightmapUVBuild::VertexMapping( int idx, Mesh::IDCard& mesh)
	{/*
		if( idx < mesh.m_Header.m_iNumVerts)
			return idx;

		return mesh.m_pVertexIdxAppend[ idx - mesh.m_Header.m_iNumVerts];*/
		return 1;
	}

	// �����ļ�
	void LightmapUVBuild::Save( const char* filePath)
	{/*
		if( !m_meshsIDCard)
			return;

		string storePath = filePath ? filePath : path(m_filePath).replace_extension(".mod").string();

		FILE* fileModel = fopen( storePath.c_str(), "wb");
		if( fileModel)
		{
			m_meshsIDCard->Save( fileModel);

			fflush( fileModel);
			fclose( fileModel);
		}
		*/
	}

	// ����D3D9Device
	void LightmapUVBuild::CreateNullRefDevice()
	{
		if( m_device)
			return;

		IDirect3D9* pD3D = Direct3DCreate9( D3D_SDK_VERSION);
		if( !pD3D )
			return;

		D3DDISPLAYMODE Mode;
		pD3D->GetAdapterDisplayMode( 0, &Mode );

		D3DPRESENT_PARAMETERS pp;
		ZeroMemory( &pp, sizeof( D3DPRESENT_PARAMETERS ) );
		pp.BackBufferWidth  = 1;
		pp.BackBufferHeight = 1;
		pp.BackBufferFormat = Mode.Format;
		pp.BackBufferCount  = 1;
		pp.SwapEffect		= D3DSWAPEFFECT_COPY;
		pp.Windowed			= TRUE;

		HRESULT hr = pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, GetConsoleWindow(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &m_device);

		//A_ASSERT( hr == S_OK);
		//A_ASSERT( m_device);

		SAFE_RELEASE( pD3D );
	}

	// �����ļ�
	void LightmapUVBuild::BackupMod()
	{
		if( m_filePath.extension() != ".mod_tmp")
		{
			bool haveLightmapUV = false;
			for( size_t i=0; i<m_meshs.size(); i++)
			{
				if( m_meshs[i]->m_uvsLightmap.size())
					haveLightmapUV = true;
			}

			if( !haveLightmapUV)
			{
				// ���ݳɹ�
				path pathTo( m_filePath); pathTo.replace_extension( ".mod_tmp");

				copy_file( m_filePath, pathTo);
			}
		}
	}

	// �ж��Ƿ���Դ����
	bool LightmapUVBuild::IsOrigMod()
	{/*
		if( m_meshsIDCard)
		{
			bool haveLightmapUV = false;
			for( size_t i=0; i<m_meshsIDCard->m_header.m_iNumMeshes; i++)
			{
				if( m_meshsIDCard->m_pMeshes[i].m_Header.m_bLightmapUV)
					haveLightmapUV = true;
			}

			return !haveLightmapUV;
		}
		*/
		return false;
	}
}