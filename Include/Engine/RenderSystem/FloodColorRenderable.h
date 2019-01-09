#pragma once

#include <Core/AresCore.h>
#include <Engine/RenderSystem/SuperMaterial.h>

namespace Ares
{
	//------------------------------------
	// FloodLightRenderable 2013-3-6 ����
	//------------------------------------
	class FloodColorRenderable
	{
	public:
		FloodColorRenderable();
		~FloodColorRenderable();

		// ��Ⱦ
		void Render( const Matrix44& worldViewProj);

		// ���ü��β���
		void SetRenderlayout( const RenderLayoutPtr& layout) { m_layout = layout; }

	private:
		RenderLayoutPtr		m_layout;			// ���β���
		SuperMaterial		m_material;			// ����
		ShaderParamPtr		m_worldViewProj;	// ����
		ShaderParamPtr		m_floodColor;		// ������ɫ
	};
}