#include "MoveLogic.h"
#include "CharacterProxy.h"
#include "SCLogic.h"

namespace Ares
{
	// ���캯��
	CMoveLogic::CMoveLogic()
	{
		m_default	= NULL;
		m_character = NULL;
		m_moveType  = EM_THIRD;
	}

	// ����
	void CMoveLogic::FrameMove( float fDeltaTime)
	{
		if( m_moveType == EM_THIRD)
		{
			m_default->FrameMove( fDeltaTime);
		}
		else if( m_moveType == EM_FOLLOW)
		{
			if( m_character)		
				m_character->FrameMove( fDeltaTime);
		}			
	}

	// ��ȡ�ƶ��������ĵ�
	Vector3 CMoveLogic::GetCenterPos()
	{
		if( m_moveType == EM_FOLLOW && m_character)
		{
			return m_character->GetCharacterPos();
		}
		else if( m_moveType == EM_THIRD)
		{
			return SCLogic_Camera->GetPosition();
		}

		return Vector3( 0, 0, 0);
	}

	// �����ƶ�����
	void CMoveLogic::SetMoveType( MoveType type)
	{ 
		m_moveType = type;
		
		if( m_moveType == EM_FOLLOW)
		{
			if( !m_character)
				m_character = new CCharacterProxy;

			m_character->SetPos( m_default->GetPosition());
			m_character->Active();

		}
		else if( m_moveType == EM_THIRD)
		{
			if( !m_default)
				m_default = new_ DefaultProxy;

			m_default->Active();
			m_character->Decative();
		}
	}

	// ���ø����������Ƿ�ɼ�
	void CMoveLogic::SetCapsuleVisible( bool visible)
	{
		if( m_character)
			m_character->SetCapsuleVisible( visible);
	}

	// ����ProjParams
	void CMoveLogic::SetProjParams(float fovW, int screenWidth, int screenHeight, float fNearPlane, float fFarPlane,  RenderDeviceType type)
	{
		if( m_default)
		{
			Camera* pCamera = m_default->GetCamera();
			if( pCamera)
			{
				// ����ͶӰ����
				float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
				pCamera->SetProjParams(  fovW/aspect, screenWidth, screenHeight, fNearPlane, fFarPlane, type);
			}
		}
	}
}