#pragma once

#include "Segment3.h"
#include "Rect3.h"

namespace Ares
{
	//----------------------------------------
	// capsule segment + radius 
	//			2011-04-28    ����
	struct Capsule3 : public Shape
	{
		Segment3    m_segment;
		float		m_radius;

		// construction
		Capsule3();

		// initialized
		Capsule3( const Segment3& segment, float radius);

		// set parameters
		void Set( const Segment3& segment, float radius);

		// constructor AABB bounding box
		virtual void BuildAABB( Rect3& box, const Transform& trans) const;

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass) { A_ASSERT(false); return Vector3::Zero; }

		// ��ȡ֧�ŵ�
		virtual Vector3 GetSupportPoint( const Vector3& normal) const;

		// ��ȡ���ĵ�
		virtual Vector3 GetCenter() const { return m_segment.m_orig; }

		// ִ��ת��
		void DoTransform( const Transform& transform);

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Shape>(*this);
			ar & m_segment;
			ar & m_radius;
		}
	};
}