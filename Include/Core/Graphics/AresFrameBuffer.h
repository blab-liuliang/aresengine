#pragma once

#include "Core/AresMath.h"
#include "AresViewPort.h"
#include "AresRenderAPITypedefs.h"

using namespace std;

namespace Ares
{
	// ������
	enum ClearBufferMask
	{
		CBM_Depth  = 1ul << 0,		// ������
		CBM_Stencil= 1ul << 1,		// ���ģ��
		CBM_Color  = 1ul << 2,		// �����ɫ
	};

	//------------------------------
	// FrameBuffer 2012-3-3 ����
	//------------------------------
	class RenderDevice;
	class CORE_EXPORT FrameBuffer
	{
	public:
		// ����
		enum Attachment
		{
			ATT_Color0 = 0,
			ATT_Color1,
			ATT_Color2,
			ATT_Color3,
			ATT_Color4,
			ATT_Color5,
			ATT_Color6,
			ATT_Color7,
			ATT_DepthStencil
		};

	public:
		FrameBuffer( RenderDevice* renderDevice);
		virtual ~FrameBuffer();

		// rendertarget's left point
		UINT GetLeft() const { return m_left; }

		// rendertarget's top point
		UINT GetTop() const { return m_top; }

		// render target's width
		UINT GetWidth() const { return m_width; }

		// render target's height
		UINT GetHeight() const { return m_height; }

		// get viewport
		const ViewPort& GetViewport() const { return m_viewPort; }

		// set viewport
		void SetViewport( const ViewPort& viewPort) { m_viewPort = viewPort; }

		// set active
		void SetActive( bool active) { m_active = active; }

		// Is views dirty
		bool IsDirty() const { return m_viewsDirty; }

		// Attach RenderView
		virtual void AttachRenderView( Attachment att, const RenderViewPtr& renderView);

		// Detach RenderView
		virtual void DetachRenderView( Attachment att);

		// Clear
		virtual void Clear( const ColorRGB& color, float depth, UINT stencil, UINT flags=CBM_Depth|CBM_Stencil|CBM_Color)=0;

		// Clear
		virtual void ClearMRTColor( const ColorRGB& color, Attachment attachment)=0;

		// GetRenderView
		RenderViewPtr GetRenderView( Attachment att);

	public:
		// ��
		virtual void Bind();

		// ���
		virtual void Unbind();

	protected:
		UINT					m_left;			
		UINT					m_top;			// ����λ��
		UINT					m_width;		// ��
		UINT					m_height;		// ��
		BOOL					m_active;		// Is active

		ViewPort				m_viewPort;		// �ӿ�
		bool					m_viewsDirty;	// views dirty
		RenderViewPtr			m_dsView;		// DepthstencilRenderview
		vector<RenderViewPtr>	m_clrViews;		// ���views
		RenderDevice*			m_renderDevice; // ��Ⱦ�豸
	};
}