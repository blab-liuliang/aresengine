#include <QtGui/QtGui>
#include "UIMainWindow.h"
#include <Engine/AresRoot.h>

namespace QT_UI
{
	// ���캯��
	UIMainWindow::UIMainWindow( QMainWindowEx* parent/* = 0*/)
		: QObject( parent)
		, m_mainWindow( parent)
	{
		m_uiEditLogic = new_ UiEdit;

		setupUi( m_mainWindow);

		// ��Ϣ����
		connect( m_pActionAbout, SIGNAL(triggered()), this, SLOT(AresAbout()));
		connect( m_actionNew,	 SIGNAL(triggered()), this, SLOT(New()));
		connect( m_actionOpen,	 SIGNAL(triggered()), this, SLOT(Open()));
		connect( m_actionSave,	 SIGNAL(triggered()), this, SLOT(Save()));
	}

	// ����
	void UIMainWindow::Active()
	{
		m_toolBar->setVisible( true);

		m_mainWindow->setMenuBar( m_menubar);
	}

	// ʧЧ
	void UIMainWindow::Deactive()
	{
		m_toolBar->setVisible( false);
	}

	// ��ʼ��Ⱦ
	void UIMainWindow::BeginRender() 
	{ 
	}

	// �½�Ч��
	void UIMainWindow::New()
	{
		m_uiEditLogic->New();
	}

	// ��Ч���ļ�
	void UIMainWindow::Open()
	{
		QString fileName = QFileDialog::getOpenFileName( m_mainWindow, tr("Open gui"), "", tr("Designer UI files(*.gui)"));
		if( !fileName.isEmpty())
		{
			string tFileName = fileName.toStdString();

			m_uiEditLogic->Open( tFileName.c_str());
		}
	}

	// ����Ч���ļ�
	void UIMainWindow::Save()
	{

	}

	// ��ʾ���ظ���
	void UIMainWindow::SwitchGridVisible()
	{
		//Logic_Auxiliary->SetGridVisible( m_gridVisible->isChecked());
	}

	// ��ʾ���ر���
	void UIMainWindow::SwitchBackgroundVisible()
	{
		//Logic_Auxiliary->SetBackgroundVisible( m_bgVisible->isChecked());
	}

	// about
	void  UIMainWindow::AresAbout()
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