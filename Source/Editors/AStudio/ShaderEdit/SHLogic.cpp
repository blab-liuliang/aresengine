#include "SHLogic.h"
#include <Engine/AresRoot.h>
#include <Engine/RenderSystem/SuperMaterialShaderTree.h>
#include <Physics/IntrParabola3Rect3.h>
#include <string>

using namespace std;

namespace Ares
{ 
	// ȫ�ֱ���
	SHLogic*	 g_pSHLogic  = NULL;

	// ���캯��
	SHLogic::SHLogic()
	{
		g_pSHLogic = this;

		m_shaderTreeEdit = new_ ShaderTreeEdit;
	}

	// Ϊ��ǰ���ʸ���ģ��
	void SHLogic::SetModel( const char* resPath)
	{
		//if( m_activeEntity)
		//{
		//	// ����ģ��
		//	SPtr<IAresModel> pModel = g_pResManager->CreateAresModel( resPath);

		//	m_activeEntity->SetModel( pModel);
		//}
	}

	// Ӧ�õ�ǰ����shader
	void SHLogic::ApplyShader()
	{
		//m_pMaterialList[0]->ReBirth();

		//float a = 0.005f;

		//m_pMaterialList[0]->SetTexture( 0, "Data\\m1\\kucao_001.tga");
		//m_pMaterialList[0]->SetStaticData( (size_t)0, &a);
	}

	// ����shader
	void SHLogic::SetActiveShader( const char* shaderName, const char* modelName)
	{
		//// ȫ������ʾ
		//for ( EntityMap::iterator it=m_entitys.begin(); it!=m_entitys.end(); it++)
		//{
		//	it->second->SetVisible( false);
		//}

		//EntityMap::iterator it = m_entitys.find( shaderName);
		//if( it == m_entitys.end())
		//{
		//	// ������
		//	SPtr<IM1Entity> pEntity = Root::GetRenderSystem()->CreateM1Entity( NULL);
		//	if( pEntity)
		//	{
		//		// ���ӵ��������
		//		SPtr<SceneNode> pSceneNode = m_area->GetRootNode()->CreateChildSceneNode();
		//		pEntity->AttachSceneNode( pSceneNode);

		//		// �����ж��Ƿ��Ѵ��ڵ�shader
		//		// �������
		//		char matName[1024];
		//		changeExt( matName, shaderName, ".material");

		//		DWORD result = GetFileAttributesA( matName);

		//		if( INVALID_FILE_ATTRIBUTES == result)
		//		{
		//			// ������
		//			SPtr<ISurfaceMaterial> pMaterial = g_pResManager->CreateSurfaceMaterial();
		//			pMaterial->LoadEffectFile( shaderName);
		//			pEntity->SetMaterial( pMaterial);
		//		}
		//		else
		//		{
		//			// ����
		//			SPtr<ISurfaceMaterial> pMaterial = g_pResManager->CreateSurfaceMaterial( matName, false);
		//			pMaterial->LoadResource();
		//			pEntity->SetMaterial( pMaterial);
		//		}

		//		m_entitys[shaderName] = pEntity;
		//		m_activeEntity		  = pEntity;
		//		m_shaderName		  = shaderName;	
		//	}
		//}
		//else
		//{
		//	m_activeEntity = it->second;
		//	m_shaderName   = shaderName;	
		//}

		//// ����ģ��
		//if( modelName)
		//	SetModel( modelName);

		//m_activeEntity->SetVisible( true);
	}

	// ���浱ǰ����shader����ʾ����
	void SHLogic::SaveActiveShader()
	{
		//if( m_activeEntity)
		//{
		//	// �������
		//	char matName[1024];
		//	changeExt( matName, m_shaderName.c_str(), ".material");

		//	SPtr<ISurfaceMaterial> pMaterial = m_activeEntity->GetMaterial();
		//	pMaterial->Save( matName);
		//}
	}

	// ��ȡ�������
	//RenderMaterial& SHLogic::GetActiveMaterial()
	//{
	//	return m_material;
	//}

	// ����Ƿ��ڴ�����
	static bool IsCursorInWindow( HWND hwnd)
	{
		POINT ptPoint;
		GetCursorPos( &ptPoint);

		RECT clientRect;
		GetWindowRect( hwnd, &clientRect);		

		if ( ptPoint.x > clientRect.left && ptPoint.x <clientRect.right
			&& ptPoint.y > clientRect.top && ptPoint.y <clientRect.bottom)
			return true;

		return false;
	}

	// ��Ⱦ����
	void SHLogic::FrameMove(float fTime)
	{	
		// ����֡��
		UpdateFPS( fTime);

		static float fTotalTime = 0.0f;
		fTotalTime += fTime;

		if (fTotalTime > 0.05f)
		{
			fTotalTime = 0.0f;
		}
	}

	// ��Ⱦ
	void SHLogic::Render()
	{
		//if(m_map)
		//	m_map->Render();
	}

	// ������䷽ʽ
	void SHLogic::SetFillMode(WORD index)
	{
		if ( index == 0)
		{
			//g_pSceneMgr->SetFillMode( D3DFILL_POINT);
		}
		else if( index == 1)
		{
			//g_pSceneMgr->SetFillMode( D3DFILL_WIREFRAME);
		}
		else
		{
			//g_pSceneMgr->SetFillMode( D3DFILL_SOLID);
		}
	}

	// ����ʵ��
	void SHLogic::SetModelEntity( const char* resPath)
	{
		// ��ֹ�ظ�����
		//static string tResPath;
		//if( strcmp( tResPath.c_str(), resPath)==0)
		//	return;
		//else
		//	tResPath = resPath;

		//SPtr<IM1Entity> pEntity = Root::GetRenderSystem()->CreateM1Entity( resPath);
		//SPtr<SceneNode> pSceneNode = m_area->GetRootNode()->CreateChildSceneNode();
		//pEntity->AttachSceneNode( pSceneNode);
		//pSceneNode->SetPosition( 0.f, 0.f, 0.f);
		//pEntity->GetAnimationController()->PlayAnimationByIndex( 0, true);

		//m_pEntity = (pEntity);
	}

	// inline
	bool  SHLogic::UpdateFPS(float fTime)
	{
		static float fTotalTime = 0.0f;
		static DWORD dwFrames   = 0;

		fTotalTime += fTime;
		dwFrames++;

		if (fTotalTime > 0.5f)
		{
			m_fFPS = dwFrames / fTotalTime;

			fTotalTime = 0.0f;
			dwFrames   = 0;

			// ��������
			return true;
		}

		// δ����
		return false;
	}
}