#pragma once

#include <QtGui/QDockWidget>
#include <QtGui/QtEvents>
#include "ui_MaterialExpression.h"

namespace Ares
{
	//---------------------------------
	// ���ʱ��ʽ 2013-3-19 ����
	//---------------------------------
	class UIMaterialExpression : public QDockWidget, public Ui_MaterialExpression
	{
		Q_OBJECT

	public:
		// ���캯��
		UIMaterialExpression( QWidget* parent= NULL);

	protected slots:
		// ������ק�¼�
		void OnSelectExpression();
	};
}