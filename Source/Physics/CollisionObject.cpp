#include <Physics/CollisionObject.h>

namespace Ares
{
	// ���캯��
	CollisionObject::CollisionObject()
		: m_collisionShape( NULL)
		, m_parent( NULL)
		, m_broadphaseProxy( NULL)
		, m_userData( NULL)
	{

	}

	// ��������
	CollisionObject::~CollisionObject()
	{
		SAFE_DELETE( m_collisionShape);
		SAFE_DELETE( m_broadphaseProxy);
	}

	// ����״̬
	void CollisionObject::SetActivationState( int newState) const
	{
		if( ( m_activationState1 != CF_DisableDeactivation) && (m_activationState1!=CF_DisableSimulation))
			m_activationState1 = newState;
	}

	// ��������ת��
	void CollisionObject::SetTransform( const Transform& transform) 
	{ 
		if( m_parent)
			m_localTransform = ~m_parent->GetTransform() * transform;
		else
			m_localTransform = transform;
	}

	// ��ȡ����ת��
	const Transform& CollisionObject::GetTransform()
	{ 
		m_worldTransform			 = m_localTransform;
		CollisionObject* parent  = m_parent;
		while( parent)
		{
			m_worldTransform = parent->GetTransform() * m_worldTransform;

			parent = parent->m_parent;
		}

		return m_worldTransform;
	}

	// ����AABB��Χ��
	void CollisionObject::BuildAABB( Rect3& box)
	{
		if( m_collisionShape)
			m_collisionShape->BuildAABB( box, GetTransform());
		else
			m_localBounds.BuildAABB( box, GetTransform());
	}

	// ����ӽ��
	void CollisionObject::AddChild( CollisionObject* child)
	{
		if( std::find( m_childs.begin(), m_childs.end(), child)==m_childs.end())
		{
			child->m_parent = this;

			m_childs.push_back( child);
		}
	}

	// ɾ���ӽ��
	void CollisionObject::DelChile( CollisionObject* child)
	{
		std::remove( m_childs.begin(), m_childs.end(), child);

		child->m_parent = NULL;
	}
}