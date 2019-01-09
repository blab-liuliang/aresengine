#include "PbrtTaskQueue.h"
#include <pbrt/core/api.h>
#include <pbrt/core/parser.h>
#include <pbrt/core/parallel.h>
#include <pbrt/core/api.h>
#include <pbrt/core/pbrt.h>

namespace Ares
{
	// �鷽�� Loop
	void PbrtTaskQueue::Loop()
	{
		// ��ȡ����
		string  tPbrt;
		Options tOptions;
		{
			ENTER_CRITICAL_SECTION( locker, m_criticalSection);
			if( !m_tasks.empty())
			{
				tPbrt    = m_tasks.begin()->first;
				tOptions = m_tasks.begin()->second;
				
				m_tasks.erase( m_tasks.begin());		
			}

			m_curTask = tPbrt;
		}

		if( tPbrt.size())
		{
			// ��ʼ��
			pbrtInit( tOptions);

			// ���������ļ�
			ParseFile( tPbrt.c_str());

			// �������
			pbrtCleanup();

			Signal_OnPbrtFinised( tOptions.imageFile.c_str());
		}
	}

	// ���pbrt����
	void PbrtTaskQueue::AddTask( const char* pbrtFileName, const Options& options)
	{
		ENTER_CRITICAL_SECTION( holder, m_criticalSection);
		
		m_tasks[pbrtFileName] = options;
	}

	// �ж������Ƿ��Ѵ���
	bool PbrtTaskQueue::IsTaskExist( const char* pbrtTask)
	{
		ENTER_CRITICAL_SECTION( locker, m_criticalSection);
		if( m_tasks.find( pbrtTask) != m_tasks.end())
			return true;

		if( m_curTask == pbrtTask)
			return true;

		return false;
	}
}