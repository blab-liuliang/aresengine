#pragma once

#include <Physics/Collision/MotionState.h>

namespace Ares
{
	//------------------------------------------
	// EntityMotionState 2012-7-30 ����
	// Synchronize world transform with graphics
	//------------------------------------------
	class EntityMotionStae : public MotionState
	{
	public:
		// ���캯��
		EntityMotionStae( Entity* entity)
			: m_entity(entity)
		{}

		// ��ȡ��ʼλ��
		virtual void GetWorldTransform( Transform& worldTrans) const
		{

		}

		// ����λ�� the update only be calls for active objects
		virtual void SetWorldTransform( const Transform& worldTrans)
		{

		}

	private:
		Entity*		m_entity;			// ����ʵ��
	};
}