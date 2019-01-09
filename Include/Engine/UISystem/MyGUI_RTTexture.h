#pragma once

#include "MyGUI_IRenderTarget.h"
#include <Core/Graphics/AresFrameBuffer.h>

using namespace Ares;

namespace MyGUI
{
	//---------------------------------------
	// ��ȾĿ������ 2012-10-16 ����
	//---------------------------------------
	class MyGUIRTTexture : public IRenderTarget
	{
	public:
		// ���캯��
		MyGUIRTTexture( TexturePtr texture);

		// ���캯��
		MyGUIRTTexture( FrameBufferPtr frame);

		// ��������
		~MyGUIRTTexture();

		// ����Ϊ��ȾĿ��
		virtual void begin();

		// ����
		virtual void end();

		// ��Ⱦ
		virtual void DoRender( Renderable& renderable);

		// ����������Ϣ
		virtual const RenderTargetInfo& getInfo() { return m_info; }

	private:
		RenderTargetInfo	m_info;
		FrameBufferPtr		m_frame;		// FrameBuffer
		
		FrameBufferPtr		m_preFrame;		// ԭFrameBuffer
	};
}