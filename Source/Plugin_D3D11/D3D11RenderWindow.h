#pragma once

#include <Core/AresCore.h>
#include "D3D11FrameBuffer.h"
#include "D3D11Typedefs.h"
#include "D3D11Adapter.h"

using namespace std;
using namespace boost;

namespace Ares
{
	//---------------------------------------------
	// D3D11RenderWindow 2012-3-3 ����
	//---------------------------------------------
	class D3D11RenderDevice;
	class D3D11RenderWindow : public RenderWindow
	{
	public:
		// constructor
		D3D11RenderWindow( IDXGIFactory1Ptr giFactory, D3D11Adapter* adapter, const RenderSettings& settings);

		// ��ȡ����
		virtual const char* GetType() { return "D3D11RenderWindow"; }

		// ��ȡFrameBuffer
		virtual FrameBufferPtr GetFrameBuffer() { return m_frameBuffer; }

		// ���Ĵ��ڴ�С
		virtual void Resize( size_t width, size_t height);

		// �����Ƿ�ȫ��
		virtual void SetFullScreen( bool fullScreen);

		// ��ȡ������������
		virtual TexturePtr GetBackbufferTextureCopy();

		// Present the information rendered to the back buffer to the front buffer(the screen)
		virtual void SwapBuffers();

	private:
		// ����SurfacePtrs
		void UpdateSurfacePtrs();

		// ����FrameBuffer
		void ResetFrameBuffer();

	private:
		string						m_title;				// ����
		bool						m_external;				// �Ƿ��ⲿ����
		UINT						m_syncIntervel;			// ͬ�����

		bool						m_ready;				// Is ready ie. available for update
		bool						m_closed;				// is closed

		D3D11FrameBufferPtr			m_frameBuffer;			// default framebuffer

		D3D11Adapter*				m_adapter;				// ��ʹ�õ�������
		IDXGIFactory1Ptr			m_giFactory;			// Pointer to the 3D device specific for this window
		ID3D11DevicePtr				m_d3dDevice;			// D3D11Device
		ID3D11DeviceContextPtr		m_immediateContex;		// immediate context
		DXGI_SWAP_CHAIN_DESC		m_swapChainDesc;		// 
		IDXGISwapChainPtr			m_swapChain;			// swap chain pointer
		bool						m_mainWnd;				// mainWnd

		ID3D11Texture2DPtr			m_backbuffer;			// ��������
		ID3D11Texture2DPtr			m_depthStencil;			// ��Ȼ���
		ID3D11RenderTargetViewPtr	m_renderTargetView;		// ����RenderTargetView
		ID3D11DepthStencilViewPtr	m_depthStencilView;		// ���View
		D3D11Texture2DPtr			m_backBufferTexture;	// ������������
		D3D11Texture2DPtr			m_backBufferTextureCopy;// ��������������

		DXGI_FORMAT					m_backBufferFormat;		// ���������ʽ
		DXGI_FORMAT					m_depthStencilFormat;	// ���ģ�建���ʽ

#ifdef ARES_PLATFORM_WINDOWS
		HWND						m_hwnd;					// ���ھ��
#endif
	};
}