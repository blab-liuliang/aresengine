#pragma once

#include <boost/function.hpp>
#include <Core/AresCore.h>
#include <Physics/QuadTree.hpp>
#include <Physics/Shapes.h>
#include "Physics/WaterZoneMgr.h"
#include "AresRecast.h"
	
using namespace std;

namespace Ares
{
	// NavMapFilter 2013-5-21 ����
	struct NavMeshFilter
	{	
		enum Constant
		{
			Max_AreaType = 32,
		};

	public:
		NavMeshFilter();

		// ��������
		void SetCost( BYTE areaType, float cost);

		// ��ȡ����
		float GetCost( BYTE areaType);

		// ��ȡ���
		UINT GetFlags() const { return m_includeFlags; }

		// ���������Ƿ��ͨ��
		void SetAreaPathable( BYTE areaType, bool value);

		// �ж������Ƿ��ͨ��
		bool IsAreaPathable( BYTE areaType) const;

	private:
		float			m_areaCost[Max_AreaType];	// cost per area type, (Used by default implementation)
		UINT			m_includeFlags;				// flags for path that can be visited
	};

	typedef UINT PolyRef;

	#define ARES_STATIC_VERTS_PER_POLYGON 6
	//--------------------------------------------
	// ��̬��������, 2011-02-18 ����
	// ��Ҫ�ο�Recast by Mikko Mononen
	// http://code.google.com/p/recastnavigation/
	//--------------------------------------------
	class NavMeshDetour;
	class CStaticNavMesh
	{
	public:
		// ·����
		struct SPathNode
		{
			Vector3     m_vPos;	// ��ǰ��
		};
		typedef vector<SPathNode> PathResult; 

		// �����ͨ����ʽ
		enum EPolyFlag
		{
			EM_WALK = 0,		// ����
			EM_CLIMB,			// ��
		};

		// ������
		enum VertexFlag
		{
			VF_APEX = 1,		// �˵�
		};

		// structure holding the navigation polygon data
		struct SStaticPoly
		{
			UINT			m_indices [ARES_STATIC_VERTS_PER_POLYGON];		// Indices to vertices of the poly( ��������)
			PolyRef			m_neighbor[ARES_STATIC_VERTS_PER_POLYGON];		// Refs to neighbors of the poly( ��Ӷ����)
			unsigned char	m_iNumVerts;									// ʹ�õĶ�����
			EPolyFlag	    m_flag;											// Flags (not used)

			// ���캯��
			SStaticPoly()
			{
				m_iNumVerts = 0;
				m_flag      = EM_WALK;
			}
		};

		struct SStaticPolyDetail
		{
			unsigned int   m_iVertBase;		// Offset to detail vertex array
			unsigned int   m_iTriBase;		// Offset to triangle array
			unsigned short m_iNumVerts;		// Number of vertices in the detail mesh
			unsigned short m_iNumTris;		// Number of triangles
		};

		// ��������
		struct SStaticNavMeshHeader
		{
			unsigned int		m_iVersion;				// �汾
			unsigned int		m_iNumPolys;			// �������
			unsigned int		m_iNumVerts;			// ������
			UINT				m_iNumApexVerts;		// ��Ե������	
			int					m_iNVP;					// ÿ������ε���󶥵���
			float				m_fCellSize;			// cell size
			Vector3				m_vMin;				
			Vector3				m_vMax;					// ��Χ��

			int					m_iDNumVerts;			// ��������
			int					m_iDNumTris;			// Detail num triangles

			UINT*				m_pPolyRoadIDs;			// ·���
			unsigned char*		m_areaIDs;				// ��������ID
			SStaticPoly*		m_pPolys;				// ����μ�
			Vector3*			m_pVerts;				// ��������
			BYTE*				m_pVertFlags;			// ����
			SStaticPolyDetail*	m_pDetailPolys;			// ���ǻ�
			Vector3*			m_pDetailVerts;			// ����

			unsigned char*				m_pDetailTris;		// ����������
			quad_tree_member<PolyRef>*	m_pQuadTreeMember;	// �Ĳ�����Ա
		};	

	public:
		CStaticNavMesh();
		~CStaticNavMesh();

		// ����
		bool Load( const char* fileName);

		// ����·�� 
		size_t FindPath( vector<SPathNode>&	pathResult, NavMeshFilter& filter, const Vector3& startPos, const Vector3& endPos,Vector3 startExtendBox, Vector3 endExtendBox, float inwardOffset=0.1f, float walkRagne=-1.f);

		// ���ҵ㵽ͨ·����ĵ�
		bool CloestPointToRold( int roldIDs, const Vector3& center, Vector3& closetPoint) { return false; }

		// �ж�ĳ���Ƿ���Ѱ·��Χ��
		bool IsPtOnNavZone( const Vector3& pos, const Vector3& extendBox);

		// ���ö����Ϸ�������( 0-2)
		void SetUpDirIdx( int idx=2);

		// ����
		void Reset();

		// �༭��ʹ�á�
	public:
		// ���Ҿ���·��
		int FindStraightPath( const Vector3& vStart, const Vector3& vEnd, const vector<PolyRef>& path, vector<SPathNode>& straightPath, float inwardOffset=0.1f);

		// Finds the nearest navigation polygon around the center location
		bool  FindNearstPoly( PolyRef& polyRef, const Vector3& center, const Vector3& extends);

		// �����������������Poly
		bool FindNearstTwoPoly( PolyRef& polyStart, PolyRef& polyEnd, const Vector3& startCenter, const Vector3& endCenter, const Vector3& extends, NavMeshFilter& filter);

		// ��ѯ�����
		int  QueryPolygons( const Vector3& center, const Vector3& extents, vector<PolyRef>& polys);

		// ���ҵ㵽���������ĵ�
		bool CloestPointToPoly( int ref, const Vector3& center, Vector3& closetPoint);

		// ��ĳ���ڴ�ֱ��������ĳ����εĽ���
		bool CloestPointToPolyInVerticalDirection( int ref, const Vector3& center, Vector3& closetPoint, float minDist, float maxDist);

	public:
		// ����
		bool Save( const char* fileName);

		// ����������ö����
		const SStaticPoly* GetPolyByRef( PolyRef iRef) const;

		// ��ȡ���������ID
		BYTE GetPolyAreaIDByRef( PolyRef ifRef) const;

		// �������������ϸ�����
		const SStaticPolyDetail* GetPolyDetailByRef( PolyRef iRef);

		// Returns pointer to specifed vertex
		const unsigned char* GetDetailTri( int i);

		// ��ȡ����
		const Vector3& GetVertex( UINT i) const;

		// ��ȡ����
		const Vector3& GetDetailVertex( int i);

		// ���
		bool IsApexVert( PolyRef idx) const;

	public:
		// ��ȡ��ͨ����Χ�ӵ�
		virtual void GetPassAbleNeighbor( const NavMeshFilter& filter, int* childID, int& numChild,int fatherID, float walkRange=-1.f, const Vector3& startPos=Vector3::Zero) const;

		// ����ID����������μ�h
		virtual float CalcH( NavMeshFilter& filter, const Vector3& vStart, const Vector3& vEnd, int idFrom, int idTo=-1);

		// ����ID����������μ�g
		virtual float CalcG( NavMeshFilter& filter, const Vector3& vStart, int idFrom, int idTo, int idFromFrom=-1);

	public:
		// ����������εĹ��õ�
		bool GetPortalPoints( int idFrom, int idTo, Vector3& vLeft, Vector3& vRight, float inwardOffset=0.1f) const;

		// ���������α�Ե�ߵ����ĵ�( returns edge middle point between two polygons)
		bool  GetEdgeMiddlePoint( int idFrom, int idTo, Vector3& vMiddle) const;

		// ��ȡpoly��Χ��
		void GetPolyBoundingBox( PolyRef iRef, quad_tree_rect& out);

		// ��ȡ·���
		const vector<UINT>& GetPolyRoadIdsByNavMeshFilter( const NavMeshFilter& filter);

		// �������
		void Clear();

		// ��ȡPoly���ĵ�
		//void GetCenterPoint( float* out, PolyRef iRef);

		// ���ݶ����ȡ������ھ�
		void GetPolyNeighborByPoint( PolyRef polyID, UINT pointIdx, PolyRef& leftPoly, PolyRef& rightPoly);

	public:
		// ��������·��
		void AdjustPathPointInward( PathResult& oPath, float inwardOffset);

		// �����ƽ����(�۽Ƿ���)
		bool CalcAngularBisector( Vector3& result, const Vector3& edge0, const Vector3& edge1);

		// �����ؽ�ƽ���߷���ƫ�Ƴ���
		float CalcAngularBisectorInwardOffset( const Vector3& edgeDir, const Vector3& abDir, float inwardOffset);

	public:
		NavMeshDetour*			m_detour;
		SStaticNavMeshHeader*	m_pHeader;		// ���������ݰ�
		BYTE*					m_pData;		// ����
		unsigned int			m_iDataSize;	// ���ݴ�С

		QuadTree<PolyRef>*		m_quadTree;		// �Ĳ���
		int						m_upDirIdx;		// �Ϸ�������

		map<UINT, vector<UINT>> m_polyRoldIDs;	// ·���
	};
}