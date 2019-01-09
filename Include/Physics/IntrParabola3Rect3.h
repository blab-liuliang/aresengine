#pragma once

#include "Physics/Shapes.h"

namespace Ares
{
	//--------------------------------------------------------
	// intersection test between Parabola3 and Rect3
	//					2013-3-14  ����
	struct IntrParabola3Rect3
	{
		const Rect3&	 m_rect;			// AABB��Χ��
		const Parabola3& m_curve;			// ��������

		// construction
		IntrParabola3Rect3( const Parabola3& curve, const Rect3& rect3);

		// test intersection query
		bool Test();
	};
}