#include <QtGui/QtGui>
#include <QFile>
#include "LMMainWindow.h"
#include <QtDeclarative/QDeclarativeContext>
#include <pbrt/core/api.h>
#include <pbrt/core/parser.h>
#include <pbrt/core/parallel.h>
#include <algorithm>
#include <ostream>
#include <Core/AresChar.h>
#include "QLoadTga.h"

namespace Ares
{
	#define  TAB_INDEX_IMG  0
	#define  TAB_INDEX_PBRT 1

	// ���캯��
	LMMainWindow::LMMainWindow( QWidget* parent/* = 0*/)
		: QMainWindow( parent)
	{
		// 1.��Ա����Ĭ��ֵ
		m_saveDirectory = "gallery\\";

		// 2.����UI
		setupUi( this);
		m_progressBar->setVisible(false);

		// 3.����Qt�źŲ�
		connect( m_actionOpen, SIGNAL( triggered()), this, SLOT( Open()));
		connect( m_actionSave, SIGNAL( triggered()), this, SLOT( Save()));
		connect( m_actionBuild, SIGNAL( triggered()), this, SLOT( LookScene()));
		connect( m_actionReBuild, SIGNAL( triggered()), this, SLOT( RenderScene()));
		connect( m_pbrtTextEdit,  SIGNAL( textChanged()), this, SLOT( PbrtChanged()));
		connect( m_actionSutra,   SIGNAL( triggered()), this, SLOT( SetSkin()));

		// 4.����boost�źŲ�
		//ConfigMgr::GetSingleton().Signal_OnRencentFilesChanged.connect( boost::bind<void>(&MainWindow::UpdateRecentFilesDisplay, this, _1));
		//ConfigMgr::GetSingleton().Signal_OnRestoreState.connect( boost::bind<void>(&MainWindow::RestoreState, this, _1, _2, _3));
		//Pbrt::Signal_Error.connect( boost::bind<void>( &MainWindow::AppendOutput, this, _1));
		//Pbrt::Signal_Process.connect( boost::bind<void>( &MainWindow::SetProcess, this, _1));

		m_graphicsItem.setFlag( QGraphicsItem::ItemIsMovable, true);
		m_graphicsScene.addItem( &m_graphicsItem);
		m_graphicsView->setScene( &m_graphicsScene);

		// �﷨����
		m_pbrtHighlight = new QPbrtSyntaxHighLighter( m_pbrtTextEdit->document());

		//m_fileSystemModel.setRootPath("D:\\Youdao");
		//m_galleryView->setModel( &m_fileSystemModel);

		// 5.������ʾ������ļ��б�
		//ConfigMgr::GetSingleton().Load();

		// �����������(�ŵ���ʼ�ŵ����ִ��)
		//m_pbrtTaskQueue.Start( 10);
		//m_pbrtTaskQueue.Signal_OnPbrtFinised.connect( boost::bind<void>( &MainWindow::ShowResultImage, this, _1));

		// ���ý���Ƥ��
		SetSkin();
	}

	// ��������
	LMMainWindow::~LMMainWindow()
	{
		//m_pbrtTaskQueue.Finish();
		//m_pbrtTaskQueue.End();

		// �������״̬
		//ConfigMgr::GetSingleton().SetProgramState( m_currPbrt.c_str(), m_currImg.c_str(), m_mainWidget->currentIndex());
		//ConfigMgr::GetSingleton().Save();
	}

	// �ָ��ϴιر�ʱ״̬
	void LMMainWindow::RestoreState( const char* pbrtFile, const char* img, int tabIdx)
	{
		// �༭��ʾ
		ShowPbrt( pbrtFile);

		ShowResultImage( img);

		m_mainWidget->setCurrentIndex( tabIdx);
	}

	// ���ļ�
	void LMMainWindow::Open()
	{
		QString qFileName = QFileDialog::getOpenFileName( this, tr("Open pbrt"), "", tr("(*.pbrt)"));
		if( !qFileName.isEmpty())
		{
			string fileName = qFileName.toStdString();

			Open( fileName.c_str());
		}
	}

	// ���ļ�
	void LMMainWindow::Open( const char* filePath)
	{
		if( filePath)
		{
			//ConfigMgr::GetSingleton().AddToRecentlyFile( filePath); 

			// �༭��ʾ
			ShowPbrt( filePath);
		}
	}

	// �����ļ�
	void LMMainWindow::Save()
	{
		FILE* fileHandle = fopen( m_currPbrt.c_str(), "wt");
		if( fileHandle)
		{
			string plainText = m_pbrtTextEdit->toPlainText().toStdString();
			fwrite( plainText.c_str(), plainText.size(), 1, fileHandle);

			fflush(fileHandle);
			fclose(fileHandle);
		}

		// ���ı���
		m_mainWidget->setTabText( 1, m_currPbrtFileExt.c_str());
	}

	// ������ļ�
	void LMMainWindow::OpenRecentFile()
	{
		QAction *action = qobject_cast<QAction *>(sender());
		if (action)
		{
			string fileName= action->text().toStdString();
			if( fileName.size())
			{
				//ConfigMgr::GetSingleton().AddToRecentlyFile( fileName.c_str()); 

				// �༭��ʾ
				ShowPbrt( fileName.c_str());
			}
		}
	}

	// ����Ŀ���ļ���
	void LMMainWindow::GenerateImageFileName( string& oImageFile, const char* sceneFullPath)
	{
		char sceneFileName[512];
		_splitpath( sceneFullPath, NULL, NULL, sceneFileName, NULL);

		oImageFile = m_saveDirectory + sceneFileName + ".tga";
	}

	//// ����������ļ��б���ʾ
	//void LMMainWindow::UpdateRecentFilesDisplay( const ConfigMgr::FileList& rencentlyFiles)
	//{
	//	m_actionRecentFiles->clear();

	//	for ( ConfigMgr::FileList::const_iterator it=rencentlyFiles.begin(); it!=rencentlyFiles.end(); it++)
	//	{
	//		QAction* tAction = new QAction( m_actionRecentFiles);
	//		if( tAction)
	//		{
	//			tAction->setText(  it->c_str());
	//			connect( tAction, SIGNAL( triggered()), this, SLOT( OpenRecentFile()));

	//			m_actionRecentFiles->insertAction( NULL, tAction);
	//		}
	//	}	
	//}

	// �鿴�������
	void LMMainWindow::LookScene()
	{
		string sceneTga;
		GenerateImageFileName( sceneTga, m_currPbrt.c_str());

		// �ж��ļ��Ƿ����
		if( QFile::exists(sceneTga.c_str()))
		{
			ShowResultImage( sceneTga.c_str());
		}
		else
		{
			RenderScene();
		}
	}

	// ��Ⱦ����
	void LMMainWindow::RenderScene()
	{
		if( m_currPbrt.empty())
			return;

		if( m_pbrtTaskQueue.IsTaskExist( m_currPbrt.c_str()))
			return;

		m_outPut->clear();

		// ����pbrt
		Options options;
		options.nCores		= 3;
		options.openWindow	= true;
		options.quickRender = false;
		options.quiet		= false;
		options.verbose		= true;

		// �趨����ļ�λ��
		GenerateImageFileName( options.imageFile, m_currPbrt.c_str());

#if 0
		// ��ʼ��
		pbrtInit( options);

		// ���������ļ�
		ParseFile( m_currPbrt.c_str());

		// �������
		pbrtCleanup();
#else
		// ��ӵ��������
		m_pbrtTaskQueue.AddTask( m_currPbrt.c_str(), options);
#endif
		m_progressBar->setValue( 0);
		m_progressBar->setVisible( true);
	}

	// ��ʾ���ɵ�ͼƬ
	void LMMainWindow::ShowResultImage( const char* resultImage)
	{
		if( strlen( resultImage))
		{
			m_progressBar->setVisible( false);
			m_mainWidget->setCurrentIndex( 0);

			m_graphicsItem.setPixmap( QPixmap( LoadTga(resultImage)));

			m_currImg = resultImage;
		}
	}

	// ��ʾpbrt�ļ�����
	void LMMainWindow::ShowPbrt( const char* fileName)
	{
		if( !strlen( fileName))
			return;

		// ���ļ�
		QFile file( fileName);
		if( file.open( QFile::ReadOnly | QFile::Text))
		{
			m_currPbrt = fileName;

			m_pbrtTextEdit->setTabStopWidth( 24);
			m_pbrtTextEdit->setPlainText( file.readAll());
		}

		// ���ı���
		char tFileName[512];
		char tFileExt[512];
		_splitpath( m_currPbrt.c_str(), NULL, NULL, tFileName, tFileExt);

		m_currPbrtFileExt = string( tFileName) + string( tFileExt);
		m_mainWidget->setTabText( 1, m_currPbrtFileExt.c_str());
		m_mainWidget->setCurrentIndex( TAB_INDEX_PBRT);
	}

	// Pbrt�ļ����޸�
	void LMMainWindow::PbrtChanged()
	{
		if( !m_currPbrtFileExt.empty())
		{
			// ���ı���
			string title = m_currPbrtFileExt + string("*");
			m_mainWidget->setTabText( 1, title.c_str());
		}
	}

	// ������Ϣ
	void LMMainWindow::AppendOutput( const char* msg)
	{
		m_outPut->append( msg);
	}

	// ���ý���
	void LMMainWindow::SetProcess( float process)
	{
		int curValue = m_progressBar->value();
		curValue     = std::max<int>( curValue, static_cast<int>(process*100.f));

		m_progressBar->setValue( curValue);
	}

	// ����Ƥ����ʽ
	void LMMainWindow::SetSkin()
	{
		// ��ȡƤ��·��
		//QString qssPath;
		//QAction *action = qobject_cast<QAction *>(sender());
		//if( action->text() == QString("sutra"))
		//{
		//	qssPath = ":/Qss/qss/sutra.qss";
		//}

		//// ����Ƥ��
		//QFile qssFile(qssPath);
		//qssFile.open( QFile::ReadOnly);
		//QString styleSheet = QLatin1String( qssFile.readAll());

		//qApp->setStyleSheet( styleSheet);
	}

	// drag enter event
	void LMMainWindow::dragEnterEvent( QDragEnterEvent* event)
	{
		if( event->mimeData()->hasFormat("text/uri-list"))
			event->acceptProposedAction();
	}

	// drop event
	void LMMainWindow::dropEvent( QDropEvent* event)
	{
		QList<QUrl> urls = event->mimeData()->urls();
		if( urls.isEmpty())
			return;

		QString fileName = urls.first().toLocalFile();
		if( !fileName.isEmpty())
		{
			Open( fileName.toStdString().c_str());
		}
	}
}