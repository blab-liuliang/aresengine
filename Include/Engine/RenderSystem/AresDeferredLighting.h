#pragma once

#include "AresFrameFilter.h"
#include "AresGaussianBlur.h"
#include "Engine/RenderSystem/AresLight.h"
#include <Engine/RenderSystem/AresDirectionalLight.h>

namespace Ares
{
	//-----------------------------------
	// �ӳ���Ⱦ���ս׶� 2013-1-7 ����
	//-----------------------------------
	class DeferredLighting : public FrameFilter
	{
		// �����ʽ
		struct VertexFormat
		{
			float3 m_position;			// ����λ��
			float2 m_info;				// ��Դ��Ϣ
			float3 m_color;				// float3��Դ��ɫ float ��Դ����
			float3 m_direction;			// ����⳯��,���Դλ��
		};

	public:
		DeferredLighting(  Scene& scene);
		~DeferredLighting();

		// ִ���˾�
		virtual void Execute();

		// ��������
		void SetInput( const TexturePtr& mrt1, const TexturePtr& zDistance, vector<Light*> lights, const LightPtr& dominantLight);

	private:
		// ���ݹ�Դ������֯��ȾBuffer
		void OgranizeRenderLayoutByLights();

		// ����Rect3������
		void GenerateRect3Surface( vector<Vector3>& surface, const Rect3 rect);

	private:
		BlurTexOffseter			m_blurTexOffseter;		// ��˹ģ��
		ShaderParamPtr			m_mrt1Texture;			// ����1
		ShaderParamPtr			m_depthTexture;			// ���
		ShaderParamPtr			m_samplerState;			// ����״̬
		ShaderParamPtr			m_pointSamplerState;	// �����״̬

		vector<Light*>			m_lights;				// ��Դ
		AmbientLight*			m_ambientLight;			// ������
		DirectionalLightPtr		m_dominantLight;		// ����Դ
		VertexElementType		m_elementType;			// �����ʽ
		RenderLayoutPtr			m_lightsRenderLayout;	// ��Դ��Ⱦ��
		vector<VertexFormat>	m_vertexsCache;			// �������ݻ���

		Renderable				m_ambRenderable;		// ������
	};
	typedef s_ptr<DeferredLighting> DeferredLightingPtr;
}