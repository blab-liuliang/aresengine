#pragma once

#include "D3D11Typedefs.h"
#include <Core/Graphics/AresFrameBuffer.h>

namespace Ares
{
	//---------------------------------------------
	// D3D11FrameBuffer	2012-3-3 ����
	//---------------------------------------------
	class D3D11FrameBuffer : public FrameBuffer
	{
	public:
		D3D11FrameBuffer( RenderDevice* device);
		virtual ~D3D11FrameBuffer();

		// ��ȡRenderTargetView
		ID3D11RenderTargetViewPtr GetD3D11RenderTargetView( UINT i) const;

		// ��ȡ���ģ��View
		ID3D11DepthStencilViewPtr GetD3D11DepthStencilView() const;

		// Clear
		virtual void Clear( const ColorRGB& color, float depth, UINT stencil, UINT flags=CBM_Depth|CBM_Stencil|CBM_Color);

		// Clear
		virtual void ClearMRTColor( const ColorRGB& color, Attachment attachment);

		// ��
		virtual void Bind();

		// ���
		virtual void Unbind();

	private:
		D3D11_VIEWPORT	m_d3dViewPort;			// d3d11 ViewPort
	};
}