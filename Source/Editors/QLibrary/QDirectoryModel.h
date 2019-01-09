#pragma once

#include <vector>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/filesystem/path.hpp>
#include <QtGui/QTreeView>
#include <QtGui/QStandardItemModel>
#include <QtGui/QSortFilterProxyModel>

using namespace std;
using namespace boost;
using namespace boost::filesystem;

namespace Ares
{
	//---------------------------------------------
	// DirectoryModel for Qt  2012-6-3 ����
	//---------------------------------------------
	class QDirectoryModel : public QStandardItemModel
	{
		Q_OBJECT

		typedef map<string, QIcon>  IconMap;

	public:
		// ���캯��
		QDirectoryModel();

		// ������Ŀ¼, �ļ����͹���
		void SetRootPath( const char* rootPath, const char* extFilter, QTreeView* treeView, QSortFilterProxyModel* proxy);

		// �Ƿ�֧���ļ�����
		bool IsSupportExt( const string& ext);

		// ˢ����ʾ
		void Refresh();

		// ����ͼ��
		void SetIcon( const char* name, const QIcon& icon){ m_iconMaps[name] = icon; }

	private:
		// ����Ŀ¼
		void RecursiveDir( const path& dir, QStandardItem* parentItem);

	public: signals:
		// �༭����
		void FileSelected( const char* path);

		// �༭�ļ�
		void FileEdit( const char* path);

	private slots:
		// չ��ĳFiter
		void OnExpandedFilter(const QModelIndex& pIndex);

		// ѡ��ĳ�ļ�
		void OnSelectedFile( const QModelIndex& pIndex);

		// ˫��ĳ�ļ�
		void OnEditFile( const QModelIndex& pIndex);

	private:
		QTreeView*				m_treeView;		// treeView
		QSortFilterProxyModel*	m_proxy;	// �������ģ��
		string					m_rootPath;		// ��Ŀ¼	
		vector<string>			m_exts;			// �ļ�����
		IconMap					m_iconMaps;		// ͼ��
		QStandardItem*			m_activeItem;		// active item
	};
}