#pragma once

namespace Ares
{
	// ��������ýṹ��
	struct CameraSettings
	{
		float m_farPlane;		// Զƽ��
		float m_speed;			// �ƶ��ٶ�

		// ���캯��
		CameraSettings()
			: m_farPlane( 180.f)
			, m_speed( 3.f)
		{}
	};
}