#pragma once

#include <AresPlugin.h>
#include "MainSystem.h"

namespace Ares
{
	//----------------------------------
	// CQtESPlugin 2011-08-04 ����
	// �����Ĳ����ĳ�������ϵͳ 
	//----------------------------------
	class CMainPlugin : public IPlugin
	{
	public: 
		// ���캯��
		CMainPlugin();

		// ��ȡ�����, ������������ֲ��
		virtual const char* GetName() const;

		// ��װ
		virtual void Install();

		// ��ʼ��
		virtual void Init();

		// �ر�,������ر�ʱ������
		virtual void Shutdown();

		// ж��,(����ȹر�,��ж��)
		virtual void Uninstall();

	private:
		CMainSystem*		m_mainSystem;		// �������ϵͳ
	};
}