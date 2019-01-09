#pragma once

#include <Core/AresMath.h>

#include "DefaultProxy.h"
#include "CharacterProxy.h"

namespace Ares
{
	//----------------------------
	// �ƶ��߼� 2011-05-04
	//----------------------------
	class CCharacterProxy;
	class CMoveLogic
	{
	public:
		enum MoveType
		{
			EM_THIRD,
			EM_FOLLOW,
		};

		// ���캯��
		CMoveLogic();

		// ����
		void FrameMove( float fDeltaTime);

		// ���ø����������Ƿ�ɼ�
		void SetCapsuleVisible( bool visible);

	public:
		// �����ƶ�����
		void SetMoveType( MoveType type);

		// ����ͶӰ����
		void  SetProjParams( float fovW, int screenWidth, int screenHeight, float fNearPlane, float fFarPlane, RenderDeviceType type);

		// ��ȡ�ƶ�����
		MoveType GetMoveType() { return m_moveType; }

		// ��ȡĬ���ƶ�����
		DefaultProxy* GetDefaultProxy() { return m_default; }

		// ��ȡ�ƶ��������ĵ�
		Vector3 GetCenterPos();

	private:
		DefaultProxy*			m_default;			// ����Ĭ�ϲ���
		CCharacterProxy*		m_character;		// ����
		MoveType				m_moveType;			// �ƶ�����
	};
}