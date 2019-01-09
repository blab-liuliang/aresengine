#pragma once

#include <vector>
#include <Core/AresMath.h>

namespace Ares
{
	namespace Build
	{
		//--------------------------------------------------
		// ͨ�����ι���TriangleMesh 2011-10-21  ����
		//
		size_t BuildTriangle3FromRectangle( std::vector<Vector3>& out, const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, float maxEdgeLength=0.f);
	}
}