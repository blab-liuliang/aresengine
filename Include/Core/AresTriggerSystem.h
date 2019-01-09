#pragma once

#include "AresTrigger.h"

namespace Ares
{
	//--------------------------------------------
	// ͨ�ô�����ϵͳ 2011-10-3  ����
	//--------------------------------------------
	class CTriggerSystem
	{
	public:
		// ���캯��
		CTriggerSystem();

		// ��������
		~CTriggerSystem();

	public:
		// ע�ᴥ����
		size_t RegisterTrigger( ETriggerType triggerType, size_t priority, size_t idSender, const Vector3& pos, float radius, float duration, bool dynamicSourcePos);

		// �Ƴ�������
		void RemoveTrigger( size_t triggerID);

		// ����
		void FrameMove();

	private:
		TRIGGER_MAP		m_triggerMap;	
	};
}