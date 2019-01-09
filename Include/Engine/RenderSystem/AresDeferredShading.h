#pragma once

#include "AresFrameFilter.h"
#include "AresGaussianBlur.h"

namespace Ares
{
	//-----------------------------------
	// �ӳ������ս׶� 2013-1-7 ����
	//-----------------------------------
	class DeferredShading : public FrameFilter
	{
	public:
		DeferredShading( Scene& scene);
		~DeferredShading();

		// ��������
		void SetInput(  const TexturePtr& diffuse, const TexturePtr& normal, const TexturePtr& light, const TexturePtr& depth);

	private:
		BlurTexOffseter		m_blurTexOffseter;		// ��˹ģ��
		ShaderParamPtr		m_depthTexture;			// �������
		ShaderParamPtr		m_diffuseTexture;		// ����������
		ShaderParamPtr		m_normalTexture;
		ShaderParamPtr		m_lightTexture;			// ��������
	};
	typedef s_ptr<DeferredShading> DeferredShadingPtr;
}