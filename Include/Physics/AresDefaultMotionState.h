#pragma once

#include "MotionState.h"

namespace Ares
{
	//-----------------------------------------
	// DefaultMotionState 2013-910 ����
	//-----------------------------------------
	class DefaultMotionState : public MotionState
	{
	public:
		// ��ȡ��ʼλ��
		virtual void GetWorldTransform( Transform& worldTrans) const
		{

		}

		// ����λ�� the update only be calls for active objects
		virtual void SetWorldTransform( const Transform& worldTrans)
		{

		}

	public:
		
	};
}