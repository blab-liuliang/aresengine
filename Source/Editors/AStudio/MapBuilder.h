#ifndef NEW_MAP_H
#define NEW_MAP_H

#include <QtGui/QDialog>
#include "ui_MapBuilder.h"

namespace QT_UI
{
	//----------------------------------------
	// �½�����    2011-01-11
	//----------------------------------------
	class MapBuilder : public QDialog, public Ui_MapBuilder
	{
		Q_OBJECT

	public:
		// ���캯��
		MapBuilder( QWidget* parent = 0);

		// �½�Ĭ�ϵ�ͼ
		static void NewMapUnSaved();

	public: signals:
		// �½���ͼ
		void CreateMap( const char* mapName, const char* mapLocation);

	private slots:
		// �½���ͼ
		void NewMap();

		// �½�����
		void AddTerrain();

		// ѡ���ͼ���λ��
		void SelectMapLocation();
	};
}

#endif