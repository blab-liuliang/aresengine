#pragma once

#include "D3D11Typedefs.h"
#include <Core/Graphics/AresRenderView.h>

namespace Ares
{
	//---------------------------------------
	// D3D11RenderView	2012-3-19 ����
	//---------------------------------------
	class D3D11RenderView : public RenderView
	{
	public:
		D3D11RenderView();
		virtual ~D3D11RenderView();

	protected:
		ID3D11DevicePtr			m_d3dDevice;
		ID3D11DeviceContextPtr	m_d3dImmCtx;
	};

	//-------------------------------------------
	// D3D11RenderTargetRenderView 2012-3-19 ����
	//-------------------------------------------
	class D3D11RenderTargetRenderView : public D3D11RenderView
	{
	public:
		D3D11RenderTargetRenderView( TexturePtr texture, int firstArrayIndex, int arraySize, int level);
		D3D11RenderTargetRenderView( const ID3D11RenderTargetViewPtr& view, UINT width, UINT height, ElementFormat format);
		virtual ~D3D11RenderTargetRenderView() {}

		// ������FrameBuffer
		virtual void OnAttachedFrameBuffer( FrameBuffer& frameBuffer, FrameBuffer::Attachment att);

		// ��ȡD3D11RenderTargetView
		const ID3D11RenderTargetViewPtr& GetD3DRenderTargetView() const { return m_rtView; }

		// ��ȡ����(����������View�ɻ�ȡ)
		virtual TexturePtr GetTexture() { return m_texture; }

	public:
		// Get RTSrc(what? fuck)
		void* GetRTSrc() { return m_rtSrc; }

		//Get RTFirstSubRes
		UINT GetRTFirstSubRes() const { return m_rtFirstSubres; }

		// ��ȡ����
		UINT GetRTNumSubRes() const { return m_rtNumSubres; }

	private:
		TexturePtr					m_texture;
		ID3D11RenderTargetViewPtr	m_rtView;
		void*						m_rtSrc;
		UINT						m_rtFirstSubres;
		UINT						m_rtNumSubres;
	};
	
	typedef boost::shared_ptr<D3D11RenderTargetRenderView> D3D11RenderTargetRenderViewPtr;

	//-------------------------------------------
	// D3D11DepthStencilRenderView 2012-3-19 ����
	//-------------------------------------------
	class D3D11DepthStencilRenderView : public D3D11RenderView
	{
	public:
		D3D11DepthStencilRenderView( const ID3D11DepthStencilViewPtr& view, UINT width, UINT height, ElementFormat format);
		D3D11DepthStencilRenderView( UINT width, UINT height, ElementFormat format, UINT sampleCount, UINT sampleQuality);
		D3D11DepthStencilRenderView( TexturePtr& texture1d2dCube, int firstArrayIndex, int arraySize, int level);
		virtual ~D3D11DepthStencilRenderView() {}

		// ������FrameBuffer
		virtual void OnAttachedFrameBuffer( FrameBuffer& frameBuffer, FrameBuffer::Attachment att);

		// ��ȡ����(����������View�ɻ�ȡ)
		virtual TexturePtr GetTexture() { return m_texture; }
	
	public:
		// Get RTSrc(what? fuck)
		void* GetRTSrc() { return m_rtSrc; }

		//Get RTFirstSubRes
		UINT GetRTFirstSubRes() const { return m_rtFirstSubres; }

		// ��ȡ����
		UINT GetRTNumSubRes() const { return m_rtNumSubres; }

		// ��ȡD3D���ģ��view
		const ID3D11DepthStencilViewPtr& GetD3DDepthStencilView() const { return m_dsView; }

	private:
		UINT						m_rtFirstSubres;
		UINT						m_rtNumSubres;
		void*						m_rtSrc;
		ID3D11DepthStencilViewPtr	m_dsView;		// D3D11DepthStencilView
		TexturePtr					m_texture;		// ����
		ID3D11Texture2DPtr			m_textured3d;	// ����
	};

	typedef boost::shared_ptr<D3D11DepthStencilRenderView> D3D11DepthStencilRenderViewPtr;
}