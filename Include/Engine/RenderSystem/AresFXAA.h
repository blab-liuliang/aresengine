#ifndef ARES_FXAA_H
#define ARES_FXAA_H

#include "AresFrameFilter.h"

namespace Ares
{
	//------------------------------------
	// FXAA 2013-7-13 ����
	//------------------------------------
	class FXAA : public FrameFilter
	{
	public:
		// ���캯��
		FXAA( Scene& scene);

		// ���ò���
		void Set( FXAALevel level);

		// ����Դ����
		bool SetSrcTexture( TexturePtr& src);

	private:
		ShaderParamPtr			m_srcTexture;
	};
	typedef s_ptr<FXAA> FXAAPtr;
}

#endif