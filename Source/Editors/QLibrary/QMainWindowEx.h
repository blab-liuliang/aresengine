#pragma once

#include <QtGui/QMainWindow>

namespace QT_UI
{
	//----------------------------------------
	// QMainWindowEx 2013-7-31 ����
	//----------------------------------------
	class QMainWindowEx : public QMainWindow
	{
		Q_OBJECT

	public:
		QMainWindowEx( QWidget* parent = 0);

		// ���ò˵�
		virtual void setMenuBar(QMenuBar *menubar);

		// �������Ŀؼ�
		void setCentralWidgetEx(QWidget *widget);
	};
}