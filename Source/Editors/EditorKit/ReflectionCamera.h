#pragma once

#include "BaseCamera.h"

namespace Ares
{
	//--------------------------------
	// ���������   2010-10-12  ����
	//--------------------------------
	class CReflectionCamera : public Camera
	{
	public:
		// ��ȡ�۲�ͶӰ����
		virtual Matrix44&  GetViewProj();

		// ��ȡ�������պо���
		virtual Matrix44&  GetSkyViewProj();
	};
}