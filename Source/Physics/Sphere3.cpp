#include "Physics/Sphere3.h"

namespace Ares
{
	// ���캯��
	Sphere3::Sphere3()
	{

	}

	// ���캯��
	Sphere3::Sphere3( const Vector3& center, float radius)
		: m_center( center)
		, m_radius( radius)
	{}
}