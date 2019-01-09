#pragma once

#include <vector>
#include <Core/AresMath.h>

using namespace std;

namespace Ares
{
	//-------------------------------------------------------------
	//  2ά͹�� (Ĭ��˳ʱ��) 
	//  <<���㼸��.�㷨��Ӧ��.�ڶ���>> chapter 1
	//							    2011-01-21
	//-------------------------------------------------------------
	class  ConvexHull2
	{
	public:
		ConvexHull2();
		~ConvexHull2();

		// ͨ�����㼯����ConvexHull
		bool Build( vector<Vector2>& vertices);

		// �Ƿ����ĳ��
		bool IsContain( const Vector2& vertex);

	private:
		vector<Vector2>		m_vertices;		// ˳ʱ���ŷ�
	};
}