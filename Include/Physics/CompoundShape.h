#pragma once

#include "Rect3.h"

namespace Ares
{
	// CompoundShapeChild
	struct CompoundShapeChild
	{
		Transform		m_transform;
		Shape*			m_shape;

		// ���캯��
		CompoundShapeChild() : m_shape( NULL)
		{}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_transform;
			ar & m_shape;
		}
	};

	//----------------------------------------------------
	// CompoundShape 2012-9-10 ����
	//----------------------------------------------------
	class CompoundShape : public Shape
	{
	public:
		CompoundShape();
		~CompoundShape();

		// ���������
		void AddChildShape( const Transform& localTransform, Shape* shape);

		// ��ȡ����������
		int GetNumChildShapes() const { return static_cast<int>(m_children.size()); }

		// ����������ȡ������
		Shape* GetChildShape( int idx) { return m_children[idx].m_shape; }

		// ����������ȡ������
		const Shape* GetChildShape( int idx) const { return m_children[idx].m_shape; }

		// ��ȡ�����α���ת��
		Transform& GetChildTransform( int idx) { return m_children[idx].m_transform; }

		// ��ȡ�����α���ת��
		const Transform& GetChildTransform( int idx) const { return m_children[idx].m_transform; }

		// ����AABB��Χ��
		virtual void BuildAABB( Rect3& box, const Transform& trans) const;

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass) { A_ASSERT(false); return Vector3::Zero; }

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Shape>(*this);
			ar & m_localAABB;
			ar & m_children;
		}

	private:
		// ���±��ذ�Χ��
		void RefreshLocalBoundingBox();

	private:
		Rect3						m_localAABB;		// ���ذ�Χ��
		vector<CompoundShapeChild>	m_children;			// ������
	};
}