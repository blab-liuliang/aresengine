#include "WorldMap.h"
#include <QtGui/QFileDialog>
#include "SCLogic.h"
#include <boost/filesystem.hpp>
#include "SCMainWindow.h"

using namespace Ares;
using namespace boost::filesystem;

namespace QT_UI
{
	// ���캯��
	CWorldMap::CWorldMap( QWidget* parent)
		: QMainWindow( parent)
	{
		setupUi( this);

		m_areaGroupBox->setVisible( false);

		connect( m_areaAdd,     SIGNAL(clicked()), this, SLOT( AddArea()));
		connect( m_areaConfirm, SIGNAL(clicked()), this, SLOT( EditArea()));
		connect( m_areaList,    SIGNAL(activated(QString)), this, SLOT( EditAreaChanged( QString)));
		connect( m_areaName,     SIGNAL(textChanged ( const QString&)), this, SLOT(UpdateEnabled()));

		m_graphicsView->setScene( &m_graphicsScene);

		// ʱ���¼�
		//connect( &m_timer, SIGNAL( timeout()), this, SLOT( UpdateGPWindow()));
		//m_timer.start( 20);

		m_gpWindow = NULL;
	}

	// ��������
	CWorldMap::~CWorldMap()
	{
	}

	// ����GPWindow��ʾ
	void CWorldMap::UpdateGPWindow()
	{
		Vector3 tPos;
		float tRadius = static_cast<float>(m_radius->value());
		if( SCLogic_Move && SCLogic_Move->GetMoveType() == CMoveLogic::EM_FOLLOW)
		{
			// ��Ϸģʽ��������
			tPos = SCLogic_Move->GetCenterPos();

			SCLogic_Map->SetNavWindow( tPos.x, tPos.y, tRadius);
		}
		else
		{
			// �༭ģʽ����������
			Scene* scene = SCLogic_Scene;
			if( scene)
			{
				//Scene::SSize tSize = scene->GetSize();

				// ��뾶, ���ĵ�
				//tRadius = (std::max)( tSize.m_height, tSize.m_width) / 2.f;
				//tPos.x   = tSize.m_posX + tSize.m_width / 2.f;
				//tPos.y   = tSize.m_posY + tSize.m_height/ 2.f; 

				//SCLogic_Map->SetNavWindow( tPos.x,  tPos.y, tRadius);
			}
		}

		// ���½���
		float tX = (tPos.x - tRadius)* 0.25f;
		float tY = (tPos.y - tRadius)* 0.25f;
		float tScaleRadius = tRadius * 0.5f;

		if( !m_gpWindow)
		{
			QPen   pen( QColor( 0, 0, 128, 80));
			QBrush brush( QColor( 0, 128, 128, 80));
			pen.setWidth( 2);

			m_gpWindow = m_graphicsScene.addRect( tX, tY, tScaleRadius, tScaleRadius, pen, brush);
			m_graphicsScene.setFocusItem( m_gpWindow);
		}
		else
		{
			m_gpWindow->setRect( tX, tY, tScaleRadius, tScaleRadius);
		}
	}

	// �½�
	void CWorldMap::NewScene( const char* name, const char* location)
	{
		// Ŀ¼�Ѵ���,���Ѳ����
		path locationPath( location);
		if( exists( locationPath))
		{
			if( QMessageBox::Yes ==QMessageBox::warning( this, "Warning", "Ŀ¼�Ѵ���,ȷ�������Ŀ¼��������Դ", QMessageBox::Yes | QMessageBox::Cancel))
				remove_all( locationPath);
			else
				return;
		}

		// ����·��
		create_directory( locationPath);

		// ����ͼ·��
		path lightmapPath( string( location) + string("lightmap/"));
		create_directory( lightmapPath);

		// �������
		setWindowTitle( name);

		// �߼�����
		SCLogic_Map->CreateScene( name, location);

		m_graphicsScene.clear();
		m_gpWindow = NULL;
	}

	// �򿪵�ͼ
	void CWorldMap::OpenMap()
	{
		QString fileName = QFileDialog::getOpenFileName( this, tr("Open Map"), "", tr("(*.map)"));
		if( !fileName.isEmpty())
		{
			string tFileName = fileName.toStdString();

			SCLogic_Map->OpenScene( tFileName.c_str());
			Scene* tMap = SCLogic_Scene;
			if( tMap)
			{
				m_areaList->clear();

				setWindowTitle(tMap->GetName());

				m_areaList->addItem( tMap->GetName());
	
				/*if( tMap->GetAreaNum())
				{
					size_t tAreaIdx = 0;
					EditAreaChanged( tMap->GetArea( tAreaIdx)->GetName());
				}*/

				UpdateMapShow();
			}
		}
	}

	// ����map��ʾ
	void CWorldMap::UpdateMapShow()
	{
		m_graphicsScene.clear();

		m_gpWindow = NULL;

		Scene* scene = SCLogic_Scene;
		if( scene)
		{
			//const Scene::SSize& size = scene->GetSize();

			//QRect tRect( size.m_posX/4, size.m_posY/4, size.m_width/4, size.m_height/4);
			//QGraphicsRectItem  *rect = m_graphicsScene.addRect( tRect);
			//if( rect)
			//{

			//}
		}
	}

	// �����������ť������
	void CWorldMap::UpdateEnabled()
	{
		string tAreaName = m_areaName->text().toStdString();
		if( tAreaName.empty() || !SCLogic_Scene)
			m_areaAdd->setEnabled( false);
		else
			m_areaAdd->setEnabled( true);
	}

	// �����ͼ
	void CWorldMap::SaveMap()
	{
		// �˴��ĵ����Ϊ
		//QString tName    = m_mapName->text();
		//QString fileName = QFileDialog::getSaveFileName( this, tr("Save Map"), tName, tr("(*.map)"));
		//if( !fileName.isEmpty())
		//{
		//	string tFileName = fileName.toStdString();
			SCLogic_Map->SaveMap( NULL);
		//}
	}

	// �������
	void CWorldMap::AddArea()
	{/*
		string tAreaName = m_areaName->text().toStdString();

		// �߼����
		g_pLogic->m_mapLogic.SetSceneSize( tAreaName.c_str(), m_locationX->value(), m_locationY->value(), m_width->value(), m_height->value());

		// ���Ľ���
		m_areaList->addItem( tAreaName.c_str());

		// �����ͼ��ʾ
		UpdateMapShow();

		// �����������group
		m_areaGroupBox->setVisible( false);*/
	}

	// �༭����
	void CWorldMap::EditArea()
	{

	}

	// ���ñ༭����
	void CWorldMap::EditAreaChanged(QString areaName)
	{
		/*g_pLogic->m_mapLogic.SetActiveArea( areaName.toStdString().c_str());

		IArea* pArea = g_pLogic->m_mapLogic.GetActiveArea();
		if( pArea)
		{
			emit EditAreaChanged( pArea);

			return;
		}

		emit EditAreaChanged( NULL);*/
	}
}