#pragma once

#include <QMainWindowEx.h>
#include <QFileSystemWatcher>
#include <QTranslator>
#include "ui_MOMainWindow.h"
#include "MOAnimationEdit.h"
#include "MOUVBuild.h"
#include "MOCollisionBuild.h"
#include "MOMaterialView.h"
#include "MOVideoSetting.h"
#include "MOModelConverter.h"
#include <boost/array.hpp>

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭���沼�� 2010-12-30
	//----------------------------------------
	class MOUILayout : public QObject, public Ui_MOMainWindow
	{
		Q_OBJECT

	public:
		// ���캯��
		MOUILayout( QMainWindowEx* parent = 0);

		// ����
		void Active();

		// ʧЧ
		void Deactive();

		// ��ʼ��Ⱦ
		void BeginRender();

		// �ļ�����
		void  FileCorelation();

		// ��ȡtranslator
		QTranslator& GetTranslator() { return m_translator; }

		// ��ȡUVBuild����
		UVBuild* GetUVBuild() { return m_uvBuild; }

		// ��ȡ�ļ�������
		QFileSystemWatcher* GetFileSystemWatcher() { return m_filesystemWatcher; }

	public slots:
		// ��
		void Open();

		// ��������
		void Save();

		// ��ʵ���ļ�
		void OpenEntity( const char* fileName);

		// ����ת������Ϊƽ��
		void SetTransTypeMove();

		// ����ת������Ϊ��ת
		void SetTransTypeRotation();

	private slots:
		// ��ʾ�ر�UVBuild
		void HideShowUVBuild();

		// ��ʾ�ر�CollisionBuild();
		void HideShowCollisionBuild();

		// ��ʾ�ر�ģ��ת�����
		void ShowModelConverter();

		// �ļ������仯
		void OnFileChanged( const QString& file);

		// ת������
		void SwitchLanguage();

	private:
		MOVideoSetting*		m_pVideoSetting;		// ��ʾ����
		CAnimationEdit*		m_animationPlay;		// �������ſ���
		UVBuild*			m_uvBuild;				// ����ͼ����
		CollisionBuild*		m_collisionBuild;		// ��ײ���ݱ༭
		MateriaViewer*		m_materialView;			// ���ʲ鿴���
		QTranslator			m_translator;			// ����
		QFileSystemWatcher*	m_filesystemWatcher;	// �ļ�ϵͳ������
		QMainWindowEx*		m_mainWindow;			// ������
		MOModelConverter*	m_modelConverter;		// ģ��ת�����
		boost::array<bool,6>m_visibleState;			// �ɼ���״̬
	};

	extern  MOUILayout*				g_mainWindowME;						
	#define MOUI_MainWindow			g_mainWindowME							// ������
	#define MOUI_UVBuild			MOUI_MainWindow->GetUVBuild()				// UVBuild����
	#define MOUI_FileSystemWatcher	MOUI_MainWindow->GetFileSystemWatcher()	// �ļ�ϵͳ������
}