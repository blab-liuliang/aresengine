#include <Core/AresTriggerSystem.h>

namespace Ares
{
	// ע�ᴥ����
	size_t CTriggerSystem::RegisterTrigger( ETriggerType triggerType, size_t priority, size_t idSender, const Vector3& pos, float radius, float duration, bool dynamicSourcePos)
	{
		// Create a trigger signalslot, and fill it in
		//STriggerSignal* triggerSignal = new STriggerSignal( triggerType, idSender, pos, radius, duration, dynamicSourcePos);

		// Trigger records are sorted by priority
		//m_triggerMap.insert( TRIGGER_MAP::value_type( priority, triggerSignal));

		//return triggerSignal->m_triggerID;

		return 0;
	}

	// �Ƴ�������
	void CTriggerSystem::RemoveTrigger( size_t triggerID)
	{
		TRIGGER_MAP::iterator it = m_triggerMap.begin();
		while( it != m_triggerMap.end())
		{
			if( it->second->m_triggerID == triggerID)
			{
				delete( it->second);
				
				return;
			}

			++it;
		}
	}

	// ����
	void CTriggerSystem::FrameMove()
	{
		// ɾ�����ڵĴ�������Ϣ

		// ˢ�¶�̬λ�õĴ�������Ϣ

		// ֪ͨ��ĳ����������Ϣ�йص�����������
	}
}