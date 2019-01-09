#pragma once

#include "AresPlatform.h"
#include <boost/thread.hpp>

namespace Ares
{
	//----------------------------------------------------------
	// class CThreadLoopObject 2011-08-28 ����
	// description:
	//     This class provides an easy way to implement a Thread
	// Object with its own process loop. It also provides the 
	// methods to control it.
	//     The user of CThreadLoopObject only have to implement the 
	// methode "virtual void Loop()=0;" which should contain the 
	// cide to be excute in each loop. the loop control is already
	// implemented in the method process loop.
	//----------------------------------------------------------
	class CThreadLoopObject
	{
	public:
		// ���캯��
		CThreadLoopObject();

		// ��������
		virtual ~CThreadLoopObject();

	public:
		// ��ȡ�߳�
		boost::thread* GetThread() const;

	public:
		// �������ȼ�
		void SetPriority( int priority);

		// ��ȡ���ȼ�
		int GetPriority() const;

	public:
		// ��ʼ(�����߳�,�ָ��߳�)
		virtual void Start( DWORD hz=0);

		// ��ͣ(�����߳�)
		void Pause();

		// �������
		void Finish();

		// �ж��Ƿ����������
		bool IsFinishing() const;

		// ����ѭ��
		void ProcessLoop();

		// ��ʼ��
		virtual void Init();

		// ����
		virtual void End();

	protected:
		// �鷽��,������ʵ��
		virtual void Loop()=0;

	protected:
		// �̺߳���
		static DWORD ThreadObjectFunPtr(void* pArg);

	protected:
		boost::thread*	m_thread;			// �߳�
		bool			m_isFinishing;		// ��ɱ��
		bool			m_exitFlag;			// �˳����
		DWORD			m_loopIntervel;		// ѭ�����

	private:
		// copy constructor function, not implemented
		CThreadLoopObject( const CThreadLoopObject& ref);
	};
}