#include <iostream>
#include <Physics/HeightField.h>

BOOST_CLASS_EXPORT( Ares::HeightField)

namespace Ares
{
	// ���캯��
	HeightField::HeightField()
		: Shape( ST_HeightField)
	{
		m_version	 = 1;

		m_hollowWidth = 0;
		m_tableHeight = 0;

		m_hollowWidth = 0;
		m_hollowHeight= 0;
	}

	// ��������
	HeightField::~HeightField()
	{
		Reset();
	}

	// ����
	void HeightField::Reset()
	{
	}

	// ��ʼ��
	void HeightField::Init( UINT width, UINT height, float* heightData/*=NULL*/, UINT gridSize/*=1*/)
	{
		// ����,ʹHeightField���Ա���γ�ʼ��
		Reset();

		m_tableWidth  = width;
		m_tableHeight = height;
		m_gridSize	  = gridSize;

		// ������
		m_heightData.resize( (width+1) * (height+1), 0.f);
		if( heightData)
		{
			for( size_t i=0; i<m_heightData.size(); i++)
				m_heightData[i] = heightData[i];
		}
	}

	// �����ο�
	void HeightField::SetHollow( UINT width, UINT height, BYTE* hollowData/*=NULL*/)
	{
		m_hollowWidth = width;
		m_hollowHeight= height;

		// ������
		m_hollowData.resize( (width+1) * (height+1), 0);
		if( hollowData)
		{
			for( size_t i=0; i<m_hollowData.size(); i++)
				m_hollowData[i] = hollowData[i];
		}
	}

	// �Ƿ�Ϊ�ն�
	BYTE HeightField::GetFlag( UINT x, UINT y) const
	{
		if( m_hollowData.empty())
			return 0x0;

		x = (std::min)( x, m_hollowWidth);
		y = (std::min)( y, m_hollowHeight);

		UINT hollowIdx = y * m_hollowWidth + x;

		return m_hollowData[hollowIdx];
	}

	// ����λ�û�ȡ����
	UINT HeightField::TableIdx( UINT x, UINT y) const
	{
		x = std::min<UINT>( x, m_tableWidth);
		y = std::min<UINT>( y, m_tableHeight);

		return y * ( m_tableWidth+1) + x;
	}

	// ��ȡĳ��߶�
	float HeightField::GetHeightAt( UINT x, UINT y) const
	{
		UINT idx = TableIdx( x, y);

		return m_heightData[idx];
	}

	// ��ȡĳ��߶�(��������)
	float HeightField::GetHeightAt( UINT idx)
	{
		return m_heightData[idx];
	}

	// ��ȡ����
	Vector3 HeightField::GetNormalAt( UINT x, UINT y)
	{
		// ���㷨��(������ο�:��Ϸ��̾���3-4.2 ���ٸ߶ȳ����ߵļ��� P302)
		float h0 = GetHeightAt( x, y);
		float h1 = GetHeightAt( x+1,   y) - h0;
		float h2 = GetHeightAt(   x, y-1) - h0;
		float h3 = GetHeightAt( x-1,   y) - h0;
		float h4 = GetHeightAt(   x, y+1) - h0;

		Vector3 normal( h3 - h1, h2 - h4, 2);
		normal.Normalize();
		
		return normal;
	}

	// ����ĳ��߶�
	void HeightField::SetHeightAt( UINT x, UINT y, float height)
	{
		UINT idx = TableIdx( x, y);

		m_heightData[idx] = height;
	}

	// ���������С��ȡ������Χ
	void HeightField::GetIdxRegion( int& minX, int& maxX, int& minY, int& maxY, const Rect3& region) const
	{
		maxX = ((int)region.m_max.x + m_gridSize) / m_gridSize;
		maxY = ((int)region.m_max.y + m_gridSize) / m_gridSize;
		minX = (int)region.m_min.x /  m_gridSize;
		minY = (int)region.m_min.y /  m_gridSize;

		maxX = std::min<int>( m_tableWidth, maxX);
		maxY = std::min<int>( m_tableHeight,maxY);
		minX = std::max<int>( 0, minX);
		minY = std::max<int>( 0, minY);
	}

	// ��Ӷ�Ӧ���ӵ����������ε�������
	void HeightField::AddTri( vector<Triangle3>& triangles, UINT x, UINT y) const
	{
		// ����������
		Triangle3 triangle;

		float hx1y1 = GetHeightAt( x+1, y+1);

		triangle.m_v[0].x = (float)x;
		triangle.m_v[0].y = (float)y;
		triangle.m_v[0].z =  GetHeightAt( x, y);
		triangle.m_v[1].x = (float)x+1;
		triangle.m_v[1].y = (float)y;
		triangle.m_v[1].z =  GetHeightAt( x + 1, y);
		triangle.m_v[2].x = (float)x+1;
		triangle.m_v[2].y = (float)y+1;
		triangle.m_v[2].z =  hx1y1;

		triangles.push_back( triangle);

		//triangle.m_v[1].x = (float)x+1;
		triangle.m_v[1].y = (float)y+1;
		triangle.m_v[1].z =  hx1y1;
		triangle.m_v[2].x = (float)x;
		//triangle.m_v[2].y = (float)y+1;
		triangle.m_v[2].z =  GetHeightAt( x, y+1);

		triangles.push_back( triangle);
	}

	// ��ȡ������
	size_t HeightField::GetTriangle(vector<Triangle3>& triangles, const Rect3& region) const
	{
		// ���
		triangles.clear();

		int minX, maxX, minY, maxY;
		GetIdxRegion( minX, maxX, minY, maxY, region);

		// ����������
		Triangle3 triangle;

		// ���
		for ( int y=maxY; y>=minY; y--)
		{
			for ( int x=maxX; x>=minX; x--)
				AddTri( triangles, x, y);
		}

		return triangles.size();
	}

	// ��ȡ������(ȥ���ն�)
	size_t HeightField::GetTriangleByFlag( vector<Triangle3>& triangles, const Rect3& region, BYTE flag) const
	{
		if( m_hollowData.empty())
			return GetTriangle( triangles, region);

		// ���
		triangles.clear();

		int minX, maxX, minY, maxY;
		GetIdxRegion( minX, maxX, minY, maxY, region);

		// ����������
		Triangle3 triangle;

		// ���
		for ( int y=maxY; y>=minY; y--)
		{
			for ( int x=maxX; x>=minX; x--)
			{
				if( GetFlag( x, y) & flag)
					AddTri( triangles, x, y);
			}
		}

		return triangles.size();
	}

	// ����AABB��Χ����
	void HeightField::BuildAABBArrayByXY( vector<Rect3>& aabbArrays, const Transform& trans, const Parabola3& parabola, float t0, float t1) const
	{
		aabbArrays.clear();

		Rect3   region;
		Vector3 beginPos, endPos, dirxy;
		parabola.BuildPos( beginPos, t0);
		parabola.BuildPos( endPos,	 t1);
		region.UnionPoint( beginPos);
		region.UnionPoint( endPos);
		dirxy = endPos - beginPos;

		int minX, maxX, minY, maxY;
		GetIdxRegion( minX, maxX, minY, maxY, region);
		int		splitNum = max( abs( maxX-minX) < abs( maxY-minY) ? abs( maxX-minX) : abs( maxY-minY), 1);
		Vector3 stepLen  = dirxy / (float)splitNum;
		for ( int i=0; i<splitNum; i++)
		{
			Rect3 aabb;
			aabb.UnionPoint( beginPos+(i+0.001f)*stepLen);
			aabb.UnionPoint( beginPos+(i+0.999f)*stepLen);

			aabbArrays.push_back( aabb);
		}
	}
}