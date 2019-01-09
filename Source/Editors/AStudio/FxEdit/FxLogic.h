#pragma once

#include <Core/Graphics/AresRenderWindow.h>
#include <Engine/FxSystem/AresFxSystem.h>
#include <EditorKit/Ares3DAxis.h>
#include "FxEdit.h"

namespace Ares
{
	//---------------------------------------
	// �༭���߼����	2010-07-20 ����	
	//---------------------------------------
	class FxLogic
	{
	public:
		// ���в�������
		enum EHandleType
		{
			EM_HT_NULL,					// Nothing
			EM_HT_EDITORTERRAIN,		// �༭����
			EM_HT_EDITTERRAINTEXTURE,	// �༭��������
			EM_HT_EDITOENTITY,			// �༭���������ʵ��(�ƶ� ��ת ����)
			EM_HT_PUTENTITY,			// �ڷ�ʵ��
			EM_HT_PUT_WATER,			// �ڷ�ˮ
			EM_HT_SELECT_WATER,			// ѡ��ˮ
			EM_HT_BRUSH_WATER,			// ˢˮ,����ˮ�ĸ߶�(������Ȼ�߶�)
		};

		// ���캯��
		FxLogic();

		// ����
		void FrameMove( float fTime);

		// ����3D��
		CAres3DAxis* Get3DAxis() { return m_p3DAxis; }

		// ��ȡ֡��
		float GetFPS()  { return m_fFPS; }

		// ��ȡ��Ļ��ѡ����
		void GetPickRay( Vector3& rayOrig, Vector3& rayDir);

		// ����������
		void OnMouseLeftButtonDown();

		// ������̧��
		void OnMouseLeftButtonUp();

		// ����ƶ�
		void OnMouseMove();

		// ����ѡ
		Entity* Pick( Vector3* intersectPos=NULL, float* pDist=NULL);

		// ��Ⱦ
		void Render();

		// ���ñ༭����
		void SetHandleType( EHandleType type);
		
		// ����֡��
		bool UpdateFPS( float fTime);

		// ������䷽ʽ
		void SetFillMode(WORD index);

	private:
		// �༭ʵ��
		void PickEntity();

	public:
		// ��ȡЧ���༭�߼�
		FxEdit* GetFxEdit() { return m_fxEdit; }

		// ���Ĵ��ڴ�С
		void ResizeWindow( int width, int height);

	private:
		HWND                    m_hWnd;
		EHandleType				m_flags;				// �������
		float                   m_fFPS;					// frames per second
		CAres3DAxis*			m_p3DAxis;				// 3D��   

		// ���λ�õ�
		POINT                   m_lastPoint;
		bool                    m_mouseLeftButtonDown;	// ����Ƿ���   

	public:
		FxEdit*					m_fxEdit;				// Ч���༭�߼�
	};

	extern  FxLogic*			g_fxLogic;
	#define FxLogic_Main		g_fxLogic
	#define FxLogic_FxEdit		FxLogic_Main->GetFxEdit()
}