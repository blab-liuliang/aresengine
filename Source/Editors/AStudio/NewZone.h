#ifndef NEW_MAP_H
#define NEW_MAP_H

#include <QtGui/QDialog>
#include "ui_NewZone.h"

namespace QT_UI
{
	//----------------------------------------
	// �½�����    2011-01-11
	//----------------------------------------
	class CNewZone : public QDialog, public Ui_NewZone
	{
		Q_OBJECT

	public:
		enum Type
		{
			EM_NEWMAP_OLD = 1,
			EM_NEWMAP,
		};

		// ���캯��
		CNewZone( QWidget* parent = 0);

		// ������ʾ����
		void SetType( Type type);

	public: signals:
		// �½���ͼ
		void CreateMap( const char* mapName, const char* mapLocation);

	private slots:
		// �½�����
		void AddTerrain();

		// �½���ͼ
		void NewMap();

		// ѡ���ͼ���λ��
		void SelectMapLocation();
	};
}

#endif