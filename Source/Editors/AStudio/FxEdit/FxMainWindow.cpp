#include <QtGui/QtGui>
#include "FxMainWindow.h"

using namespace Ares;

namespace QT_UI
{
	FxMainWindow*	g_mainWindowFx = NULL;			// ������

	// ���캯��
	FxMainWindow::FxMainWindow( QMainWindowEx* parent/* = 0*/)
		: m_mainWindow( parent)
	{
		g_mainWindowFx = this;

		// �߼�����
		new_ FxLogic();

		setupUi( m_mainWindow);

		// ��Ϣ����
		connect( m_pActionAbout, SIGNAL(triggered()), this, SLOT(AresAbout()));
		connect( m_actionNew,	 SIGNAL(triggered()), this, SLOT(New()));
		connect( m_actionOpen,	 SIGNAL(triggered()), this, SLOT(Open()));
		connect( m_actionSave,	 SIGNAL(triggered()), this, SLOT(Save()));
		connect( m_gridVisible,  SIGNAL(triggered()), this, SLOT(SwitchGridVisible()));
		connect( m_bgVisible,	 SIGNAL(triggered()), this, SLOT(SwitchBackgroundVisible()));

		connect( m_generalCamera,SIGNAL(triggered()), this, SLOT(SwitchToGeneralCamera()));
		connect( m_skyCamera,    SIGNAL(triggered()), this, SLOT(SwitchToSkyCamera()));

		// ����鿴��
		m_objectViewer = new_ FxObjectViewer( m_mainWindow);
		m_mainWindow->addDockWidget( Qt::RightDockWidgetArea, m_objectViewer);

		// ���Ա༭��
		m_propertyEdit = new_ FxPropertyEdit( m_mainWindow);
		m_mainWindow->addDockWidget( Qt::RightDockWidgetArea, m_propertyEdit);

		connect( m_actionTrans,	   SIGNAL(triggered()), this, SLOT(SetTransTypeMove()));

		m_objectViewer->setVisible( false);
		m_propertyEdit->setVisible( false);
	}

	// ����
	void FxMainWindow::Active()
	{
		m_mainWindow->setMenuBar( m_menuBar);

		m_toolBar->setVisible( true);
		m_objectViewer->setVisible( true);
		m_propertyEdit->setVisible( true);
	}

	// ʧЧ
	void FxMainWindow::Deactive()
	{
		m_toolBar->setVisible( false);
		m_objectViewer->setVisible( false);
		m_propertyEdit->setVisible( false);
	}

	// ��ʼ��Ⱦ
	void FxMainWindow::BeginRender() 
	{ 
	}

	// �½�Ч��
	void FxMainWindow::New()
	{
		if( FxLogic_FxEdit->GetFxEntity())
		{
		}

		FxLogic_FxEdit->New();
	}

	// ��Ч���ļ�
	void FxMainWindow::Open()
	{
		QString qFileName = QFileDialog::getOpenFileName( m_mainWindow, tr("Open Model"), "", tr("*.afx"));
		if( !qFileName.isEmpty())
		{
			string fileName = qFileName.toLocal8Bit();

			FxLogic_FxEdit->OpenAfx( fileName.c_str());

			m_objectViewer->UpdateObjectListDisplay();
		}
	}

	// ����Ч���ļ�
	void FxMainWindow::Save()
	{
		string fileName = FxLogic_FxEdit->GetAfxPath();
		if( fileName.empty())
		{
			QString qFileName = QFileDialog::getSaveFileName( m_mainWindow, tr("Save Afx"), "", tr("*.afx"));
			if( !qFileName.isEmpty())
				fileName = qFileName.toLocal8Bit();
		}
		
		FxLogic_FxEdit->SaveAfx( fileName.c_str());
	}

	// ��ʾ���ظ���
	void FxMainWindow::SwitchGridVisible()
	{
		//Logic_Auxiliary->SetGridVisible( m_gridVisible->isChecked());
	}

	// ��ʾ���ر���
	void FxMainWindow::SwitchBackgroundVisible()
	{
		//Logic_Auxiliary->SetBackgroundVisible( m_bgVisible->isChecked());
	}

	// ����ת������Ϊƽ��
	void FxMainWindow::SetTransTypeMove()
	{
		//Logic_Transform->SetTranformType( CAres3DAxis::EM_EDIT_TRANSLATE);
	}

	// ת�������������
	void FxMainWindow::SwitchToGeneralCamera()
	{
		//Logic_Camera->SetActive( CT_Normal);
	}

	// ת��Ϊ��������
	void FxMainWindow::SwitchToSkyCamera()
	{
		//Logic_Camera->SetActive( CT_Sky);
	}

	// about
	void  FxMainWindow::AresAbout()
	{	
		QMessageBox::about( m_mainWindow, tr("About Ares"),
			tr("<h2>Ares Effect Editor 1.0</h2>"
			   "<p>Ares Effect Editor is the AresEngine'"
			   "Editor. used for Effect editor.</p>"
			   "<p>Copyright &copy; 2011 Software Inc.</p>"
			   "<p>See <a href=www.51play.com>www.quyougame.com</a>"
			   " for more information</p>"
			   ));
	}
}