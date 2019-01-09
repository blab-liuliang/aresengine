#pragma once

#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

namespace QT_UI
{
	//-------------------------------------------
	// FileSelect �ļ�ѡ��ؼ� 2013-1-22 ����
	//-------------------------------------------
	class QFileSelect : public QWidget
	{
		Q_OBJECT
	public:
		QFileSelect( QWidget* parent = 0);

		// ����·��
		void SetPath( QString text) { m_lineEdit->setText( text);  }

		// ��ȡ·��
		QString GetPath() { return m_lineEdit->text(); }

	private slots:
		// ѡ��·��
		void OnSelectPath();

	private:
		QHBoxLayout*	m_horizonLayout;
		QLineEdit*		m_lineEdit;
		QToolButton*	m_toolButton;
	};
}