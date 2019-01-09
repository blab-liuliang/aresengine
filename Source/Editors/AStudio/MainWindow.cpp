#include "MainWindow.h"
#include <string>
#include "ModelEdit/MOMainWindow.h"
#include "SCMainWindow.h"
#include "SCLogic.h"
#include "ModelEdit/MOLogic.h"

using namespace std;
using namespace Ares;

template<> QT_UI::MainWindow* Ares::Singleton<QT_UI::MainWindow>::m_singleton = NULL;

namespace QT_UI
{
	MainWindow*	g_mainWindow = NULL;			// ������

	// ���캯��
	MainWindow::MainWindow( QWidget* parent/* = 0*/)
		: QMainWindowEx( parent)
		, m_comBoBox( NULL)
	{
		// �½�Ӧ�ó���
		g_mainWindow = this;
		m_application = new_ Application;

		m_mainMenuToolBar.setupUi( this);
		m_moUILayout = new_ MOUILayout( this);
		m_fxUILayout = new_ FxMainWindow( this);
		m_scUILayout = new_ SCMainWindow( this);
		m_uiUILayout = new_ UIMainWindow( this);

		this->Active();

		// ������ʱ��
		m_timer = new QTimer(this);
		connect( m_timer, SIGNAL( timeout()), this, SLOT( Loop()));
		m_timer->start( 15);

		// ��ʾ����
		m_mdiArea = new_ MOMdiArea( this);
		this->setCentralWidget( m_mdiArea);

		// ������ʾ��
		m_logPanel = new LogPanel( this);
		m_logPanel->setVisible( false);

		// ������־���
		ALogSystem.Signal_Warning.connect( boost::bind<void>(&LogPanel::Warning, m_logPanel, _1));
	}

	// ��������
	MainWindow::~MainWindow() 
	{
		SAFE_DELETE( m_application);
	}

	// ѭ��
	void MainWindow::Loop()
	{
		m_application->Exec();

		m_mdiArea->ResizeWindow();
	}

	// ���ñ༭������
	void MainWindow::SetEditorType( const QString& edType)
	{
		m_moUILayout->Deactive();
		m_scUILayout->Deactive();
		m_fxUILayout->Deactive();
		m_uiUILayout->Deactive();
		if( edType == "Scene")
		{
			m_scUILayout->Active();
			m_mdiArea->SetRenderenable( true, false);
		}
		else if( edType == "Model")
		{
			m_moUILayout->Active();
			m_mdiArea->SetRenderenable( false, true);
		}
		else if( edType == "Fx")
		{
			m_fxUILayout->Active();
			m_mdiArea->SetRenderenable( false, true);
		}
		else if( edType == "UI")
		{
			m_uiUILayout->Active();
			m_mdiArea->SetRenderenable( false, true);
		}
	}

	// ����
	void MainWindow::Active()
	{
		static bool init = false;
		if( !init)
		{
			QComboBox* comboBox = new_ QComboBox( m_mainMenuToolBar.m_toolBarAstuido);
			comboBox->addItem( "Scene");
			comboBox->addItem( "Model");
			comboBox->addItem( "Fx");
			comboBox->addItem( "UI");

			m_comBoBox = comboBox;

			QWidgetAction* widgetAction = new_ QWidgetAction( m_mainMenuToolBar.m_toolBarAstuido);
			widgetAction->setDefaultWidget( comboBox);
			m_mainMenuToolBar.m_toolBarAstuido->addAction( widgetAction);

			QObject::connect( comboBox, SIGNAL( currentIndexChanged(const QString &)), this, SLOT(SetEditorType(const QString&)));
			
			init = true;
		}

		m_mainMenuToolBar.m_toolBarAstuido->setVisible( true);
	}

	// ʧЧ
	void MainWindow::Deactive()
	{
		m_mainMenuToolBar.m_toolBarAstuido->setVisible( false);
	}

	// ��ʼ��Ⱦ
	void MainWindow::BeginRender()
	{
		m_mdiArea->BeginRender();
	}

	// ����
	void MainWindow::AresAbout()
	{	
		QMessageBox::about( this, tr("About Ares"),
			tr("<h2>AStudio 1.0</h2>"
			"<p>Ares Model Editor is the AresEngine'"
			"Editor. used for physics and show.</p>"
			"<p>Copyright &copy; 2010 Software Inc.</p>"
			"<p>See <a href=www.quyougame.com>www.quyougame.com</a>"
			" for more information</p>")
			);
	}
}