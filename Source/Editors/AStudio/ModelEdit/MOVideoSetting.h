#ifndef VIDEO_SETTING_H
#define VIDEO_SETTING_H

#include <QtGui/QDockWidget>
#include "ui_MOVideoSetting.h"

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class MOVideoSetting : public QDockWidget, public Ui_MOVideoSetting
	{
		Q_OBJECT

	public:
		// ���캯��
		MOVideoSetting( QWidget* parent = 0);

	private slots:
		// ����VideoFillMode
		void  UpdateFillMode();
	};
}

#endif