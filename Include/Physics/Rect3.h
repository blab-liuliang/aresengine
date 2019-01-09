#pragma  once

#include <Core/AresMath.h>
#include "Physics/Shape.h"

namespace Ares
{
	//-------------------------------------------------------------
	// 2D���� 
	//-------------------------------------------------------------
	class Rect3;
	class Rect2
	{
	public:
		union
		{
			struct 
			{
				float x0, x1;
				float y0, y1;
			};
		};

		// ���캯��
		Rect2();
		Rect2( float _x0, float _x1, float _y0, float _y1);

		// ���صȺ�  "=" 
		void operator = (const Rect2& src);

		// ���ط���  "="
		void operator = (const Rect3& src);

		// ����XSize
		float GetXSize() { return std::abs(x1 - x0); }

		// ����YSize
		float GetYSize() { return std::abs(y1 - y0); }

		// �����Ƿ���2D������
		bool IsPointIn( float x, float y);

		// �ϲ���
		void  UnionPoint( float x, float y);

		// ����
		void Reset();
	};

	//-------------------------------------------------------------
	// 3D���� AABB 2010-03-28 17:08   -- δ֪   ����
	//-------------------------------------------------------------
	class Rect3 : public Shape
	{
	public:
		static const Rect3 Infinity;			// �����

	public:
		Vector3 m_min;
		Vector3	m_max;

		// ���캯��
		Rect3();
		Rect3(const Rect3& src);
		Rect3(const Vector3& v0, const Vector3& v1);

		// ���صȺ�  "="
		void operator = (const Rect2& src);

		// ���صȺ�  "="
		void operator = (const Rect3& src);

		// ���ط���  "+="
		const Rect3& operator += (const Vector3& vec);

		// ���ط���  "*="
		const Rect3& operator *= (const Vector3& vec);

		// ��������� "!="
		UBOOL operator != ( const Rect3& r) const
		{
			return m_min!=r.m_min || m_max!=r.m_max;
		}

		// ��������� "=="
		UBOOL operator == ( const Rect3& r) const
		{
			return m_min==r.m_min && m_max==r.m_max;
		}

		// ����
		void Set( float _x0, float _x1, float _y0, float _y1, float _z0, float _z1);

		// ����3D����ߴ�
		Vector3 GetSize();

		// ����XSize
		float GetXSize() const { return std::abs(m_max.x - m_min.x); }

		// ����YSize
		float GetYSize() const { return std::abs(m_max.y - m_min.y); }

		// ����ZSize
		float GetZSize() const { return std::abs(m_max.z - m_min.z); }

		// ���ر����
		float GetSurfaceArea() const;

		// ����Сλ��
		Vector3& GetMinPoint() { return m_min; }

		// ���ش�����
		Vector3& GetMaxPoint() { return m_max; }

		// ����Сλ��
		const Vector3& GetMinPoint() const { return m_min; }

		// ���ش�����
		const Vector3& GetMaxPoint() const { return m_max; }

		// ��ȡ�˸���
		void GetEightPoints( vector<Vector3>& points) const;

		// �����Ƿ���2D������
		virtual bool IsPointIn( const Vector3& p) const;

		// AABB�Ƿ���������
		bool IsContain( const Rect3& aabb) const;

		// �ϲ�X
		void UnionX( float x);

		// �ϲ�Y
		void UnionY( float y);

		// �ϲ�Z
		void UnionZ( float z);

		// �ϲ���
		void  UnionPoint(const Vector3& point);

		// �ϲ���
		void  UnionPoint( float x, float y, float z);

		// ����AABB��Χ��
		virtual void BuildAABB( Rect3& box, const Transform& trans) const;

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass) { A_ASSERT(false); return Vector3::Zero; }

		// ת��
		void  TransformByMatrix( const Matrix44& matrix);

		// ����
		void Reset();

	public:
		// �ϲ�,��̬����
		static void Merge( Rect3& result, const Rect3& inA, const Rect3& inB);

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Shape>(*this);
			ar & m_min;
			ar & m_max;
		}
	};
}