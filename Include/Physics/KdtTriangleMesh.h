#pragma once

#include "Physics/Kdt.h"
#include "Triangle3.h"

namespace Ares
{
	//----------------------------------------
	// KdtTriangleMesh 2012-11-23 ����
	//----------------------------------------
	class KdtTriangleMesh : public Shape
	{
	public:
		KdtTriangleMesh();
		~KdtTriangleMesh();

		// ��ʼ��
		bool Init( size_t numVertexs, Vector3* vertsData, size_t numTris, int* trisData);

		// ���߼��
		bool RayTrace( const Vector3& rayOrig, const Vector3& rayDir, float& dist, Vector3& normal) const;

		// ��ȡ��Χ��������������
		void GetTriIdxs( set<int>& triIdxs, const Rect3& aabb) const;

		// ��ȡ������
		Triangle3 GetTriangle( size_t idx) const;

		// ����AABB��Χ��
		virtual void BuildAABB( Rect3& box, const Transform& trans) const;

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass) { A_ASSERT(false); return Vector3::Zero; }

		// ��������
		void Reset();

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Shape>(*this);
			ar & m_kdt;
			ar & m_localAabb;
			ar & m_verts;
			ar & m_tris;
		}

	private:
		Kdt<int>		m_kdt;				// KDTree
		Rect3			m_localAabb;		// ��Χ��
		vector<Vector3>	m_verts;			// ����
		vector<Int3>	m_tris;				// ������
		int				m_rayDir[8][3][2];	// �������߸���
	};
}