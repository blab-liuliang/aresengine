#pragma once

#include "OGLPlatform.h"
#include <Core/Graphics/AresElementFormat.h>

namespace Ares
{
	//--------------------------------------
	// OpenGL ӳ�� 2013-4-7 ����
	//--------------------------------------
	class OGLMapping
	{
	public:
		// ӳ���ʽ
		static void MappingFormat( GLint& internalFormat, GLenum& glformat, GLenum& gltype, ElementFormat ef);

		// ӳ�䶥���ʽ
		static void MappingVertexFormat( GLenum& gltype, GLboolean& normalized, ElementFormat ef);

		// ӳ��
		static void Mapping( GLenum& primType, UINT& primCount, const RenderLayout& layout);

		// ӳ��Attribute
		static void Mapping( VertexElementUsage& usage, BYTE& usageIdx, const char* attributeName);
	};
}