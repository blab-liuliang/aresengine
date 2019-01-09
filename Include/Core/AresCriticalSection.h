#pragma once

#include <boost/thread.hpp>

namespace Ares
{
	////-----------------------------------------
	//// ��װ�ٽ���  2011-04-14  ����
	////-----------------------------------------
	//class CriticalSection
	//{
	//public:
	//	// �ٽ���������
	//	class CHolder
	//	{
	//	public:
	//		// ����
	//		explicit CHolder( CriticalSection& cs)
	//			: m_crit(cs)
	//		{
	//			m_crit.Enter();
	//		}

	//		// ����
	//		~CHolder()
	//		{
	//			m_crit.Leave();
	//		}

	//	private:
	//		CriticalSection&	m_crit;

	//		// ���ø��ƹ��캯��( ��ʵ��)
	//		CHolder( const CHolder& cowner);
	//		CHolder & operator =( const CHolder& cowner);
	//	};

	//	// ���캯��
	//	CriticalSection()
	//	{
	//		InitializeCriticalSection( &m_criticalSection);
	//	}

	//	// ��������
	//	~CriticalSection()
	//	{
	//		DeleteCriticalSection( &m_criticalSection);
	//	}

	//	// ��ʶ�ٽ���
	//	void Enter()
	//	{
	//		EnterCriticalSection( &m_criticalSection);
	//	}

	//	// �˳��ٽ��� 
	//	void Leave() 
	//	{
	//		LeaveCriticalSection( &m_criticalSection);
	//	}

	//private:
	//	CRITICAL_SECTION	m_criticalSection;

	//	// ���ø��ƹ��캯��( ��Ҫʵ��)
	//	CriticalSection( const CriticalSection& cs);
	//	CriticalSection &operator = ( const CriticalSection& cs);
	//};

	#define ENTER_CRITICAL_SECTION( locker, cs) boost::recursive_mutex::scoped_lock locker(cs)
}