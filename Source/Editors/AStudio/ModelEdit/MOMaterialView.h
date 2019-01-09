#pragma once

#include <QtGui/QDockWidget>
#include "ui_MOMaterialView.h"

namespace QT_UI
{
	//----------------------------------------
	// ���ʱ༭	2011-05-16   ����
	//----------------------------------------
	class MateriaViewer : public QDockWidget, public Ui_MaterialView
	{
		Q_OBJECT

	public:
		// ���캯��
		MateriaViewer(  QWidget* parent = 0);

		// �򿪲����ļ�
		void RefreshDisplay();

	private slots:
		// ����ѡ�иı�
		void OnSelectedMaterialChanged( int idx);

		// �༭����
		void OnEditMaterial();

	private:
	};
}