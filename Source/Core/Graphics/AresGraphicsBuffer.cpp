#include "Core/Graphics/AresGraphicsBuffer.h"

namespace Ares
{
	// ���캯��
	GraphicsBuffer::GraphicsBuffer( BufferUsage usage, UINT accessHint)
		: m_usage( usage),
		  m_accessHint( accessHint),
		  m_sizeInByte( 0)
	{

	}

	// ��������
	GraphicsBuffer::~GraphicsBuffer()
	{

	}
}