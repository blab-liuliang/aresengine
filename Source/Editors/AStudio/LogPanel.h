#pragma once

#include <QtGui/QDialog>
#include "ui_LogPanel.h"

namespace QT_UI
{
	//----------------------------------------
	// ��� ������ 2010-12-30
	//----------------------------------------
	class LogPanel : public QDialog, public Ui_LogPanel
	{
		Q_OBJECT

	public:
		// ���캯��
		LogPanel( QWidget* parent = 0);

		// ��������
		~LogPanel();

		// ����
		void Warning( const char* msg);

	protected:
		// �ر�
		void closeEvent(QCloseEvent *event);

	};
}