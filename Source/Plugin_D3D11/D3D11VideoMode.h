#pragma once

#include <d3d11.h>
#include <Core/AresPlatform.h>

namespace Ares
{
	//--------------------------------------------
	// ��ʾģʽ	2012-02-11 ����
	//--------------------------------------------
	class D3D11VideoMode
	{
	public:
		// ���캯��
		D3D11VideoMode();

		// ���캯��
		D3D11VideoMode( UINT width, UINT height, DXGI_FORMAT format);

	public:
		// ��ȡ���
		UINT GetWidth() const { return m_width; }

		// ��ȡ�߶� 
		UINT GetHeight() const { return m_height; }

		// ��ȡ��ʽ
		DXGI_FORMAT GetFormat() const { return m_format; }

	private:
		UINT		m_width;		// ��
		UINT		m_height;		// ��
		DXGI_FORMAT m_format;		// ��ʽ
	};

	// ���ز����� "<"
	BOOL operator < ( const D3D11VideoMode& first, const D3D11VideoMode& second);

	// ���ز����� "=="
	BOOL operator == ( const D3D11VideoMode& first, const D3D11VideoMode& second);
}