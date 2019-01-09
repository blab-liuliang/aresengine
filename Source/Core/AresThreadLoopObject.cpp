#include "Core/AresThreadLoopObject.h"

using namespace boost;

namespace Ares
{
	// ���캯��
	CThreadLoopObject::CThreadLoopObject()
		: m_isFinishing( false),
		  m_thread( NULL),
		  m_exitFlag( false),
		  m_loopIntervel()
	{
		//Start( 20);
	}

	// ��������
	CThreadLoopObject::~CThreadLoopObject()
	{
		if( m_thread)
		{
			m_thread->join();

			SAFE_DELETE( m_thread);
		}
	}

	// ��ȡ�߳�
	boost::thread* CThreadLoopObject::GetThread() const
	{
		return m_thread;
	}

	// �������ȼ�
	void CThreadLoopObject::SetPriority( int priority)
	{
	}

	// ��ȡ���ȼ�
	int CThreadLoopObject::GetPriority() const
	{
		if( m_thread)
		{
		}

		return 0;
	}

	// ��ʼ(�����߳�,�ָ��߳�)
	void CThreadLoopObject::Start(DWORD hz/*=0*/)
	{
		// ѭ��֡�ʿ���
		if( hz == 0)
			m_loopIntervel = 0;
		else
			m_loopIntervel = 1000 / hz; 

		// �̲߳�����,����
		if( m_thread == NULL)
		{
			m_thread = new_ boost::thread( ThreadObjectFunPtr, this);
		}

		// �ָ�
		//m_thread->Resume();
	}

	// ��ͣ(�����߳�)
	void CThreadLoopObject::Pause()
	{
		//if( m_thread)
		//	m_thread->Suspend();
	}

	// �������
	void CThreadLoopObject::Finish()
	{
		m_isFinishing = true;

		Start();
		End();
		//Sleep(0);
	
		SAFE_DELETE( m_thread);

		m_isFinishing = false;
	}

	// �ж��Ƿ����������
	bool CThreadLoopObject::IsFinishing() const
	{
		return m_isFinishing;
	}

	// ����ѭ��
	void CThreadLoopObject::ProcessLoop()
	{
		Init();

		while( !m_exitFlag)
		{ 
			Loop();

            this_thread::sleep(posix_time::seconds(m_loopIntervel));
		}
	}

	// ��ʼ��
	void CThreadLoopObject::Init()
	{
		m_exitFlag = false;
	}

	// ����
	void CThreadLoopObject::End()
	{
		m_exitFlag = true;
	}

	// �̺߳���
	DWORD CThreadLoopObject::ThreadObjectFunPtr(void* pArg)
	{
		// �̴߳���,��ʼѭ��
		CThreadLoopObject* pThreadObject = (CThreadLoopObject*)pArg;
		pThreadObject->ProcessLoop();

		return 0;
	}
}