#pragma once

#include "Physics/Shapes.h"

namespace Ares
{
	// ��ײ���
	struct CollideContact
	{
		Vector3  m_normal;
		Vector3	 m_point0;
		Vector3	 m_point1;
	};
	typedef std::vector<CollideContact> CollideContactList;

	//------------------------------------------
	// ��ײ�㷨 2012-11-21 ����
	//------------------------------------------
	struct CollideAlgorithm
	{
		// �ཻ����
		virtual bool IntersectionTest( const Shape* shape1, const Shape* shape2);

		// �ཻ����
		virtual bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2)=0;

		// �Ӵ�����
		virtual bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList)=0;
	};

	//---------------------------------------
	// XenoCollide 2012-12-13 ����
	//---------------------------------------
	struct CollideXeno : public CollideAlgorithm
	{
		// �ཻ����
		virtual bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2);

		// �Ӵ�����
		virtual bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList);
	};

	//------------------------------------------------
	// intersection test between Segment3 and Rect3
	//				2012-05-23      ����
	struct CollideSegment3Rect3 : public CollideAlgorithm
	{
		// �ཻ����
		virtual bool IntersectionTest( const Shape* shape1, const Shape* shape2);

		// construction
		virtual bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2);

		// �Ӵ�����
		virtual bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList);
	};

	//------------------------------------------------
	// ������������ģ�� 2012-11-28 ����
	//------------------------------------------------
	struct CollideSegment3KdtTriangleMesh : public CollideAlgorithm
	{
		// construction
		virtual bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2);

		// �Ӵ�����
		virtual bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList);
	};

	//------------------------------------------------
	// ������߶�ͼ 2012-11-30 ����
	//------------------------------------------------
	struct CollideSegment3HeightField : public CollideAlgorithm
	{
		// �ཻ���
		virtual bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2);

		// �Ӵ�����
		virtual bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList);
	};

	//---------------------------------------------
	// Box3 with Rect3 2013-7-9 ����
	//---------------------------------------------
	struct CollideBox3Rect3 : public CollideAlgorithm
	{
		// �ཻ����
		virtual bool IntersectionTest( const Shape* shape1, const Shape* shape2);

		// �ཻ���
		virtual bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2);

		// �Ӵ�����
		virtual bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList);

	};

	//---------------------------------------------
	// Rect3 with Rect3 2012-12-13 ����
	//---------------------------------------------
	struct CollideRect3Rect3 : public CollideAlgorithm
	{
		// �ཻ����
		virtual bool IntersectionTest( const Shape* shape1, const Shape* shape2);

		// �ཻ���
		virtual bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2);

		// �Ӵ�����
		virtual bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList);
	};

	//---------------------------------------------
	// Rect3 with Frustum 2013-7-6 ����
	//---------------------------------------------
	struct CollideFrustum3Rect3 : public CollideAlgorithm
	{
		// �ཻ����
		virtual bool IntersectionTest( const Shape* shape1, const Shape* shape2);

		// �ཻ���
		virtual bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2);

		// �Ӵ�����
		virtual bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList);
	};

	//---------------------------------------------
	// Capsule3 with Capsule3 2012-12-18 ����
	//---------------------------------------------
	struct CollideCapsule3Capsule3 : public CollideAlgorithm
	{
		// �ཻ���
		virtual bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2);

		// �Ӵ�����
		virtual bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList);
	};

	//---------------------------------------------
	// Rect3 with Rect3 2012-12-13 ����
	//---------------------------------------------
	struct CollideCompountCompount : public CollideAlgorithm
	{
		// �ཻ���
		virtual bool IntersectionTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2);

		// �Ӵ�����
		virtual bool ContactTest( const Shape* shape1, const Quat& q1, const Vector3& t1, const Shape* shape2, const Quat& q2, const Vector3& t2, CollideContactList& oContactList);
	};
}