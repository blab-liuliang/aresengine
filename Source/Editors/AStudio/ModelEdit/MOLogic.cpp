#include "MOLogic.h"
#include <Engine/AresRoot.h>
#include <Core/AresCore.h>
#include <Engine/RenderSystem/AresAnimationController.h>

using namespace std;

namespace Ares
{ 
	// ȫ�ֱ���
	MOLogic*	g_MOLogic        = NULL;

	// ���캯��
	MOLogic::MOLogic( HWND hwnd)
	{
		MOLogic_Main = this;

		m_flags			= EM_HT_NULL;

		RenderSettings tSettings( hwnd);
		tSettings.m_title      = "ModelEditor";

		// ��������
		m_cameraLogic = new_ MOCameraLogic();	
		m_cameraLogic->SetProjParams( PI / 4.f, tSettings.m_width, tSettings.m_height, .2f, 200.0f);
		//if( m_sceneSystem = ARoot->BuildSceneSystem( m_cameraLogic, tSettings))
		{
			m_scene					= ARoot->BuildScene( m_cameraLogic, tSettings, NULL, NULL);
			m_modelEdit				= new_ ModelEdit;
			m_lightmapUVBuild		= new_ LightmapUVBuild;
			m_lightmapUVRender		= new_ LightmapUVRender;
			m_collisionBuildLogic	= new_ CollisionBuildLogic;
			m_transformLogic		= new_ TransformLogic;
			m_lightLogic			= new_ LightEditLogic;
			m_inputListener			= new_ MOInputListener(hwnd);

			m_inputListener->RegisterMouseEventCallback( m_cameraLogic);
		}
	}

	// ��������
	MOLogic::~MOLogic()
	{
		MOConfigMgr::Destory();

		SAFE_DELETE(g_lightmapUVBuild);
	}

	// �Ƿ���ͣ��
	bool MOLogic::IsPaused()
	{
		if( !m_scene)
			return true;

		if( m_scene->IsPaused())
			return true;

		return false;
	}

	// ���Ĵ��ڴ�С
	void MOLogic::ResizeWindow( int width, int height)
	{
		static size_t oWidth = 65535, oHeight = 65535;
		if( oWidth!=width || oHeight!=height)
		{
			m_cameraLogic->SetProjParams( PI / 4.f, width, height, .2f, 200.0f);

			MOLogic_RenderSystem.ResizeWindow( width, height);

			oWidth = width;
			oHeight= height;
		}
	}

	// ��Ⱦ����
	void MOLogic::FrameMove(float fTime)
	{
		m_inputListener->Capture();

		if( m_cameraLogic)
			m_cameraLogic->FrameMove( fTime);

		if( m_lightLogic)
			m_lightLogic->FrameMove();

		MOLogic_ModelEdit->FrameMove( fTime);

		MOLogic_Transform->FrameMove();

		if( m_scene)
		{
			m_scene->FrameMove( fTime);
		}
		
		// ����֡��
		UpdateFPS( fTime);
	}

	// ���ʵ��
	void MOLogic::AddEntity( char* namePath)
	{
	}

	// ������䷽ʽ
	void MOLogic::SetFillMode(WORD index)
	{
		//if ( index == 0)
		//{
		//	g_pSceneMgr->SetFillMode( D3DFILL_POINT);
		//}
		//else if( index == 1)
		//{
		//	g_pSceneMgr->SetFillMode( D3DFILL_WIREFRAME);
		//}
		//else
		//{
		//	g_pSceneMgr->SetFillMode( D3DFILL_SOLID);
		//}
	}

	// ���Ŷ���
	void MOLogic::PlayAnimation(int index)
	{/*
		if( m_currEntity)
		{
			m_currEntity->GetAnimationController()->PlayAnimationByIndex( index, true);
		}*/
	}

	// ��ȡ��ģ������
	size_t  MOLogic::GetMeshNum()
	{
		//IMd3Entity* pMd3Entity = m_pEntityList[0];
		//if ( pMd3Entity)
		//{
		//	return pMd3Entity->GetMeshNum();
		//}

		return 0;
	}

	// �½���ɫ
	void MOLogic::NewCharacter( const char* resPath)
	{/*
		ICharacterEntity* pEntity = Root::GetRenderSystem()->CreateCharacterEntity();

		pEntity->Save( resPath);*/
	}

	// ��ȡ�����ļ��в�����
	int MOLogic::GetMaterialNumInFile( const char* matFile)
	{
		// ���ز���
		//SPtr<ISurfaceMaterial> pMaterial = g_pResManager->CreateSurfaceMaterial( matFile, false);
		//pMaterial->LoadResource();

		//return pMaterial->GetMaterialNum();
		return 0;
	}

	// ��ʾ��������ϵ
	void MOLogic::ShowBoneCoord( const Matrix44& coord)
	{
		//m_p3DAxis->SetVisible( true);
		//m_p3DAxis->SetPosition( coord._41, coord._42, coord._43);
	}

	// ת������
	void MOLogic::ChangeTextureToDDS( vector<string>& textures)
	{
		for ( size_t i=0; i<textures.size(); i++)
		{
			//D3DXCreateTexture( g_pDevice, iWidth, iHeight, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_DXT1, D3DX, &m_pTexture)
		}
	}

	//
	// inline
	//
	bool MOLogic::UpdateFPS(float fTime)
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

	// ���ñ༭����
	void MOLogic::SetHandleType( EHandleType type)
	{
		m_flags = type;
	}
}