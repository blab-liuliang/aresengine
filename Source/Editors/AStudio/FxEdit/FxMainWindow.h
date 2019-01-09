#ifndef MODEL_MAINWINDOW_H
#define MODEL_MAINWINDOW_H

#include "QMainWindowEx.h"
#include "ui_FxMainWindow.h"
#include "FxPropertyEdit.h"
#include "FxObjectViewer.h"
#include "FxLogic.h"

using namespace Ares;

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class FxMainWindow : public QObject, public Ui_FxMainWindow
	{
		Q_OBJECT

	public:
		// ���캯��
		FxMainWindow( QMainWindowEx* parent = 0);

		// ����
		void Active();

		// ʧЧ
		void Deactive();

		// ��ʼ��Ⱦ
		void BeginRender();

		// ��ȡ���Ա༭����
		FxPropertyEdit* GetPropertyEditor() { return m_propertyEdit; }

		// ��ȡ����鿴��
		FxObjectViewer* GetObjectViewer() { return m_objectViewer; }

	private slots:
		// �½�Ч��
		void New();

		// ��Ч���ļ�
		void Open();

		// ����Ч���ļ�
		void Save();

		// ��ʾ���ظ���
		void SwitchGridVisible();

		// ��ʾ���ر���
		void SwitchBackgroundVisible();

		// ת�������������
		void SwitchToGeneralCamera();

		// ת��Ϊ��������
		void SwitchToSkyCamera();

		// ����ת������Ϊƽ��
		void SetTransTypeMove();

		// about
		void  AresAbout();

	private:
		FxPropertyEdit*		m_propertyEdit;		// ���Ա༭˳
		FxObjectViewer*		m_objectViewer;		// ����鿴��
		QMainWindowEx*		m_mainWindow;		// ������
	};

	extern  FxMainWindow*		g_mainWindowFx;						
	#define FxUI_MainWindow		g_mainWindowFx							// ������
	#define FxUI_PropertyEdit	FxUI_MainWindow->GetPropertyEditor()	// ���Ա༭����
	#define FxUI_ObjectView		FxUI_MainWindow->GetObjectViewer()
}

#endif