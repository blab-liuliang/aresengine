#pragma once

#include <QtGui/QMenu>
#include <QtGui/QContextMenuEvent>
#include <QtGui/QDockWidget>
#include "ui_MOCollisionBuild.h"
#include <string>

using namespace std;

namespace QT_UI
{
	//----------------------------------------
	// ����鿴�� ������ 2012-8-28
	//----------------------------------------
	class CollisionBuild : public QDockWidget, public Ui_CollisionBuild
	{
		Q_OBJECT

	public:
		// ���캯��
		CollisionBuild( QWidget* parent = 0);

		// ����CollisionShapes
		void ImportCollisionShapes( const string& path);

		// ����CollisionShapes
		void ExportCollisionShapes( const string& path);

	protected:
		// �Ҽ��˵�
		virtual void contextMenuEvent( QContextMenuEvent* event);

		// �����б���ʾ
		void UpdateTableDisplay();

		// ���µ�ǰѡ����״������
		void UpdateShapeParameterToUI();

	private slots:
		// add collision shape capsule
		void AddCapsule();

		// ɾ����ǰѡ��
		void DeleteSelectedCapsule();

		// ѡ��collision shape
		void OnSelectedCollisionShape();

		// ���½��ҽ������ݵ���״
		void UpdateUICapsuleParameterToShape();

		// ������ײģ��
		void ExportCollisionShapes();

		// ������ײģ��
		void ImportCollisionShapes();

		// �������ģʽ
		void SwitchToWireFrameFillMode();

		// �������ģʽ
		void SwitchToNormalFillMode();

	private:
		bool			m_locking;		// ������ 
		QMenu*          m_mouseMenu;    // ����Ҽ��˵�
	};
}
