#pragma once

#include <vector>
#include <Core/AresMath.h>
#include "AresActionInterface.h"
#include "AresVehicleRaycaster.h"
#include "RigidBody.h"

using namespace std;

namespace Ares
{
	//----------------------------------------
	// RaycastVehicle 2013-9-4 ����
	//----------------------------------------
	class RaycastVehicle : public ActionInterface
	{
	public:
		// ����
		struct Wheel
		{
			struct RaycastInfo
			{
				Vector3		m_contactNormalWS;			// ����
				Vector3		m_contactPostionWS;			// �Ӵ���
				float		m_suspensionLength;			// ��������
				Vector3		m_hardPositionWS;			// �������
				Vector3		m_wheelDirectionWS;			// ���ӳ���
				Vector3		m_wheelAxisWS;				// ����
				bool		m_isInContact;				// �Ƿ�Ӵ�
				void*		m_groundObject;				// ��ײ����
			};

			RaycastInfo m_raycastInfo;					// ���߼����Ϣ
			Transform	m_worldTransform;				// ����ת��
			float		m_engineForce;					// 
			Vector3		m_chassisConnectionPointCS;		// ��������ӵ�
			float		m_suspensionRestLenght1;		// ����
			float		m_suspensionStiffness;			// ����
			float		m_maxSuspensionTravelCm;		// 
			Vector3		m_wheelDirectionCS;				// ���ֳ���
			Vector3		m_wheelAxisCS;					// ��������(����,��Steering�޸�)
			float		m_wheelRadius;					// ���ְ뾶
			float		m_steering;						// ת��
			float		m_rotation;						// ������ת
			float		m_deltaRotation;				// ��ת
			float		m_rollInfluence;
			float		m_maxSuspensionForce;			// ���������
			float		m_wheelSuspensionForce;			// ������
			float		m_clippedInvContactDotSuspension;
			float		m_suspensionRelativeVelocity;
			float		m_wheelsDampingCompression;
			float		m_wheelsDampingRelaxation;
			float		m_wheelsSuspensionForce;		// ����������
			float		m_frictionSlip;					// Ħ������
			float		m_brake;
			float		m_skidInfo;						// ����

			// �����������ó���
			float GetSuspensionRestLength() const
			{
				return m_suspensionRestLenght1;
			}
		};

	public:
		virtual ~RaycastVehicle() {}

		// ��ȡ����
		RigidBody* GetRigidBody() { return m_chassis; }

		// ��ȡ����
		const RigidBody* GetRigidBody() const { return m_chassis; }

		// ��ȡ��������
		int GetNumWheels() const { return (int)m_wheels.size();}

		// ��ȡ����Transform
		const Transform& GetWheelTransformWS( int idx) const;

	private:
		// ����
		virtual void UpdateAction( PhysicsWorld* physicsWorld, float deltaTimeStep);

		// ���³���
		void UpdateVehicle( float timeStep);

		// ����ָ������
		void UpdateWheelTransform( int wheelIdx, bool interpolateTransform=true);

		// ���³�ָ������
		void UpdateWheeltransformWS( Wheel& wheel, bool isInterpolatedTransform=true);

		// ����
		void UpdateSuspension( float deltaTime);

		// ����Ħ����
		void UpdateFriction( float timeStep);

		// ��ȡ������ת��
		const Transform& GetChassisWorldTransform();

		// ���߼��
		float RayCast( Wheel& wheel);

	private:
		float				m_currentVehicleSpeedKmHour;	// �ٶ�

		RigidBody*			m_chassis;						// ����
		vector<Wheel>		m_wheels;						// ����
		VehicleRaycaster*	m_raycaster;					// ���߼����
		vector<Vector3>		m_forwardWS;					// 
		vector<Vector3>		m_axle;
		vector<float>		m_forwardImpulse;
		vector<float>		m_sideImpulse;
		int					m_indexUpAxis;					// �Ϸ���
	};
}