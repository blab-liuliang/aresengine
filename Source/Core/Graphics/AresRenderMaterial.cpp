#include <algorithm>
#include "Core/Graphics/AresRenderMaterial.h"
#include "Core/AresException.h"

namespace Ares
{
	// ���캯��
	RenderMaterial::RenderMaterial()
		: m_frontStencilRef( 0)
		, m_renderQueue( 0)
	{}

	// ��������
	RenderMaterial::~RenderMaterial()
	{
		m_renderQueue = 0;
	}

	// ����Ч���ļ�
	void RenderMaterial::SetMethod( RenderMethodPtr& method)
	{
		m_method = method;

		if( m_method)
		{
			// ָ��method�ĵ�ǰ����ֵ
			m_paramPtrs.clear();
			for ( size_t i=0; i<m_method->GetParamNum(); i++)
			{
				m_paramPtrs.push_back( m_method->GetVisualParamPtr(i));
			}

			m_spabDescs.resize( m_paramPtrs.size(), string());

			// Ĭ��״̬
		}
	}

	// ����������ȡ����
	const ShaderParamPtr& RenderMaterial::GetShaderParam( size_t i) const
	{
		BOOST_ASSERT( i>=0);
		BOOST_ASSERT( i<m_paramPtrs.size());

		return m_paramPtrs[i];
	}

	// ���ݲ�������ȡ����
	const ShaderParamPtr& RenderMaterial::GetShaderParam( const string& paramName) const
	{
		size_t idx = 0;
		V_ASSERT( m_method->GetParamIdx( idx, paramName));
			
		return m_paramPtrs[idx];
	}

	// �����������ò���
	void RenderMaterial::SetParamRef( size_t i, const ShaderParamPtr& param)
	{
		A_ASSERT( i>=0);
		A_ASSERT( i<m_paramPtrs.size());

		m_paramPtrs[i] = param;
	}

	// ���ݲ��������ò���
	void RenderMaterial::SetParamRef( const string& paramName, const ShaderParamPtr& param)
	{
		size_t idx;
		if( m_method->GetParamIdx( idx, paramName.c_str()))
		{
			m_paramPtrs[idx] = param;
		}
	}

	// ����������ȡ����
	const string& RenderMaterial::GetParamAutoBind( size_t i) const
	{
		BOOST_ASSERT( i>=0);
		BOOST_ASSERT( i<m_spabDescs.size());

		return m_spabDescs[i];
	}

	// ���ݲ�������ȡ����
	const string& RenderMaterial::GetParamAutoBind( const string& paramName) const
	{
		size_t idx = 0;
		V_ASSERT( m_method->GetParamIdx( idx, paramName));
			
		return m_spabDescs[idx];
	}

	// �����������ò���
	void RenderMaterial::SetParamAutoBind( size_t i, const string& spabDesc)
	{
		BOOST_ASSERT( i>=0);
		BOOST_ASSERT( i<m_spabDescs.size());

		m_spabDescs[i] = spabDesc;
	}

	// ���ݲ��������ò���
	void RenderMaterial::SetParamAutoBind( const string& paramName, const string& spabDesc)
	{
		size_t idx;
		if( m_method->GetParamIdx( idx, paramName))
		{
			m_spabDescs[idx] = spabDesc;
		}
	}

	// ���ò���
	void RenderMaterial::SetActive() 
	{
		if( m_method && m_method->IsEnabled())
		{
			// 1 ����ɫ��
			m_method->Bind();

			// 2 ���ò���
			m_method->SetParams( *this);

			// 3 ����״̬
			this->SetState();
		}
	}

	// ���û��״̬
	void RenderMaterial::SetBlendState( BlendStatePtr& state, const ColorRGB& factor, UINT mask) 
	{ 
		m_blendState  = state;
		m_blendFactor = factor;
		m_sampleMask  = mask;
	}

	// ����״̬
	void RenderMaterial::SetState()
	{
		RasterizerStatePtr&		rasterState = m_rasterState ? m_rasterState : m_method->m_rasterState;
		DepthStencilStatePtr&   depthState  = m_depthStencilState ? m_depthStencilState : m_method->m_depthStencilState;
		BlendStatePtr&			blendState  = m_blendState ? m_blendState : m_method->m_blendState;

		rasterState->SetActive();
		depthState->SetActive( 0, 0);
		blendState->SetActive();
	}
}