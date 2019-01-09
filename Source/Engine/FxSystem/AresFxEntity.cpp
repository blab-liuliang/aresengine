#include <Engine/FxSystem/AresFxEntity.h>
#include <Engine/FxSystem/AresFx3DPatch.h>
#include <Engine/FxSystem/AresFxDecal.h>
#include <Engine/FxSystem/AresFxParticleSystem.h>
#include <Engine/SceneSystem/AresScene.h>

namespace Ares
{
	// ���캯��
	FxEntity::FxEntity()
		: Entity( ET_Render, ED_FxGroup)
	{
	}

	// ��ȡ����
	FxObject* FxEntity::GetObjectByIndex( int idx) 
	{
		if( idx<static_cast<int>(m_objects.size()))
		{
			//A_ASSERT( idx>=0 && idx<(int)m_objects.size());

			return m_objects[idx];
		}

		return NULL;
	}

	// ɾ��FxObject
	void FxEntity::DeleteObjectByIndex( int idx)
	{
		if( m_objects.size())
		{
			size_t back = m_objects.size()-1;
			swap( m_objects[back], m_objects[idx]);

			m_objects.pop_back();
		}
	}

	// ��ȡ����
	FxObject* FxEntity::GetObjectByName( const char* name)
	{
		for( size_t i=0; i<m_objects.size(); i++)
		{
			if( m_objects[i]->GetName()==string(name))
				return m_objects[i];
		}

		return NULL;
	}

	// ��Ӷ���
	void FxEntity::AddObject( FxObject* object)
	{
		A_ASSERT( object);

		if( object)
		{ 
			object->SetEntity( this);

			m_objects.push_back( object);
		}
	}

	// �Ƴ�����
	void FxEntity::RemoveObject( FxObject* object)
	{
		for ( vector<FxObject*>::iterator it=m_objects.begin(); it!=m_objects.end();)
		{
			if( object = *it)
				it = m_objects.erase(it);
			else
				it++;
		}
	}

	// ����
	void FxEntity::FrameMove( float fTime)
	{
		for ( vector<FxObject*>::iterator it=m_objects.begin(); it!=m_objects.end(); it++)
			(*it)->FrameMove( fTime, this);
	}

	// ִ��
	void FxEntity::SubmitRenderElements( RenderElementMgr& renderElementMgr)
	{
		for ( vector<FxObject*>::iterator it=m_objects.begin(); it!=m_objects.end(); it++)
			(*it)->SubmitRenderElements( renderElementMgr);
	}

	// ��ӵ�����
	void FxEntity::OnAddToScene( Scene* scene)
	{
		Entity::OnAddToScene( scene);

		for ( vector<FxObject*>::iterator it=m_objects.begin(); it!=m_objects.end(); it++)
		{
			switch( (*it)->GetType())
			{
			case FOT_Decal:
				{
					FxDecal* decal = dynamic_cast<FxDecal*>(*it);
					if( decal)
						decal->SetPhysicsWorld( scene->GetPhysicsWorld());
				}
				break;
			}
		}
	}

	// ���±��ذ�Χ��
	void FxEntity::UpdateLocalBounds()
	{
		Rect3 localBounds;
		for ( vector<FxObject*>::iterator it=m_objects.begin(); it!=m_objects.end(); it++)
		{
			const Rect3& objectLocalBounds = (*it)->GetLocalBounds();
			localBounds.UnionPoint( objectLocalBounds.m_min);
			localBounds.UnionPoint( objectLocalBounds.m_max);
		}

		SetLocalBounds( localBounds);
	}
}