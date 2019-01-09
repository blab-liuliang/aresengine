#include "OGLESRenderState.h"

namespace Ares
{
	// ���캯��
	OGLESRasterizerState::OGLESRasterizerState( const RasterizerStateDesc& desc)
		: RasterizerState( desc)
	{

	}

	// ����
	void OGLESRasterizerState::SetActive()
	{

	}

	// ���캯��
	OGLESDepthStencilState::OGLESDepthStencilState( const DepthStencilStateDesc& desc)
		: DepthStencilState( desc)
	{

	}

	// ����
	void OGLESDepthStencilState::SetActive( UINT frontStencilRef, UINT backStencilRef)
	{

	}

	// ���캯��
	OGLESBlendState::OGLESBlendState( const BlendStateDesc& desc)
		: BlendState( desc)
	{

	}

	// ����
	void OGLESBlendState::SetActive( const ColorRGB& blendFactor, UINT sampleMask)
	{

	}

	// ���캯��
	OGLESSamplerState::OGLESSamplerState( const SamplerStateDesc& desc)
		: SamplerState( desc)
	{

	}
}