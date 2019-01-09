#pragma once

#include "D3D11Typedefs.h"
#include "D3D11ShaderDesc.h"
#include <Core/Graphics/AresRenderMethod.h>

using namespace std;

namespace Ares
{
	//-------------------------------------------
	// D3D11RenderMethod 2012-8-29 ����
	//-------------------------------------------
	class D3D11RenderMethod : public RenderMethod
	{
	public:
		D3D11RenderMethod();
		virtual ~D3D11RenderMethod();

		// ���� *.hlsl
		virtual bool Load( const char* fileName, const ShaderMacros& macros);

		// ���ڴ����
		virtual bool LoadFromMemory( const void* code, size_t length);

		// ��
		virtual void Bind();

		// ���
		void Unbind();

		// Ӧ�ò���
		virtual void SetParams(const RenderMaterial& mat);

		// ����ByteCode
		virtual void SaveByteCode( const char* fileName, ShaderType type);

		// ��ȡIASignature
		ID3D10Blob* GetVSCode() { return m_shaderCodes[ST_VertexShader].get(); }

	private:
		// ����
		ID3DBlobPtr CompileToBytecode( const void* pSrcData, size_t srcDataSize, ShaderType type);

		// ���ӻ��
		void AttachByteCode( const ID3DBlobPtr& byteCode, ShaderType type);

		// ��������
		void ParseParameters( const ID3DBlobPtr& byteCode, ShaderType type);

		// ����״̬
		void ParseStates();

		// ˢ�³���Buffer����
		void RefreshBufferData( const RenderMaterial& mat, ShaderType type);

		// ��ӿ�����ӱ���
		void AddVariable( const char* name, ShaderParamType type, ShaderParamPtr& defaultValue=MakeShaderParam());

	private:
		ID3D11VertexShaderPtr		m_vertexShader;		// ������ɫ��
		ID3D11PixelShaderPtr		m_pixelShader;		// ������ɫ��
		ID3D11GeometryShaderPtr		m_geometryShader;	// ������ɫ��
		ID3D11ComputeShaderPtr		m_computeShader;	// ������ɫ��
		ID3D11HullShaderPtr			m_hullShader;		// what's this
		ID3D11DomainShaderPtr		m_domainShader;		// ������ɫ��

		boost::array<ID3DBlobPtr,							ST_NumShaderTypes>	m_shaderCodes;		// ������
		boost::array<HLSL::ShaderDesc,						ST_NumShaderTypes>	m_shaderDescs;		// ������Ϣ
		boost::array<vector<ID3D11BufferPtr>,				ST_NumShaderTypes>	m_constantBuffers;	// ��������
		boost::array<vector<ID3D11SamplerStatePtr>,			ST_NumShaderTypes>	m_samplers;			// ����״̬
		boost::array<vector<ID3D11ShaderResourceViewPtr>,	ST_NumShaderTypes>	m_srvs;				// ����
	};
}