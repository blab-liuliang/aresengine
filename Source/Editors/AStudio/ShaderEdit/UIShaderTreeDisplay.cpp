#include <QtGui/QtGui>
#include "SHMainWindow.h"
#include "TabWidget.h"
#include "SHLogic.h"
#include <Engine/RenderSystem/SuperMaterialShaderTree.h>
#include "UIShaderTreeDisplay.h"

namespace Ares
{
	// ���캯��
	UIShaderTreeDisplay::UIShaderTreeDisplay( QWidget* parent/* = NULL*/)
		: QMdiArea( parent)
		//, m_pTimer( NULL)
		, m_materialSlot( NULL)
	{
		m_pDx9Widget = new QWidget( this);
		//addSubWindow( m_pDx9Widget);

		// ��ʾ����
		m_pTabWidget = new CTabWidget( this);

		//m_pTabWidget->showMaximized();

		this->setBackground( QBrush( QColor( 50, 50, 50)));

		viewport()->setAcceptDrops( true);
		viewport()->setMouseTracking( true);

		// Ĭ�ϲ��ʲ�
		m_materialSlot = new_ ST::MaterialSlot( this);
		m_materialSlot->GetMdiSubWindow()->move( QPoint( 100, 250));
	}

	// ��������
	UIShaderTreeDisplay::~UIShaderTreeDisplay()
	{
		//SAFE_DELETE( m_pTimer);		
	}

	//// ��ʼ��Ⱦ
	//void UIShaderTreeDisplay::BeginRender()
	//{
	//	m_dx9Size = this->size();
	//	//m_pTabWidget->show();
	//	m_pDx9Widget->setWindowTitle( tr("Dx9 Show"));

	//	// ��չ����
	//	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	//	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	//	// ʱ���¼�
	//	m_pTimer = new QTimer( this);
	//	connect( m_pTimer, SIGNAL( timeout()), this, SLOT( Render()));
	//	m_pTimer->start( 15);
	//}

	// ��Ⱦ����
	void  UIShaderTreeDisplay::Render()
	{
	}

	// ����shadertree��ʾ
	void UIShaderTreeDisplay::UpdateShaderTreeDisplay()
	{
		MaterialShaderTree* shaderTree = SHLogic_ShaderTreeEdit->GetShaderTree();
		if( shaderTree)
		{
			// 1.Material slot
			MaterialExpressionSlot& materialSlot   = shaderTree->GetExpressionSlot();
			Vector2 slotPos = materialSlot.GetUICoordinate().m_pos;
			m_materialSlot->GetMdiSubWindow()->move( slotPos.x, slotPos.y);
			m_materialSlot->SetID( materialSlot.m_diffuseColor.m_id, materialSlot.m_normal.m_id);
			m_materialSlot->BindUICoordinate( &materialSlot.GetUICoordinate());
	
			// 2.Expression
			RemoveUselessQExpression( shaderTree);

			const vector<MaterialExpression*>& expressions = shaderTree->GetMaterialExpression();
			for( size_t i=0; i<expressions.size(); i++)
			{
				A_ASSERT( expressions[i]);
			
				if( !GetExpressionControl( expressions[i]->GetID()))
				{
					switch( expressions[i]->GetType())
					{
					case ET_ConstantColor:
						{
							ST::ConstantColor* constantColor = new_ ST::ConstantColor( this);
							Vector2 slotPos = expressions[i]->GetUICoordinate().m_pos;
							constantColor->GetMdiSubWindow()->move( slotPos.x, slotPos.y);
							constantColor->BindUICoordinate( &expressions[i]->GetUICoordinate());
							constantColor->SetID( expressions[i]->GetID());
							constantColor->BindExpression( dynamic_cast<MaterialExpressionConstantColor*>(expressions[i]));
							m_shaderTreeControls.push_back( constantColor);
						}
						break;
					}
				}
			}

			// 3.Connection
			m_shaderTreeConnectMgr.RemoveUselessConnection( shaderTree);
			const vector<MaterialExpressionConnection*>& connections = shaderTree->GetMaterialExpressionConnection();
			for( size_t i=0; i<connections.size(); i++)
			{
				A_ASSERT( connections[i]);

				if( !m_shaderTreeConnectMgr.GetConnection( connections[i]->m_expression, connections[i]->m_input))
				{
					ST::QBezierCurve* curve = new_ ST::QBezierCurve();

					QExpressionInputOutput* start = GetInputOutput( connections[i]->m_expression);
					QExpressionInputOutput* end	  = GetInputOutput( connections[i]->m_input);

					A_ASSERT( start);
					A_ASSERT( end);

					curve->BindStart( start);
					curve->BindEnd( end);

					m_shaderTreeConnectMgr.AddConnection( curve);
				}
			}
		}

		viewport()->repaint();
	}

	// �Ƴ����ʽ
	void UIShaderTreeDisplay::RemoveUselessQExpression( MaterialShaderTree* shaderTree)
	{
		for( vector<ST::ShaderTreeControl*>::iterator it=m_shaderTreeControls.begin(); it!=m_shaderTreeControls.end(); )
		{
			if( !shaderTree->GetMaterialExpression( (*it)->GetID()))
			{
				this->removeSubWindow( (*it)->GetMdiSubWindow());
				SAFE_DELETE( (*it));
				it = m_shaderTreeControls.erase( it);
			}
			else
			{
				it++;
			}
		}
	}

	// ��ȡInputOutput
	QExpressionInputOutput* UIShaderTreeDisplay::GetInputOutput( const string& id)
	{
		// ���ʲ�
		foreach_( QExpressionInputOutput* inputoutput, m_materialSlot->GetInputOutputs())
		{
			if( inputoutput->GetID() == id)
				return inputoutput;
		}

		// ���ʽ
		foreach_( ST::ShaderTreeControl* control, m_shaderTreeControls)
		{
			foreach_( QExpressionInputOutput* inputoutput, control->GetInputOutputs())
			{
				if( inputoutput->GetID() == id)
					return inputoutput;
			}
		}

		return NULL;
	}

	// ��ȡ���ʽ�ؼ�
	ShaderTreeControl* UIShaderTreeDisplay::GetExpressionControl( const string& id)
	{
		foreach_( ST::ShaderTreeControl* control, m_shaderTreeControls)
		{
			if( control->GetID() == id)
				return control;
		}

		return NULL;
	}

	// �����豸
	void  UIShaderTreeDisplay::ResetDevice()
	{

	}

	// ��Ⱦ����
	void UIShaderTreeDisplay::paintEvent(QPaintEvent* event)
	{
		QMdiArea::paintEvent( event);

		// ��������
		foreach_( ST::QBezierCurve* curve, m_shaderTreeConnectMgr.m_curves)
			curve->paint( viewport());

		if( m_shaderTreeConnectMgr.m_curveEdit)
			m_shaderTreeConnectMgr.m_curveEdit->paint( viewport());
	}

	// ��ק�����¼�
	void UIShaderTreeDisplay::dragEnterEvent( QDragEnterEvent* event)
	{
		if( event->mimeData()->hasFormat( "text/plain"))
			event->acceptProposedAction();
	}

	// ��ק�ͷ��¼�
	void UIShaderTreeDisplay::dropEvent( QDropEvent * event)
	{
		if( event->mimeData()->hasFormat("text/plain"))
		{
			Vector2 pos = Vector2( static_cast<float>( event->pos().x()), static_cast<float>( event->pos().y()));

			const QMimeData* mime = event->mimeData();
			QString text = mime->text();
			if( text == "ConstantColor")
			{
				MaterialShaderTree* shaderTree = SHLogic_ShaderTreeEdit->GetShaderTree();
				if( shaderTree)
				{
					pos = pos - Vector2( 64, 8);
					SHLogic_ShaderTreeEdit->AddExpression( ET_ConstantColor, pos);
				}
			}

			if( event->source()==this)
			{
				event->setDropAction( Qt::MoveAction);
				event->accept();
			}
			else
			{
				event->acceptProposedAction();
			}
		}
		else
		{
			event->ignore();
		}

		UpdateShaderTreeDisplay();
	}

	// ����,������н���
	void UIShaderTreeDisplay::Reset()
	{
		while( !m_shaderTreeControls.empty())
		{
			ST::ShaderTreeControl* control = m_shaderTreeControls.back();
			removeSubWindow( control->GetMdiSubWindow());
			SAFE_DELETE( control);

			m_shaderTreeControls.pop_back();
		}

		m_shaderTreeConnectMgr.Reset();
	}
}