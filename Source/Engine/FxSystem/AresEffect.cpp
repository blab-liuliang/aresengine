//#include "AresEffect.h"
//#include "AresResource.h"
//#include "ParticleEmitter.h"
//
//namespace Ares
//{
//	// ȫ�ֱ���
//	IResourceManager* g_pResManager = NULL;
//	LPDIRECT3DDEVICE9 g_pDevice=NULL;			// ����װ
//
//	// ��ʼ����Чģ��
//	EFFECT_API void AresEffectModuleInitialize(LPDIRECT3DDEVICE9 pDevice, IResourceManager* pResourceMgr)
//	{
//		g_pResManager = pResourceMgr;
//		g_pDevice     = pDevice;
//	}
//
//
//	// �������ͷ������ӷ�����
//	EFFECT_API CPtr<IParticleEmitter> AresCreateParticleEmitter()
//	{
//		return new CParticleEmitter();
//	}
//}