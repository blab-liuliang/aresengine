#pragma once

#include <vector>
#include <string>
#include <Core/AresThreadLoopObject.h>
#include <Core/AresCriticalSection.h>
#include <boost/signals2/signal.hpp>

using namespace std;
using namespace boost;
using namespace boost::signals2;

struct Options;

namespace Ares
{
	//-----------------------------------------
	// Pbrt����������� 2012-4-19  ����
	//-----------------------------------------
	class PbrtTaskQueue : public CThreadLoopObject
	{
	public:
		// �鷽�� Loop
		virtual void Loop();

		// ���pbrt����
		void AddTask( const char* pbrtFileName, const Options& options);

		// �ж������Ƿ��Ѵ���
		bool IsTaskExist( const char* pbrtTask);

	public:
		// pbrt���ɽ����ź�
		signal<void(const char*)> Signal_OnPbrtFinised;

	private:
		string					m_curTask;			// ��ǰ����
		map<string, Options>	m_tasks;			// Ҫִ�����ɵ�pbrt�ļ�
		boost::recursive_mutex	m_criticalSection;	// �ٽ���(����m_tasks�����б�)
	};
}