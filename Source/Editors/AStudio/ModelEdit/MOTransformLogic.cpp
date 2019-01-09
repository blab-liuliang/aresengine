#include <Physics/Intersect.h>
#include <Engine/AresRoot.h>
#include "MOLogic.h"

namespace Ares
{
	// ���캯��
	TransformLogic::TransformLogic()
	{
		// 3D���ʼ��
		m_3dAxis = new CAres3DAxis( MOLogic_RenderSystem.GetVisualShapeMgr());
		m_3dAxis->SetPosition( Vector3::Zero);
		m_3dAxis->SetVisible( false);

		m_bMouseLeftButtonDown = false;

		SetEditType( EM_MOVE);
	}

	// ÿ֡����
	void TransformLogic::FrameMove()
	{
		if( m_handleType == EM_SELECT)
			SelectEntity();

		// �ƶ�
		MouseMove();

		// ������̧��
		if ( m_bMouseLeftButtonDown && !MOLogic_Input->IsMouseDown( OIS::MB_Left))
		{
			m_bMouseLeftButtonDown = false;
			m_3dAxis->OnMouseUp();

			MOLogic_Input->RegisterMouseEventCallback( MOLogic_Camera);
		}

		// ����������
		if ( !m_bMouseLeftButtonDown && MOLogic_Input->IsMouseDown( OIS::MB_Left))
		{
			m_bMouseLeftButtonDown = true;

			Vector3 rayOrig;
			Vector3 rayDir;
			GetPickRay( rayOrig, rayDir);
			m_3dAxis->OnMouseDown( rayOrig, rayDir);

			if( m_3dAxis->IsWorking())
				MOLogic_Input->UnRegisterEventCallback( MOLogic_Camera);
		}
	}

	// ���ñ༭����
	void TransformLogic::SetTranformType( CAres3DAxis::EditType type)
	{
		if( m_3dAxis)
			m_3dAxis->SetEditType( type);
	}

	// ���ñ༭ʵ��
	void TransformLogic::SetSelected( Transform* transform)
	{
		// 2.�����ǰ��ѡ��ʵ��,����ʵ��,��ӵ�������
		m_curTransform = transform;
		if( m_curTransform)
		{
			// ��ʾ3D��
			m_3dAxis->Clear();
			m_3dAxis->SetVisible( true);
			m_3dAxis->SetPosition( m_curTransform->GetTrans());
			m_3dAxis->CatchTransform( transform);
		}
		else
		{
			UnSelect();
		}
	}

	// ȡ��ѡ��
	void TransformLogic::UnSelect()
	{
		// ��ʾ3D��
		m_3dAxis->Clear();
		m_3dAxis->SetVisible( false);
	}

	// ѡ��ʵ��
	void TransformLogic::SelectEntity()
	{
		//if( IsMLBDown())
		//{
		//	SPtr<Entity> pEntity = SCLogic_Map->SelectEntity();
		//	if( pEntity /*&& pEntity->GetTypeDetail() != ED_Model*/)
		//	{
		//		SetSelEntity( pEntity);
		//	}
		//}
	}

	// ����ƶ�
	void  TransformLogic::MouseMove()
	{
		static POINT m_lastPoint;

		POINT ptPoint;
		GetCursorPos( &ptPoint);
		ScreenToClient( MOLogic_RenderSystem.GetRenderSettings().m_hwnd, &ptPoint);

		// ����������(����3D��)
		//if ( IsMLBDown() MOLogic_Input->)
		{	
			Vector3 raylastOrig;
			Vector3 raylastDir;
			Vector3 rayOrig;
			Vector3 rayDir;

			RECT clientRect;
			::GetClientRect( MOLogic_RenderSystem.GetRenderSettings().m_hwnd, &clientRect);

			long clientWidth  = clientRect.right  - clientRect.left; 
			long clientHeight = clientRect.bottom - clientRect.top;

			WindowPointToRay( raylastOrig, raylastDir, m_lastPoint.x, m_lastPoint.y, clientWidth, clientHeight, MOLogic_Camera->GetView(), MOLogic_Camera->GetProj());
			WindowPointToRay( rayOrig, rayDir, ptPoint.x, ptPoint.y, clientWidth, clientHeight, MOLogic_Camera->GetView(), MOLogic_Camera->GetProj());

			m_3dAxis->OnMouseMove( raylastOrig, raylastDir, rayOrig, rayDir, &m_lastPoint, &ptPoint);
		}

		m_lastPoint = ptPoint;
	}


	// ���ñ༭����
	void TransformLogic::SetEditType( EHandleType type)
	{
		m_handleType = type;

		switch ( type)
		{
		case EM_SELECT:
			{

			}
			break;
		case EM_MOVE:
			{
				m_3dAxis->SetEditType( CAres3DAxis::EM_EDIT_TRANSLATE);
			}
			break;
		case EM_ROTATE:
			{
				m_3dAxis->SetEditType( CAres3DAxis::EM_EDIT_ROTATE);
			}
			break;
		case EM_SCALE:
			{
				m_3dAxis->SetEditType( CAres3DAxis::EM_EDIT_SCALE);
			}
			break;
		}
	}

	// ��ȡ��Ļ��ѡ����
	void TransformLogic::GetPickRay( Vector3& rayOrig, Vector3& rayDir)
	{
		HWND hwnd = MOLogic_RenderSystem.GetRenderSettings().m_hwnd;

		POINT ptPoint;
		::GetCursorPos( &ptPoint);
		::ScreenToClient( hwnd, &ptPoint);

		RECT clientRect;
		::GetClientRect( hwnd, &clientRect);

		long clientWidth  = clientRect.right  - clientRect.left; 
		long clientHeight = clientRect.bottom - clientRect.top;

		WindowPointToRay( rayOrig, rayDir, ptPoint.x, ptPoint.y, clientWidth, clientHeight, MOLogic_Camera->GetView(), MOLogic_Camera->GetProj(), MOLogic_Camera->GetOffset());
	}

	// ��ȡ���������
	void TransformLogic::Get3DAxisPickRay( Vector3& rayOrig, Vector3& rayDir)
	{
		HWND hwnd = MOLogic_RenderSystem.GetRenderSettings().m_hwnd;

		POINT ptPoint;
		::GetCursorPos( &ptPoint);
		::ScreenToClient( hwnd, &ptPoint);

		RECT clientRect;
		::GetClientRect( hwnd, &clientRect);

		long clientWidth  = clientRect.right  - clientRect.left; 
		long clientHeight = clientRect.bottom - clientRect.top;

		ScreenPointTo3DSpace( rayDir, ptPoint.x, ptPoint.y, clientWidth, clientHeight, MOLogic_Camera->GetViewProj());

		rayOrig = MOLogic_Camera->GetPosition();
		rayDir  = rayDir-rayOrig;
		rayDir.Normalize();
	}
}