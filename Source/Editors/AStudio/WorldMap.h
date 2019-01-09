#pragma once

#include "ui_WorldMap.h"
#include <QtGui/QtGui>
#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "MapLogic.h"
#include <Engine/RenderSystem/AresTerrain.h>

using namespace Ares;

namespace QT_UI
{
	//--------------------------------
	// �����ͼ 2011-08-16  ����
	//--------------------------------
	class CWorldMap : public QMainWindow, public Ui_WorldMap
	{
		Q_OBJECT

	public:
		// ���캯��
		CWorldMap( QWidget* parent = 0);

		// ��������
		~CWorldMap();

	public: signals:
		// ���θı�
		//void EditAreaChanged( IArea* pAres);

	public slots:
		// �½�
		void NewScene( const char* name, const char* location);

		// �򿪵�ͼ
		void OpenMap();

		// �����ͼ
		void SaveMap();

		// �������
		void AddArea();

		// �༭����
		void EditArea();

		// ���ñ༭����
		void EditAreaChanged( QString areaName);

	private:
		// ����map��ʾ
		void UpdateMapShow();

	public slots: 
		// ����GPWindow��ʾ
		void UpdateGPWindow();

		// �����������ť������
		void UpdateEnabled();

	private:
		//QTimer					m_timer;		// ��ʱ��
		QGraphicsScene			m_graphicsScene;// ��ͼ����	

		QGraphicsRectItem*		m_gpWindow;		// gp����
	};
}