#pragma once

#include "Physics/Shapes.h"

namespace Ares
{
	//--------------------------------------------------------
	// intersection test between ProjectileMotion3 and Plane3
	//					2013-3-14  ����
	struct IntrParabola3Plane3
	{
		float					m_intrTime[2];		// ����ʹ��
		Vector3					m_intrPoints[2];
		UINT					m_numIntrPoint;

		const Plane3&			 m_plane;			// ƽ��
		const Parabola3& m_curve;			// ��������

		// construction
		IntrParabola3Plane3( const Parabola3& curve, const Plane3& plane);

		// test intersection query
		bool Test();
	};
}