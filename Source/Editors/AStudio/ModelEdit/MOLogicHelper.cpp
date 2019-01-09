#include "MOLogicHelper.h"
#include <Engine/AresRoot.h>
#include <Engine/RenderSystem/AresRenderSystem.h>

namespace Ares
{
	// ����
	void CPutEntity::New( char* resPath)
	{
		// �����
		//SAFE_RELEASE( m_pEntity);

		// �½�ʵ����
		//m_resPath = resPath;
		//m_pEntity =  Root::GetSingleton()->GetRenderSystem()->CreateM1Entity(resPath);
		//m_pSceneNode   = g_pScene->RootNode()->CreateChildSceneNode();
		//m_pEntity->AttachSceneNode( m_pSceneNode);
	}

	// ����һ��
	void CPutEntity::Copy()
	{
		//// �������
		//if ( !m_resPath.empty())
		//{
		//	m_pEntity = Root::GetSingleton()->GetRenderSystem()->CreateM1Entity( m_resPath.c_str());
		//	m_pSceneNode = g_pScene->RootNode()->CreateChildSceneNode();
		//	m_pEntity->AttachSceneNode( m_pSceneNode);
		//}
	}

	// ���
	void CPutEntity::Clear()
	{
		// Ӧ�������ʵ���
		m_pEntity	 = s_ptr<Entity>();
		m_resPath.clear();
	}

	// ����ʵ��λ��
	void CPutEntity::SetPosition( Vector3& pos)
	{
		if ( m_pEntity)
		{
			Transform transform = m_pEntity->GetTransform();
			transform.SetTrans( pos);
			m_pEntity->SetTransform( transform);
		}
	}
}