#include "QFileSelect.h"
#include <boost/filesystem.hpp>
#include <QtGui/QFileDialog>

namespace QT_UI
{
	// ���캯��
	QFileSelect::QFileSelect( QWidget* parent)
		: QWidget( parent)
	{
		// ���ֿؼ�
		m_horizonLayout = new QHBoxLayout( this);
		m_horizonLayout->setSpacing( 0);
		m_horizonLayout->setContentsMargins(0, 0, 0, 0);
		m_horizonLayout->setObjectName( QString::fromUtf8("horizontalLayout"));

		// LineEdit
		m_lineEdit = new QLineEdit( this);
		m_lineEdit->setObjectName( QString::fromUtf8("lineEdit"));
		m_lineEdit->setContentsMargins(0, 0, 0, 0);
		m_horizonLayout->addWidget( m_lineEdit);

		// ToolButton
		m_toolButton = new QToolButton( this);
		m_toolButton->setObjectName( QString::fromUtf8("toolButton"));
		m_toolButton->setText( "...");
		m_toolButton->setContentsMargins(0, 0, 0, 0);
		m_horizonLayout->addWidget( m_toolButton);

		setFocusProxy( m_toolButton);

		// ��Ϣ
		connect( m_toolButton, SIGNAL(clicked()), this, SLOT(OnSelectPath()));
	}

	// ѡ��·��
	void QFileSelect::OnSelectPath()
	{
		QString qFileName = QFileDialog::getOpenFileName( this, tr("Open Picture"), "", tr("*.dds"));
		if( !qFileName.isEmpty())
		{
			boost::filesystem::path filePath( QString(qFileName.toLocal8Bit()).toStdString());

			QString text = QString::fromLocal8Bit( filePath.filename().string().c_str());
			m_lineEdit->setText( text);
		}
	}
}