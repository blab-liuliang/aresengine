#include "EntityEditLogic.h"
#include <Physics/Intersect.h>
#include "SCLogic.h"
#include "SCMainWindow.h"
#include "PropertyEditor.h"

using namespace QT_UI;

namespace Ares
{
	// ���캯��
	CEntityEditLogic::CEntityEditLogic()
		: m_entityWorldBox( NULL)
		, m_curEditEntity( NULL)
	{
		m_entityWorldBox = SELogic_VisualShape.CreateRect3();

		// 3D���ʼ��
		m_p3DAxis = new CAres3DAxis( SELogic_VisualShape);
		m_p3DAxis->SetPosition( 0.0f, 0.0f, 0.0f);
		m_p3DAxis->SetVisible( false);

		m_bMouseLeftButtonDown = false;
	}

	// ÿ֡����
	void CEntityEditLogic::FrameMove()
	{
		if( m_handleType == EM_SELECT)
			SelectEntity();

		// �ƶ�
		MouseMove();

		// ������̧��
		if ( m_bMouseLeftButtonDown && !SCLogic_Input->IsMouseDown( OIS::MB_Left))
		{
			m_bMouseLeftButtonDown = false;
			m_p3DAxis->OnMouseUp();
		}

		// ����������
		if ( !m_bMouseLeftButtonDown && SCLogic_Input->IsMouseDown( OIS::MB_Left))
		{
			m_bMouseLeftButtonDown = true;

			Vector3 rayOrig;
			Vector3 rayDir;
			Logic_Physics->GetPickRay( rayOrig, rayDir);
			m_p3DAxis->OnMouseDown( rayOrig, rayDir);
		}

		// ȡ��ѡ��
		if( IsKeyDown( OIS::KC_ESCAPE))
		{
			SetSelEntity( NULL);
		}

		// ɾ����ǰѡ��ʵ��
		if( IsKeyDown( OIS::KC_DELETE))
		{
			DeleteSelectedEntity();
		}
	}

	// �򳡾������Entity
	void CEntityEditLogic::AddEntity( const char* uName, s_ptr<Entity>& pEntity)
	{
		if( SCLogic_Scene)
			SCLogic_Scene->AddEntity( uName, pEntity);

		// ���ñ�ѡ��
		SetSelEntity( pEntity.get());
	}

	// ���ñ༭ʵ��
	void CEntityEditLogic::SetSelEntity( Entity* pEntity)
	{
		if( pEntity)
		{
			// 2.�����ǰ��ѡ��ʵ��,����ʵ��,��ӵ�������
			m_curEditEntity = pEntity;
			if( m_curEditEntity)
			{
				// ��ʾ3D��
				m_p3DAxis->Clear();
				m_p3DAxis->SetVisible( true);
				m_p3DAxis->SetPosition( m_curEditEntity->GetTransform().GetTrans());
				m_p3DAxis->CatchEntity( m_curEditEntity);
			}

			// ����ѡ���ʵ������, ��ʾ���Կ���
			SCUI_Property->ShowProperty( pEntity);
		}
		else
		{
			m_p3DAxis->Clear();
			m_p3DAxis->SetVisible( false);
			SCUI_Property->ShowProperty( NULL);

			m_curEditEntity = NULL;

			ShowWorldBox();
		}

		ShowWorldBox();
	}

	// ���ñ༭ʵ��
	void CEntityEditLogic::SetSelEntity( const string& entityName)
	{
		// �Ƴ�
		Scene* pScene = SCLogic_Scene;
		if( pScene)
		{
			EntityPtr& selEntity = pScene->GetEntity( entityName.c_str());
			if( selEntity)
			{
				SetSelEntity( selEntity.get());
			}
		}
	}

	// ɾ����ǰѡ��ʵ��
	void CEntityEditLogic::DeleteSelectedEntity()
	{
		Entity* entity = m_curEditEntity;
		if( entity)
		{
			// �ÿ�ѡ��
			SetSelEntity( NULL);

			// �Ƴ�
			Scene* pScene = SCLogic_Scene;
			if( pScene)
				pScene->DelEntity( entity->GetName());
		}
	}

	// ѡ��ʵ��
	void CEntityEditLogic::SelectEntity()
	{
		if( IsMLBDown())
		{
			Entity* entity = SCLogic_Map->SelectEntity();

			SetSelEntity( entity);
		}
	}

	// ����ƶ�
	void  CEntityEditLogic::MouseMove()
	{
		static POINT m_lastPoint;

		POINT ptPoint;
		GetCursorPos( &ptPoint);
		ScreenToClient( SCLogic_Main->GetHwnd(), &ptPoint);

		// ����������(����3D��)
		if ( IsMLBDown())
		{	
			Vector3 raylastOrig;
			Vector3 raylastDir;
			Vector3 rayOrig;
			Vector3 rayDir;

			RECT clientRect;
			::GetClientRect( SCLogic_Main->GetHwnd(), &clientRect);

			long clientWidth  = clientRect.right  - clientRect.left; 
			long clientHeight = clientRect.bottom - clientRect.top;

			WindowPointToRay( raylastOrig, raylastDir, m_lastPoint.x, m_lastPoint.y, clientWidth, clientHeight, SCLogic_Camera->GetView(), SCLogic_Camera->GetProj());
			WindowPointToRay( rayOrig, rayDir, ptPoint.x, ptPoint.y, clientWidth, clientHeight, SCLogic_Camera->GetView(), SCLogic_Camera->GetProj());

			m_p3DAxis->OnMouseMove( raylastOrig, raylastDir, rayOrig, rayDir, &m_lastPoint, &ptPoint);

			if( !m_curEditEntity)
				SCUI_Property->ShowFrame( "Setting");

			// ����ѡ���ʵ������, ��ʾ���Կ���
			//if( m_pCurEditEntity->GetDetailType() == Entity::EM_DT_LIGHTPOINT)
			//	g_mainWindow->GetPropertyEditor()->ShowFrame( "PointLight");

			ShowWorldBox();
		}

		m_lastPoint = ptPoint;
	}


	// ���ñ༭����
	void CEntityEditLogic::SetEditType( EHandleType type)
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
				m_p3DAxis->SetEditType( CAres3DAxis::EM_EDIT_TRANSLATE);
			}
			break;
		case EM_ROTATE:
			{
				m_p3DAxis->SetEditType( CAres3DAxis::EM_EDIT_ROTATE);
			}
			break;
		case EM_SCALE:
			{
				m_p3DAxis->SetEditType( CAres3DAxis::EM_EDIT_SCALE);
			}
			break;
		}
	}

	// ��ʾ��Χ��
	void CEntityEditLogic::ShowWorldBox()
	{
		// ��ʾ��Χ��
		if ( m_curEditEntity)
		{
			Rect3 rect = m_curEditEntity->GetWorldBounds();

			// ��ʾ��Χ��
			m_entityWorldBox->Set( rect);
			m_entityWorldBox->SetVisible( true);
		}
		else
		{
			m_entityWorldBox->SetVisible( false);
		}
	}
}