#pragma once

#include <QtGui/QDockWidget>
#include "ui_ParametersEditor.h"

namespace Ares
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class UIParametersEditor : public QDockWidget, public Ui_ParametersEditor
	{
		Q_OBJECT

	public:
		// ���캯��
		UIParametersEditor( QWidget* parent = 0);

		// �򿪲���
		void OpenMaterial( const char* materialPath, size_t index);

	private slots:
		// �������Ըı�
		void MaterialPropertyChanged();

	private:
	};
}