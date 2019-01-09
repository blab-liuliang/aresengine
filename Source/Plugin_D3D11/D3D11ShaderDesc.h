#pragma once

#include <string>

using namespace std;

namespace Ares {
namespace HLSL
{
	// Variable desc
	struct VariableDesc
	{
		string		m_name;						// ��������
		UINT		m_startOffset;				// ƫ����
		UINT		m_size;						// ��С
		BYTE		m_type;						// ����
		BYTE		m_rows;						// ����
		BYTE		m_columns;					// ����
		WORD		m_elements;
	};

	// BoundResourceDesc
	struct BoundResourceDesc
	{
		string		m_name;
		BYTE		m_type;
		BYTE		m_dimension;
		WORD		m_bindpoint;
	};

	// Constant buffer desc
	struct ConstantBufferDesc
	{
		UINT					m_size;			// ���ݴ�С
		vector<VariableDesc>	m_varDesc;		// ��������
		vector<BYTE>			m_memorys;		// �ڴ�����
	};

	// Shader����
	struct ShaderDesc
	{
		vector<ConstantBufferDesc>	m_cbDesc;		// constand buffer desc
		vector<BoundResourceDesc>	m_sampDesc;		// bound resource desc
		vector<BoundResourceDesc>	m_srvDesc;		// bound resource desc

		// ���캯��
		ShaderDesc()
		{}
	};
}}