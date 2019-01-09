#include "Physics/Shapes.h"

namespace Ares
{
	// �Ƿ�Ϊ͹�����
	bool Shape::IsConvex()
	{
		static boost::array<bool, ST_Total+1> convexFlag = { true, true, false, false };

		return convexFlag[m_type];
	}

	// ��ȡ��Χ��
	void Shape::BuildBoundingSphere( Vector3& center, float& radius) const
	{
		Transform transform;
		Rect3		boundingBox;

		BuildAABB( boundingBox, transform);

		radius = ( boundingBox.GetMaxPoint()-boundingBox.GetMinPoint()).Length() * 0.5f;
		center = ( boundingBox.GetMaxPoint()+boundingBox.GetMinPoint()) * 0.5f;
	}

	// ��ȡ֧�ŵ�
	Vector3 Shape::GetSupportPoint( const Vector3& normal) const
	{
		A_ASSERT( FALSE);

		return Vector3::Zero;
	}

	// ��ȡ���ĵ�
	Vector3 Shape::GetCenter() const
	{
		A_ASSERT( FALSE);

		return Vector3::Zero;
	}

	// Checks whether a point is within the shape
	bool Shape::IsPointIn( const Vector3& point) const
	{
		A_ASSERT( FALSE);

		return false;
	}
}