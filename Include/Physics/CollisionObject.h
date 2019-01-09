#pragma once

#include <boost/any.hpp>
#include <Core/AresMath.h>
#include <Core/AresTransform.h>
#include "Broadphase.h"
#include "Shape.h"

namespace Ares
{
	// CollisionFlags
	enum CollisionFlags
	{
		CF_StaticObject			= 1,
		CF_KinematicObject		= 2,
		CF_NoContactResponse	= 4,
	};

	// CollisionObjectTypes
	enum CollisionObjectTypes
	{
		COT_CollisionObject = 1,
		COT_RigidBody,
		COT_GhostObject,
	};

	//--------------------------------------------------------------------
	// CollisionObject can be used to manage collision detection objects
	// CollisionObject maintains all information that is needed for a 
	// collision detection: Shape Transform and AABB proxy, They can be
	// added to the CollisionWorld 2012-7-28 ���� excerpt bullet
	//--------------------------------------------------------------------
	class CollisionObject
	{
		friend class CollisionObject;
	public:
		// ���
		enum COFlags
		{
			CF_ActiveTag			= 1,
			CF_IslandSleeping		= 2,
			CF_WantsDeactivation	= 3,
			CF_DisableDeactivation	= 4,
			CF_DisableSimulation	= 5,
		};

		// �û�����
		struct UserData
		{
			INT			m_type;			// �û���������

			// ���캯��
			UserData( INT type) : m_type( type){}
			virtual ~UserData() {}
		};

	public:
		CollisionObject();
		~CollisionObject();

		// �Ƿ��ڻ״̬
		bool IsActive() const { return (GetActivationState()!=CF_IslandSleeping) && (GetActivationState()!=CF_DisableSimulation); }

		// �Ƿ�Ϊ�˶�ѧ����
		bool IsKinematicObject() { return ( m_collisionFlags & CF_KinematicObject) != 0; }

		// �����û�����
		void SetUserData( UserData* userData) { m_userData = userData; }

		// ��ȡ�û�����
		UserData* GetUserData() { return m_userData; }

		// ��ȡ״̬
		int GetActivationState() const { return m_activationState1; }

		// ����״̬
		void SetActivationState( int newState) const;

		// ��������ת��
		void SetTransform( const Transform& transform);

		// ��ȡ����ת��
		const Transform& GetTransform();

		// ������ײģ��
		void SetCollisionShape( Shape* collisionShape) { m_collisionShape = collisionShape; }

		// ��ȡ��ײģ��
		Shape* GetCollisionShape() { return m_collisionShape; }

		// ��ȡ��ײģ��
		const Shape* GetCollisionShape() const  { return m_collisionShape; }

		// ��ȡ����
		BroadphaseProxy* GetBroadphaseProxy() { return m_broadphaseProxy; }

		// ��ȡ����
		const BroadphaseProxy* GetBroadphaseProxy() const { return m_broadphaseProxy; }

		// ���ô���
		void SetBroadphaseProxy( BroadphaseProxy* proxy) { m_broadphaseProxy = proxy; }

		// ���ô�������
		void SetLocalBounds( const Rect3* rect) { m_localBounds = *rect; }

		// ��ȡ��Χ��
		Rect3 GetLocalBounds() { return m_localBounds; }

		// ����AABB��Χ��
		void BuildAABB( Rect3& box);

		// ����ӽ��
		void AddChild( CollisionObject* child);

		// ɾ���ӽ��
		void DelChile( CollisionObject* child);

	protected:
		UserData*				m_userData;						// �û�����
		int						m_internalType;					// ����
		int						m_collisionFlags;				// ��ײ���
		mutable int				m_activationState1;				// ����״̬
		Transform				m_localTransform;				// ����ת��(�Ը����Ϊ������)
		Transform				m_worldTransform;				// ����ת��(ֻӦ������ת��ƽ��)
		Shape*					m_collisionShape;				// ��ײģ��
		Rect3					m_localBounds;					// ���ذ�Χ��
		BroadphaseProxy*		m_broadphaseProxy;				// ����
		CollisionObject*		m_parent;						// ������
		vector<CollisionObject*>m_childs;						// �Ӷ���

		Transform				m_interpolationWorldTransform;	// ���Բ�ֵ
		Vector3					m_interpolationLinearVelocity;	// �����ٶȲ�ֵ
		Vector3					m_interpolationAngularVelocity;	// ���ٶȲ�ֵ

		float					m_friction;						// Ħ����
		float					m_restitution;					// �ָ���???
		float					m_rollingFriction;				// ��תĦ����
	};
}