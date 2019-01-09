#pragma once

#include <Core/AresCore.h>
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <string>

using namespace std;

namespace QT_UI
{
	//------------------------------------
	// ��ѡ�༭ 2013-4-12 ����
	//------------------------------------
	class QCheckBoxList : public QWidget
	{
		Q_OBJECT

	public:
		QCheckBoxList( QWidget* parent=0, const char* items="Opacity");

		// ��ȡֵ
		QString GetValue() const { return m_value.c_str(); }

		// ����ֵ
		void SetValue( QString& value) { m_value = value.toStdString(); }

	private:
		// ��ʼ��Items
		void InitItems();

	private:
		string				m_value;		// ֵ
		string				m_items;		// ѡ��
		vector<QCheckBox*>	m_checkBoxs;	// �ؼ��б�

		QHBoxLayout*		m_horizonLayout;
		QLineEdit*			m_lineEdit;
		QToolButton*		m_toolButton;
	};
}