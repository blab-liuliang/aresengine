#pragma once

#include <string>
#include "MyGUI_ITexture.h"
#include <Core/Graphics/AresTexture.h>

using namespace Ares;

namespace MyGUI
{
	//--------------------------------
	// UI������ 2012-10-16 ����
	//--------------------------------
	class MyGUITexture : public ITexture
	{
	public:
		// ���캯�� 
		MyGUITexture( const std::string& name);

		// ��������
		~MyGUITexture();

		// ��ȡ����
		virtual const std::string& getName() const { return m_name; }

		// �ֶ�����
		virtual void createManual( int width, int height, TextureUsage usage, PixelFormat format);

		// ��Դ����
		virtual void loadFromFile( const std::string& fileName);

		// ����
		virtual void destroy() { m_texture = TexturePtr(); }

		// ����
		virtual void saveToFile( const std::string& fileName) {}

		// ��ȡ��
		virtual int getWidth() { return m_texture->GetWidth(0); }

		// ��ȡ��
		virtual int getHeight() { return m_texture->GetHeight(0); }

		// ��ȡTexture
		virtual TexturePtr GetTexture() { return m_texture; }

		// ��ȡ��ȾĿ��
		virtual IRenderTarget* getRenderTarget();

	private:
		std::string		m_name;			// ����
		TexturePtr		m_texture;		// ����
		IRenderTarget*	m_renderTarget;
	};
}