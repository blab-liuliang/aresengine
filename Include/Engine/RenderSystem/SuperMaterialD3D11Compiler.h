#pragma once

#include "SuperMaterialCompiler.h"

namespace Ares
{
	// D3D11MaterialUserInput
	struct MaterialD3D11UserInput
	{
		virtual ~MaterialD3D11UserInput() {}
	};

	// MaterialD3D11UserInputConstant
	struct MaterialD3D11UserInputConstant : public MaterialD3D11UserInput
	{
		float4		m_value;		// ֵ
		UINT		m_numComponents;// �������

		// ���캯��
		MaterialD3D11UserInputConstant( const float4& value, UINT numComponents)
			: m_value( value), m_numComponents( numComponents)
		{}
	};

	//-------------------------------------------
	// D3DMaterialCompiler 2013-3-11 ����
	//-------------------------------------------
	class D3D11MaterialCompiler : public MaterialCompiler
	{
	public:
		// ����� 
		struct ShaderCodeChunk
		{
			string					m_code;		// ����
			MaterialD3D11UserInput* m_input;	// ����
			OutputType				m_type;		// ����

			ShaderCodeChunk( const char* code, OutputType type)
				: m_code( code), m_type( type)
			{}

			ShaderCodeChunk( MaterialD3D11UserInput* input, const char* code, OutputType type)
				: m_input( input), m_code( code), m_type( type)
			{}
		};

	public:
		// ��ȡ�����
		const char* GetChunkCode( size_t chunkIdx);

		// ��ȡ��������
		OutputType GetChunkCodeOutputType( size_t chunkIdx);

		// ����
		virtual INT Constant( const float4& val, INT numComponents);

		// �������
		virtual INT TextureSample( int chunkIdx, INT coordinateIdx);

		// ������
		virtual INT ComponentMask( int chunkIdx, bool maskR, bool maskG, bool maskB, bool maskA);

		// ����û�����
		INT AddUserInput( const float4& constant, OutputType type, const char* format, ...);

		// AddCodeChunk - Adds a formatted code string to the code array and returns its index
		INT AddCodeChunk( OutputType type, DWORD flags, const char* format, ...);

	private:
		vector<ShaderCodeChunk>						m_codeChunks;		// �����
		vector<MaterialD3D11UserInput*>				m_userInputs;		// �û�����
		vector<MaterialD3D11UserInputConstant*>		m_userConstants;	// �û�����
	};
}