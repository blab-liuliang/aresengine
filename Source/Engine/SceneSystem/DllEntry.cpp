#pragma once

#include "MainPlugin.h"

#ifdef VANGUARD_EXPORTS
#define VANGUARD_API __declspec(dllexport)
#else
#define VANGUARD_API __declspec(dllimport)
#endif

namespace Ares
{
	CMainPlugin*       g_plugin = 0;			// ��ǰ���

	extern "C"
	{
		// �������
		VANGUARD_API IPlugin*  DllStartPlugin()
		{
			g_plugin = new CMainPlugin;

			return g_plugin;
		}

		// �������
		VANGUARD_API void DllStopPlugin()
		{

		}
	}
}