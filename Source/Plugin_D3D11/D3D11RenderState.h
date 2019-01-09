#pragma once

#include "D3D11Typedefs.h"
#include <Core/Graphics/AresRenderState.h>

namespace Ares
{
	//----------------------------------------
	// D3D11��դ��״̬ 2012-3-30 ����
	//----------------------------------------
	class D3D11RasterizerState : public RasterizerState
	{
	public:
		// ���캯��
		D3D11RasterizerState( const RasterizerStateDesc& desc);

		// ����
		virtual void SetActive();

	private:
		ID3D11RasterizerStatePtr	m_d3d11RasterizerState;
	};

	//----------------------------------------
	// D3D11���ģ��״̬ 2012-3-30 ����
	//----------------------------------------
	class D3D11DepthStencilState : public DepthStencilState
	{
	public:
		// ���캯��
		D3D11DepthStencilState( const DepthStencilStateDesc& desc);

		// ����
		virtual void SetActive( UINT frontStencilRef, UINT backStencilRef);

	private:
		ID3D11DepthStencilStatePtr	m_d3d11DepthStencilState;
	};

	//----------------------------------------
	// D3D11���״̬ 2012-3-31 ����
	//----------------------------------------
	class D3D11BlendState : public BlendState
	{
	public:
		// ���캯��
		D3D11BlendState( const BlendStateDesc& desc);

		// ����
		virtual void SetActive( const ColorRGB& blendFactor, UINT sampleMask);

	private:
		ID3D11BlendStatePtr	m_d3d11BlendState;
	};

	//----------------------------------------
	// D3D11�������״̬ 2012-3-31 ����
	//----------------------------------------
	class D3D11SamplerState : public SamplerState
	{
	public:
		// ���캯��
		explicit D3D11SamplerState( const SamplerStateDesc& desc);

		// ��ȡD3D11SamplerState
		ID3D11SamplerStatePtr& GetD3D11SamperState() { return m_d3d11SamplerState; }

	private:
		ID3D11SamplerStatePtr		m_d3d11SamplerState;
	};
}