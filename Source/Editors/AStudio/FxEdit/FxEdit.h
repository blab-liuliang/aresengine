#pragma once

#include <Engine/FxSystem/AresFx3DPatch.h>
#include <Engine/FxSystem/AresFxParticleSystem.h>
#include <Engine/FxSystem/AresFxEntity.h>

namespace Ares
{
	//--------------------------------------
	// Ч���༭�߼� 2012-8-20 ����
	//--------------------------------------
	class FxEdit
	{
	public:
		FxEdit();

		// ��ȡ��ǰFxEntity
		FxEntity* GetFxEntity() { return m_fxEntity.get(); }

		// ����
		void FrameMove(  float elapsedTime);

		// ִ��
		void SubmitToRenderQueue();

	public:
		// ��ȡ·��
		string GetAfxPath() { return m_afxPath; }

		// ��Ч��
		void OpenAfx( const char* file);

		// ����Ч��
		void SaveAfx( const char* filePath);

		// �½�Ч��
		void New();

		// ����FxEntity
		void ResetFxEntity();

		// ���Ч������
		void AddObject( FxObjectType type);

		// ��ȡ��Ч�뾶
		float GetFxRadius() { return 10.f;}

		// ����ѡ��
		void SetSelected( int idx);

		// ɾ��ѡ��
		void DeleteSelected( int idx);

	private:
		// ����Ψһ����
		string GetUniqueName();

	private:
		int						m_selectedIdx;
		string					m_afxPath;			// �洢·��
		FxEntityPtr				m_fxEntity;			// Ч��ʵ��
	};
}