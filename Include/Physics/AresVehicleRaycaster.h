#pragma once

#include <Core/AresMath.h>

namespace Ares
{
	//---------------------------------------
	// VehicleRaycaster 2013-9-6 ����
	//---------------------------------------
	struct VehicleRaycaster
	{
		struct Result
		{
			Vector3		m_hitPointInWorld;
			Vector3		m_hitNormalInWorld;
			float		m_distFraction;

			// ��������
			Result::Result() : m_distFraction( -1.f)
			{}
		};

		// ���߼��
		virtual void* RayCast( const Vector3& from, const Vector3& to, Result& result)=0;
	};
}