#pragma once

#include "Physics/Shape.h"

using namespace Ares;

namespace Xeno
{
	//---------------------------------
	// CollideNegative 2012-12-13 ����
	//---------------------------------
	class CollideNeg : public Shape
	{
	public:
		CollideNeg( const Shape* s1, const Quat& q1, const Vector3& t1);

		// ����AABB��Χ��
		virtual void BuildAABB( Rect3& box, const Transform& trans) const;

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass) { A_ASSERT(false); return Vector3::Zero; }

		// ��ȡ֧�ŵ�
		virtual Vector3 GetSupportPoint( const Vector3& normal);

		// ��ȡ���ĵ�
		virtual Vector3 GetCenter();

	private:
		Quat		m_quat;
		Vector3		m_trans;
		const Shape*m_shape;
	};

	//---------------------------------
	// CollideSum 2012-12-13 ����
	//---------------------------------
	class CollideSum : public Shape
	{
	public:
		CollideSum( const Shape* s1, const Quat& q1, const Vector3& t1, const Shape* s2, const Quat& q2, const Vector3& t2);

		// ����AABB��Χ��
		virtual void BuildAABB( Rect3& box, const Transform& trans) const;

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass) { A_ASSERT(false); return Vector3::Zero; }

		// ��ȡ֧�ŵ�
		virtual Vector3 GetSupportPoint( const Vector3& normal);

		// ��ȡ���ĵ�
		virtual Vector3 GetCenter();

	private:
		Quat		m_quat1;
		Quat		m_quat2;
		Vector3		m_trans1;
		Vector3		m_trans2;
		const Shape*m_shape1;
		const Shape*m_shape2;
	};

	// ת��������ռ�
	FORCEINLINE Vector3 TransformSupportVert( const Shape* p, const Quat& q, const Vector3& t, const Vector3& n )
	{
		Vector3 localNormal = (~q).Rotate( n);
		Vector3 localSupport = p->GetSupportPoint( localNormal);
		Vector3 worldSupport = q.Rotate( localSupport) + t;
		
		return worldSupport;
	}
}