#pragma once

#include <map>
#include <Core/AresSerialization.h>
#include "SuperMaterialD3D11Compiler.h"

using namespace std;

namespace Ares
{
	//-------------------------------------------
	// SuperMaterialShaderTree 2013-3-12 ���� 
	//-------------------------------------------
	class MaterialShaderTree
	{
	public:
		MaterialShaderTree();
		~MaterialShaderTree();

		// ����
		INT Compile( string& oCode, const string& iCode);

		// ��ӱ��ʽ
		void AddExpression( MaterialExpression* expression);

		// �������
		void AddConnection( MaterialExpressionConnection* conection);

		// ɾ������
		void DelConnection( const string& input);

		// ��ȡ���ʲ�
		MaterialExpressionSlot& GetExpressionSlot() { return m_slot; }

		// ��ȡ���ʽ����
		ExpressionInput* GetExpressionInput( const string& id);

		// ��ȡ���ʽ
		MaterialExpression* GetMaterialExpression( const string& id);

		// ��ȡ���ʽ
		const vector<MaterialExpression*>& GetMaterialExpression() { return m_expressions; }

		// ��ȡ����
		MaterialExpressionConnection* GetMaterialExpressionConnection( const string& expression, const string& input);

		// ��ȡ����
		const vector<MaterialExpressionConnection*>& GetMaterialExpressionConnection() { return m_connections; }

		// ���л�
		BOOST_SERIALIZATION_SPLIT_MEMBER()
		template<typename Archive> void save( Archive& ar, const unsigned int version) const
		{
			ar & m_idSeed;
			ar & m_slot;
			ar & m_expressions;
			ar & m_connections;
		}
		template<typename Archive> void load( Archive& ar, const unsigned int version)
		{
			ar & m_idSeed;
			ar & m_slot;
			ar & m_expressions;
			ar & m_connections;

			RegisterInputs();
			ReConnection();
		}

	private:
		// ��������
		void ReConnection();

		// ��ȡΨһID
		void BuildUniqueID( string& oID);

		// ע��inputs
		void RegisterInputs();

	private:
		D3D11MaterialCompiler					m_compiler;		// D3D11MaterialCompiler

		int										m_idSeed;		// id����
		MaterialExpressionSlot					m_slot;			// ��
		vector<ExpressionInput*>				m_inputs;		// ����
		vector<MaterialExpression*>				m_expressions;	// ���ʽ
		vector<MaterialExpressionConnection*>	m_connections;	// ����
	};
}