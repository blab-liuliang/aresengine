#pragma once

#include <QtGui/QWidget>
#include "ui_MOModelConverter.h"

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class MOModelConverter : public QDialog, public Ui_MOModelConverter
	{
		Q_OBJECT

	public:
		// ���캯��
		MOModelConverter( QWidget* parent = 0);

	private slots:
		// ѡ��YND��Դ·��
		void SelectYNDLocation();

		// ѡ��Ares�洢·��
		void SelectAresLocation();

		// ת��
		void ConvertexFromYNDToAres();

	private:
	};
}
