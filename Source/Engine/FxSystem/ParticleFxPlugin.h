#include <AresPlugin.h>
#include "System.h"

namespace Ares
{
	//------------------------------------
	// ParticleFxPlugin 2011-09-13 ����
	// Plugin instance for ParticleSystem
	//------------------------------------
	class CParticleFxPlugin : public IPlugin
	{
	public: 
		// ���캯��
		CParticleFxPlugin();

		// ��ȡ�����, ������������ֲ��
		virtual const char* GetName() const;

		// ��װ
		virtual void Install();

		// ��ʼ��
		virtual void Init();

		// �ر�,������ر�ʱ������
		virtual void Shutdown();

		// ж��,(����ȹر�,��ж��)
		virtual void Uninstall();

	private:
		CSystem*		m_particleSystem;	// �˲������ϵͳ
	};
}