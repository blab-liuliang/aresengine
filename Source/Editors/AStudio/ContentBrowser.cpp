#include <QtGui/QtGui>
#include "ContentBrowser.h"
#include "SCLogic.h"

using namespace Ares;

namespace QT_UI
{
	// ���캯��
	ContentBrowser::ContentBrowser( QWidget* parent/* = 0*/)
		: QMainWindow( parent)
	{
		setupUi( this);

		// ��ʼ��ͼ��
		m_iconMap["filter"]       = ( QIcon(":/icon/Icon/folder_close.png"));
		m_iconMap["filterexpend"] = ( QIcon(":/icon/Icon/folder_open.png"));
		m_iconMap[".m1"]          = ( QIcon(":/icon/Icon/model.png"));

		m_model = new_ QDirectoryModel;
		m_proxyModel = new_ QSortFilterProxyModel( this);
		m_proxyModel->setSourceModel( m_model);
		m_proxyModel->setFilterKeyColumn( 0);
		m_pModelListTreeView->setModel( m_proxyModel);

		InitModelList();

		connect( m_filter,	 SIGNAL(textChanged(QString)), this, SLOT(ApplyFilter(QString)));

		connect( m_model, SIGNAL(FileSelected(const char*)), this, SLOT( OnSelectEntity( const char*)));
		connect( m_model, SIGNAL(FileEdit( const char*)),    this, SLOT( EditSelect( const char*)));
		/*connect( m_pModelListTreeView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT( ShowMenu(const QPoint&)));
		connect( m_pModel, SIGNAL(dataChanged( const QModelIndex&, const QModelIndex&)), this, SLOT( NameChanged( const QModelIndex&)));
		connect( m_pModel, SIGNAL(FileSelected(const char*)), this, SLOT( OnSelectEntity( const char*)));

		// action
		connect( m_pActionAdd, SIGNAL(triggered()), this, SLOT( AddRes()));
		connect( m_pActionAddFilter, SIGNAL(triggered()), this, SLOT( AddFilter()));
		connect( m_pActionReMove, SIGNAL(triggered()), this, SLOT( ReMoveFile()));
		connect( m_pActionReName, SIGNAL(triggered()), this, SLOT( ReName()));

		// ��̬��Դ
		connect( m_dynamicDirectLight, SIGNAL(clicked()),this, SLOT( NewDynamicDirectLight()));*/
		connect( m_dynamicAmbientLight,SIGNAL(clicked()), this,SLOT( NewDynamicAmbientLight()));
		connect( m_dynamicPointLight, SIGNAL(clicked()), this, SLOT( NewDynamicPointLight()));

		// ����
		connect( m_entityTerrain, SIGNAL( clicked()), this, SLOT( NewTerrain()));
		connect( m_entityOcean,	  SIGNAL( clicked()), this, SLOT( NewOcean()));


		m_entityMenu = NULL;
		m_filterMenu = NULL;
	}

	// ��������
	ContentBrowser::~ContentBrowser()
	{
	}

	// ����ģ���б�
	void ContentBrowser::InitModelList()
	{
		m_model->clear();

		QStringList titleLable;
		titleLable << "EntityList";
		m_model->setHorizontalHeaderLabels( titleLable);

		m_rootPath = "data\\model";
		m_extFilter= ".model";

		m_model->SetRootPath( m_rootPath.c_str(), m_extFilter.c_str(), m_pModelListTreeView, m_proxyModel);
		m_model->Refresh();
	}

	// �½����Դ
	void ContentBrowser::NewDynamicPointLight()
	{
		// �������Դ
		SCLogic_Main->SetHandleType( EM_HT_PUTENTITY);
		Logic_EntityPut->New( ED_LightPoint);
	}

	// �½������
	void ContentBrowser::NewDynamicDirectLight()
	{
		// �������Դ
		SCLogic_Main->SetHandleType( EM_HT_PUTENTITY);
		Logic_EntityPut->New( ED_LightDirection);
	}

	// �½�������
	void ContentBrowser::NewDynamicAmbientLight()
	{
		// ������
		SCLogic_Main->SetHandleType( EM_HT_PUTENTITY);
		Logic_EntityPut->New( ED_LightAmbient);
	}

	// �½�����
	void ContentBrowser::NewTerrain()
	{
		SCLogic_Main->SetHandleType( EM_HT_PUTENTITY);
		Logic_EntityPut->New( ED_Terrain);
	}

	// �½�����
	void ContentBrowser::NewOcean()
	{
		SCLogic_Main->SetHandleType( EM_HT_PUTENTITY);
		Logic_EntityPut->New( ED_Ocean);
	}

	// ������
	void ContentBrowser::ReName()
	{	
		m_pModelListTreeView->edit( m_pModelListTreeView->currentIndex());
	}

	// �����Դ
	void ContentBrowser::AddRes()
	{
	}

	// ���Filter
	void ContentBrowser::AddFilter()
	{
		
	}

	// �Ƴ� or ɾ���ļ�
	void ContentBrowser::ReMoveFile()
	{
	}

	// ���ַ����ı�
	void ContentBrowser::NameChanged( const QModelIndex& index)
	{

	}

	// ѡ��ĳʵ��
	void ContentBrowser::OnSelectEntity( const char* filePath)
	{
		if( filePath)
		{
			SCLogic_Main->SetHandleType( EM_HT_PUTENTITY);
			Logic_EntityPut->SetResPath( filePath);
			Logic_EntityPut->New( ED_Model);
		}
	}

	// �༭ĳʵ��
	void ContentBrowser::EditSelect( const char* filePath)
	{
		if( filePath)
		{
			ostringstream oss;
			oss << "ModelEditor_d.exe " << filePath;
			WinExec( oss.str().c_str(), SW_NORMAL);
		}
	}

	// �Ҽ�ʵ��˵�
	void ContentBrowser::ShowMenu(const QPoint& point)
	{/*
		TiXmlElement* pXmlElement = m_pModel->data( m_pModelListTreeView->currentIndex(), Qt::UserRole).value<TiXmlElement*>();
		if( !pXmlElement)
			return;

		if( !pXmlElement->Parent())
			int a = 3;

		// ����㲻�ܱ��Ƴ�
		if( !pXmlElement->Parent() || !pXmlElement->Parent()->Parent())
			m_pActionReMove->setEnabled( false);
		else
			m_pActionReMove->setEnabled( true);

		if( pXmlElement->ValueStr() == string("filter"))
		{
			if( !m_filterMenu)
			{
				m_filterMenu = new_ QMenu();

				QMenu* addMenu = new QMenu("Add");
				addMenu->addAction( m_pActionAdd);
				addMenu->addAction( m_pActionAddFilter);

				m_filterMenu->addMenu( addMenu);
				m_filterMenu->addSeparator();
				m_filterMenu->addAction( m_pActionReMove);
				m_filterMenu->addAction( m_pActionReName);
			}

			m_filterMenu->exec( QCursor::pos());
		}
		else
		{
			if( !m_entityMenu)
			{
				m_entityMenu = new QMenu();

				m_entityMenu->addAction( m_pActionOpen);
				m_entityMenu->addAction( m_pActionOpenMethod);
				m_entityMenu->addSeparator();
				m_entityMenu->addAction( m_pActionReMove);
				m_entityMenu->addAction( m_pActionReName);
			}

			m_entityMenu->exec( QCursor::pos());
		}	*/
	}

	// ����
	void  ContentBrowser::Save()
	{
	}

	// ִ�й���
	void ContentBrowser::ApplyFilter( QString str)
	{
		QRegExp regExp( str, Qt::CaseInsensitive, QRegExp::Wildcard);
		m_proxyModel->setFilterRegExp( regExp);
	}
}