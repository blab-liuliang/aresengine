#pragma once

#include <map>
#include <Engine/RenderSystem/AresModel.h>

using namespace std;

namespace Ares
{
	//---------------------------------------------
	// ģ�ͰڷŽṹ��  2010-08-16  ����
	//---------------------------------------------
	class CEntityPutLogic
	{
	public:
		typedef map<string, s_ptr<Model>> EntityMap;
	public:
		// ���캯��
		CEntityPutLogic();

		// ÿ֡����
		void FrameMove( float fTime, bool IsCursorInWindow);

		// ����
		void SetResPath( const char* resPath) { m_resPath = resPath; }

		// ����
		void New( EntityTypeDetail type);
		
		// ���
		void Reset();

		// ����
		void Put();

	private:
		// ��ȡΨһʵ����
		bool GetUniqueEntityName( char* uniqueName);

	private:
		EntityTypeDetail	m_typeDetail;		// ʵ�����
		s_ptr<Entity>		m_currEntity;		// ��ǰʵ��
		string				m_resPath;			// ��Դ·��
		EntityMap			m_dynamicEntityList;
	};
}