#ifndef SCENE_MAINWINDOW_H
#define SCENE_MAINWINDOW_H

#include "LightMap.h"
#include "LogPanel.h"
#include <QtGui/QMainWindow>
#include "ui_SCMainWindow.h"
#include <Core/AresSingleton.hpp>
#include "SceneInspector.h"
#include "PropertyEditor.h"
#include "AI_UI.h"
#include "WorldMap.h"
#include "ContentBrowser.h"
#include "VideoSetting.h"
#include "WaterEdit.h"
#include "ImageProcess.h"
#include <QMainWindowEx.h>

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class SCMainWindow : public QObject, public Ui_SCMainWindow
	{
		Q_OBJECT

	public:
		SCMainWindow( QMainWindowEx* parent = 0);
		~SCMainWindow();

		// ��ʼ��Ⱦ
		void BeginRender();

		// ����styleSheet
		void SetStyleSheet( const char* fileName);

		// ����״̬�ı�,���ƽ�����ʾ
		void OnSceneStateChanged();

		// ����
		void Active();

		// ʧЧ
		void Deactive();

	public:
		// ��ȡ���Ա༭����
		CPropertyEditor* GetPropertyEditor() { return m_pPropertyEditor; }

		// ��ͼ��Դ�鿴��
		SceneInspector* GetMapView() { return m_inspector; }

		// ��ȡ������
		//ToolKit* GetToolKit() { return m_toolKit; }

	private:
		// ����������ļ��б���ʾ
		void UpdateRecentFilesDisplay( const list<string>& rencentlyFiles);

	private slots:
		// �������ģʽ
		void SwitchToWireFrameFillMode();

		// �������ģʽ
		void SwitchToNormalFillMode();

		// ������Ĭ��Ƥ��
		void SwitchToDefaultSkin();

		// ����������Ƥ��
		void SwitchToClassicSkin();

		// ѡ���û��Զ���Ƥ��
		void SwitchToCustomSkin();

	private slots:
		// �½���ͼ
		void  NewMap();

		// ������
		void  OpenMap();

		// ���ļ�
		void OpenFile( const char* filePath);

		// ������ļ�
		void OpenRecentFile();

		// �����ļ�����ǰ����
		void ImportFileToCurScene();

		// ��ʾ���ͼ
		void ShowWorldMap();

		// ��ʾ�ر�����༭����
		void HideShowTextureTool();

		// ��Ч���༭��
		void HideShowShaderEdit();

		// ��Lightmass
		void HideShowLightmass();

		// ��ʾ�ر����������
		void HideShowContentBrowser();

		// ��ʾ���ع���ͼ�決������
		void HideShowLightmapBake();

		// ��ʾ���ص�����������
		void HideShowNavMeshBuild();

		// ��ʾ�������ô���
		void HideShowSettings();

		// �༭ʵ��
		void  EntityMove();
		void  EntityScale();
		void  EntityRotate();
		void  EntitySelect();

		// ·������
		void AIPathFind();

		// �����ƶ�����
		void SetMoveType();

		// �ϲ�ʵ��
		void CombinationBatch();

	private:
		CAIUI*            m_pAI;				// AI�༭
		CWorldMap*		  m_pWorldMap;			// �����ͼ��ʾ
		ContentBrowser*   m_contentBrowser;		// ���������
		CWaterEdit*		  m_pWaterEdit;			// ˮ�༭
		//ToolKit*		  m_toolKit;		// ���α༭
		CVideoSetting*    m_pVideoSetting;		// ��ʾ����
		CImageProcess*    m_pImageProcess;		// ͼ����UI
		CPropertyEditor*  m_pPropertyEditor;	// ���Ա༭
		Lightmap*		  m_lightMap;			// ����ͼ�決
		SceneInspector*   m_inspector;			// ��ͼ�鿴�༭���ͽṹ
		QMainWindowEx*	  m_mainWindow;			// ������
		map<void*, bool>  m_visibles;			// �ɼ���
	};

	extern	SCMainWindow*				g_mainWindowSC;
	#define SCUI_MainWindow				g_mainWindowSC
	#define SCUI_Property				SCUI_MainWindow->GetPropertyEditor()
	#define SCUI_SceneInspector			SCUI_MainWindow->GetMapView()
	#define SCUI_SceneInspectorModel	SCUI_SceneInspector->GetSceneInsepctorModel()
	//#define SCUI_ToolKit				SCUI_MainWindow->GetToolKit()
}

#endif