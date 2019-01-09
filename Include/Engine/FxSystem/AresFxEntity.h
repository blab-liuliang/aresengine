#pragma once

#include <vector>
#include "AresFxObject.h"
#include <Engine/SceneSystem/AresEntity.h>

using namespace std;

namespace Ares
{
	//------------------------------------------------------
	// Ч��ʵ�� 2011-9-14   ����
	//------------------------------------------------------
	class FxEntity : public Entity
	{
	public:
		FxEntity();
		~FxEntity() {}

		// ��ȡ��������
		int GetNumObjects() { return static_cast<int>(m_objects.size()); }

		// ��ȡ����
		FxObject* GetObjectByIndex( int idx);

		// ��ȡ����
		FxObject* GetObjectByName( const char* name);

		// ɾ��FxObject
		void DeleteObjectByIndex( int idx);

		// ��Ӷ���
		void AddObject( FxObject* object);

		// �Ƴ�����
		void RemoveObject( FxObject* object);

		// ����
		virtual void FrameMove( float fTime);

		// ִ��
		void SubmitRenderElements( RenderElementMgr& renderElementMgr);

		// ��ӵ�����
		virtual void OnAddToScene( Scene* scene);

		// ���±��ذ�Χ��
		void UpdateLocalBounds();

		// Serialize
		template<typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_objects;
		}

	private:
		vector<FxObject*>	m_objects;				// Ч�������б�
	};
	typedef s_ptr<FxEntity> FxEntityPtr;
}