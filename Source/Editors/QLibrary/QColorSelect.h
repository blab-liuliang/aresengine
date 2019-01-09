#pragma once

#include <QtGui/QPainter>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include <Core/AresMath.h>

using namespace std;
using namespace Ares;

namespace QT_UI
{
	//-------------------------------------------
	// ColorSelect ��ɫѡ��ť 2013-3-4 ����
	//-------------------------------------------
	class QColorSelect : public QWidget
	{
		Q_OBJECT
	public:
		QColorSelect( QWidget* parent = 0);

		// ������ɫ
		void SetColor( string color);

		// ������ɫ
		void SetColor( const ColorRGB& color);

		// ��ȡ��ɫ
		string GetColor();

		// ��ȡ��ɫ
		const ColorRGB& GetColor() const { return m_color; }

		// MVC��Ⱦ
		static void ItemDelegatePaint( QPainter *painter, const QRect& rect, const string& val);

	private:
		// ������ʾ
		void UpdateDisplay();

	private slots:
		// ѡ��·��
		void OnSelectColor();

	private:
		ColorRGB		m_color;
		QPushButton*	m_colorButton;
		QHBoxLayout*	m_horizonLayout;
	};
}