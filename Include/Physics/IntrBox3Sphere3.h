#pragma once

#include "Physics/Shapes.h"

namespace Ares
{
	//----------------------------------------
	// IntrBox3Sphere3	2012-9-7 ����
	//----------------------------------------
	struct IntrBox3Sphere3
	{
		Vector3			m_intrPoint;	// �ཻ��

		const Box3&		m_box3;			// ����
		const Sphere3&	m_sphere3;		// ��

		// constructor
		IntrBox3Sphere3( const Box3& box3, const Sphere3& sphere);

		// test intersection query
		bool Test();
	};
}