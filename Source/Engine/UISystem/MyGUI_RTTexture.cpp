#include "Engine/UISystem/MyGUI_RTTexture.h"
#include "Engine/AresRoot.h"

namespace MyGUI
{
	// ���캯��
	MyGUIRTTexture::MyGUIRTTexture( TexturePtr texture)
	{
		A_ASSERT( texture);

		m_frame = ARenderDevice->CreateFrameBuffer();
		m_frame->AttachRenderView( FrameBuffer::ATT_Color0,	ARenderDevice->Create2DRenderView( texture, 0, 1, 0));
	}

	// ���캯��
	MyGUIRTTexture::MyGUIRTTexture( FrameBufferPtr frame)
	{
		m_frame = frame;
	}

	// ��������
	MyGUIRTTexture::~MyGUIRTTexture()
	{

	}

	// ����Ϊ��ȾĿ��
	void MyGUIRTTexture::begin()
	{
		m_preFrame = ARenderDevice->GetCurFrameBuffer();

		// ����DepthMapΪ��ǰFrameBuffer
		ARenderDevice->BindFrameBuffer( m_frame);
		m_frame->Clear( ColorRGB::Black, 1.f, 0);
	}

	// ����
	void MyGUIRTTexture::end()
	{
		ARenderDevice->BindFrameBuffer( m_preFrame);
	}

	// ��Ⱦ
	void MyGUIRTTexture::DoRender( Renderable& renderable)
	{
		renderable.Render();
	}
}