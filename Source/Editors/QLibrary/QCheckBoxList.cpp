#include "QCheckBoxList.h"
#include <boost/tokenizer.hpp>

using namespace boost;

namespace QT_UI
{
	QCheckBoxList::QCheckBoxList( QWidget* parent, const char* items)
		: QWidget( parent)
		, m_items( items)
	{
		m_value = "RQ_Opacity";

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
		//connect( m_toolButton, SIGNAL(clicked()), this, SLOT(OnSelectPath()));
	}

	// ��ʼ������
	void QCheckBoxList::InitItems() 
	{ 
		typedef tokenizer<char_separator<char>> tokenizer;
		char_separator<char> sep(" |");
		tokenizer tok( m_items, sep);
		for( tokenizer::iterator it=tok.begin(); it!=tok.end(); it++)
		{
			QCheckBox* checkBox = new_ QCheckBox( this);
			checkBox->setText( (*it).c_str());

			m_checkBoxs.push_back( checkBox);

			//m_layout->addWidget( m_checkBoxs.back(), m_checkBoxs.size()-1, 0);
		}
	}
}