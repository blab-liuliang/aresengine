#include "OGLRenderView.h"

namespace Ares
{
	// ���캯��
	OGLTexture2DRenderView::OGLTexture2DRenderView( TexturePtr& texture, int arrayIndex, int level)
	{

	}

	// ���캯��
	OGLScreenRenderTargetRenderView::OGLScreenRenderTargetRenderView( UINT width, UINT height, ElementFormat ef)
	{
		m_width  = width;
		m_height = height;
		m_format = ef;
	}

	// ���캯��
	OGLScreenDepthStencilRenderView::OGLScreenDepthStencilRenderView( UINT width, UINT height, ElementFormat ef)
	{

	}

	// ���캯��
	OGLDepthStencilRenderView::OGLDepthStencilRenderView( UINT width, UINT height, ElementFormat format, UINT sampleCount, UINT sampleQuality)
	{

	}
}