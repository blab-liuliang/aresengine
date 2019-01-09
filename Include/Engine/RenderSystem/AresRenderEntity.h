#pragma once

#include "AresRenderElementMgr.h"
#include "Engine/SceneSystem/AresEntity.h"

namespace Ares
{
	//--------------------------------------------------------
	// ��Ⱦʵ��: 2010-08-05  -- δ֪      ����
	//--------------------------------------------------------
	class RenderEntity : public Entity
	{
	public:
		// shader param type
		enum SPType
		{
			SP_World			= 0,
			SP_WorldView,	
			SP_WorldViewProj,
		};

	public:
		// ���캯��
		RenderEntity( EntityTypeDetail typeDetail);

		// ����
		virtual void  FrameMove( float fTime);

		// ��ȡshader�󶨲���
		ShaderParamPtr GetSPAB( SPType type) const;

		// ��ȡ�Ƿ�ɼ�
		bool IsVisible() { return m_visible; }

		// �����Ƿ���ʾ
		void SetVisible(  bool visible) { m_visible = visible; }

	private:
		bool							m_visible;			// �Ƿ���ʾ
		boost::array<ShaderParamPtr,3>	m_spab;				// ShaderParamAutoBind
	};

	typedef s_ptr<RenderEntity> RenderEntityPtr;
}