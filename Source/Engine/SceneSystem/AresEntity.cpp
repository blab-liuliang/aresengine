#include <Engine/SceneSystem/AresEntity.h>
#include <Engine/SceneSystem/AresScene.h>
#include <Engine/SceneSystem/AresScene.h>
#include <Physics/PhysicsWorld.h>
#include <Engine/PhysicsSystem/AresCollisionObjectUserData.h>

namespace Ares
{
	// ���캯��
	Entity::Entity( EntityType type, EntityTypeDetail typeDetail)
		: m_type( type),
		  m_typeDetail( typeDetail),
		  m_static( false)
		, m_scene( NULL)
	{
		// �ͻ���ʹ��ʱһ��Ϊ��̬����
		m_bEnabled           = true;

		m_collSift.SetUserData( new_ COUserDataEntityFilter(this));
	}

	// ����������
	Entity::~Entity()
	{
	}

	// ��ȡʵ����
	const char* Entity::GetName()
	{
		return m_name.c_str();
	}

	// ����ʵ����
	void Entity::SetName( const char* name)
	{
		m_name = name;
	}

	// ��ȡת������
	const Transform& Entity::GetTransform()
	{ 
		return m_collSift.GetTransform();
	}

	// ����ת��
	void Entity::SetTransform( const Transform& transform)
	{
		m_collSift.SetTransform( transform);
	}

	// ��ȡ��Χ��
	Rect3 Entity::GetLocalBounds()
	{
		return m_collSift.GetLocalBounds();
	}

	// ��ȡ�����Χ��
	Rect3 Entity::GetWorldBounds() 
	{ 
		Rect3 result;

		m_collSift.BuildAABB( result);

		return result;
	}

	// ��ȡ��Ӧ�����ϵͳ
	CameraSystem& Entity::GetCameraSystem() 
	{ 
		return m_scene->GetCameraSystem(); 
	}

	// ����ʵ���Χ��
	void Entity::SetLocalBounds( const Rect3& rect)
	{
		m_collSift.SetLocalBounds( &rect);
	}

	// ����
	void Entity::FrameMove( float fTime)
	{
	}

	// ��ӵ�������Ϣ
	void Entity::OnAddToScene( Scene* scene) 
	{
		A_ASSERT( scene);

		m_scene = scene;

		PhysicsWorldPtr& physicsWorld = scene->GetPhysicsWorld();
		if( physicsWorld)
		{
			physicsWorld->AddCollisionObject( &m_collSift);
		}
	}
}