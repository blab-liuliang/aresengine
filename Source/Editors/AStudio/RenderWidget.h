#pragma once

#include <string>
#include <QUrl>
#include <QtGui/QtEvents>
#include <QtGui/QWidget>
#include <boost/signals2/signal.hpp>

using namespace std;
using namespace boost::signals2;

namespace QT_UI
{
	//-----------------------------------
	// Dx9MdiArea dx��ʾ����
	//-----------------------------------
	class MORenderWidget : public QWidget
	{
		Q_OBJECT

	public:
		MORenderWidget( QWidget* parent = NULL);
		~MORenderWidget();

		// ����ƶ��¼�
		virtual void mouseMoveEvent(QMouseEvent *);

	protected:
		// �������¼�
		void dragEnterEvent( QDragEnterEvent * event);

		// ����ͷ��¼�
		void dropEvent( QDropEvent* event);
	};
}