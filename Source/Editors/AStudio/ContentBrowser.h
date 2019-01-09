#ifndef MODEL_LIST_H
#define MODEL_LIST_H

#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>
#include <QtGui/QMainWindow>
#include <QtGui/QSortFilterProxyModel>
#include <map>
#include <string>
#include "ui_ContentBrowser.h"
#include "QDirectoryModel.h"

using namespace std;
using namespace Ares;

class QIcon;
class QTreeWidgetItem;
namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class ContentBrowser : public QMainWindow, public Ui_ContentBrowser
	{
		Q_OBJECT

		typedef map<string, QIcon>  IconMap;
	public:
		// ���캯��
		ContentBrowser( QWidget* parent = 0);

		// ��������
		~ContentBrowser();

	private slots:
		// ѡ��ĳʵ��
		void OnSelectEntity( const char* filePath);

		// �༭ĳʵ��
		void EditSelect( const char* filePath);

		// �Ҽ�ʵ��˵�
		void ShowMenu(const QPoint& point);

		// �Ƴ� or ɾ���ļ�
		void ReMoveFile();

		// �����Դ
		void AddRes();

		// ���Filter
		void AddFilter();

		// ������
		void ReName();

		// ���ַ����ı�
		void NameChanged( const QModelIndex& index);

		// ��ʼ��ģ���б�
		void InitModelList();

	private slots:
		// �½����Դ
		void NewDynamicPointLight();

		// �½������
		void NewDynamicDirectLight();

		// �½�������
		void NewDynamicAmbientLight();

		// �½�����
		void NewTerrain();

		// �½�����
		void NewOcean();

		// ִ�й���
		void ApplyFilter( QString str);

	private:
		// ����
		void  Save();

	private:
		IconMap					m_iconMap;
		QDirectoryModel*		m_model;
		QSortFilterProxyModel*	m_proxyModel;	// �������ģ��

		QMenu*					m_entityMenu;
		QMenu*					m_filterMenu;

		string					m_rootPath;			// ��Ŀ¼
		string					m_extFilter;		// ��׺������
	};
}

#endif