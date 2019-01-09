#include <QtGui/QtGui>
#include "MapBuilder.h"
#include "SCMainWindow.h"
#include "MainWindow.h"
#include "SCLogic.h"
#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace Ares;
using namespace boost::filesystem;

namespace QT_UI
{
	// ���캯��
	MapBuilder::MapBuilder( QWidget* parent/* = 0*/)
		: QDialog( parent)
	{
		setupUi( this);

		connect( m_okNewMap,	  SIGNAL(clicked()), this, SLOT( NewMap()));
		connect( m_locationOpen,  SIGNAL(clicked()), this, SLOT( SelectMapLocation()));
	}

	// �½�����
	void MapBuilder::AddTerrain()
	{/*
		string zoneName = m_pZoneNameEdit->text().toStdString();
		int width  = m_pZoneWidthEdit->text().toInt();
		int height = m_pZoneHeightEdit->text().toInt();

		Rect3 rect;
		rect.z0 = -125.f; rect.z1 = 500.f;
		rect.x0 = 0.f,    rect.x1 = width;
		rect.y0 = 0.f,    rect.y1 = height;

		int terrainShift = m_terrainShift->value();

		//g_pLogic->NewScene( zoneName.c_str(), rect, 7, ARES_TERRAIN_DEFAULT, rect, terrainShift);

		setVisible( false);*/
	}

	// �½���ͼ
	void MapBuilder::NewMap()
	{
		string mapLocation = m_mapLocation->text().toStdString();
		string mapName     = m_mapName->text().toStdString();

		if( mapLocation.empty())
			m_error->setText( "��ͼλ�ò���Ϊ��");

		if( mapName.empty())
			m_error->setText( "��ͼ������Ϊ��");
		else
		{
			m_error->setText("");
				
			string tLocation = mapLocation + "/" + mapName + "/";
			mapName += ".map";

			// Ŀ¼�Ѵ���,���Ѳ����
			path locationPath( tLocation);
			if( exists( locationPath))
			{
				try
				{
					if( QMessageBox::Yes ==QMessageBox::warning( this, "Warning", "Ŀ¼�Ѵ���,ȷ�������Ŀ¼��������Դ", QMessageBox::Yes | QMessageBox::Cancel))
						remove_all( locationPath);
					else
						return;
				}
				catch( filesystem::filesystem_error&)
				{
					if( QMessageBox::Yes ==QMessageBox::warning( this, "Warning", "���Ŀ¼����Դʧ��,��ѡ������Ŀ¼��������", QMessageBox::Yes))
						return;
				}
			}

			// ����·��
			create_directory( locationPath);

			// ����ͼ·��
			path lightmapPath( string( tLocation) + string("lightmap/"));
			create_directory( lightmapPath);

			// �������
			UI_MainWindow->setWindowTitle( mapName.c_str() + QString("-Ares Studio(32λ,Dx11)"));

			// �߼�����
			SCLogic_Map->CreateScene( mapName.c_str(), tLocation.c_str());

			setVisible( false);
		}
	}

	// �½�Ĭ�ϵ�ͼ
	void MapBuilder::NewMapUnSaved()
	{
		string mapLocation = "data/maps";
		string mapName     = "UnSaved";

		string tLocation = mapLocation + "/" + mapName + "/";
		mapName += ".map";

		// Ŀ¼�Ѵ���,���Ѳ����
		path locationPath( tLocation);
		if( exists( locationPath))
		{
			try 
			{ 
				remove_all( locationPath); 
			}
			catch( filesystem::filesystem_error&) 
			{}
		}

		try
		{
			// ����·��
			create_directory( locationPath);

			// ����ͼ·��
			path lightmapPath( string( tLocation) + string("lightmap/"));
			create_directory( lightmapPath);
		}
		catch( filesystem::filesystem_error&) 
		{

		}

		// �������
		UI_MainWindow->setWindowTitle( mapName.c_str() + QString("-Ares Studio(32λ,Dx11)"));

		// �߼�����
		SCLogic_Map->CreateScene( mapName.c_str(), tLocation.c_str());
	}

	// ѡ���ͼ���λ��
	void MapBuilder::SelectMapLocation()
	{
		QString qFileDir = QFileDialog::getExistingDirectory( this, tr("choose a directory"), "data\\map\\", QFileDialog::ShowDirsOnly);

		QDir dir( QDir::currentPath());
		qFileDir = dir.relativeFilePath( qFileDir);

		if( !qFileDir.isEmpty())
		{
			m_mapLocation->setText( qFileDir);
		}
	}
}