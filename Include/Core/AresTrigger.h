#pragma once

#include <map>
#include "AresMath.h"

namespace Ares
{
	//-------------------------------
	// ���������� 2011-10-3 ����
	//-------------------------------
	enum ETriggerType
	{
		TRIGGER_NONE		= 0,
		TRIGGER_EXPLOSION	= (1<<0),
		TRIGGER_ENEMYNEAR	= (1<<1),
		TRIGGER_GUNFIRE		= (1<<2),
	};

	//-------------------------------
	// ��������Ϣ 2011-10-03
	//-------------------------------
	struct STriggerSignal
	{
		ETriggerType	m_triggerType;		// ����������
		size_t			m_triggerID;		// ������ID
		size_t			m_idSource;			// ��������Ϣ��������ID
		Vector3			m_pos;				// λ��
		float			m_radius;			// �뾶
		size_t			m_timeStamp;		// ʱ��ӡ��
		size_t			m_timeExpiration;	// �ս�ʱ��
		bool			m_dynamicSourcePos;	// Lookup position of trigger source every update

		static size_t	m_nextTriggerID;	// Next unique registration ID for trigger	
	};

	typedef std::multimap<size_t /*priority*/, STriggerSignal*> TRIGGER_MAP;
}