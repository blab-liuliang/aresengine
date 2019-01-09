#pragma once

#include <QtGui/QDockWidget>
#include "ui_FxObjectViewer.h"
#include <Engine/FxSystem/AresFxObject.h>
#include <string>

using namespace std;
using namespace Ares;

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class FxObjectViewer : public QDockWidget, public Ui_FxObjectViewer
	{
		Q_OBJECT

	public:
		// ���캯��
		FxObjectViewer( QWidget* parent = 0);

	public:
		// �Ҽ��˵�
		virtual void contextMenuEvent( QContextMenuEvent* event);

		// �����б���ʾ
		void UpdateObjectListDisplay();

		// ��֯Ч��������ʾ����
		QString GetFxObjectDisplayName( FxObject* object);

	private slots:
		// ���3D��Ƭ
		void Add3dPatch();

		// �������ϵͳ
		void AddPartcileSystem();

		// ѡ����Ч����
		void OnSelectedFxObject();

		// ɾ��ѡ��Object
		void DeleteSelectedObject();

	private:
		QMenu*          m_mouseMenu;    // ����Ҽ��˵�
		vector<QIcon>	m_icons;		// ͼ��
	};
}
