//#pragma once
//
//#include "max.h"
//
//namespace M1_IGame
//{
//	//---------------------------------------
//	// ������� 2010-08-26     ����
//	//---------------------------------------
//	class CAeSceneExport : public SceneExport
//	{
//	public:
//		// ���캯��
//		CAeSceneExport();
//
//		// ��������
//		~CAeSceneExport();
//
//		// ��չ������
//		virtual int  ExtCount();
//
//		// �����ļ���׺��(�� "3DS")
//		virtual const char* Ext(int n);		
//
//		// ��ϸ����( ���� "Autodesk 3D Studio File")
//		virtual const char*	LongDesc();			
//
//		// �������
//		virtual const char*	ShortDesc();
//
//		// ������
//		virtual const char*	AuthorName();
//
//		// ��Ȩ��Ϣ
//		virtual const char*	CopyrightMessage();		
//
//		// ������Ϣ1
//		virtual const char*	OtherMessage1();
//
//		// ������Ϣ2
//		virtual const char*	OtherMessage2();	
//
//		// �汾��( ��. v3.01 = 301)
//		virtual UINT Version();
//
//		// ��ʾ����Show DLL's "About..." box
//		virtual void ShowAbout(HWND hWnd);
//
//		// ִ�е���
//		virtual int	DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);
//	};
//}