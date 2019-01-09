#pragma once

#include <Core/Graphics/AresRenderWindow.h>
#include "OGLESTypedefs.h"
#include "OGLESPlatform.h"
#include "OGLESFrameBuffer.h"

namespace Ares
{
	//-----------------------------------
	// OGLESRenderWindow 2013-02-05 ����
	//-----------------------------------
	class OGLESRenderWindow : public RenderWindow
	{
	public:
		OGLESRenderWindow( const RenderSettings& settings);

		// ��ȡ����
		virtual const char* GetType() { return "OGLESRenderWindow"; }

		// ���Ĵ��ڴ�С
		virtual void Resize( size_t width, size_t height);

		// �����Ƿ�ȫ��
		virtual void SetFullScreen( bool fullScreen);

		// ��ȡFrameBuffer
		virtual FrameBufferPtr GetFrameBuffer() { return m_frameBuffer; }

		// ��ȡ������������
		virtual TexturePtr GetBackbufferTextureCopy() { return TexturePtr(); }

		// Present the information rendered to the back buffer to the front buffer(the screen)
		virtual void SwapBuffers();

	private:
		// ����SurfacePtrs
		void UpdateSurfacePtrs();

		// ����
		void ResetFrameBuffer();

	private:
#ifdef ARES_PLATFORM_WINDOWS
		HWND						m_hwnd;				// ���ھ��
		HDC							m_hDC;				// 

		EGLDisplay					m_display;
		EGLSurface					m_surface;
		EGLConfig					m_config;
		EGLContext					m_context;
#endif
    
		string						m_title;			// ����
		ElementFormat				m_colorFormat;		// color format
		ElementFormat				m_depthStencilFormat;	// depth stencil format
		UINT						m_syncIntervel;		// ͬ�����
		OGLESFrameBufferPtr			m_frameBuffer;		// Default FrameBuffer

		UINT32						m_colorBits;		// ��ɫλ��
		string						m_description;		// ������Ϣ
	};
}