#ifndef SPIRAL_H
#define SPIRAL_H

#include <Core/AresMath.h>

namespace Ares
{
	//--------------------------------
	// ������ 2013-6-18 ����
	//--------------------------------
	struct Spiral3
	{
		// ���㵱ǰλ��
		static void CalculatePos( Vector3& oResult, const Vector3& centerPos, const Vector3& centerDir, float radius, float angle);
	};
}

#endif