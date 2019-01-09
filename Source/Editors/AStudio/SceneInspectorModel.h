
#pragma once

#include <map>
#include <vector>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <QtGui/QTreeView>
#include <QtGui/QStandardItemModel>
#include <QtGui/QSortFilterProxyModel>
#include <Engine/SceneSystem/AresScene.h>

using namespace std;
using namespace boost;
using namespace boost::filesystem;
using namespace Ares;

namespace QT_UI
{
	//---------------------------------------------
	// DirectoryModel for Qt  2012-6-3 ����
	//---------------------------------------------
	class SceneInspectorModel : public QStandardItemModel
	{
		Q_OBJECT

		typedef map<string, QIcon>			IconMap;
		typedef map<int,	QIcon>			EnityIcon;
		typedef map<string, QStandardItem*> EntityItemMap;

	public:
		// ���캯��
		SceneInspectorModel();

		// ������Ŀ¼, �ļ����͹���
		void SetTreeViewAndProxy( QTreeView* treeView, QSortFilterProxyModel* proxy);

		// ���õ�ͼ
		void SetScene( Scene* scene);

		// �Ƿ�֧���ļ�����
		bool IsSupportExt( const string& ext);

		// ˢ����ʾ
		void Refresh();

		// ����ͼ��
		void SetIcon( const char* name, const QIcon& icon){ m_iconMaps[name] = icon; }

	private:
		// ����Ŀ¼
		void RecursiveDir( const path& dir, QStandardItem* parentItem);

		// ��������������ʾ
		void RefreshEntityListDisplay( const Scene& scene);

		// ���
		void Reset();

	public: signals:
		// �༭����
		void FileSelected( const char* path);

	private slots:
		// չ��ĳFiter
		void OnExpandedFilter(const QModelIndex& pIndex);

		// ѡ��ĳ�ļ�
		void OnSelectedFile( const QModelIndex& pIndex);

	private:
		QTreeView*				m_treeView;		// treeView
		QSortFilterProxyModel*	m_proxy;		// �������ģ��
		string					m_rootPath;		// ��Ŀ¼	
		vector<string>			m_exts;			// �ļ�����
		IconMap					m_iconMaps;		// ͼ��
		EnityIcon				m_entityIcons;	// ʵ��ͼ��
		map<int, QStandardItem*>m_entityTypes;	// ���ͷ���

		QStandardItem*			m_activeItem;	// active item
		EntityItemMap			m_entityItems;	// ʵ���б�
	};
}