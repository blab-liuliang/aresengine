#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <QtGui/QDockWidget>
#include "ui_ImageProcess.h"

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class CImageProcess : public QDockWidget, public Ui_ImageProcess
	{
		Q_OBJECT

	public:
		// ���캯��
		CImageProcess( QWidget* parent = 0);

	private slots:
		// ����Filter���� 
		void FilterLostFocus();

		// ˫��
		void OnClicked( QListWidgetItem* pItem);
	};
}

#endif