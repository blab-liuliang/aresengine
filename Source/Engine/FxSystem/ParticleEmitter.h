//#ifndef ARES_PARTICLE_H
//#define ARES_PARTICLE_H
//
//#include <vector>
//#include <list>
//#include "AresEffect.h"
//#include "Sprite.h"
//
//using namespace std;
//
//namespace Ares
//{
//	#define D3DFVF_PARTICLE (D3DFVF_XYZ | D3DFVF_PSIZE| D3DFVF_DIFFUSE) 
//
//	struct VERTEX_PARTICLE
//	{
//		Vector3     vPosition;  // ����λ��	
//		float       pointSize;	// λ�úͳߴ�����˻�������
//		DWORD       color;		// ������ɫ
//	};
//
//	//-----------------------------------------
//	// ���ӷ����� CParticle��Ŀ��(ʹ����)
//	//-----------------------------------------
//	class  ITexture;
//	class  IRenderMethod;
//	struct SRenderEntry;
//	class  CParticleEmitter : public IParticleEmitter
//	{
//	public:
//		// ���캯��
//		CParticleEmitter();
//
//		// ��������
//		~CParticleEmitter();
//
//		// ��ʼ��
//		virtual bool Initialize(char* cTextureFileName);
//
//		// ÿ֡���� 
//		virtual void FrameMove(float fTime);
//
//		// �ύ����Ⱦ����( ʹ����Ч ��������)
//		virtual void SubmitToRenderQueue( const char* searchName);
//
//		// ��Ⱦ
//		virtual void Render(SRenderEntry** entry, int iSameEntry, U32Flags activateionFlags);
//
//	private:
//		UINT                     m_iMaxSprites;		  // ���������㾫����	
//		float					 m_fEmitRateMin;      // ��λ����/��
//		float					 m_fEmitRateMax;      // 
//
//        CPtr<IVertexBuffer>      m_pVertexBuffer;     // ���㻺��
//		CPtr<ITexture>   	     m_pTexture;	      // ��������
//		vector<SSPrite>          m_Particles;         // ��������
//		list<int>				 m_idleParticleIndex; // ��¼�����Particle�±�
//		CPtr<ISurfaceMaterial>	 m_pMaterial;		  // ���� 
//		VERTEX_PARTICLE*         m_pVertexData;		  // �ڴ��д洢����	
//	};
//}
//
//#endif