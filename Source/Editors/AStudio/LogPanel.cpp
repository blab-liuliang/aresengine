#include "LogPanel.h"
#include <QtGui/QListWidgetItem>

namespace QT_UI
{
	// ���캯��
	LogPanel::LogPanel( QWidget* parent/* = 0*/)
		: QDialog( parent)
	{
		setupUi( this);
	}

	// ��������
	LogPanel::~LogPanel()
	{
	}

	// ����
	void LogPanel::Warning( const char* msg)
	{
		QListWidgetItem* warningItem = new QListWidgetItem( msg);
		if( warningItem)
		{	
			warningItem->setIcon( QIcon(":/icon/Icon/MapCheck_Warning.png"));
			m_logList->addItem( warningItem);
		}

		// ��ʾ����
		setVisible( true);
	}

	// �ر�
	void LogPanel::closeEvent(QCloseEvent *event)
	{
		m_logList->clear();

		QDialog::closeEvent( event);
	}
}