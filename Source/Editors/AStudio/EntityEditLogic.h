#pragma once

#include <EditorKit/Ares3DAxis.h>
#include <Engine/SceneSystem/AresEntity.h>

namespace Ares
{
	//---------------------------------------
	// ʵ��༭�߼�	2011-01-18 ����	
	//---------------------------------------
	class CEntityEditLogic
	{
	public:
		enum EHandleType
		{
			EM_PUT,		// �ڷ�
			EM_SELECT,	// ѡ��
			EM_MOVE,	// �ƶ�
			EM_ROTATE,	// ��ת
			EM_SCALE,	// ����
		};

		// ���캯��
		CEntityEditLogic();

		// ÿ֡����
		void  FrameMove();

		// �򳡾������Entity
		void AddEntity( const char* uName, s_ptr<Entity>& pEntity);

		// ���ñ༭ʵ��
		void SetSelEntity( Entity* pEntity);

		// ���ñ༭ʵ��
		void SetSelEntity( const string& entityName);

		// ѡ��ʵ��
		void  SelectEntity();

		// ɾ����ǰѡ��ʵ��
		void DeleteSelectedEntity();

		// ���ñ༭����
		void  SetEditType( EHandleType type);

		// ����3D������
		void SetAxisScale( float scale) { m_p3DAxis->SetScale( scale); }

	public:
		// ��ȡ��ǰ�༭ʵ��
		template<typename T> T* GetEditEntity() const { return static_cast<T*>( m_curEditEntity);}

	private:
		// ÿ֡����
		void  MouseMove();

		// ��ʾ��Χ��
		void ShowWorldBox();

	private:
		EHandleType			m_handleType;			// ��������
		CAres3DAxis*		m_p3DAxis;				// 3D��
		bool				m_bMouseLeftButtonDown;
		Entity*				m_curEditEntity;		// ��ǰ�༭��ʵ��
		VisualRect3*		m_entityWorldBox;		// �����Χ��
	};
}