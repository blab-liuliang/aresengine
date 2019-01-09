//#include <Foundation/AresFoundation.h>
//#include "ParticleEmitter.h"
//#include <AresRenderEntry.h>
//#include <AresResource.h>
//
//namespace Ares
//{
//	extern IResourceManager* g_pResManager;
//	extern LPDIRECT3DDEVICE9 g_pDevice;
//
//	//----------------------------------------------------------------------
//	// ���ӷ����� CParticleEmitter   
//	//----------------------------------------------------------------------
//	CParticleEmitter::CParticleEmitter()
//	{
//		m_iMaxSprites  = 500;
//		m_fEmitRateMin = 0; 
//		m_fEmitRateMax = 0;
//		m_pVertexData  = NULL;
//
//		Rect3 box( -1000.f, 1000.f, -1000.f, 1000.f, -1000.f, 1000.f);
//		SetBoundingBox( box);
//
//		srand( GetTickCount());
//	}
//
//	// ��������
//	CParticleEmitter::~CParticleEmitter()
//	{
//		SAFE_DELETE_ARRAY( m_pVertexData);
//	}
//	
//	bool CParticleEmitter::Initialize(char *cTextureFileName)
//	{	
//		// ��������Ŀ�������������,��տ���������������
//		m_Particles.clear();
//		m_idleParticleIndex.clear();
//
//		// ��������ϵͳ������
//		m_pMaterial = g_pResManager->CreateSurfaceMaterial();
//		m_pMaterial->LoadEffectFile("Data\\shader\\Sprite.fx");
//		m_pMaterial->SetTexture( 0, cTextureFileName);
//
//		m_pVertexBuffer = g_pResManager->CreateVertexBuffer();
//		m_pVertexBuffer->Create( m_iMaxSprites, sizeof(VERTEX_PARTICLE), 0, NULL);
//		m_pVertexData = new VERTEX_PARTICLE[m_iMaxSprites];
//
//		m_sqmNum	= 1;
//		m_searchQueueMaterial = new SRenderSearchParam[m_sqmNum];
//		m_searchQueueMaterial[0].m_searchName = "main";
//		m_searchQueueMaterial[0].m_queueName	= "opacity";
//		m_searchQueueMaterial[0].m_material	= m_pMaterial;
//
//		return true;
//	}
//
//	// ����
//	void CParticleEmitter::FrameMove(float fTime)
//	{
//		// ���´��ڵ�����
//		for(int i = (int)m_Particles.size()-1; i>=0; i--)
//		{
//			// ������Ϊ����״̬ʱ; ���¸�����
//			if ( !m_Particles[i].m_bIdle)
//			{
//				if( !m_Particles[i].FrameMove(fTime))	// ���º�;�ﵽ��������
//				{
//					m_idleParticleIndex.push_back(i);
//				}
//			}
//		}
//
//		m_fEmitRateMin = m_fEmitRateMax = 1;
//		
//		size_t newParticles = (int)(Random(30.0f, 100.0f) * fTime + 0.5f);
//		newParticles = min( newParticles, m_iMaxSprites - (m_Particles.size()-m_idleParticleIndex.size()));
//
//		for (size_t i=0; i<newParticles; i++)
//		{		
//			if (m_idleParticleIndex.size())	
//			{			
//				// ���ڿ�������
//				list<int>::iterator it = m_idleParticleIndex.begin();
//	
//				m_Particles[*it].m_vPos = Vector3( 0.f, 0.f, 0.f);
//				m_Particles[*it].m_fSize = Random(0.1f, 0.5f);
//				m_Particles[*it].m_fLifeTime = Random(10.0f, 10.0f);
//				m_Particles[*it].m_vMoveDir = Vector3(Random(-1.0f, 1.0f), Random(-1.0f, 1.0f),Random(0.4f, 1.0f));
//				m_Particles[*it].m_color = 0xffffffff;
//				m_Particles[*it].m_bIdle = false;
//				m_Particles[*it].m_fAge = 0.0f;
//
//				m_idleParticleIndex.erase(it);
//			}
//			else
//			{
//				SSPrite  tParticle;	  // Ĭ������
//				tParticle.m_vPos = Vector3( 0.f, 0.f, 0.f);
//				tParticle.m_fSize = Random(0.1f, 0.5f);
//				tParticle.m_fLifeTime = Random(10.0f, 10.0f);
//				tParticle.m_vMoveDir = Vector3(Random(-1.0f, 1.0f), Random(0.4f, 1.0f),Random(-1.0f, 1.0f));
//				tParticle.m_color = 0xffffffff;
//				tParticle.m_bIdle = false;
//				m_Particles.push_back(tParticle);
//			}
//		}
//
//		// Render each particle
//		Rect3 rect3d;
//		VERTEX_PARTICLE* pVertices = m_pVertexData;
//		for(vector<SSPrite>::iterator it = m_Particles.begin(); it != m_Particles.end(); ++it)
//		{
//			if( !it->m_bIdle)
//			{
//				rect3d.UnionPoint( it->m_vPos);
//				pVertices->vPosition = it->m_vPos;
//				pVertices->pointSize = it->m_fSize;
//				pVertices->color = (DWORD)it->m_color;
//				pVertices++;
//			}
//		}
//
//		SetBoundingBox( rect3d);
//
//		// �������
//		m_pVertexBuffer->SetData( 0, sizeof(VERTEX_PARTICLE) * m_Particles.size(), m_pVertexData);
//	}
//
//
//	// �ύ����Ⱦ����( ʹ����Ч ��������)
//	void CParticleEmitter::SubmitToRenderQueue( const char* searchName)
//	{
//		//for ( size_t i=0; i<m_sqmNum; i++)
//		//{
//		//	SRenderSearchParam& it = m_searchQueueMaterial[i];
//		//	if( it.m_searchName == searchName)
//		//	{
//		//		SRenderEntry& renderEntry = AresRenderQueueMgr::OpenRenderQueue( it.m_queueName);
//		//		int totalPasses = it.m_material->GetEffectFile()->TotalPasses();
//
//		//		for (int iPass=0; iPass<totalPasses; iPass++)
//		//		{
//		//			renderEntry.hEffectFile      = it.m_material->GetEffectFile()->GetResourceHandle();
//		//			renderEntry.hSurfaceMaterial = it.m_material->GetResourceHandle();
//		//			renderEntry.modelType = SRenderEntry::EM_BUFFER_ENTRY;
//		//			renderEntry.hModel			 = m_pVertexBuffer->GetResourceHandle();
//		//			renderEntry.renderPass = iPass;
//		//			renderEntry.object = this;
//		//		}
//		//	}
//		//}
//	}
//
//	// ��Ⱦ
//	void CParticleEmitter::Render(SRenderEntry** entry, int iSameEntry, U32Flags activateionFlags)
//	{
//		// ������Ⱦ״̬
//		g_pDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, TRUE);
//		g_pDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  TRUE);   // TRUE ����Direct3D�������ӵ�������ľ������������ӳߴ�
//
//		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//
//		const CPtr<IEffectFile>& pEffectFile = m_pMaterial->GetEffectFile();
//		//pEffectFile->GetEffect()->SetMatrix();
//
//		if ( activateionFlags.TestBit( EM_ACTIVATE_RENDER_METHOD))
//		{
//			pEffectFile->Begin();
//		}
//
//		// Do we need to activate the surface material
//		if (activateionFlags.TestBit( EM_ACTIVATE_SURFACE_MATERIAL))
//		{
//			m_pMaterial->Apply();
//		}
//
//		// Do we need to active the render pass
//		if ( activateionFlags.TestBit( EM_ACTIVATE_RENDER_METHOD_PASS))
//		{
//			pEffectFile->ActivatePass( entry[0]->renderPass);
//		}
//
//		// Do we need to active the primary vertex buffer
//		if (activateionFlags.TestBit( EM_ACTIVATE_MODEL))
//		{
//			m_pVertexBuffer->SetStreamSource( 0, 0);
//			g_pDevice->SetFVF( D3DFVF_PARTICLE);
//		}
//
//		// render
//		HRESULT hr = g_pDevice->DrawPrimitive(
//			D3DPT_POINTLIST,
//			0,
//			m_Particles.size()
//			);
//
//		//// Reset render states
//		g_pDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
//		g_pDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  FALSE );
//		g_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,  FALSE);
//
//		//AlphaBlendEnable = true;
//		//SrcBlend = SrcAlpha;
//		//DestBlend = InvSrcAlpha; 
//		//ZWriteEnable = false; 
//	}
//}
