#pragma once

#include <QtGui/QMainWindow>
#include "QMainWindowEx.h"
#include "ui_UIMainWindow.h"
#include "UIEdit.h"

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class UIMainWindow : public QObject, public Ui_UIMainWindow
	{
		Q_OBJECT

	public:
		// ���캯��
		UIMainWindow( QMainWindowEx* parent = 0);

		// ��ʼ��Ⱦ
		void BeginRender();

		// ����
		void Active();

		// ʧЧ
		void Deactive();

	private slots:
		// �½�Ч��
		void New();

		// ��Ч���ļ�
		void Open();

		// ����Ч���ļ�
		void Save();

		// ��ʾ���ظ���
		void SwitchGridVisible();

		// ��ʾ���ر���
		void SwitchBackgroundVisible();

		// about
		void  AresAbout();

	private:
		UiEdit*				m_uiEditLogic;		// ����༭�߼�
		QMainWindowEx*		m_mainWindow;		// ������
	};
}