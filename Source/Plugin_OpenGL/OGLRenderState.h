#pragma once

#include <Core/Graphics/AresRenderState.h>

namespace Ares
{
	//----------------------------------
	// OGL��դ��״̬ 2013-4-3 ����
	//----------------------------------
	class OGLRasterizerState : public RasterizerState
	{
	public:
		OGLRasterizerState( const RasterizerStateDesc& desc);

		// ����
		virtual void SetActive();
	};

	//----------------------------------
	// OGL���ģ��״̬ 2013-4-3 ����
	//----------------------------------
	class OGLDepthStencilState : public DepthStencilState
	{
	public:
		OGLDepthStencilState( const DepthStencilStateDesc& desc);

		// ����
		virtual void SetActive( UINT frontStencilRef, UINT backStencilRef);
	};

	//----------------------------------
	// OGL���״̬ 2013-4-3 ����
	//----------------------------------
	class OGLBlendState : public BlendState
	{
	public:
		OGLBlendState( const BlendStateDesc& desc);

		// ����
		virtual void SetActive( const ColorRGB& blendFactor, UINT sampleMask);
	};

	//----------------------------------
	// OpenGL�������״̬ 2013-4-3 ����
	//----------------------------------
	class OGLSamplerState : public SamplerState
	{
	public:
		explicit OGLSamplerState( const SamplerStateDesc& desc);
	};
}