#pragma once

#include <vector>
#include "Contacts.h"
#include "Rect3.h"
#include "CollisionObject.h"
#include "Broadphase.h"
#include "Collide.h"
#include "AresDispatch.h"

using namespace std;

namespace Ares
{
	//-----------------------------------------------
	// CollisionWorld 2012-7-30 ����  excerpt bullet
	// CollisionWorld is interface and container for
	// the collision detection.
	//-----------------------------------------------
	class CollisionWorld
	{
	public:
		// ����AABB
		void UpdateSingleAABB( CollisionObject* colObj);

		// ��������AABB
		void UpdateAABBs();

		// ��ȡ��������ײ��������
		int GetNumCollisionObjects() const { return (int)m_collisionObjects.size(); }

		// ��ȡ��ײ����ָ��
		CollisionObject* GetCollisionObject( int idx) { return m_collisionObjects[idx]; }

		// ���CollisionObject
		virtual void AddCollisionObject( CollisionObject* collisionObject, UINT collisionFilterGroup=BroadphaseProxy::Filter_Default, UINT collisionFilterMask=BroadphaseProxy::Filter_All);

		// �Ƴ���ײ����
		virtual void RemoveCollisionObject( CollisionObject* collisionObject);

		// ��ȡBroadphase
		Broadphase* GetBroadphase() { return m_broadphase; }

		// ��ȡBroadphase
		const Broadphase* GetBroadphase() const { return m_broadphase; }

		// ��ȡ��Ϣ
		DispatcherInfo& GetDispatchInfo() { return m_dispatchInfo; }

		// �Ӵ����(shape not in the collision world)
		virtual bool ContactTest( Shape* shape, ContactResult& result);

		// ��ײ���(object in the collision world)
		virtual bool ContactTest( CollisionObject* object, ContactResult& result);

		// ��ײ���(object in the collision world)
		virtual void ContactPairTest( CollisionObject* objectA, CollisionObject* objectB,  ContactResult& result);

		// ˢ��
		virtual void FrameMove(  float timeStep, int maxSubSteps=1, float fixedTimeStep=1.f/60.f);

	protected:
		CollisionWorld( Broadphase* broadphase=NULL);
		virtual ~CollisionWorld();

	protected:
		Broadphase*					m_broadphase;				// �ּ�������
		DispatcherInfo				m_dispatchInfo;				// ������Ϣ
		vector<CollisionObject*>	m_collisionObjects;			// ���е���ײ����
	};
	typedef s_ptr<CollisionWorld>	CollisionWorldPtr;
}