#include "Core/AresThread.h"

namespace Ares
{
	// ���캯��
	CThread::CThread( ThreadFuncPtr pFun, void* pArg)
		: m_handle( 0),
		  m_ID( -1)
	{
		m_handle = CreateThread( 0, 0, pFun, pArg, CREATE_SUSPENDED, &m_ID);
	}

	// ��������
	CThread::~CThread()
	{
		// �����߳�
		/*DWORD exitCode;
		GetExitCodeThread( m_handle, &exitCode);
		ExitThread( exitCode);*/

		// �رվ��
		CloseHandle( m_handle);
	}

	// �������ȼ�
	void CThread::SetPriority( int priority)
	{
		SetThreadPriority( m_handle, priority);
	}

	// ��ȡ���ȼ�
	int CThread::GetPriority() const 
	{ 
		return GetThreadPriority( m_handle); 
	}

	// �ָ��߳�
	void CThread::Resume()
	{
		ResumeThread( m_handle);
	}

	// ����
	void CThread::Suspend()
	{
		SuspendThread( m_handle);
	}

	// �ȴ����
	void CThread::WaitForFinish( DWORD milliseconds/* = 100*/)
	{
		WaitForSingleObject( m_handle, milliseconds);
	}

	// �Ƿ�������
	bool CThread::IsRunning() const
	{
		DWORD exitCode;
		GetExitCodeThread( m_handle, &exitCode);

		return (exitCode == STILL_ACTIVE);
	}
}