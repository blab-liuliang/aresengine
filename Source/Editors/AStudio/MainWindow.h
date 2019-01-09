#pragma once

#include <QTimer>
#include <QMainWindowEx.h>
#include <Core/AresSingleton.hpp>
#include "ui_MainWindow.h"
#include "SCMainWindow.h"
#include "FxEdit/FxMainWindow.h"
#include "ModelEdit/MOMainWindow.h"
#include "UIEdit/UIMainWindow.h"
#include "Application.h"
#include "MdiArea.h"

namespace QT_UI
{
	//----------------------------------------
	// AStudio ������ 2013-07-25
	//----------------------------------------
	class MainWindow : public QMainWindowEx
	{
		Q_OBJECT

	public:
		MainWindow( QWidget* parent = 0);
		~MainWindow();

	public:
		// ����
		void Active();

		// ʧЧ
		void Deactive();

		// ��ʼ��Ⱦ
		void BeginRender();

		// ��־���
		LogPanel* GetLogPanel() { return m_logPanel; }

	public slots:
		// ���ñ༭������
		void SetEditorType( const QString& edType);

		// ѭ��
		void Loop();

		// ����
		void  AresAbout();

	private:
		QTimer*				m_timer;			// ��ʱ��
		Application*		m_application;		// Ӧ�ó���
		Ui_MainWindow		m_mainMenuToolBar;	// �����ڱ༭MenuBar ToolBar
		SCMainWindow*		m_scUILayout;		// �����༭��MenuBar ToolBar
		MOUILayout*			m_moUILayout;		// ģ�ͱ༭����
		FxMainWindow*		m_fxUILayout;		// ��Ч�༭����
		UIMainWindow*		m_uiUILayout;		// ����༭����
		LogPanel*			m_logPanel;			// ��־��徯��������ʾ

		MOMdiArea*			m_mdiArea;			// ��������

		QComboBox*			m_comBoBox;
	};

	extern  MainWindow*			g_mainWindow;	// ������
	#define UI_MainWindow		g_mainWindow	// ������
	#define UI_LogPanel			UI_MainWindow->GetLogPanel()
}