#pragma once

#include "AresFrameFilter.h"

namespace Ares
{
	//------------------------------------
	// EdgePadding 2012-8-8 ����
	//------------------------------------
	class GrayscaleFilter : public FrameFilter
	{
	public:
		// ���캯��
		GrayscaleFilter( Scene& scene);

		// ����Դ����
		bool SetSrcTexture( TexturePtr& src);
	};
	typedef s_ptr<GrayscaleFilter> GrayScalePtr;
}