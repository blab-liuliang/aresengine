#pragma once

#include <Core/Graphics/AresFrameBuffer.h>
#include <Engine/RenderSystem/AresGaussianBlur.h>
#include <Engine/RenderSystem/AresDeferredLighting.h>
#include <Engine/RenderSystem/AresDeferredShading.h>

namespace Ares
{
	//------------------------------------
	// �ӳ���Ⱦ������ 2013-1-6 ����
	//------------------------------------
	class DeferredRenderingMgr
	{
	public:
		DeferredRenderingMgr( size_t width, size_t height, Scene& scene);
		~DeferredRenderingMgr();

		// �����ӳ���Ⱦ�׶�
		void BeginDeferredPhase( const ColorRGB& gbufferbackcolor);

		// �����ӳ���Ⱦ�׶�
		void EndDeferredPhase( const FrameBufferPtr& output, const vector<Light*>& lights, const LightPtr& dominantLight);

		// ���Ĵ��ڴ�С
		void Resize( size_t width, size_t height);

		// ��ȡGBuffer
		FrameBufferPtr& GetOpaqueGBuffer() { return m_opaqueGBuffer; }

		// ��ȡ�������
		ShaderParamPtr GetSPABOpaqueZDistance() { return m_spabOpaqueGBufferZDistance; }

	private:
		// ִ�й��ս׶�
		void ExecLightingPhase( const vector<Light*>& lights, const LightPtr& dominantLight);

		// ִ����ɫ�׶�
		void ExecShadingPhase();

	private:
		size_t				m_gBufferWidth;
		size_t				m_gbufferheight;
		FrameBufferPtr		m_opaqueGBuffer;
		TexturePtr			m_opaqueGBufferRT0Diffuse;		// RT0 ������
		TexturePtr			m_opaqueGBufferRT1Normal;		// RT1 ����
		TexturePtr			m_opaqueGBufferZDistance;		// RT2 λ��

		ShaderParamPtr		m_spabOpaqueGBufferZDistance;	// �����ͼ

		FrameBufferPtr		m_lightingBuffer;				// Lighting Buffer
		TexturePtr			m_lightingTexture;				// Lighting Texture

		DeferredLightingPtr m_deferredLighting;				// ���ս׶��˾�
		GaussianBlurPtr		m_gaussianBlur;					// ��˹ģ��(����Ӱ)
		DeferredShadingPtr	m_deferredShading;				// ������ɫ�׶�

		Scene&				m_scene;					// ��������ϵͳ
	};
	typedef s_ptr<DeferredRenderingMgr> DeferredRenderingMgrPtr;
}