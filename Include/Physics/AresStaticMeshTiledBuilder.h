#pragma once

// ע����ͷ�ļ��ɲ����ⷢ��

#include "AresRecast.h"
#include "AresStaticNavMesh.h"
#include "Physics/Shapes.h"

namespace Ares
{
	//---------------------------------
	// ����������(�����鴦��) 2011-03-24 ����
	//---------------------------------
	struct SRcChunkyTriMesh;
	class  CStaticMeshTiledBuilder
	{
	public:
		// ������
		struct SBuildParam
		{
			Vector3*	  m_pVerts;			// ����
			int           m_iVerts;			// ������
			int*		  m_pTris;			// ������(��������)
			//WaterZoneMgr* m_waterZone;		// ˮ����
			//const float*  m_pNormals;		// �淨��
			int           m_iTris;			// ����������
			VolumeList	  m_convexVolumes;	// ͹������
			Vector3		  m_vMin;
			Vector3		  m_vMax;			// �����Χ��
			float         m_fCellSize;		// ���Ӵ�С(���絥λ)
			float         m_fCellHeight;	// ���Ӹ߶�
			float         m_fAgentMaxSlope;	// �����б��
			float         m_fAgentHeight;	// ��ͨ��߶�
			float         m_fAgentClimb;	// ��ͨ���߶�
			float		  m_fAgentRadius;	// �뾶

			float         m_fRegionMinSize;
			float		  m_fRegionMergeSize;

			float		  m_fEdgeMaxLen;
			float		  m_fEdgeMaxError;
			int  		  m_iVertesPerPoly;
			int			  m_iTileSize;		// width and height of a tile

			float		  m_fDetailSampleDist;
			float		  m_fDetailSampleMaxError;

			// ���캯��
			SBuildParam()
			{
				m_pVerts   = 0;
				m_pTris    = 0;
				//m_waterZone= NULL;
				//m_pNormals = 0;
				m_iVerts   = 0;
				m_iTris    = 0;

				m_fCellSize   = 0.2f;
				m_fCellHeight = 0.2f;

				m_fAgentHeight	 = 2.8f;
				m_fAgentRadius	 = 0.45f;
				m_fAgentClimb	 = 0.6f;
				m_fAgentMaxSlope = 45.f;

				m_fRegionMinSize   = 50.f;
				m_fRegionMergeSize = 20.f;

				m_fEdgeMaxLen   = 24.f;
				m_fEdgeMaxError = 1.3f;
				m_iVertesPerPoly= 6;
				m_iTileSize     = 100;

				m_fDetailSampleDist   	= 6.f;
				m_fDetailSampleMaxError = 1.f;
			}

			// ����
			~SBuildParam()
			{
				//SAFE_DELETE( m_waterZone);
				SAFE_DELETE_ARRAY( m_pVerts);
				SAFE_DELETE_ARRAY( m_pTris);
			}
		};

		// tile( Ƭ, ����)
		struct STile
		{
			SRcHeightField*			m_pSolid;				// height field	
			SRcCompactHeightField*	m_pCHF;					// compact height field
			SRcContourSet*          m_pCSet;				// contour set
			RcPolyMesh*				m_pMesh;				// �����mesh
			SRcPolyMeshDetail*		m_pDMesh;				// ��ϸ�����mesh

			// ���캯��
			STile()
			{
				m_pSolid = NULL;
				m_pCHF   = NULL;
				m_pCSet  = NULL;
				m_pMesh  = NULL;
				m_pDMesh = NULL;
			}

			// ��������
			~STile()
			{
				Reset();
			}

			// ����
			void Reset()
			{
				SAFE_DELETE( m_pSolid);
				SAFE_DELETE( m_pCHF);
				SAFE_DELETE( m_pCSet);
				SAFE_DELETE( m_pMesh);
				SAFE_DELETE( m_pDMesh);
			}	
		};

		CStaticMeshTiledBuilder();
		~CStaticMeshTiledBuilder();

	public:
		// ����
		bool HandleBuild( CStaticNavMesh& navMesh, SBuildParam& params, LogSystem* logSystem=NULL);

		// ����·���(������·����ѯ)
		static void ConstructRoadIDs( vector<UINT>& oRoadIds, const CStaticNavMesh& navMesh, const NavMeshFilter& filter);

		// ���·��
		static void MarkRoadId( vector<UINT>& oRoadIds, const NavMeshFilter& filter, const CStaticNavMesh& navMesh, set<PolyRef>& polyIDs, int roadNum);

	private:
		// ����
		void  Reset();

		// ��ʼ��Config
		bool InitCfg( const SBuildParam& params);

		// ��ʼ��ChunkMesh
		bool InitChunkMesh( const SBuildParam& params);

		// ������������Tile
		bool BuildTile( STile& tile, int xIdx, int yIdx, const SBuildParam& params);

		// ������
		void TileBatching( STile* tile, vector<STile*>& tiles, vector<RcPolyMesh*>& polyMeshs, vector<SRcPolyMeshDetail*>& polyMeshDetails,  bool isEnd);

		// ������Mesh
		bool MergeTilesMesh( RcPolyMesh*& outMesh, SRcPolyMeshDetail*& outMeshD, vector<STile*>& tiles);

		// ����NavMesh
		bool ConstructStaticNavMesh( CStaticNavMesh& navMesh);

		// ��Ƕ��˵�
		void MarkApexVertex( CStaticNavMesh& navMesh);

		// �Ƿ�Ϊ���˵�
		bool IsApexPoint( CStaticNavMesh& navMesh, PolyRef polyID, UINT pointIdx);

	public:
		SRcConfig				m_rcConfig;				// ����
		SRcChunkyTriMesh*       m_pChunkMesh;			// chunk Mesh(����tile����)
		RcPolyMesh*			m_pMesh;				// �����mesh
		SRcPolyMeshDetail*		m_pDMesh;				// ��ϸ�����mesh
		LogSystem*				m_logSystem;			// ��־ϵͳ
	};
}