#include <QtGui/QtGui>
#include "SCMainWindow.h"
#include "AI_UI.h"
#include "ContentBrowser.h"
#include "MapBuilder.h"
#include "WaterEdit.h"
#include "WorldMap.h"
#include "ImageProcess.h"
#include "PropertyEditor.h"
#include "VideoSetting.h"
#include "SCLogic.h"
#include "ModelEdit/MOMainWindow.h"
#include "ShaderEdit/SHMainWindow.h"
#include "TextureTool/TextureTool.h"
#include "lightmass/LMMainWindow.h"
#include <string>

using namespace std;
using namespace Ares;

namespace QT_UI
{
	SCMainWindow*	g_mainWindowSC = NULL;		

	// ���캯��
	SCMainWindow::SCMainWindow( QMainWindowEx* parent/* = 0*/)
		: QObject( parent)
		, m_contentBrowser( NULL)
		, m_lightMap( NULL)
		, m_pWorldMap( NULL)
		, m_mainWindow( parent)
	{
		g_mainWindowSC = this;

		setupUi( m_mainWindow);

		// ��Ϣ����
		connect( m_pActionAbout, SIGNAL(triggered()), m_mainWindow, SLOT(AresAbout()));
		connect( m_actionNewMap, SIGNAL(triggered()), this, SLOT(NewMap()));

		connect( m_pActionSelect,   SIGNAL( triggered()), this, SLOT( EntitySelect()));
		connect( m_pActionMove,     SIGNAL( triggered()), this, SLOT( EntityMove()));
		connect( m_pActionScale,    SIGNAL( triggered()), this, SLOT( EntityScale()));
		connect( m_pActionRotation, SIGNAL( triggered()), this, SLOT( EntityRotate()));
		connect( m_actionPathFind, SIGNAL( triggered()),  this, SLOT( AIPathFind()));

		connect( m_actionSwitch_to_Game, SIGNAL(triggered()), this, SLOT(SetMoveType()));
		connect( m_actionCombination, SIGNAL(triggered()), this, SLOT(CombinationBatch()));

		connect( m_skinDefault,SIGNAL( triggered()), this, SLOT( SwitchToDefaultSkin()));
		connect( m_skinClassic,SIGNAL( triggered()), this, SLOT( SwitchToClassicSkin()));
		connect( m_skinCustom, SIGNAL( triggered()), this, SLOT( SwitchToCustomSkin()));

		connect( m_actionWorldMap, SIGNAL( triggered()), this, SLOT( ShowWorldMap()));

		// ��Դ������
		m_inspector = new_ SceneInspector( m_mainWindow);
		m_mainWindow->addDockWidget( Qt::RightDockWidgetArea, m_inspector);

		// �����ͼ(Ĭ�ϲ��ɼ�)
		m_pWorldMap = new_ CWorldMap( m_mainWindow);
		//this->addDockWidget( Qt::AllDockWidgetAreas, m_pWorldMap);	

		// ���α༭
		//m_toolKit = new ToolKit( m_mainWindow);
		//m_mainWindow->addDockWidget( Qt::RightDockWidgetArea, m_toolKit);

		// ��Ƶ����
		m_pVideoSetting = new_ CVideoSetting( m_mainWindow);

		// AI
		m_pAI = new_ CAIUI( m_mainWindow);

		// ˮ�༭
		m_pWaterEdit = new CWaterEdit( m_mainWindow);
		m_mainWindow->addDockWidget( Qt::RightDockWidgetArea, m_pWaterEdit);

		// ͼ����
		m_pImageProcess = new CImageProcess( m_mainWindow);
		m_mainWindow->addDockWidget( Qt::RightDockWidgetArea, m_pImageProcess);	

		// ���Ա༭
		m_pPropertyEditor = new CPropertyEditor( m_mainWindow);
		m_mainWindow->addDockWidget( Qt::RightDockWidgetArea, m_pPropertyEditor);

		//this->tabifyDockWidget( m_pPropertyEditor, m_pWaterEdit);
		//this->tabifyDockWidget( m_pVideoSetting, m_pTerrainEdit);
		//this->tabifyDockWidget( m_pPropertyEditor, m_pTerrainEdit);
		//this->tabifyDockWidget( m_pAI, m_mapView);

		connect( m_pActionSave,  SIGNAL(triggered()), m_pWorldMap, SLOT(SaveMap()));
		connect( m_pActionOpen,  SIGNAL(triggered()), this, SLOT(OpenMap()));
		//connect( m_pShowArea, SIGNAL(fpsChanged(float)), m_pPropertyEditor->GetFrame("Setting"), SLOT(SetFps(float)));
		//connect( m_actionWorldMap, SIGNAL( triggered(bool)), m_pWorldMap, SLOT(setVisible(bool)));
		//connect( m_pWorldMap, SIGNAL( EditAreaChanged(IArea*)), m_pTerrainEdit, SLOT(SetCurrArea( IArea*)));

		connect( m_actionTextureTool,   SIGNAL(triggered()), this, SLOT(HideShowTextureTool()));
		connect( m_actionShaderEdit,	SIGNAL(triggered()), this, SLOT(HideShowShaderEdit()));
		connect( m_actionLightmass,		SIGNAL(triggered()), this, SLOT(HideShowLightmass()));
		connect( m_actionContentBrowser,SIGNAL(triggered()), this, SLOT(HideShowContentBrowser()));
		connect( m_actionBuildLightmap, SIGNAL(triggered()), this, SLOT(HideShowLightmapBake()));
		connect( m_actionNavigationMesh,SIGNAL(triggered()), this, SLOT(HideShowNavMeshBuild()));
		connect( m_actionPropertys,		SIGNAL(triggered()), this, SLOT(HideShowSettings()));

		// ��䷽ʽ
		connect( m_actionWireFrame,		SIGNAL(triggered()), this, SLOT(SwitchToWireFrameFillMode()));
		connect( m_actionNormal,		SIGNAL(triggered()), this, SLOT(SwitchToNormalFillMode()));

		// ����
		connect( m_actionImportCurScene, SIGNAL(triggered()), this, SLOT( ImportFileToCurScene()));

		// ����
		connect( m_actionExportNavigationMesh, SIGNAL(triggered()), m_pAI, SLOT(SaveNavMesh()));

		// Ĭ������
		m_pImageProcess->setVisible( false);
		m_pWaterEdit->setVisible( false);
		//m_toolKit->setVisible( false);
		m_pWorldMap->setVisible( false);
		m_pVideoSetting->setVisible( false);

		m_visibles[m_pPropertyEditor] = true;
		m_visibles[m_inspector]		  = true;
	}

	// ����
	void SCMainWindow::Active()
	{
		m_toolBar->setVisible( true);

		// Ĭ������
		m_pImageProcess->setVisible( false);
		m_pPropertyEditor->setVisible( m_visibles[m_pPropertyEditor]);
		m_pWaterEdit->setVisible( false);
		//m_toolKit->setVisible( false);
		m_pWorldMap->setVisible( false);
		m_inspector->setVisible( m_visibles[m_inspector]);
		m_pVideoSetting->setVisible( false);

		m_mainWindow->setMenuBar( m_menuBar);
	}

	// ʧЧ
	void SCMainWindow::Deactive()
	{
		m_toolBar->setVisible( false);

		// Ĭ������
		m_pImageProcess->setVisible( false);
		m_pPropertyEditor->setVisible( false);
		m_pWaterEdit->setVisible( false);
		//m_toolKit->setVisible( false);
		m_pWorldMap->setVisible( false);
		m_inspector->setVisible( false);
		m_pVideoSetting->setVisible( false);
	}

	// ��ʼ��Ⱦ
	void SCMainWindow::BeginRender() 
	{ 
		// ��������
		Logic_Cfg->Signal_OnRencentFilesChanged.connect( boost::bind<void>(&SCMainWindow::UpdateRecentFilesDisplay, this, _1));
		Logic_Cfg->Signal_CameraSettingsChanged.connect( boost::bind<void>(&CVideoSetting::UpdateCameraSettingsDisplay, m_pVideoSetting));
		Logic_Cfg->Load();

		// ������Ϣ
		SCLogic_Map->Signal_OnSceneChanged.connect( boost::bind<void>(&SCMainWindow::OnSceneStateChanged, this));
		SCLogic_Map->Restore();

		// ���ı���
		switch( ARenderDevice->GetType())
		{
		case D3D11:		m_mainWindow->setWindowTitle( tr("Ares Studio(32λ, Dx11)"));		break;
		case OPENGL:	m_mainWindow->setWindowTitle( tr("Ares Studio(32λ, OpenGL)"));		break;
		case OPENGLES:	m_mainWindow->setWindowTitle( tr("Ares Studio(32λ, OpenGLES)"));	break;
		default:		m_mainWindow->setWindowTitle( tr("Ares Studio(32λ, UnKnown)"));		break;	
		}
	}

	// ��������
	SCMainWindow::~SCMainWindow()
	{
		Logic_Cfg->Save();
	}

	// ƽ��
	void  SCMainWindow::EntityMove()
	{
		SCLogic_Main->SetHandleType( EM_HT_EDITOENTITY);
		SCLogic_EntityEdit->SetEditType( CEntityEditLogic::EM_MOVE);

		m_pActionScale->setChecked( false);
		m_pActionSelect->setChecked( false);
		m_pActionRotation->setChecked( false);
	}

	// ����
	void  SCMainWindow::EntityScale()
	{
		SCLogic_Main->SetHandleType( EM_HT_EDITOENTITY);
		SCLogic_EntityEdit->SetEditType( CEntityEditLogic::EM_SCALE);

		m_pActionSelect->setChecked( false);
		m_pActionRotation->setChecked( false);
		m_pActionMove->setChecked( false);
	}

	// ��ת
	void  SCMainWindow::EntityRotate()
	{
		SCLogic_Main->SetHandleType( EM_HT_EDITOENTITY);
		SCLogic_EntityEdit->SetEditType( CEntityEditLogic::EM_ROTATE);

		m_pActionScale->setChecked( false);
		m_pActionSelect->setChecked( false);
		m_pActionMove->setChecked( false);
	}

	// ѡ��
	void  SCMainWindow::EntitySelect()
	{
		SCLogic_Main->SetHandleType( EM_HT_EDITOENTITY);
		SCLogic_EntityEdit->SetEditType( CEntityEditLogic::EM_SELECT);

		m_pActionScale->setChecked( false);
		m_pActionRotation->setChecked( false);
		m_pActionMove->setChecked( false);
	}

	// ·������
	void SCMainWindow::AIPathFind()
	{
		SCLogic_Main->SetHandleType( EM_HT_AI);
	}

	// ������״̬
	static void SetActionsEnabled( QList<QAction*>& actions, bool enabled)
	{
		for( int i=0; i<actions.size(); i++)
			actions[i]->setEnabled( enabled);
	}


	// ����״̬�ı�,���ƽ�����ʾ
	void SCMainWindow::OnSceneStateChanged()
	{
		if( SCLogic_Scene && SCLogic_Scene->GetLocation().size())
		{
			// Enable all menubar, toolbar actions
			SetActionsEnabled( m_menuBar->actions(), true);
			SetActionsEnabled( m_toolBar->actions(), true);
			SetActionsEnabled( m_menuF->actions(), true);
		}
		else
		{
			// Disenable all menubar actions
			QAction*		 menuFAction = m_menuF->menuAction();
			QList<QAction*>	 menuActions = m_menuBar->actions(); menuActions.removeAll( menuFAction);

			SetActionsEnabled( menuActions, false);
			SetActionsEnabled( m_menuF->actions(), false);
			SetActionsEnabled( m_toolBar->actions(), false);

			m_actionNewMap->setEnabled( true);
			m_pActionOpen->setEnabled( true);

			MapBuilder::NewMapUnSaved();
		}
	}

	// �½���ͼ
	void  SCMainWindow::NewMap()
	{
		static MapBuilder* pForm = NULL;
		if( !pForm)
			pForm = new MapBuilder( m_mainWindow);

		pForm->setVisible( true);
	}

	// ������
	void  SCMainWindow::OpenMap()
	{
		m_pWorldMap->OpenMap();

		//m_pTerrainEdit->UpdateTerrainTexture();
	}

	// ��ʾ���ͼ
	void SCMainWindow::ShowWorldMap()
	{
		m_pWorldMap->setVisible( !m_pWorldMap->isVisible());
	}

	// ��ʾ�ر�����༭����
	void SCMainWindow::HideShowTextureTool()
	{
		static TextureTool* textureTool = NULL;
		if( !textureTool)
			textureTool = new_ TextureTool;		

		textureTool->show();
	}

	// ��Ч���༭��
	void SCMainWindow::HideShowShaderEdit()
	{
		static SHMainWindow* shMainWindow = NULL;
		if( !shMainWindow)
			shMainWindow = new_ SHMainWindow;		
		
		shMainWindow->show();
	}

	// ��Lightmass
	void SCMainWindow::HideShowLightmass()
	{
		static LMMainWindow* lmMainWindow = NULL;
		if( !lmMainWindow)
			lmMainWindow = new_ LMMainWindow( m_mainWindow);		

		lmMainWindow->show();
	}

	// ��ʾ�������������
	void SCMainWindow::HideShowContentBrowser()
	{
		// ģ���б�
		if( !m_contentBrowser)
			m_contentBrowser = new ContentBrowser( m_mainWindow);

		m_contentBrowser->setVisible( !m_contentBrowser->isVisible());
	}

	// ��ʾ���ع���ͼ�決������
	void SCMainWindow::HideShowLightmapBake()
	{
		if( !m_lightMap)
			m_lightMap = new Lightmap( m_mainWindow);

		m_lightMap->setVisible( !m_lightMap->isVisible());
	}

	// ��ʾ���ص�����������
	void SCMainWindow::HideShowNavMeshBuild()
	{
		if( m_pAI)
			m_pAI->setVisible( !m_pAI->isVisible());
	}

	// ��ʾ��������
	void SCMainWindow::HideShowSettings()
	{
		if( m_pVideoSetting)
			m_pVideoSetting->setVisible( !m_pVideoSetting->isVisible());
	}

	// �����ƶ�����
	void SCMainWindow::SetMoveType()
	{
		if( m_actionSwitch_to_Game->isChecked())
		{
			SCLogic_Move->SetMoveType( CMoveLogic::EM_FOLLOW);
		}
		else
		{
			SCLogic_Move->SetMoveType( CMoveLogic::EM_THIRD);
		}
	}

	// �ϲ�ʵ��
	void SCMainWindow::CombinationBatch()
	{
		SCLogic_Main->CombinationBatch();
	}

	// �������ģʽ
	void SCMainWindow::SwitchToWireFrameFillMode()
	{
		// ���ù�դ��״̬
		Logic_AI->SwitchToWireFrameFillMode();
	}

	// �������ģʽ
	void SCMainWindow::SwitchToNormalFillMode()
	{
		Logic_AI->SwitchToNormalFillMode();
	}

	// ������Ĭ��Ƥ��
	void SCMainWindow::SwitchToDefaultSkin()
	{
		qApp->setStyleSheet("");
	}

	// ����������Ƥ��
	void SCMainWindow::SwitchToClassicSkin()
	{
		SetStyleSheet("edit_res/skin/classic.qss");
	}

	// ѡ���û��Զ���Ƥ��
	void SCMainWindow::SwitchToCustomSkin()
	{
		QString qFileName = QFileDialog::getOpenFileName( m_mainWindow, tr("open qss"), "", tr("*.qss"));

		QDir dir( QDir::currentPath());
		qFileName = dir.relativeFilePath( qFileName);

		SetStyleSheet( qFileName.toStdString().c_str());
	}

	// ����styleSheet
	void SCMainWindow::SetStyleSheet( const char* fileName)
	{
		QFile qss( fileName);
		qss.open(QFile::ReadOnly);
		qApp->setStyleSheet(qss.readAll());
		qss.close();
	}

	// ����������ļ��б���ʾ
	void SCMainWindow::UpdateRecentFilesDisplay( const list<string>& rencentlyFiles)
	{
		m_actionRecentFiles->clear();

		for ( ConfigMgr::FileList::const_iterator it=rencentlyFiles.begin(); it!=rencentlyFiles.end(); it++)
		{
			QAction* tAction = new QAction( m_actionRecentFiles);
			if( tAction)
			{
				tAction->setText(  QObject::tr(it->c_str()));
				connect( tAction, SIGNAL( triggered()), this, SLOT( OpenRecentFile()));

				m_actionRecentFiles->insertAction( NULL, tAction);
			}
		}	
	}

	// ������ļ�
	void SCMainWindow::OpenRecentFile()
	{
		QAction *action = qobject_cast<QAction *>(sender());
		if (action)
		{
			string fileName= action->text().toStdString();

			OpenFile( fileName.c_str());
		}
	}

	// �����ļ�����ǰ����
	void SCMainWindow::ImportFileToCurScene()
	{
		QString qFileName = QFileDialog::getOpenFileName( m_mainWindow, tr("����"), "", tr("*.tri *.nav"));
		QDir dir( QDir::currentPath());
		qFileName = dir.relativeFilePath( qFileName);

		OpenFile( qFileName.toStdString().c_str());
	}

	// ���ļ�
	void SCMainWindow::OpenFile( const char* filePath)
	{
		// ���ݲ�ͬ��׺�����д���
		string ext = FileUtils::GetExt( filePath);
		if( ext==".tri")
			Logic_AI->OpenTri( filePath);
		else if( ext==".nav")
			Logic_AI->OpenNav( filePath);
	}
}