#include "Engine/UISystem/MyGUI_Texture.h"
#include "Engine/UISystem/MyGUI_RTTexture.h"
#include "Engine/AresRoot.h"

namespace MyGUI
{
	// ���캯�� 
	MyGUITexture::MyGUITexture( const std::string& name)
		: m_renderTarget( NULL)
	{
	}

	// ��������
	MyGUITexture::~MyGUITexture()
	{
	}

	// �ֶ�����
	void MyGUITexture::createManual( int width, int height, TextureUsage usage, PixelFormat format)
	{
		ElementFormat elementFormat = EF_UnKnown;
		if( format==PixelFormat::L8)
			elementFormat = EF_A8;
		else if( format==PixelFormat::L8A8)
			elementFormat = EF_GR8;
		else if( format==PixelFormat::R8G8B8)
			elementFormat = EF_BGR8;
		else if( format==PixelFormat::R8G8B8A8)
			elementFormat = EF_ARGB8;

		m_texture = ARenderDevice->CreateTexture2D( width, height, 1, 1, elementFormat, 1, 0, EAH_CPUWrite | EAH_GPURead, NULL);
	}

	// ��Դ����
	void MyGUITexture::loadFromFile( const std::string& fileName)
	{
		m_name = fileName;

		m_texture = AResSystem.SyncLoadDDS( fileName.c_str(), EAH_GPURead | EAH_Immutable);
	}

	// ��ȡ��ȾĿ��
	IRenderTarget* MyGUITexture::getRenderTarget()
	{
		if( m_texture)
		{
			m_renderTarget = new MyGUIRTTexture( m_texture);
		}

		return m_renderTarget;
	}
}