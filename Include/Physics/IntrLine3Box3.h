#pragma once

#include "Physics/Box3.h"
#include "Physics/Line3.h"

namespace Ares
{
	//-----------------------------------
	// IntrLine3Box3 2012-12-6 ����
	//-----------------------------------
	struct IntrLine3Box3
	{
		const Line3&	m_line;
		const Box3&		m_box;

		int				m_quantity;
		Vector3			m_points[2];

		// ���캯�� 
		IntrLine3Box3( const Line3& line, const Box3& box);

		// �ཻ����
		bool Test();
	};
}