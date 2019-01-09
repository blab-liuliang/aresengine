#include "MOLogic.h"
#include <Engine/AresRoot.h>

namespace Ares
{
	// ���캯��
	LightEditLogic::LightEditLogic()
	{
		// Ĭ�Ϲ�Դ
		m_dirLight = dynamic_pointer_cast<DirectionalLight>(EntityEdit_Scene->CreateLight( "DirectionLight", LT_Direction));
		if( m_dirLight)
		{
			m_dirLight->SetColor( ColorRGB( 1.f, 1.f, .9f));
			m_dirLight->SetDirection( Vector3( -1.f, 0.f, 0.f));				
		}

		m_dominantLight = m_dirLight;

		// ������Ϣ
		m_dominantLight->GetCSMMgr()->SetShadowMapResolution( 1024);
		m_dominantLight->SetLocalBounds( Rect3::Infinity);
		//m_dominantLight->GetCSMMgr()->Signal_WriteDepth.connect( boost::bind<void>(&MOLogic::RenderDepth, MOLogic_Main, _1, _2));

		//m_lights.push_back( m_dirLight);
	}

	// ÿ֡����
	void LightEditLogic::FrameMove()
	{
		Vector3 face  = MOLogic_Camera->GetFacing() * 0.25f;
		Vector3 right = MOLogic_Camera->GetRight();
		Vector3 dir( -right.x + face.x, -right.y + face.y, 0);
		dir.Normalize();
		dir.z = -0.2f;
		dir.Normalize();

		if( m_dirLight)
			m_dirLight->SetDirection( dir);
	}
}