#include <Physics/CompoundShape.h>

BOOST_CLASS_EXPORT( Ares::CompoundShape)

namespace Ares
{
	// ���캯��
	CompoundShape::CompoundShape()
		: Shape( ST_Compount)
	{
	}

	// ��������
	CompoundShape::~CompoundShape()
	{
		for( size_t i=0; i<m_children.size(); i++)
			SAFE_DELETE( m_children[i].m_shape);
	}

	// ���������
	void CompoundShape::AddChildShape( const Transform& localTransform, Shape* shape)
	{
		CompoundShapeChild child;
		child.m_transform = localTransform;
		child.m_shape	  = shape;

		m_children.push_back( child);

		// Update the local bounding Box
		RefreshLocalBoundingBox();
	}

	// ���±��ذ�Χ��
	void CompoundShape::RefreshLocalBoundingBox()
	{
		m_localAABB.Reset();
		for( size_t i=0; i<m_children.size(); i++)
		{
			Rect3 localAABB;
			m_children[i].m_shape->BuildAABB( localAABB, m_children[i].m_transform);

			m_localAABB.UnionPoint( localAABB.GetMinPoint());
			m_localAABB.UnionPoint( localAABB.GetMaxPoint());
		}
	}

	// ����AABB��Χ��
	void CompoundShape::BuildAABB( Rect3& box, const Transform& trans) const
	{
		box = m_localAABB;
		box.TransformByMatrix( trans.GetMatrix());
	}
}