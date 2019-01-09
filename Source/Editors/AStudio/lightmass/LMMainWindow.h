#pragma once

#include <list>
#include <string>
//#include <boost/tuple/tuple.hpp>
#include <QtGui/QMainWindow>
#include <QtGui/QFileSystemModel>
#include <QtGui/QGraphicsPixmapItem>
#include "ui_LMMainWindow.h"
//#include "ConfigMgr.h"
#include "QPbrtSyntaxHighLighter.h"
#include "PbrtTaskQueue.h"

using namespace std;

namespace Ares
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2011-12-20
	//----------------------------------------
	class LMMainWindow : public QMainWindow, public Ui_LMMainWindow
	{
		Q_OBJECT

	public:
		// ���캯��
		LMMainWindow( QWidget* parent = 0);

		// ��������
		~LMMainWindow();

		// �ָ��ϴιر�ʱ״̬
		void RestoreState( const char* pbrtFile, const char* img, int tabIdx);

	private slots:
		// ���ļ�
		void Open();

		// ���ļ�
		void Open( const char* filePath);

		// �����ļ�
		void Save();

		// ������ļ�
		void OpenRecentFile();

		// ��Ⱦ����
		void RenderScene();

		// �鿴�������
		void LookScene();

		// Pbrt�ļ����޸�
		void PbrtChanged();

		// ����Ƥ����ʽ
		void SetSkin();

	private:
		// ����������ļ��б���ʾ
		//void UpdateRecentFilesDisplay( const ConfigMgr::FileList& rencentlyFiles);

		// ����Ŀ���ļ���
		void GenerateImageFileName( string& oImageFile, const char* sceneFullPath);

		// ��ʾ���ɵ�ͼƬ
		void ShowResultImage( const char* resultImage);

		// ��ʾpbrt�ļ�����
		void ShowPbrt( const char* fileName);

		// ������Ϣ
		void AppendOutput( const char* msg);

		// ���ý���
		void SetProcess( float process);

	protected:
		// drag enter event
		void dragEnterEvent( QDragEnterEvent* event);
		
		// drop event
		void dropEvent( QDropEvent* event);

	private:
		string					m_currPbrt;				// ��ǰpbrt�ļ�
		string					m_currImg;				// ��ǰ��ͼƬ
		string					m_currPbrtFileExt;		// ��ǰpbrt�ļ���
		string					m_saveDirectory;		// ���ñ���Ŀ¼
		QFileSystemModel		m_fileSystemModel;		// �ļ�ϵͳĿ¼
		QGraphicsScene			m_graphicsScene;		// ��Ⱦ����
		QGraphicsPixmapItem		m_graphicsItem;			// ��ʾ��
		QPbrtSyntaxHighLighter*	m_pbrtHighlight;		// pbrt�﷨�߶�(pbrt�����ű�)

		PbrtTaskQueue			m_pbrtTaskQueue;		// pbrt�������
	};
}