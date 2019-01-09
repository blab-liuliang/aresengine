#pragma once

#include "CollisionWorld.h"
#include "SegmentDetect.h"

namespace Ares
{
	//-----------------------------------------
	// Ĭ���������� 2012-11-20
	//-----------------------------------------
	class RigidBody;
	class ActionInterface;
	class PhysicsWorld : public CollisionWorld
	{
	public:
		PhysicsWorld( Broadphase* broadphase=NULL);
		~PhysicsWorld();

		// ��������
		void SetGravity( const Vector3& gravity);

		// ��ȡ����
		const Vector3& GetGravity() { return m_gravity; }

		// �߶μ��
		bool SegmentDetect( Segment3& segment, const SegmentDetectConfig& detectConfig, SegmentDetectResult& result);

		// ��ѡ���������
		bool RaycastSingle( const Vector3& rayOrig, const Vector3& rayDir, float distance, CollisionObject*& object);

		// ��ѯ������������
		void RegionQueryTriangles( vector<Triangle3>& oResult, const Rect3& region);

		// ��ѯ�����ڶ���
		void RegionQueryCollisionObjects( vector<CollisionObject*>& results, const Shape* region);

		// Add Action
		void AddAction( ActionInterface* action);

		// ��ӽ�ͨ����
		void AddVehicle( ActionInterface* vehicle);

		// ��Ӹ���
		void AddRigidBody( RigidBody* body);

		// ˢ��
		virtual void FrameMove( float timeStep, int maxSubSteps=1, float fixedTimeStep=1.f/60.f);

	private:
		// ����
		void UpdateActions( float timeStep);

		// ��֡ģ��
		void InternalSingleStepSimulation( float timeStep);

		// �����˶�״̬
		virtual void SaveKinematicState( float timeStep);

		// Ӧ������
		void ApplyGravity();

		// ͬ���ƶ�״̬
		virtual void SynchronizeMotionStates();

		// 
		void PredictUnconstraintMotion( float timeStep);

		// �����Ӵ�
		void CreatePredictiveContacts( float timeStep);

		// ִ����ײ���
		void PerformCollisionDetection();

		// ����ģ��
		void CalculateSimulationIslands();

	private:
		Vector3						m_gravity;				// ����
		float						m_localTime;			// ����ʱ��
		vector<ActionInterface*>	m_actions;				// �����
		vector<RigidBody*>			m_nonStaticRigidBodys;	// �Ǿ�̬����
	};
	typedef s_ptr<PhysicsWorld> PhysicsWorldPtr;
}