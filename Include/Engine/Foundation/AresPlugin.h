#pragma once

#include "Ares3DEngine_h.h"

namespace Ares
{
	//---------------------------------------------------
	// AresPlugin Interface 2011-08-04 ����
	// @Remarks
	//	  This class abstracts the generic interface that
	// all plugin must support.
	class ARES_EXPORT IPlugin
	{
	public:
		// ���캯��
		IPlugin() {}

		// ��������
		virtual ~IPlugin() {}

		// ��ȡ�����, ������������ֲ��
		virtual const char* GetName() const = 0;

		// ��װ
		virtual void Install()=0;

		// ��ʼ��
		virtual void Init()=0;

		// �ر�,������ر�ʱ������
		virtual void Shutdown()=0;

		// ж��,(����ȹر�,��ж��)
		virtual void Uninstall()=0;
	};

	typedef IPlugin* (*DLL_START_PLUGIN)(void);
	typedef void     (*DLL_STOP_PLUGIN) (void);
}