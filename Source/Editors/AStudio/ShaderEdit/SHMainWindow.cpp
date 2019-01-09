#include <QtGui/QtGui>
#include "SHMainWindow.h"
#include "UIShaderTreeDisplay.h"
#include "TabWidget.h"
#include "ParametersEditor.h"
#include "SHLogic.h"
#include <Engine/AresRoot.h>
#include <boost/filesystem.hpp>

using namespace Ares;

namespace Ares
{
	SHMainWindow*	g_mainWindowSH = NULL;			// ������

	// ���캯��
	SHMainWindow::SHMainWindow( QWidget* parent/* = 0*/)
		: QMainWindow( parent)
	{
		g_mainWindowSH = this;
		m_shLogic	   = new_ SHLogic;

		setupUi( this);

		// ��Ϣ����
		connect( m_actionNew,	 SIGNAL(triggered()), this, SLOT(NewShaderTree()));
		connect( m_pActionAbout, SIGNAL(triggered()), this, SLOT(AresAbout()));

		// ��ʾ����
		m_pMdiArea = new UIShaderTreeDisplay( this);
		setCentralWidget( m_pMdiArea);

		// ���ʱ��ʽ
		m_materialExpression = new_ UIMaterialExpression( this);
		this->addDockWidget( Qt::RightDockWidgetArea, m_materialExpression);

		// ���Ա༭
		m_parametersEditor = new UIParametersEditor( this);
		this->addDockWidget( Qt::LeftDockWidgetArea, m_parametersEditor);
		m_parametersEditor->setVisible( false);

		//m_pOutPut = new COutPut( this);
		//this->addDockWidget(Qt::BottomDockWidgetArea, m_pOutPut);
		//m_pOutPut->setVisible( false);

		connect( m_pActionOpen,  SIGNAL(triggered()), this, SLOT( Open()));
		connect( m_pActionSave,	SIGNAL(triggered()),  this, SLOT( Save()));

		// ����
		connect( m_pActionCompile, SIGNAL(triggered()), m_pMdiArea->m_pTabWidget, SLOT( Compile()));
		//connect( m_pMdiArea->m_pTabWidget, SIGNAL(Error(const char*)), m_pOutPut, SLOT(SetText(const char*)));

		FileCorelation();
	}

	// ��ʼ��Ⱦ
	void SHMainWindow::BeginRender() 
	{ 
		//m_pMdiArea->BeginRender();

		// ������־���
		//ALogSystem.Signal_Info.connect( boost::bind<void>(&COutPut::SetText, m_pOutPut, _1));
		//ALogSystem.Signal_Warning.connect( boost::bind<void>(&COutPut::SetText, m_pOutPut, _1));
		//ALogSystem.Signal_Error.connect( boost::bind<void>(&COutPut::Error, m_pOutPut, _1));

		OnStateChanged();
	}

	// ��
	void  SHMainWindow::Open()
	{
		QString qFileName = QFileDialog::getOpenFileName( this, tr("open shader"), "", tr("*.hlsl *.glsl *.ast"));

		QDir dir( QDir::currentPath());
		qFileName = dir.relativeFilePath( qFileName);

		boost::filesystem::path tPath( qFileName.toStdString());
		if( tPath.extension()==".ast")
		{
			SHLogic_ShaderTreeEdit->Load( tPath.string());

			// ���½�����ʾ
			SHUI_ShaderTreeDisplay->Reset();
			SHUI_ShaderTreeDisplay->UpdateShaderTreeDisplay();
		}
		else 
		{
			Open( qFileName.toStdString().c_str());
		}

		// ״̬�ı�
		OnStateChanged();
	}

	// ����
	void SHMainWindow::Save()
	{
		if( SHLogic_ShaderTreeEdit->GetShaderTree())
		{
			if( !SHLogic_ShaderTreeEdit->IsHaveSavePath())
			{
				QString qFileName = QFileDialog::getSaveFileName( this, tr("save shader tree"), "", tr("*.ast"));
				SHLogic_ShaderTreeEdit->SetSavePath( qFileName.toStdString());
			}

			SHLogic_ShaderTreeEdit->Save();
		}
	}

	// ���ļ�
	void SHMainWindow::Open( const char* fileName)
	{
		m_pMdiArea->m_pTabWidget->Open( fileName);
	}

	// ״̬�ı�,���ƽ�����ʾ
	void SHMainWindow::OnStateChanged()
	{
		m_materialExpression->setEnabled( SHLogic_ShaderTreeEdit->GetShaderTree() ? true : false);
		m_pMdiArea->setEnabled( SHLogic_ShaderTreeEdit->GetShaderTree() ? true : false);
	}

	// �½�������
	void SHMainWindow::NewShaderTree() 
	{ 
		SHLogic_ShaderTreeEdit->New();

		// ���½�����ʾ
		m_pMdiArea->UpdateShaderTreeDisplay();

		// ״̬�ı�
		OnStateChanged();
	}

	// zoom
	void  SHMainWindow::ZoomEntity()
	{
		//g_pSHLogic->ZoomEntity();
	}

	// �ļ�����
	void SHMainWindow::FileCorelation()
	{
		string currPath = QDir::currentPath().toStdString();
		replace( currPath.begin(), currPath.end(), '/', '\\');

		// ����ͼ��·��,ִ�г���·��
		string iconPath = currPath + "\\corelation\\hlsl.ico";

#ifdef _DEBUG
		string exePath     = currPath + "\\MaterialEdit_d.exe";
		string exePathfile = currPath + "\\MaterialEdit_d.exe %1";
#else
		string exePath     = currPath + "\\MaterialEdit.exe";
		string exePathfile = currPath + "\\MaterialEdit.exe %1";
#endif // _DEBUG

		// дע���
		QSettings reg("HKEY_CLASSES_ROOT\\.hlsl", QSettings::NativeFormat);
		reg.setValue(".", "hlslfile");

		QSettings regIcon("HKEY_CLASSES_ROOT\\hlslfile\\DefaultIcon", QSettings::NativeFormat);
		regIcon.setValue(".", iconPath.c_str());

		QSettings regOpen("HKEY_CLASSES_ROOT\\hlslfile\\shell\\edit\\command", QSettings::NativeFormat);
		regOpen.setValue(".", exePathfile.c_str());

		// ע��ϵͳλ��
		QSettings regPath("HKEY_CURRENT_USER\\Software\\Ares\\MaterialEdit", QSettings::NativeFormat);
		regPath.setValue("ExePath", exePath.c_str());
	}

	// about
	void  SHMainWindow::AresAbout()
	{	
		QMessageBox::about( this, tr("About Ares"),
			tr("<h2>Ares Effect Editor 1.0</h2>"
			   "<p>Ares Effect Editor is the AresEngine'"
			   "Editor. used for Effect editor.</p>"
			   "<p>Copyright &copy; 2011 Software Inc.</p>"
			   "<p>See <a href=www.51play.com>www.quyougame.com</a>"
			   " for more information</p>"
			   ));
	}
}