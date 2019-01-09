#pragma once

#include <Core/Graphics/AresRenderWindow.h>
#include "OGLTypedefs.h"
#include "OGLFrameBuffer.h"

namespace Ares
{
	//-----------------------------------
	// OGLESRenderWindow 2013-02-05 ����
	//-----------------------------------
	class OGLRenderWindow : public RenderWindow
	{
	public:
		OGLRenderWindow( const RenderSettings& settings);

		// ��ȡ����
		virtual const char* GetType() { return "OGLRenderWindow"; }

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
		string						m_title;			// ����
		ElementFormat				m_colorFormat;		// color format
		ElementFormat				m_depthStencilFormat;	// depth stencil format
		UINT						m_syncIntervel;		// ͬ�����
		OGLFrameBufferPtr			m_frameBuffer;		// Default FrameBuffer

		UINT32						m_colorBits;		// ��ɫλ��

#ifdef ARES_PLATFORM_WINDOWS
		HWND						m_hwnd;				// ���ھ��
		HGLRC						m_hRC;
		HDC							m_hDC;				// what?
#endif
	};
}