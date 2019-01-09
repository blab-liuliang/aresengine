#pragma once

#include "Core/AresPlatform.h"
#include "AresFrameBuffer.h"

namespace Ares
{
	//-----------------------------------------------------------------------
	// IRenderWindow 2011-11-14 ����
	// ��Ҫ�ο� Ogre
	//		Instances are created and communicated with by the 
	// render system. although client programs can get refrence
	// to it from the render system, if required for resizing or
	// moving.			
	//											auther: Steven Streeting
	//-----------------------------------------------------------------------
	class RenderWindow
	{
	public:
		// ��ȡ����
		virtual const char* GetType()=0;

		// ��ȡ��
		UINT	GetWidth() const { return m_width; }

		// ��ȡ��
		UINT	GetHeight() const { return m_height; }

		// �Ƿ�ȫ��
		bool  IsFullScreen() { return m_isFullScreeen; }

		// ���Ĵ��ڴ�С
		virtual void Resize( size_t width, size_t height)=0;

		// �����Ƿ�ȫ��
		virtual void SetFullScreen( bool fullScreen)=0;

		// ��ȡFrameBuffer
		virtual FrameBufferPtr GetFrameBuffer()=0;

		// ��ȡ������������
		virtual TexturePtr GetBackbufferTextureCopy()=0;

		// Present the information rendered to the back buffer 
		// to the front buffer(the screen), Refresh screen.
		virtual void SwapBuffers() {}

	protected:
		UINT			m_left;			
		UINT			m_top;				// ����λ��
		UINT			m_width;			// ��
		UINT			m_height;			// ��
		bool			m_isFullScreeen;	// �Ƿ�ȫ��
	};
}