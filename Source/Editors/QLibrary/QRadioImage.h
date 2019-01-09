#pragma once

#include <QtGui/QPixmap>
#include <QtGui/QRadioButton>

namespace QT_UI
{
	//----------------------------------------
	// �½�����    2011-01-11
	//----------------------------------------
	class QRadioImage : public QRadioButton
	{
		Q_OBJECT

	public:
		// ���캯��
		QRadioImage( QWidget* parent = 0);

	public:
		// ������ʾͼƬ
		bool  SetImage( const char* resPath);

	signals:
		// ͼ��ı�
		void imageChanged( QString resPath);

	private slots:
		// ����
		void  paintEvent(QPaintEvent * e);

		// ���˫���¼�
		void  mouseDoubleClickEvent ( QMouseEvent * event );

	private:
		QString       m_resPath;
		QPixmap       m_image;
	};
}