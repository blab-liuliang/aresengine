#pragma once

#include <boost/shared_ptr.hpp>
#include "AresElementFormat.h"
#include "AresFrameBuffer.h"

namespace Ares
{
	//--------------------------------------
	// RenderView 2012-3-16  ����
	//--------------------------------------
	class RenderView
	{
	public:
		RenderView() {}
		virtual ~RenderView(){}

		// ��ȡ���
		UINT GetWidth() { return m_width; }

		// ��ȡ�߶� 
		UINT GetHeight() { return m_height; }

		// ��ȡ����(����������View�ɻ�ȡ)
		virtual TexturePtr GetTexture() { return TexturePtr(); }

		// ��FramberBuffer
		virtual void OnBind( FrameBuffer& frameBuffer, UINT attach);

		// ���FrameBuffer
		virtual void OnUnbind( FrameBuffer& frameBuffer, UINT attach);

	public:
		// ������FrameBuffer
		virtual void OnAttachedFrameBuffer( FrameBuffer& frameBuffer, FrameBuffer::Attachment att);

		// ����Framebuffer
		virtual void OnDetachedFrameBuffer( FrameBuffer& frameBuffer, FrameBuffer::Attachment att);

	protected:
		UINT			m_width;	// ��
		UINT			m_height;	// ��
		ElementFormat	m_format;	// ��ʽ
	};

	typedef boost::shared_ptr<RenderView> RenderViewPtr;
}