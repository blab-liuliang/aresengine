#pragma once

#include <Core/AresMath.h>

namespace Ares
{
	//-------------------------------------------------------------
	//  ͹������  http://www.eecs.tufts.edu/~mhorn01/comp163/
	//  Randomized Incremental Algorithm 
	//	http://www.eecs.tufts.edu/~mhorn01/comp163/algorithm.html
	//							    2010-12-01
	//-------------------------------------------------------------
	class  CConvexHull3D
	{
	public:
		enum ALGORITM_TYPE
		{
			EM_RANDOMIZED_INCREMENTAL = 0,
		};

		// ���캯��
		CConvexHull3D();

		// ��������
		~CConvexHull3D();

		// ͨ�����㼯����ConvexHull
		bool Build( Vector3* pVertices, size_t iNum, ALGORITM_TYPE a_t=EM_RANDOMIZED_INCREMENTAL);

	private:
		size_t      m_iNumVertex;		// ��������	
		size_t      m_iNumFace;			// ������	
		Vector3*	m_pVertexList;		// �����б�
		size_t*		m_pFaceList;		// ���б�(����һ��)
	};
}