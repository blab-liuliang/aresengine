#include <Engine/RenderSystem/AresRenderEntity.h>
#include "Engine/AresRoot.h"

namespace Ares
{
	// ���캯��
	RenderEntity::RenderEntity( EntityTypeDetail typeDetail) 
		: Entity( ET_Render, typeDetail)
		, m_visible( true) 
	{
		m_spab[SP_World]		 = MakeShaderParam( Matrix44::Identity);
		m_spab[SP_WorldView]	 = MakeShaderParam( Matrix44::Identity);
		m_spab[SP_WorldViewProj] = MakeShaderParam( Matrix44::Identity);
	}

	// ��ȡshader�󶨲���
	ShaderParamPtr RenderEntity::GetSPAB( SPType type) const
	{
		return m_spab[type];
	}

	// ����
	void RenderEntity::FrameMove( float fTime)
	{
		// ���� shader param
		*m_spab[SP_World]		  = GetTransform().GetMatrix();
		*m_spab[SP_WorldView]	  = GetTransform().GetMatrix() * GetCameraSystem().GetView();
		*m_spab[SP_WorldViewProj] = GetTransform().GetMatrix() * GetCameraSystem().GetViewProj();
	}
}