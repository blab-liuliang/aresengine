#include <AresRoot.h>
#include "ParticleFxPlugin.h"
#include <string>

using namespace std;

namespace Ares
{
	const string sPluginName = "ParticleFxPlugin";

	// ���캯��
	CParticleFxPlugin::CParticleFxPlugin()
	{
		m_particleSystem = NULL;
	}

	// ��ȡ�����, ������������ֲ��
	const char* CParticleFxPlugin::GetName() const
	{
		return sPluginName.c_str();
	}

	// ��װ
	void CParticleFxPlugin::Install()
	{
		m_particleSystem = new CSystem;

		Root::SetFxSystem( m_particleSystem);
	}

	// ��ʼ��
	void CParticleFxPlugin::Init()
	{

	}

	// �ر�,������ر�ʱ������
	void CParticleFxPlugin::Shutdown()
	{

	}

	// ж��,(����ȹر�,��ж��)
	void CParticleFxPlugin::Uninstall()
	{
		
	}
}