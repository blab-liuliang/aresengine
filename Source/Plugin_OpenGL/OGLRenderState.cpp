#include "OGLRenderState.h"

namespace Ares
{
	// ���캯��
	OGLRasterizerState::OGLRasterizerState( const RasterizerStateDesc& desc)
		: RasterizerState( desc)
	{

	}

	// ����
	void OGLRasterizerState::SetActive()
	{

	}

	// ���캯��
	OGLDepthStencilState::OGLDepthStencilState( const DepthStencilStateDesc& desc)
		: DepthStencilState( desc)
	{

	}

	// ����
	void OGLDepthStencilState::SetActive( UINT frontStencilRef, UINT backStencilRef)
	{

	}

	// ���캯��
	OGLBlendState::OGLBlendState( const BlendStateDesc& desc)
		: BlendState( desc)
	{

	}

	// ����
	void OGLBlendState::SetActive( const ColorRGB& blendFactor, UINT sampleMask)
	{

	}

	// ���캯��
	OGLSamplerState::OGLSamplerState( const SamplerStateDesc& desc)
		: SamplerState( desc)
	{

	}
}