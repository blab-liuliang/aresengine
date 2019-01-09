#include "MOLogic.h"
#include "MOCollisionBuild.h"
#include <Engine/RenderSystem/AresVisualShape.h>
#include <QtGui/QFileDialog>

using namespace Ares;

namespace QT_UI
{
	// ���캯��
	CollisionBuild::CollisionBuild( QWidget* parent)
		: QDockWidget( parent)
		, m_mouseMenu( NULL)
		, m_locking( true)
	{
		setupUi( this);

		connect( m_shapeList, SIGNAL(itemSelectionChanged()), this, SLOT(OnSelectedCollisionShape()));

		connect( m_capsuleRadius, SIGNAL(valueChanged(double)), this, SLOT( UpdateUICapsuleParameterToShape()));
		connect( m_capsuleHeight, SIGNAL(valueChanged(double)), this, SLOT( UpdateUICapsuleParameterToShape()));
	}

	// ��ʾ�Ҽ��˵�
	void CollisionBuild::contextMenuEvent( QContextMenuEvent* event)
	{
		if( !m_mouseMenu)
		{
			m_mouseMenu = new_ QMenu;

			// ��Ӳ˵�
			QMenu* addMenu = new_ QMenu(tr("Add"));
			addMenu->addAction( m_actionCapsule3);
			m_mouseMenu->addMenu( addMenu);

			m_mouseMenu->addAction( m_actionDeleteCapsule);

			QMenu* fillMode = new_ QMenu("FillMode");
			fillMode->addAction( m_actionSolid);
			fillMode->addAction( m_actionWireFrame);
			m_mouseMenu->addMenu( fillMode);

			// ��Ϣ����
			connect( m_actionCapsule3, SIGNAL(triggered()), this, SLOT(AddCapsule()));
			connect( m_actionDeleteCapsule, SIGNAL(triggered()),  this, SLOT( DeleteSelectedCapsule()));
			connect( m_actionSolid,     SIGNAL(triggered()), this, SLOT(SwitchToNormalFillMode()));
			connect( m_actionWireFrame, SIGNAL(triggered()), this, SLOT(SwitchToWireFrameFillMode()));
		}

		m_mouseMenu->exec( event->globalPos());
	}

	// add collision shape capsule
	void CollisionBuild::AddCapsule()
	{
		MOLogic_CollisionBuild->AddShape( VST_Capsule);

		// ������״�б���ʾ
		UpdateTableDisplay();
	}

	// ɾ����ǰѡ��
	void CollisionBuild::DeleteSelectedCapsule()
	{
		MOLogic_CollisionBuild->DeleteSelected();

		UpdateTableDisplay();
	}

	// �����б���ʾ
	void CollisionBuild::UpdateTableDisplay()
	{
		m_shapeList->clear();
		const vector<VisualShape*>& shapes = MOLogic_CollisionBuild->GetShapes();
		for( size_t i=0; i<shapes.size(); i++)
		{
			QListWidgetItem* item = new_ QListWidgetItem("capsule");

			m_shapeList->addItem( item);
		}
	}

	// ѡ��collision shape
	void CollisionBuild::OnSelectedCollisionShape()
	{
		// 1.���õ�ǰѡ������
		MOLogic_CollisionBuild->SetSelected( static_cast<size_t>(m_shapeList->currentRow()));

		// 2.���½�����ʾ
		UpdateShapeParameterToUI();
	}

	// ���µ�ǰѡ����״������
	void CollisionBuild::UpdateShapeParameterToUI()
	{
		// ����
		m_locking = true;

		// 2.�������б༭����
		m_capsuleEditPanel->setVisible( false);

		VisualShape* vc = MOLogic_CollisionBuild->GetSelected();
		if( vc)
		{
			switch( vc->GetType())
			{
			case VST_Capsule:
				{
					VisualCapsule* capsule = dynamic_cast<VisualCapsule*>(vc);
					if( capsule)
					{
						m_capsuleRadius->setValue( capsule->GetRadius());
						m_capsuleHeight->setValue( capsule->GetHeight());
					}

					m_capsuleEditPanel->setVisible( true);
				}
				break;
			}
		}

		// ����
		m_locking = false;
	}

	// ���½������ݵ���״
	void CollisionBuild::UpdateUICapsuleParameterToShape()
	{
		VisualShape* vs = MOLogic_CollisionBuild->GetSelected();
		if( !m_locking && vs && vs->GetType()==VST_Capsule)
		{
			float radius = static_cast<float>(m_capsuleRadius->value());
			float height = static_cast<float>(m_capsuleHeight->value());

			VisualCapsule* vc = dynamic_cast<VisualCapsule*>(vs);
			if( vc)
				vc->SetShape( height, radius);
		}
	}

	// ������ײģ��
	void CollisionBuild::ExportCollisionShapes()
	{
		QString fileName = QFileDialog::getSaveFileName( this, tr("Export CollisionShapes"), "", tr("(*.cs)"));
		if( !fileName.isEmpty())
		{
			string tFileName = fileName.toStdString();

			ExportCollisionShapes( tFileName);
		}
	}

	// ����CollisionShapes
	void CollisionBuild::ExportCollisionShapes( const string& path)
	{
		if( MOLogic_ModelEdit->GetModelType()==MT_YND)
			MOLogic_CollisionBuild->YNDSavePhysicsShapes( path.c_str());
		else
			MOLogic_CollisionBuild->SavePhysicsShapes( path.c_str());
	}

	// ������ײģ��
	void CollisionBuild::ImportCollisionShapes()
	{
		QString fileName = QFileDialog::getOpenFileName( this, tr("Import CollisionShapes"), "", tr("(*.cs)"));
		if( !fileName.isEmpty())
		{
			string tFileName = fileName.toStdString();

			ImportCollisionShapes( tFileName);
		}
	}

	// ����CollisionShapes
	void CollisionBuild::ImportCollisionShapes( const string& path)
	{
		if( MOLogic_ModelEdit->GetModelType()==MT_YND)
			MOLogic_CollisionBuild->YNDLoadPhysicsShapes( path.c_str());
		else
			MOLogic_CollisionBuild->LoadPhysicsShapes( path.c_str());

		UpdateTableDisplay();
	}

	// �������ģʽ
	void CollisionBuild::SwitchToWireFrameFillMode()
	{
		MOLogic_CollisionBuild->SwitchToWireFrameFillMode();
	}

	// �������ģʽ
	void CollisionBuild::SwitchToNormalFillMode()
	{
		MOLogic_CollisionBuild->SwitchToNormalFillMode();
	}
}