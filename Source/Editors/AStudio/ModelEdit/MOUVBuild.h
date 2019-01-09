#pragma once

#include <QtGui/QDockWidget>
#include "ui_MOUVBuild.h"

namespace QT_UI
{
	//----------------------------------------
	// ����鿴�� ������ 2012-8-28
	//----------------------------------------
	class UVBuild : public QDockWidget, public Ui_UVBuild
	{
		Q_OBJECT

	public:
		// ���캯��
		UVBuild( QWidget* parent = 0);

		// ����
		void Warning( const char* msg);

	private slots:
		// ����ΨһUV
		void Build();

		// ��ԭģ��
		void Restore();
	};
}
