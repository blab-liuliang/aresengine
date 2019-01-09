#include <Engine/RenderSystem/SuperMaterialShaderTree.h>
#include <Engine/AresRoot.h>
#include <boost/algorithm/string.hpp>

namespace Ares
{
	// ���캯��
	MaterialShaderTree::MaterialShaderTree()
		: m_idSeed( 0)
	{
		m_inputs.reserve( 512);	

		m_inputs.push_back( &m_slot.m_diffuseColor);
		m_inputs.push_back( &m_slot.m_normal);
	}

	// ��������
	MaterialShaderTree::~MaterialShaderTree()
	{
		foreach_( MaterialExpression* expression, m_expressions)
			SAFE_DELETE( expression);

		foreach_( MaterialExpressionConnection* connection, m_connections)
			SAFE_DELETE( connection);

		m_expressions.clear();
		m_connections.clear();
	}

	// ����
	INT MaterialShaderTree::Compile( string& oCode, const string& iCode)
	{
		// ��ȡ������
		INT diffuseChunkIdx = m_slot.m_diffuseColor.Compile( m_compiler);

		oCode = iCode;
		boost::replace_first( oCode, "SLOT_VARIABLES", "");
		boost::replace_first( oCode, "SLOT_DIFFUSE",   m_compiler.GetChunkCode( diffuseChunkIdx));

		return INVALID;
	}

	// ��ӱ��ʽ
	void MaterialShaderTree::AddExpression( MaterialExpression* expression)
	{
		if( expression)
		{
			// ��ӹ�ʽ
			m_expressions.push_back( expression);
			BuildUniqueID( expression->m_id);

			// �������
			vector<ExpressionInput*> inputs; 
			expression->GetInputs( inputs);
			foreach_( ExpressionInput* input, inputs)
			{
				BuildUniqueID( input->m_id);
				m_inputs.push_back( input);
			}
		}
	}

	// ע��inputs
	void MaterialShaderTree::RegisterInputs()
	{
		foreach_( MaterialExpression* expression, m_expressions)
		{
			vector<ExpressionInput*> inputs; 
			expression->GetInputs( inputs);
			foreach_( ExpressionInput* input, inputs)
			{
				m_inputs.push_back( input);
			}
		}	
	}

	// �������
	void MaterialShaderTree::AddConnection( MaterialExpressionConnection* conection)
	{
		if( conection)
		{
			// 1.ȥ����ͻ������
			DelConnection( conection->m_input);

			// 2.����µ���������
			m_connections.push_back( conection);

			// 3.������֯����
			ReConnection();
		}
	}

	// ɾ������
	void MaterialShaderTree::DelConnection( const string& input)
	{
		// 1.ȥ����ͻ������
		for( vector<MaterialExpressionConnection*>::iterator it=m_connections.begin(); it!=m_connections.end(); )
		{
			if( (*it)->m_input == input)
				it = m_connections.erase( it);
			else
				it++;
		}
	}

	// ��ȡExpressionInput
	ExpressionInput* MaterialShaderTree::GetExpressionInput( const string& id)
	{
		for( size_t i=0; i<m_inputs.size(); i++)
		{
			if( m_inputs[i]->m_id == id)
				return m_inputs[i];
		}

		return NULL;
	}

	// ��ȡ���ʽ
	MaterialExpression* MaterialShaderTree::GetMaterialExpression( const string& id)
	{
		for( size_t i=0; i<m_expressions.size(); i++)
		{
			if( m_expressions[i]->m_id == id)
				return m_expressions[i];
		}

		return NULL;
	}

	// ��ȡ����
	MaterialExpressionConnection* MaterialShaderTree::GetMaterialExpressionConnection( const string& expression, const string& input)
	{
		for( size_t i=0; i<m_connections.size(); i++)
		{
			if( m_connections[i]->m_expression==expression && m_connections[i]->m_input==input)
				return m_connections[i];
		}

		return NULL;
	}

	// ��������,(����ʱ��ʹ�ô˺���)
	void MaterialShaderTree::ReConnection()
	{
		// �Ͽ���������
		for( size_t i=0; i<m_inputs.size(); i++)
			m_inputs[i]->m_expression = NULL;

		// ��������
		for( size_t i=0; i<m_connections.size(); i++)
		{
			ExpressionInput*	input      = GetExpressionInput( m_connections[i]->m_input);
			MaterialExpression* expression = GetMaterialExpression( m_connections[i]->m_expression);
			if( input && expression)
				input->m_expression = expression;
			else
				ALogSystem.Warning( "Expression or connected missed! can't connect");
		}
	}

	// ��ȡΨһID
	void MaterialShaderTree::BuildUniqueID( string& oID)
	{
		char id[512];
#ifdef ARES_PLATFORM_WINDOWS
		sprintf_s( id, 512, "%d", m_idSeed++);
#else
        sprintf( id, "%d", m_idSeed++);
#endif

		oID = id;
	}
}