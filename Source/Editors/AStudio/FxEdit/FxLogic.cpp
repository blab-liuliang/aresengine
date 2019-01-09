#include "FxLogic.h"
#include <Engine/AresRoot.h>
#include <Physics/Rect3.h>
#include <Engine/FxSystem/AresFxSystem.h>
#include <string>

using namespace std;

namespace Ares
{ 
	// ȫ�ֱ���
	FxLogic*		g_fxLogic        = NULL;

	// ���캯��
	FxLogic::FxLogic()
	{
		g_fxLogic = this;
		m_fxEdit  = new_ FxEdit;
	}

	// �༭ʵ��
	void FxLogic::PickEntity()
	{
		Entity* pEntity = this->Pick();

		if( pEntity && pEntity->GetTypeDetail() == ED_Model)
		{
			// ��ʾ3D��
			m_p3DAxis->Clear();
			m_p3DAxis->SetVisible( true);
			//m_p3DAxis->GetTransform()->SetPosition( &pEntity->GetSceneNode()->GetPosition());
			//m_p3DAxis->CatchTransform( &pEntity->GetTransform());
		}
	}

	// ��Ⱦ����
	void FxLogic::FrameMove(float fTime)
	{
		//if( m_group)
		//	m_group->FrameMove( fTime);

		//IFxSystem* fxSystem = Root::GetSingleton()->GetFxSystem();
		//if( fxSystem)
		//	fxSystem->FrameMove( fTime);
		/*
		m_inputListener->Capture();

		if( m_cameraLogic)
		{
			m_auxiliaryDisplay->Refresh( fTime);

			m_cameraLogic->FrameMove( fTime);
		}

		// 
		m_fxEdit->FrameMove( fTime);

		Logic_Transform->FrameMove();
		
		// ����֡��
		UpdateFPS( fTime);*/
	}

	// ��Ⱦ
	void FxLogic::Render()
	{
		// ��Ⱦ
		//ARenderSystem.Render();
	}


	// ����������
	void FxLogic::OnMouseLeftButtonDown()
	{
		m_mouseLeftButtonDown = true;

		Vector3 rayOrig;
		Vector3 rayDir;
		this->GetPickRay( rayOrig, rayDir);

		if ( m_flags == EM_HT_EDITOENTITY)
		{
			this->PickEntity();
		}

		m_p3DAxis->OnMouseDown( rayOrig, rayDir);
	}

	// ������̧��
	void FxLogic::OnMouseLeftButtonUp()
	{
		m_mouseLeftButtonDown = false;

		if ( m_p3DAxis)
		{
			m_p3DAxis->OnMouseUp();
		}
	}

	// ����ƶ�
	void FxLogic::OnMouseMove()
	{

	}

	// ����ѡ
	Entity* FxLogic::Pick( Vector3* intersectPos, float* pDist)
	{
		//if ( g_pScene)
		//{
		//	D3DXVECTOR3 rayOrig;
		//	D3DXVECTOR3 rayDir;
		//	
		//	this->GetPickRay( rayOrig, rayDir);

		//	D3DXVECTOR3 intersePos = m_pCameraLogic->GetPosition();
		//	IEntity* pEntity = g_pScene->Pick( rayOrig, rayDir, 0.0f, 1000.0f, intersePos, pDist);
		//	if ( intersectPos)
		//	{
		//		*intersectPos = intersePos;
		//	}

		//	// ��ʾ��Χ��
		//	if ( pEntity)
		//	{
		//		static IBox* pBox = NULL;
		//		if ( !pBox)
		//		{
		//			pBox = g_pSceneMgr->CreateBox();
		//		}

		//		CRect3D rect = pEntity->GetSceneNode()->GetWorldBounds();
		//		
		//		// ��ʾ��Χ��
		//		pBox->SetParam( rect.x0, rect.y0, rect.z0, rect.x1, rect.y1,rect.z1);
		//	}

		//	return pEntity;
		//}

		return NULL;
	}

	// ��ȡ��Ļ��ѡ����
	void FxLogic::GetPickRay( Vector3& rayOrig, Vector3& rayDir)
	{
		//POINT ptPoint;
		//::GetCursorPos( &ptPoint);
		//::ScreenToClient( g_pApp->Hwnd(), &ptPoint);

		////g_pDevice->GetBackBuffer();
		//WindowPointToRay( rayOrig, rayDir, ptPoint.x, ptPoint.y, g_pApp->GetBackBufferWidth(), g_pApp->GetBackBufferHeight(), 
		//	g_pCameraLogic->GetView(), g_pCameraLogic->GetProj());
	}

	// ������䷽ʽ
	void FxLogic::SetFillMode(WORD index)
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

	//
	// inline
	//
	bool FxLogic::UpdateFPS(float fTime)
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
	void FxLogic::SetHandleType( EHandleType type)
	{
		m_flags = type;

		switch( m_flags)
		{
		case EM_HT_EDITORTERRAIN:
			{
				m_p3DAxis->SetVisible( false);	
			}
			break;
		}
	}

	// ���Ĵ��ڴ�С
	void FxLogic::ResizeWindow( int width, int height)
	{
		//m_cameraLogic->SetProjParams( PI / 4.f, width, height, .1f, 500.0f);

		//ARenderSystem.ResizeWindow( width, height);
	}
}