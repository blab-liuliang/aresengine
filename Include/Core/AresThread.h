#pragma once

#include "AresPlatform.h"

namespace Ares
{
	//-----------------------------------------
	// ��װ�߳�  2011-07-05  ����
	//-----------------------------------------
	class CThread
	{
	public:
		// �̺߳���
		typedef DWORD (WINAPI *ThreadFuncPtr)(void* arg);

		// ���캯��
		CThread( ThreadFuncPtr pFun, void* pArg);

		// ��������
		~CThread();

	public:
		// ��ȡ���
		HANDLE GetHandle() const { return m_handle; }

		// ��ȡIdentifier
		DWORD GetIdentifier() const { return m_ID; }

	public:
		// �������ȼ�
		void SetPriority( int priority);

		// ��ȡ���ȼ�
		int GetPriority() const;

	public:
		// �ָ�
		void Resume();

		// ����
		void Suspend();

		// �ȴ����
		void WaitForFinish( DWORD milliseconds = 100);

		// �Ƿ�������
		bool IsRunning() const;

	private:
		HANDLE       m_handle;
		DWORD        m_ID;				// �߳�ID

	private:
		// ���ÿ�������( Not Implemented)
		CThread( const CThread& ref);
	};
}