#pragma once

namespace Ares
{
	//---------------------------------------------------------
	// MotionState 2012-7-30  ���� ��bullet
	// The MotionState interface class allows the dynamics
	// world to synchronized and interpolate the updated world
	// transforms with graphics For optimizations, potentially
	// only moving objects get synchronized.
	//---------------------------------------------------------
	class MotionState
	{
	public:
		// ����������
		virtual ~MotionState()
		{}

		// ��ȡ��ʼλ��
		virtual void GetWorldTransform( Transform& worldTrans) const=0;

		// ����λ�� the update only be calls for active objects
		virtual void SetWorldTransform( const Transform& worldTrans)=0;
	};
}