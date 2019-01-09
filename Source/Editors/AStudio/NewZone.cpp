#include <QtGui/QtGui>
#include "NewZone.h"
#include "Logic.h"
#include <string>

using namespace std;
using namespace Ares;

extern CLogic*    g_pLogic;

namespace QT_UI
{
	// ���캯��
	CNewZone::CNewZone( QWidget* parent/* = 0*/)
		: QDialog( parent)
	{
		setupUi( this);

		connect( m_pPushButtonOK, SIGNAL(clicked()), this, SLOT( AddTerrain()));
		connect( m_okNewMap,	  SIGNAL(clicked()), this, SLOT( NewMap()));
		connect( m_locationOpen,  SIGNAL(clicked()), this, SLOT( SelectMapLocation()));
	}

	// ������ʾ����
	void CNewZone::SetType( Type type)
	{
		// ��������,��ʾ��ͬ
		m_oldNewMap->setVisible( true);
		m_newMap->setVisible( true);

		if( type == EM_NEWMAP_OLD)
		{
			m_newMap->setVisible( false);
		}
		else if( type==EM_NEWMAP)
		{
			m_oldNewMap->setVisible( false);
		}

		this->adjustSize();
	}

	// �½�����
	void CNewZone::AddTerrain()
	{
		string zoneName = m_pZoneNameEdit->text().toStdString();
		int width  = m_pZoneWidthEdit->text().toInt();
		int height = m_pZoneHeightEdit->text().toInt();

		Rect3 rect;
		rect.z0 = -125.f; rect.z1 = 500.f;
		rect.x0 = 0.f,    rect.x1 = width;
		rect.y0 = 0.f,    rect.y1 = height;

		int terrainShift = m_terrainShift->value();

		//g_pLogic->NewScene( zoneName.c_str(), rect, 7, ARES_TERRAIN_DEFAULT, rect, terrainShift);

		setVisible( false);
	}

	// �½���ͼ
	void CNewZone::NewMap()
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

			emit CreateMap( mapName.c_str(), tLocation.c_str());

			setVisible( false);
		}
	}

	// ѡ���ͼ���λ��
	void CNewZone::SelectMapLocation()
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