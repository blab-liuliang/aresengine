#pragma once

#include <Core/AresTransform.h>
#include <Core/AresSerialization.h>

namespace Ares
{
	// ֧�ֵ�Shape����
	enum ShapeType
	{
		ST_Segment3		=  0,		// ����
		ST_Rect3,					// �����Χ��
		ST_Capsule,					// ����
		ST_KdtTriangleMesh,			// KDTree����������
		ST_HeightField,				// �߶�ͼ
		ST_Frustum,					// ƽ��ͷ��
		ST_Box3,					// �����Χ��
		ST_Compount,				// �������
		ST_Total,					// ��������
		ST_UnKnown,					// δ֪
	};

	//----------------------------------------------------
	// CollisionShape 2012-7-30 ����
	// CollisionShape provides an interface for collision
	// shapes that can be shared among CollionObjects
	//----------------------------------------------------
	class Rect3;
	class Shape
	{
	public:
		// ���캯��
		Shape( ShapeType type)
			: m_type( type)
			, m_scale( 1.f, 1.f, 1.f)
		{}

		// ����������
		virtual ~Shape(){}

		// ����ģ������
		int GetShapeType() const { return m_type; }

		// �Ƿ�Ϊ͹�����
		bool IsConvex();

		// ����AABB��Χ��
		virtual void BuildAABB( Rect3& box, const Transform& trans) const=0;

		// ��ȡ��Χ��
		virtual void BuildBoundingSphere( Vector3& center, float& radius) const;

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass)=0;

		// ��������
		virtual void SetScale( const Vector3& scale) { m_scale=scale; }

		// ��ȡ֧�ŵ�
		virtual Vector3 GetSupportPoint( const Vector3& normal) const;

		// ��ȡ���ĵ�
		virtual Vector3 GetCenter() const;

		// Checks whether a point is within the shape
		virtual bool IsPointIn( const Vector3& point) const;

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_scale;
		}

	protected:
		int			m_type;
		Vector3		m_scale;
	};
	typedef s_ptr<Shape> ShapePtr;
}