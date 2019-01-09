#ifndef MODEL_MAINWINDOW_H
#define MODEL_MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_SHMainWindow.h"
#include "UIShaderTreeDisplay.h"
#include "ParametersEditor.h"
#include "UIMaterialExpression.h"
#include "SHLogic.h"

namespace Ares
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class SHMainWindow : public QMainWindow, public Ui_SHMainWindow
	{
		Q_OBJECT

	public:
		// ���캯��
		SHMainWindow( QWidget* parent = 0);

		// ��ʼ��Ⱦ
		void BeginRender();

		// �ļ�����
		void FileCorelation();

		// ���ļ�
		void Open( const char* fileName);

		// ״̬�ı�,���ƽ�����ʾ
		void OnStateChanged();

		// ��ȡ�����༭��
		UIParametersEditor* GetParametersEditor() { return m_parametersEditor; }

		// ��ȡ�������༭��
		UIShaderTreeDisplay* GetShaderTreeDisplay() { return m_pMdiArea; }

	private slots:
		// ��
		void Open();

		// ����
		void Save();

		// �½�������
		void NewShaderTree();

		// zoom
		void  ZoomEntity();

		// about
		void  AresAbout();

	private:
		SHLogic*				m_shLogic;				// �߼�
		UIParametersEditor*		m_parametersEditor;		// ���Ա༭
		UIShaderTreeDisplay*	m_pMdiArea;				// dx9Ӧ��
		UIMaterialExpression*	m_materialExpression;	// ���ʱ��ʽ
	};

	extern  SHMainWindow*			g_mainWindowSH;	
	#define SHUI_MainWindow			g_mainWindowSH
	#define SHUI_ParametersEditor	SHUI_MainWindow->GetParametersEditor()
	#define SHUI_ShaderTreeDisplay	SHUI_MainWindow->GetShaderTreeDisplay()
}

#endif