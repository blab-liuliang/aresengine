#pragma once

#include <map>
#include "OGLPlatform.h"
#include <Core/Graphics/AresRenderMethod.h>
#include "OGLShaderVariable.h"

using namespace std;

namespace Ares
{
	//------------------------------------
	// OGLESRenderMethod 2013-4-3 ����
	//------------------------------------
	class OGLRenderMethod : public RenderMethod
	{
	public:
		OGLRenderMethod();
		virtual ~OGLRenderMethod();

		// ���� *.hlsl
		virtual bool Load( const char* fileName, const ShaderMacros& macros);

		// ���ڴ����
		virtual bool LoadFromMemory( const void* code, size_t length);

		// ��
		virtual void Bind();

		// Ӧ�ò���
		virtual void SetParams(const RenderMaterial& mat);

		// ��ȡAttributeLocation
		GLint GetAttributeLocation( VertexElementUsage usage, BYTE usageIndex) const;

	private:
		// ����
		GLuint CompileToBytecode( const void* pSrcData, size_t srcDataSize, ShaderType type);

		// ��������
		void ParseParameters();

		// ����״̬
		void ParseStates();

		// ��ӿ�����ӱ���
		void AddVariable( const char* name, ShaderParamType type, ShaderParamPtr& defaultValue=MakeShaderParam());

	private:
		GLuint				m_programHandle;
		GLuint				m_vertexShader;
		GLuint				m_fragmentShader;

		vector<GLSLVariablePtr>						m_varDesc;				// ������Ϣ
		map<pair<VertexElementUsage, BYTE>, GLint>	m_attributeLocations;	
	};
}