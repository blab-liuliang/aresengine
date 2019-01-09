#pragma once

#include <EditorKit/Ares3DAxis.h>

namespace Ares
{
	//---------------------------------------
	// ת���༭�߼�	2011-01-18 ����	
	//---------------------------------------
	class TransformLogic
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
		TransformLogic();

		// ÿ֡����
		void  FrameMove();

		// ���ñ༭����
		void SetTranformType( CAres3DAxis::EditType type);

		// ���ñ༭ʵ��
		void SetSelected( Transform* transform);

		// ȡ��ѡ��
		void UnSelect();

		// ѡ��ʵ��
		void  SelectEntity();

		// ���ñ༭����
		void  SetEditType( EHandleType type);

		// ����3D������
		void SetAxisScale( float scale) { m_3dAxis->SetScale( scale); }

	public:
		// ��ȡ��ǰ�༭ʵ��
		Transform* GetCurTransform() { return m_curTransform; }

		// ��ȡ��Ļ��ѡ����
		void GetPickRay( Vector3& rayOrig, Vector3& rayDir);

		// ��ȡ���������
		void Get3DAxisPickRay( Vector3& rayOrig, Vector3& rayDir);

	private:
		// ÿ֡����
		void  MouseMove();

	private:
		EHandleType			m_handleType;			// ��������
		CAres3DAxis*		m_3dAxis;				// 3D��
		Transform*			m_curTransform;			// ��ǰ������
		bool				m_bMouseLeftButtonDown;
	};
}