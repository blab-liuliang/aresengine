#include <string>
#include <AresRoot.h>
#include "MainPlugin.h"

using namespace std;

namespace Ares
{
	CMainSystem*	g_mainSystem = NULL;

	const string sPluginName = "QuadTreeEntitySystem";

	// ���캯��
	CMainPlugin::CMainPlugin()
	{
#ifdef _DEBUG
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

		m_mainSystem = NULL;
	}

	// ��ȡ�����, ������������ֲ��
	const char* CMainPlugin::GetName() const
	{
		return sPluginName.c_str();
	}

	// ��װ
	void CMainPlugin::Install()
	{
		if( !m_mainSystem)
		{
			m_mainSystem = new CMainSystem;
			g_mainSystem  = m_mainSystem;
		}

		Root::SetMainSystem( m_mainSystem);
	}

	// ��ʼ��
	void CMainPlugin::Init()
	{

	}

	// �ر�,������ر�ʱ������
	void CMainPlugin::Shutdown()
	{

	}

	// ж��,(����ȹر�,��ж��)
	void CMainPlugin::Uninstall()
	{
		if( m_mainSystem)
			delete m_mainSystem;

		m_mainSystem = 0;
	}
}