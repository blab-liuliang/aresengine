#pragma once

#include <Core/Graphics/AresRenderState.h>

namespace Ares
{
	//----------------------------------
	// OGL��դ��״̬ 2013-4-3 ����
	//----------------------------------
	class OGLESRasterizerState : public RasterizerState
	{
	public:
		OGLESRasterizerState( const RasterizerStateDesc& desc);

		// ����
		virtual void SetActive();
	};

	//----------------------------------
	// OGL���ģ��״̬ 2013-4-3 ����
	//----------------------------------
	class OGLESDepthStencilState : public DepthStencilState
	{
	public:
		OGLESDepthStencilState( const DepthStencilStateDesc& desc);

		// ����
		virtual void SetActive( UINT frontStencilRef, UINT backStencilRef);
	};

	//----------------------------------
	// OGL���״̬ 2013-4-3 ����
	//----------------------------------
	class OGLESBlendState : public BlendState
	{
	public:
		OGLESBlendState( const BlendStateDesc& desc);

		// ����
		virtual void SetActive( const ColorRGB& blendFactor, UINT sampleMask);
	};

	//----------------------------------
	// OpenGL�������״̬ 2013-4-3 ����
	//----------------------------------
	class OGLESSamplerState : public SamplerState
	{
	public:
		explicit OGLESSamplerState( const SamplerStateDesc& desc);
	};
}