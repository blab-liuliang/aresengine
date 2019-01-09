#pragma once

#include "Engine/Foundation/Ares3DEngine_h.h"
#include "Engine/RenderSystem/AresHDREncode.h"
#include <Core/Graphics/AresTexture.h>

namespace Ares
{
	//--------------------------------------
	// �����˾� cpu 2012-7-18 ����
	//--------------------------------------
	class ARES_EXPORT CpuTextureFilter
	{
	public:
		// ��Ե��䣺��Ҫ���ڽ������ͼcolor bleeding����
		// source      ���༭����
		// ColorRGB	   ����ɫ, ����������ص�
		// extendPixel ���������չ��������
		// isRGBE	   ͼƬ�Ƿ�ΪRGBE8�����ʽ
		static bool EdgePadding( TexturePtr& source, ColorRGB backgroundColor, int extendPixel, bool isRGBE);

		// ��˹ģ��
		static bool GaussianBlur( TexturePtr& source, float radius);

	private:
	};
}