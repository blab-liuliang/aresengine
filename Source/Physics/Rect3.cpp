#include "Physics/Rect3.h"

BOOST_CLASS_EXPORT( Ares::Rect3)

namespace Ares
{
	const Rect3  Rect3::Infinity = Rect3( Vector3( -FLT_BIG, -FLT_BIG, -FLT_BIG), Vector3( FLT_BIG, FLT_BIG, FLT_BIG));

	// 2D�����캯��
	Rect2::Rect2()
	{
		Reset();
	}

	// ����
	void Rect2::Reset()
	{
		x0 =  FLT_MAX;
		x1 = -FLT_MAX;

		y0 =  FLT_MAX;
		y1 = -FLT_MAX;
	}

	// �����Ƿ���2D������
	bool Rect2::IsPointIn( float x, float y)
	{
		if( x>=x0 && x<=x1 && y>=y0 && y<=y1)
			return true;

		return false;
	}

	// 2D�����캯��
	Rect2::Rect2(float _x0, float _x1, float _y0, float _y1)
	{
		x0 = _x0;
		x1 = _x1;
		y0 = _y0;
		y1 = _y1;
	}

	// ���������"="
	void  Rect2::operator = (const Rect2& src)
	{
		x0 = src.x0;
		x1 = src.x1;
		y0 = src.y0;
		y1 = src.y1;

		// ע��memcpy(this, src, sizeof(CRect2D)); ����, �ʲ�����
	}

	// ���ط���  "="
	void Rect2::operator = (const Rect3& src)
	{
		x0 = src.m_min.x;
		x1 = src.m_max.x;
		y0 = src.m_min.y;
		y1 = src.m_max.y;
	}

	// �ϲ���
	void Rect2::UnionPoint( float x, float y)
	{
		x0 = std::min<FLOAT>( x0, x);
		y0 = std::min<FLOAT>( y0, y);

		x1 = std::max<FLOAT>( x1, x);
		y1 = std::max<FLOAT>( y1, y);
	}

	// ���캯��
	Rect3::Rect3()
		: Shape( ST_Rect3)
	{
		Reset();
	}

	// ����
	void Rect3::Reset()
	{
        m_min = Vector3( FLT_BIG, FLT_BIG, FLT_BIG);
        m_max = Vector3(-FLT_BIG,-FLT_BIG,-FLT_BIG);
	}

	// ���ƹ��캯��
	Rect3::Rect3(const Rect3& src)
		: Shape( ST_Rect3)
	{
        m_min = src.m_min;
        m_max = src.m_max;
	}

	// ���캯��
	Rect3::Rect3( const Vector3& v0, const Vector3& v1)
		: Shape( ST_Rect3)
	{
		Reset();
		UnionPoint( v0);
		UnionPoint( v1);
	}

	// ����
	void Rect3::Set(float _x0, float _x1, float _y0, float _y1, float _z0, float _z1)
	{
        m_min = Vector3( _x0, _y0, _z0);
        m_max = Vector3( _x1, _y1, _z1);
	}

	// �����Ƿ���2D������
	bool Rect3::IsPointIn( const Vector3& p) const
	{
		if( p.x<m_min.x || p.x>m_max.x || p.y<m_min.y || p.y>m_max.y || p.z<m_min.z || p.z>m_max.z)
			return false;

		return true;
	}

	// AABB�Ƿ���������
	bool Rect3::IsContain( const Rect3& aabb) const
	{
		return (m_min.x<=aabb.m_min.x) && (m_min.y<=aabb.m_min.y) && (m_min.z<=aabb.m_min.z) &&
			   (m_max.x>=aabb.m_max.x) && (m_max.y>=aabb.m_max.y) && (m_max.z>=aabb.m_max.z);
	}

	// ���صȺ�  "="
	void Rect3::operator = (const Rect2& src)
	{
        m_min.x = src.x0;
        m_min.y = src.y0;
        m_max.x = src.x1;
        m_max.y = src.y1;
	}

	// CRect3D ���� "=" 
	void  Rect3::operator = (const Rect3& src)
	{
        m_min = src.m_min;
        m_max = src.m_max;

		// ע��memcpy(this, src, sizeof(CRect3D)); ����, �ʲ�����
	}

	// ��������� "+="
	const Rect3& Rect3::operator += (const Vector3& vec)
	{
        m_min += vec;
        m_max += vec;

		return *this;
	}

	// ���غ�������ߴ�
	Vector3 Rect3::GetSize()
	{
		return m_max - m_min;
	}

	// ��ȡ�˸���
	void Rect3::GetEightPoints( vector<Vector3>& points) const
	{
		points[0].x = m_min.x;	points[0].y = m_min.y;	points[0].z = m_min.z;
		points[1].x = m_min.x;	points[1].y = m_max.y;	points[1].z = m_min.z;
		points[2].x = m_max.x;	points[2].y = m_max.y;	points[2].z = m_min.z;
		points[3].x = m_max.x;	points[3].y = m_min.y;	points[3].z = m_min.z;

		points[4].x = m_min.x;	points[4].y = m_min.y;	points[4].z = m_max.z;
		points[5].x = m_min.x;	points[5].y = m_max.y;	points[5].z = m_max.z;
		points[6].x = m_max.x;	points[6].y = m_max.y;	points[6].z = m_max.z;
		points[7].x = m_max.x;	points[7].y = m_min.y;	points[7].z = m_max.z;
	}

	// ���ر����
	float Rect3::GetSurfaceArea() const
	{
		return ( GetXSize() * GetYSize() + GetXSize() * GetZSize() + GetYSize() * GetZSize()) * 2.f;
	}

	// �ϲ�X
	void Rect3::UnionX( float x)
	{
		m_min.x = std::min<FLOAT>( m_min.x, x);
		m_max.x = std::max<FLOAT>( m_max.x, x);
	}

	// �ϲ�Y
	void Rect3::UnionY( float y)
	{
		m_min.y = std::min<FLOAT>( m_min.y, y);
		m_max.y = std::max<FLOAT>( m_max.y, y);
	}

	// �ϲ�Z
	void Rect3::UnionZ( float z)
	{
		m_min.z = std::min<FLOAT>( m_min.z, z);
		m_max.z = std::max<FLOAT>( m_max.z, z);
	}

	// �ϲ���
	void Rect3::UnionPoint(const Vector3& point)
	{
		UnionPoint( point.x, point.y, point.z);
	}

	// �ϲ���
	void Rect3::UnionPoint( float x, float y, float z)
	{
		UnionX( x);
        UnionY( y);
        UnionZ( z);
	}

	// ����������
	void Rect3::TransformByMatrix( const Matrix44& matrix)
	{
		Vector3 basePoint( m_min);
		Vector3 xLeg( m_max.x, m_min.y, m_min.z);
		Vector3 yLeg( m_min.x, m_max.y, m_min.z);
		Vector3 zLeg( m_min.x, m_min.y, m_max.z);

		basePoint = matrix.TransformVector3( basePoint);
		xLeg	  = matrix.TransformVector3( xLeg);
		yLeg	  = matrix.TransformVector3( yLeg);
		zLeg	  = matrix.TransformVector3( zLeg);

		xLeg -= basePoint;
		yLeg -= basePoint;
		zLeg -= basePoint;

		Vector3 farPoint( basePoint + xLeg + yLeg + zLeg);

		Set( basePoint.x,farPoint.x, basePoint.y,farPoint.y, basePoint.z,farPoint.z);

		UnionPoint(basePoint + xLeg);
		UnionPoint(basePoint + yLeg);
		UnionPoint(basePoint + zLeg);
		UnionPoint(basePoint + xLeg + yLeg);
		UnionPoint(basePoint + yLeg + zLeg);
		UnionPoint(basePoint + zLeg + xLeg);
	}

	// ����AABB��Χ��
	void Rect3::BuildAABB( Rect3& box, const Transform& trans) const
	{
		box = *this;
		box.TransformByMatrix( trans.GetMatrix());
	}

	// �ϲ�,��̬����
	void Rect3::Merge( Rect3& result, const Rect3& inA, const Rect3& inB)
	{
		result = inA;
		result.UnionPoint( inB.GetMinPoint());
		result.UnionPoint( inB.GetMaxPoint());
	}
}