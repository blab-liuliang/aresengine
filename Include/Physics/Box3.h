#pragma once

#include "Rect3.h"

namespace Ares
{
	//------------------------------------------------------------------
	// Box3 2011-07-12   
	// A box has center C, axis directions U[0], U[1], and U[2] ( all 
	// unit-length vectors), and extents e[0], e[1], and e[2] ( all 
	// nonnegative numbers). A point x = C + y[0]*U[0] + y[1]*U[1] + 
	// y[2]*U[2] is inside or on the box wheneve |y[i]| <= e[i] for all i
	struct Box3 : public Shape
	{
		Vector3		m_center;	// ���ĵ�
		Vector3		m_axis[3];	// ����,�ᳯ������ǹ淶������
		float		m_extent[3];// �Ǹ� 

		// construction (uninitialized)
		Box3();

		// initialized
		Box3( const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, float extent0, float extent1, float extent2);

		// Set
		void Set( const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2, float extent0, float extent1, float extent2);

		// ����AABB��Χ��
		virtual void BuildAABB( Rect3& box, const Transform& trans) const;

		// �����˸�����
		void BuildEightPoints( Vector3* points) const;

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass);

		// �жϵ��Ƿ��������Χ����
		virtual bool IsPointIn( const Vector3& point) const;

		// �ж�AABB��Χ��(д������������)
		bool  IsAABBOverlap( const Rect3& rect) const;

		// ִ��ת��
		void DoTransform( const Transform& transform);

		// transform by matrix
		void  TransformByMatrix( const Matrix44& matrix);

		// Serialize
		template< typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Shape>(*this);
			ar & m_center;
			ar & m_axis;
			ar & m_extent;
		}
	};
}