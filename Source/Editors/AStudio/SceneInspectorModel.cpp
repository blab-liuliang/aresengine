#include <algorithm>
#include "SceneInspectorModel.h"
#include "SCLogic.h"
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

using namespace boost;
using namespace boost::filesystem;

namespace QT_UI
{
	// ���캯��
	SceneInspectorModel::SceneInspectorModel()
		: QStandardItemModel(),
		m_treeView( NULL),
		m_activeItem( NULL)
	{
		// ��ʼ��ͼ��
		m_iconMaps["filter"]       = QIcon(":/icon/Icon/folder_close.png");
		m_iconMaps["filterexpend"] = QIcon(":/icon/Icon/folder_open.png");
		m_iconMaps["map"]		   = QIcon(":/icon/Icon/temp.png");
		m_iconMaps["area"]		   = QIcon(":/icon/Icon/temp.png");
		m_iconMaps["terrain"]	   = QIcon(":/icon/Icon/temp.png");
		m_iconMaps[".m1"]          = QIcon(":/icon/Icon/model.png");

		m_entityIcons[ET_Render]   = QIcon(":/icon/Icon/StaticMesh.png");
		m_entityIcons[ET_Light]    = QIcon(":/icon/Icon/EnityLight.png");
		m_entityIcons[ET_Sound]    = QIcon(":/icon/Icon/solid.bmp");
	}

	// ������Ŀ¼, �ļ����͹���
	void SceneInspectorModel::SetTreeViewAndProxy( QTreeView* treeView, QSortFilterProxyModel* proxy)
	{
		m_treeView = treeView;
		m_proxy	   = proxy;
		connect( m_treeView, SIGNAL(expanded(const QModelIndex&)),  this, SLOT( OnExpandedFilter(const QModelIndex&)));
		connect( m_treeView, SIGNAL(collapsed(const QModelIndex&)), this, SLOT( OnExpandedFilter(const QModelIndex&)));

		connect( m_treeView, SIGNAL(clicked(const QModelIndex&)),   this, SLOT( OnSelectedFile(const QModelIndex&)));
	}

	// ���õ�ͼ
	void SceneInspectorModel::SetScene( Scene* scene)
	{
		// ����
		Reset();

		if( scene)
		{
			// ͬ��
			RefreshEntityListDisplay( *scene);

			// �ź�����
			scene->Signal_OnEntitysChanged.connect( boost::bind<void>(&SceneInspectorModel::RefreshEntityListDisplay, this, _1));
		}
	}

	// ��������������ʾ
	void SceneInspectorModel::RefreshEntityListDisplay( const Scene& scene)
	{
		// ����б�
		this->clear();

		const Scene::EntityList& entityMap = scene.GetStaticEntitys();
		if( true)
		{
			for( Scene::EntityList::const_iterator it=entityMap.begin(); it!=entityMap.end(); it++)
			{
				const EntityPtr& entity = it->second;

				QStandardItem* entityItem = new QStandardItem;
				entityItem->setText( entity->GetName());
				entityItem->setIcon( m_entityIcons[entity->GetType()]);
				entityItem->setData( entity->GetName(), Qt::UserRole);

				invisibleRootItem()->appendRow( entityItem);

				m_entityItems[entity->GetName()] = entityItem;
			}
		}
		else
		{
			// �½���
			m_entityTypes[ET_Render]   = new QStandardItem( "StaticMesh");	invisibleRootItem()->appendRow( m_entityTypes[ET_Render]);
			m_entityTypes[ET_Light]    = new QStandardItem( "Light");		invisibleRootItem()->appendRow( m_entityTypes[ET_Light]);
			m_entityTypes[ET_Sound]    = new QStandardItem( "Sound");		invisibleRootItem()->appendRow( m_entityTypes[ET_Sound]);

			for( Scene::EntityList::const_iterator it=entityMap.begin(); it!=entityMap.end(); it++)
			{
				const EntityPtr& entity = it->second;

				QStandardItem* entityItem = new QStandardItem;
				entityItem->setText( entity->GetName());
				entityItem->setIcon( m_entityIcons[entity->GetType()]);

				m_entityTypes[entity->GetType()]->appendRow( entityItem);

				m_entityItems[entity->GetName()] = entityItem;
			}
		}
	}

	// ���
	void SceneInspectorModel::Reset()
	{
		m_entityItems.clear();
		m_entityTypes.clear();

		clear();
	}

	// �Ƿ�֧���ļ�����
	bool SceneInspectorModel::IsSupportExt( const string& ext)
	{
		if( !m_exts.empty())
		{
			if( std::find( m_exts.begin(), m_exts.end(), ext) == m_exts.end())
				return false;
		}

		return true;
	}

	// ˢ����ʾ
	void SceneInspectorModel::Refresh()
	{
		RecursiveDir( m_rootPath, invisibleRootItem());
	}

	// ����Ŀ¼
	void SceneInspectorModel::RecursiveDir( const path& dir, QStandardItem* parentItem)
	{
		vector<QStandardItem*> dirItems;
		vector<QStandardItem*> fileItems;
		for ( directory_iterator it(dir); it!=directory_iterator(); it++)
		{		
			path   childPath = *it;
			string tDirName  = childPath.stem().string();
			string tExt      = childPath.extension().string();

			// ����item��ʾ����
			if( is_directory( *it))
			{
				QStandardItem* childItem = new QStandardItem;
				childItem->setText( tDirName.c_str());
				childItem->setIcon( m_iconMaps["filter"]);
				childItem->setData( childPath.string().c_str(), Qt::UserRole);

				dirItems.push_back( childItem);

				RecursiveDir( *it, childItem);
			}
			else if( IsSupportExt( tExt))
			{
				QStandardItem* childItem = new QStandardItem;
				childItem->setText( childPath.filename().string().c_str());
				childItem->setIcon( m_iconMaps[tExt]);
				childItem->setData( childPath.string().c_str(), Qt::UserRole);

				fileItems.push_back( childItem);
			}
		}

		int tRow = 0;

		// �Ȳ���Ŀ¼
		for ( size_t i=0; i<dirItems.size(); i++)
		{
			parentItem->setChild( tRow, 0, dirItems[i]);
			tRow++;
		}

		// �����ļ�
		for ( size_t i=0; i<fileItems.size(); i++)
		{
			parentItem->setChild( tRow, 0, fileItems[i]);
			tRow++;
		}
	}

	// չ��ĳFiter
	void SceneInspectorModel::OnExpandedFilter(const QModelIndex& pIndex)
	{
		if( m_treeView->isExpanded( pIndex))
			itemFromIndex( pIndex)->setIcon( m_iconMaps["filterexpend"]);
		else
			itemFromIndex( pIndex)->setIcon( m_iconMaps["filter"]);
	}

	// ѡ��ĳ�ļ�
	void SceneInspectorModel::OnSelectedFile( const QModelIndex& pIndex)
	{
		QString filePath = m_proxy ? m_proxy->data( pIndex, Qt::UserRole).toString() : this->data( pIndex, Qt::UserRole).toString();

		// ȡ������ // ������ʾ
		if( m_activeItem)
			m_activeItem->setFont( m_treeView->font());

		// ���ü���
		m_activeItem = itemFromIndex( pIndex);
		if( m_activeItem)
		{
			// ������Ӧ
			QFont font = m_treeView->font();
			font.setBold( true);

			m_activeItem->setFont( font);
		}

		emit FileSelected( filePath.toStdString().c_str());
	}
}