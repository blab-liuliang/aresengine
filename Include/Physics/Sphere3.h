#pragma once

#include <Core/AresMath.h>

namespace Ares
{
	//---------------------------------------
	// Sphere3 2012-9-7 ����
	//---------------------------------------
	struct Sphere3
	{
		Vector3		m_center;		// ���ĵ�
		float		m_radius;		// �뾶

		// constructor
		Sphere3();

		// initialized
		Sphere3( const Vector3& center, float radius);

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass) { A_ASSERT(false); return Vector3::Zero; }
	};
}