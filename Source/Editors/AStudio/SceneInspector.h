#pragma once

#include "ui_WorldMap.h"
#include <QtGui/QtGui>
#include <QtGui/QDockWidget>
#include <QtGui/QSortFilterProxyModel>
#include "ui_SceneInspector.h"
#include "SceneInspectorModel.h"

namespace QT_UI
{
	//--------------------------------
	// �����ͼ 2011-08-16  ����
	//--------------------------------
	class SceneInspector : public QDockWidget, public Ui_SceneInspector
	{
		Q_OBJECT

	public:
		SceneInspector( QWidget* parent = 0);
		~SceneInspector();

		// ��ȡMapModel
		SceneInspectorModel* GetSceneInsepctorModel() { return m_model; }

	private slots:
		// �Ҽ�ʵ��˵�
		void ShowMenu(const QPoint& point);

		// ִ�й���
		void ApplyFilter( QString str);

		// ѡ��ĳʵ��
		void OnSelectEntity( const char* entityName);

	private:
		SceneInspectorModel*	m_model;		// QModel
		QSortFilterProxyModel*	m_proxyModel;	// �������ģ��
		QMenu*					m_menu;			// �Ҽ��˵�
	};
}