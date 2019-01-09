#pragma once

#include "Triangle3.h"
#include "Parabola3.h"
#include "Physics/Rect3.h"
#include <vector>

using namespace std;

namespace Ares
{
	//------------------------------------
	// HeightField   2011-08-05 ����
	//------------------------------------
	class HeightField : public Shape
	{
	public:
		HeightField();
		~HeightField();

		// ��ʼ��
		void Init( UINT width, UINT height, float* heightData=NULL, UINT gridSize=1);

		// �����ο�
		void SetHollow( UINT width, UINT height, BYTE* hollowData=NULL);

		// ��ȡĳ��߶�
		float GetHeightAt( UINT x, UINT y) const;

		// ��ȡĳ��߶�(��������)
		float GetHeightAt( UINT idx);

		// ��ȡ����
		Vector3 GetNormalAt( UINT x, UINT y);

		// ��ȡ������
		size_t GetTriangle(vector<Triangle3>& triangles, const Rect3& region) const;

		// ��ȡ������(ȥ���ն�)
		size_t GetTriangleByFlag( vector<Triangle3>& triangles, const Rect3& region, BYTE flag) const;

		// ��Ӷ�Ӧ���ӵ����������ε�������
		void AddTri( vector<Triangle3>& triangles, UINT x, UINT y) const;

		// ���ø��Ӵ�С
		void SetGridSize( UINT size=1) { m_gridSize = size; }

		// ����ĳ��߶�
		void  SetHeightAt( UINT x, UINT y, float height);

		// ��ȡ��(����)
		UINT GetWidth() const { return m_tableWidth; }

		// ��ȡ��(����)
		UINT GetHeight() const { return m_tableHeight; }

		// ����AABB��Χ��
		void BuildAABB( Rect3& box, const Transform& trans) const{}

		// ����AABB��Χ����
		void BuildAABBArrayByXY( vector<Rect3>& aabbArrays, const Transform& trans, const Parabola3& parabola, float t0, float t1) const;

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass) { A_ASSERT(false); return Vector3::Zero; }

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Shape>(*this);
			ar & m_version;
			ar & m_gridSize;
			ar & m_tableWidth;
			ar & m_tableHeight;
			ar & m_heightData;
			ar & m_hollowWidth;
			ar & m_hollowHeight;
			ar & m_hollowData;
		}

	private:
		// ����
		UINT TableIdx( UINT x, UINT y) const;

		// �Ƿ�Ϊ�ն�
		BYTE GetFlag( UINT x, UINT y) const;

		// ���������С��ȡ������Χ
		void GetIdxRegion( int& minX, int& maxX, int& minY, int& maxY, const Rect3& region) const;

		// ����
		void Reset();
		
	private:
		int				m_version;			// �汾
		UINT			m_gridSize;			// ���Ӵ�С
		UINT			m_tableWidth;		// ����
		UINT			m_tableHeight;		// ����
		vector<float>	m_heightData;		// ����߶�����

		UINT			m_hollowWidth;		// �οտ��
		UINT			m_hollowHeight;		// �οո߶�
		vector<BYTE>	m_hollowData;		// �ο�����
	};
}