#pragma once

#include "AresFrameFilter.h"
#include "Engine/FxSystem/AresFxEntity.h"

namespace Ares
{
	// ����Դ
	struct GodRaySource
	{
		Vector2				m_center;			// ���ĵ�
		FxEntityPtr			m_entity;			// RenderLayout
		FrameBufferPtr		m_output;
		RenderViewPtr		m_depth;			// ���View
	};

	//------------------------------------
	// GodRay 2013-1-29 ����
	//------------------------------------
	class GodRay : public FrameFilter
	{
	public:
		// ���캯��
		GodRay( size_t width, size_t height, Scene& scene);

		// �����ӳ���Ⱦ�׶�
		void Process( GodRaySource& source);

		// ���Ĵ��ڴ�С
		void Resize( size_t width, size_t height);

	private:
		// �������Buffer
		void BindDepthBuffer( RenderViewPtr& depth);

	private:
		size_t				m_gBufferWidth;
		size_t				m_gbufferheight;
		TexturePtr			m_godTexture;		// ��������
		FrameBufferPtr		m_godFrameBuffer;

		ShaderParamPtr		m_spWrapSampler;	// ����״̬
		ShaderParamPtr		m_spGodCenter;		// ���ĵ�����
		ShaderParamPtr		m_spGodTexture;		// ��������
	};
	typedef s_ptr<GodRay> GodRayPtr;
}