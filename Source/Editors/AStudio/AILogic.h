#pragma once

#include <boost/filesystem.hpp>
#include <Physics/AresAStar.h>
#include <Physics/AresStaticNavMesh.h>
#include <Physics/AresStaticMeshTiledBuilder.h>
#include <Physics/PhysicsWorld.h>
#include <Engine/RenderSystem/AresVisualShape.h>
#include <Physics/WaterZoneMgr.h>
#include <Engine/AresRoot.h>
#include <Engine/FxSystem/AresFxDecal.h>

namespace Ares
{
	//---------------------------------------
	// AI �߼�(��ǰ��ΪѰ·) 2011-01-19 ����
	//---------------------------------------
	class  CAILogic
	{
	public:
		CAILogic();

		// ���������ļ�
		void OpenTri( const char* fileName);

		// ��Nav�ļ�
		void OpenNav( const char* fileName);

		// ������������
		void BuildNavMesh( CStaticMeshTiledBuilder::SBuildParam& buildParam);

		// �������򹹽���������
		void BuildNavMeshByRegion( CStaticMeshTiledBuilder::SBuildParam& buildParam);

		// һ��������������(������)
		static void BuildNavMesh( const char* triFile, const char* navFile, const char* waterZone, const char* roadZoneFile);

		// ·������
		void PathFind( const Vector3& startPos, const Vector3& endPos);

		// ���浼������
		void SaveNavMesh( const char* fileName);

		// ��갴�� �߼�����
		void FrameMove();

	public:
		// ����PolyMesh(������)
		void  DebugDraw();

		// ����·����
		void DebugDrawPathLine( const vector<CStaticNavMesh::SPathNode>& pathData);

		// DebugDrawPolyMesh
		void DebugDrawPolyMesh();

		// ������ϸmesh
		void DebugDrawPolyMeshDetail();

		// Show
		void NavDebugShow( bool bShowOrig, bool bSHowNavMesh, bool bShowDetailNavMesh, bool bShowPath);

		// ��ʾ����μ��ڽӶ����
		void ShowPolyAndNearPoly( const Vector3& pos);

		// ����Poly
		void DebugDrawPoly( PolyRef ref, VisualShape* pGeometry);

		// ���ƶ��˵�
		void DebugDrawApexPoint();

		// �������ģʽ
		void SwitchToWireFrameFillMode();

		// �������ģʽ
		void SwitchToNormalFillMode();

	private:
		// ���ÿ�ʼ��
		void SetStartPos();

		// ���ý�����
		void SetEndPos();

		// ����PhysicsLogic CollMap
		void SetPhysicsCollmap();

		// ��ȡ����ѡ���ߵ��������ļ������
		bool GetPickPoint( SegmentDetectResult& detectResult);

	private:
		filesystem::path				m_triPath;				// ·��
		filesystem::path				m_apcsPath;				// CollisionShape Path
		CStaticMeshTiledBuilder::SBuildParam m_buildParam;		// ���������������
		CStaticNavMesh*					m_pStaticNavMesh;		// ����ģ��
		CStaticMeshTiledBuilder			m_meshBuilder;			// NavMeshBuilder( Debug ��)

		Vector3							m_startPos;				// Ѱ·��ʼ��
		Vector3							m_endPos;				// Ѱ·������

		VisualShape*					m_triMesh;				// ������Mesh
		VisualShape*					m_polyMeshBoundaries;	// ���Ƹ�������α߽�
		VisualShape*					m_polyMeshTriangle;		// ���Ƹ��������������
		VisualShape*					m_pPathLine;
		VisualShape*					m_PolyShow[7];			// ��ʾ
		VisualCone3*					m_pStartCone;			// ��ʼ��
		VisualCone3*					m_pEndCone;				// ������
		VisualShape*					m_pApexPoints;			// ��Χ��

		WaterZoneMgr*					m_waterZoneMgr;			// ˮ���������(��������)

		FxDecal*						m_decal;				// ������
	};
}