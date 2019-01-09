#pragma once

#include "AresRenderMethod.h"

using namespace std;

namespace Ares
{
	//--------------------------------------
	// RenderMaterial  2012-4-11 ����
	//     ÿһ����Ⱦʵ��,����һ��Ψһ�Ĳ���,
	// �ڽ����ڴ��˷ѵ�ǰ���¡�����shader
	// �����Ĺ���
	//--------------------------------------
	class CORE_EXPORT RenderMaterial
	{
		typedef vector<ShaderParamPtr> ParamPtrs;
		typedef vector<string>		   ParamAB;

	public:
		// ����Ч���ļ�
		void SetMethod( RenderMethodPtr& method);

		// �Ƿ�ΪͬԴ����(have same shader)
		bool IsSameOrigin( const RenderMaterial& material) { return false; }

		// ��ȡ��������
		size_t  GetParamNum() const { return m_paramPtrs.size(); }

		// ��ȡEffect
		RenderMethodPtr& GetMethod() { return m_method; }

		// ��ȡ��Ⱦ����
		BITFIELD GetRenderQueue() const { return m_renderQueue; }

	public:
		// ����������ȡ����
		const ShaderParamPtr& GetShaderParam( size_t i) const;

		// ���ݲ�������ȡ����
		const ShaderParamPtr& GetShaderParam( const string& paramName) const;

		// �����������ò���
		void SetParamRef( size_t i, const ShaderParamPtr& param);

		// ���ݲ��������ò���
		void SetParamRef( const string& paramName, const ShaderParamPtr& param);

		// ���ò���
		void SetActive();

	public:
		// ����������ȡ����
		const string& GetParamAutoBind( size_t i) const;

		// ���ݲ�������ȡ����
		const string& GetParamAutoBind( const string& paramName) const;

		// �����������ò���
		void SetParamAutoBind( size_t i, const string& spabDesc);

		// ���ݲ��������ò���
		void SetParamAutoBind( const string& paramName, const string& spabDesc);

		// ���ù�դ��״̬
		void SetRasterizerState( RasterizerStatePtr& state) { m_rasterState=state; }

		// �������ģ��״̬
		void SetDepthStencilState( DepthStencilStatePtr& state) { m_depthStencilState=state; }

		// ���û��״̬
		void SetBlendState( BlendStatePtr& state, const ColorRGB& factor, UINT mask);

		// ����״̬
		void SetState();

	public:
		// ������Ⱦ����
		void SetRenderQueue( BITFIELD renderQueue) { m_renderQueue = renderQueue; }

	protected:
		RenderMaterial();
		~RenderMaterial();

	protected:
		BITFIELD					m_renderQueue;				// RenderQueue

		RenderMethodPtr				m_method;					// Render Method
		ParamPtrs					m_paramPtrs;				// shader param value
		ParamAB						m_spabDescs;				// shader param auto bind

		RasterizerStatePtr			m_rasterState;				// ��դ��״̬
		DepthStencilStatePtr		m_depthStencilState;		// ���ģ��״̬
		WORD						m_frontStencilRef;			//
		BlendStatePtr				m_blendState;				// Alpha���״̬
		ColorRGB					m_blendFactor;				// ��ϲ���
		UINT						m_sampleMask;				// ��ϲ���
	};
}