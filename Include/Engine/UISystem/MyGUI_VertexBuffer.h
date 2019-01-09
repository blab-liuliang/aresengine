#pragma once

#include "MyGUI_IVertexBuffer.h"

using namespace Ares;

namespace MyGUI
{
	//-------------------------------------
	// MyGUIBuffer 2012-10-16 ����
	//-------------------------------------
	class MyGUIBuffer : public IVertexBuffer
	{
	public:
		MyGUIBuffer();
		~MyGUIBuffer();

		// ���ö�������
		virtual void setVertexCount(size_t _value);

		// ��ȡ��������
		virtual size_t getVertexCount();

		// ��ȡBuffer
		virtual GraphicBufferPtr GetBuffer() { return m_buffer; }

		// ��ȡRenderLayout
		virtual RenderLayoutPtr& GetLayout() { return m_layout; }

	private:
		int					m_vertexNum;		// ������
		RenderLayoutPtr		m_layout;			// ������
		GraphicBufferPtr	m_buffer;			// ������
	};
}