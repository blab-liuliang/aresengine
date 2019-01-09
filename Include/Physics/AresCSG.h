#ifndef CSG_BOX3_TRIANGLE3_H
#define CSG_BOX3_TRIANGLE3_H

#include "Box3.h"
#include "Triangle3.h"
#include "IntrBox3Triangle3.h"

namespace Ares
{
	//--------------------------------------
	// CSGBox3Triangle3 2013-7-3 ����
	//--------------------------------------
	struct CSGBox3Triangle3
	{
		// ��
		static void Intersection( vector<Vector3>& vertexs, vector<WORD>& indices, const Box3& box3, const Triangle3& triangle);

		// ��

		// ��
	};

	//--------------------------------------
	// CSGAABB3Frustum3 2013-8-12 ����
	//--------------------------------------
	struct CSGAABB3Frustum3
	{
		// ��
		static void Intersection();
	};
}

#endif