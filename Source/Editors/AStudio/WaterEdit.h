#pragma once

#include <QtGui/QDockWidget>
#include "ui_WaterEdit.h"

namespace QT_UI
{
	//----------------------------------------
	// �½�����    2011-01-11
	//----------------------------------------
	class CWaterEdit : public QDockWidget, public Ui_WaterEdit
	{
		Q_OBJECT

	public:
		// ���캯��
		CWaterEdit( QWidget* parent = 0);

	private slots:
		// ����ˮ
		void PutWater(bool checked);

	public:
	};
}