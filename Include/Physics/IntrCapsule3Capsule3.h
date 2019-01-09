#pragma once

#include "Physics/Shapes.h"
#include "DistSegment3Segment3.h"

namespace Ares
{
	//----------------------------------------
	// IntrCapsule3Capsule3	2012-12-18 ����
	//----------------------------------------
	struct IntrCapsule3Capsule3
	{
		const Capsule3&	m_capsule0;				// ����0
		const Capsule3&	m_capsule1;				// ����1

		// constructor
		IntrCapsule3Capsule3( const Capsule3& capsule0, const Capsule3& capsule1);

		// test intersection query
		bool Test();
	};
}