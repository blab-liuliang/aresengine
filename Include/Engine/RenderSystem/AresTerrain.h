#pragma once

#include <set>
#include <string>
#include "AresTerrainTile.h"
#include <Physics/Shapes.h>
#include <Core/Graphics/AresRenderMaterial.h>
#include <Core/Graphics/AresGraphicsBuffer.h>

#define TERRAIN_TESSELLATION

using namespace std;

namespace Ares
{
	class Terrain : public RenderEntity
	{
	public:
		friend class TerrainTile;

		typedef DWORD STexBlend;
		typedef vector<TerrainTilePtr> TileList;

	public:
		Terrain();
		~Terrain();

		// ���δ�С,�����С
		bool Build( int width, int height, BYTE shift=6);

	public:
		// ��ȡ�߶�ͼ
		const HeightField& GetHeightField() { return m_heightField; }

		// ��ȡ��Ⱦ���� 
		const RenderMaterialPtr& GetDefaultMaterial() { return m_material; }

		// ��ȡ��Χ��
		Rect3& GetWorldExtens() { return m_worldExtends; }

		// ������Ⱦ����
		void  SetMaterial( const RenderMaterialPtr& material) { m_material = material; }			

		// ����µ��θ߶ȵ��޸Ķ���
		bool SetHeight( WORD _x, WORD _y, float height);

		// ���������϶�
		bool SetTexBlend( WORD _x, WORD _y,const STexBlend& texBlend);

		// ��ȡ����
		UINT32 TableIndex(WORD mapX, WORD mapY);

		// ��ȡ��������
		int GetTileNumX() { return m_numTileX; }

		// ��ȡ��������
		int GetTileNumY() { return m_numTileY; }

		// ��ȡ��
		TileList& GetTileList() { return m_tileList; }

		// ���õ����Ƿ�ɼ�
		void SetVisible( bool visible) { m_visible = visible; }

		// ����shift
		WORD  GetTileShift() { return m_tileShift; }

		// �����Ƿ�ɱ༭(���ɱ༭�����Ⱦ�ٶ�)
		void SetEditable( bool editEnable){}

		// ��ȡָ����߶�
		virtual float Height(float x, float y);

		// ��ȡָ����߶�
		virtual float GetHeight( WORD _x, WORD _y, float defaultValue=0.f);

		// ��ȡָ���������϶�
		DWORD GetTexBlend( WORD _x, WORD _y);

		// ��ȡָ���㷨��
		virtual void  Normal(Vector3& outNoraml, float x, float y);

		// ��������
		TerrainTilePtr AllocateTile( size_t xIdx, size_t yIdx);

		// ���¸߶���ʾ
		void  UpdateHeightAndNormal( WORD _x,WORD _y, float* height=NULL);

		// ��������
		void DestroyTile( const s_ptr<TerrainTile>& tile);

		// ������ʾ
		void UpdateDisplay();

		// �ύ��ȾԪ��
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr);

		// ��ӵ�������Ϣ
		virtual void OnAddToScene( Scene* scene);

	protected:
		// ��������Buffer
		bool BuildIndexBuffer();

		// ͨ���߶�ͼ��������
		bool  BuildHeightAndNormalTables();

	public:
		// ���л�
		BOOST_SERIALIZATION_SPLIT_MEMBER()
		template<typename Archive> void save( Archive& ar, const unsigned int version) const
		{
			ar & m_version;
			ar & m_visible;
			ar & m_worldExtends;
			ar & m_vWorldSize;
			ar & m_vMapScale;
			ar & m_numTileX;
			ar & m_numTileY;
			ar & m_tileSize;
			ar & m_tileShift;
			ar & m_iSectorUnits;
			ar & m_tileVerts;
			ar & m_iTableWidth;
			ar & m_iTableHeight;
			ar & m_blendTable;
			ar & m_heightField;
		}
		template<typename Archive> void load( Archive& ar, const unsigned int version)
		{
			ar & m_version;
			ar & m_visible;
			ar & m_worldExtends;
			ar & m_vWorldSize;
			ar & m_vMapScale;
			ar & m_numTileX;
			ar & m_numTileY;
			ar & m_tileSize;
			ar & m_tileShift;
			ar & m_iSectorUnits;
			ar & m_tileVerts;
			ar & m_iTableWidth;
			ar & m_iTableHeight;
			ar & m_blendTable;
			ar & m_heightField;

			SetLocalBounds( m_worldExtends);

			// ��������
			BuildIndexBuffer();

			// ������������
			m_tileList.resize( m_numTileX * m_numTileY, s_ptr<TerrainTile>());
			for ( int x=0; x<GetTileNumX(); x++)
			{
				for ( int y=0; y<GetTileNumY(); y++)
					AllocateTile( x, y);
			}
		}

	protected:
		int						m_version;					// ��ǰ�汾
		bool					m_visible;					// �����Ƿ�ɼ�
		Rect3					m_worldExtends;				// ���ΰ�Χ��
		Vector3					m_vWorldSize;				// �����С
		Vector3					m_vMapScale;				// ��ͼ����
		size_t					m_numTileX;				
		size_t					m_numTileY;					// ��������

		Vector2					m_tileSize;					// ÿ�����С

		WORD					m_tileShift;				// 
		WORD					m_iSectorUnits;				// ��������С������
		WORD					m_tileVerts;				// ���鶥����

		WORD					m_iTableWidth;				// ����
		WORD					m_iTableHeight;				// ����

		GraphicBufferPtr		m_indexBuffer;				// ��������()
		RenderMaterialPtr		m_material;					// ����

		vector<STexBlend>		m_blendTable;				// ����������
		HeightField				m_heightField;				// �߶�ͼ
		TileList				m_tileList;					// ���鼯��
	};
	typedef s_ptr<Terrain> TerrainPtr;
}
