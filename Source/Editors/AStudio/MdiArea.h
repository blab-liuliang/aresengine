#pragma once

#include <QtGui/QMdiArea>
#include "RenderWidget.h"

namespace QT_UI
{
	//-----------------------------------
	// Dx9MdiArea dx��ʾ����
	//-----------------------------------
	class MOMdiArea : public QMdiArea
	{
		Q_OBJECT

	public:
		MOMdiArea( QWidget* parent = NULL);
		~MOMdiArea();

		// ��ʼ��Ⱦ
		void BeginRender();

		// ������Ⱦ
		void SetRenderenable( bool scRender, bool moRender);

		// ���ڴ�С�ı�
		void ResizeWindow();

	private slots:
		// ��Ⱦ
		void  Render();

		// �����豸
		void  ResetDevice();

	private:
		QSize				m_dx9Size;				// �������С

		MORenderWidget*		m_renderWidgetMO;		// ģ����Ⱦ����
		MORenderWidget*		m_renderWidgetSC;		// ģ����Ⱦ����

		QMdiSubWindow*		m_subWindowMO;			// �Ӵ���
		QMdiSubWindow*		m_subWindowSC;			// �Ӵ���

		bool				m_scRender;				// �Ƿ���Ⱦ����
		bool				m_moRender;				// �Ƿ���Ⱦģ��
	};
}