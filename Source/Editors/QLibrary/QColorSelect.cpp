#include "QColorSelect.h"
#include <Core/AresMath.h>
#include <QtGui/QColorDialog>
#include <EditorKit/DataTypeConversion.h>

namespace QT_UI
{
	QColorSelect::QColorSelect( QWidget* parent)
		: QWidget( parent)
	{
		// ���ֿؼ�
		m_horizonLayout = new_ QHBoxLayout( this);
		m_horizonLayout->setContentsMargins(0, 0, 0, 0);
		m_horizonLayout->setObjectName( QString::fromUtf8("horizontalLayout"));

		// ��ɫ��ť
		m_colorButton = new_ QPushButton( this);
		m_colorButton->setObjectName( QString::fromUtf8("colorButton"));
		m_colorButton->setContentsMargins(0, 0, 0, 0);
		m_horizonLayout->addWidget( m_colorButton);

		// ��Ϣ
		connect( m_colorButton, SIGNAL(clicked()), this, SLOT(OnSelectColor()));
	}

	// ѡ��·��
	void QColorSelect::OnSelectColor()
	{
		QColor color = QColorDialog::getColor( QColor( (int)(m_color.r*255.f), (int)(m_color.g*255.f), (int)(m_color.b*255.f)), this);

		SetColor( ColorRGB( color.red()/255.f, color.green()/255.f, color.blue()/255.f));
	}

	// ����·��
	void QColorSelect::SetColor( string color) 
	{ 
		m_color = Ares::DTC::StringToColorRGB( color);

		UpdateDisplay();
	}

	// ������ɫ
	void QColorSelect::SetColor( const ColorRGB& color)
	{ 
		m_color=color;

		UpdateDisplay();
	}

	// ��ȡ·��
	string QColorSelect::GetColor() 
	{ 
		return Ares::DTC::ColorRGBToString( m_color);
	}

	// ������ʾ
	void QColorSelect::UpdateDisplay()
	{
		char result[512];

		sprintf_s( result, 512, "background-color: rgb(%d,%d,%d);", (int)(m_color.r*255.f), (int)(m_color.g*255.f), (int)(m_color.b*255.f));

		m_colorButton->setStyleSheet( result);
	}

	// MVC��Ⱦ
	void QColorSelect::ItemDelegatePaint( QPainter *painter, const QRect& rect, const string& val)
	{
		ColorRGB color = DTC::StringToColorRGB( val);

		QRect tRect = rect; tRect.setWidth( rect.width()-1); tRect.setHeight( rect.height()-1);
		painter->setBrush( QColor( (int)(color.r*255.f), (int)(color.g*255.f), (int)(color.b*255.f)));
		painter->drawRect( tRect);
		painter->setPen( Qt::black);
		painter->drawRect( tRect);
	}
}