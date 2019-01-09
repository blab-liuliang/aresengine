#ifndef ARES_PHYSICS_ENTITY_H
#define ARES_PHYSICS_ENTITY_H

#include <Physics/CollisionObject.h>
#include <Engine/SceneSystem/AresEntity.h>

namespace Ares
{
	//----------------------------------------
	// ����ʵ�� 2013-7-4 ���� 
	//----------------------------------------
	class PhysicsEntity : public Entity
	{
	public:
		PhysicsEntity();

		// ������ײ����
		void SetCollisionShape( Shape* collShape) { m_collSift.SetCollisionShape( collShape); }

		// �ύ��ȾԪ��
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr){}
	};
	typedef s_ptr<PhysicsEntity> PhysicsEntityPtr;
}

#endif