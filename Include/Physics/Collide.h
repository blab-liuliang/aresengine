#pragma once

#include <vector>
#include "CollideAlgorithm.h"
#include "Physics/Shape.h"

namespace Ares
{
	//------------------------------------
	// ��ײ��� 2012-11-19 ����
	//------------------------------------
	class Collide
	{
	public:
		Collide();
		~Collide();

		// ������ײ�㷨
		static bool SetCollideAlgorithm( ShapeType type0, ShapeType type1, CollideAlgorithm* algorithm);

		// �ཻ����
		static bool IntersectionTest( const Shape* shape1, const Shape* shape2);

		// �ཻ����
		static bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2);

		// ������ײ���
		static bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList, bool clear=true);

	private:
		static CollideAlgorithm*	m_dispatch[ST_Total][ST_Total];			// ��ײ��⺯������
	};
}