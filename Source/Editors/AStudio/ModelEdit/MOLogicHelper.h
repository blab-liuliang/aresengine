#pragma once

#include <Engine/SceneSystem/AresEntity.h>

namespace Ares
{
	//---------------------------------------------
	// ģ�ͰڷŽṹ��  2010-08-16  ����
	//---------------------------------------------
	class CPutEntity
	{
	public:
		// ���캯��
		CPutEntity();

		// ����
		void New( char* resPath);

		// ����һ��
		void Copy();

		// ���
		void Clear();

		// ����ʵ��λ��
		void SetPosition( Vector3& pos);

	private:
		s_ptr<Entity>    m_pEntity;		// ʵ��
		string			m_resPath;		// ��Դ·��
	};

	// ���캯�� 
	inline CPutEntity::CPutEntity()
	{	
	}
}