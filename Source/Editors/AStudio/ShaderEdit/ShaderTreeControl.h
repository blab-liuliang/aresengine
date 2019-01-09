#pragma once

#include <vector>
#include <QtGui/QGroupBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QRadioButton>
#include <QtGui/QMouseEvent>
#include <QtGui/QMdiArea>
#include <QtGui/QLabel>
#include <QtGui/QMdiSubWindow>
#include <QtGui/QPushButton>
#include <Physics/Bezier3.h>
#include <boost/signals2/signal.hpp>
#include <Engine/RenderSystem/SuperMaterialExpression.h>

using namespace std;
using namespace Ares;
using namespace boost::signals2;

namespace Ares
{
	class UIShaderTreeDisplay;
}

namespace ST
{
	enum OperationState
	{
		OS_MoveWindow,		// �ƶ�����
		OS_DragConnect,		// ���ӱ��ʽ
		OS_None,
	};

	//------------------------------
	// ���ʽ������� 2013-3-18 ����
	//------------------------------
	class QBezierCurve;
	class QExpressionInputOutput : public QRadioButton
	{
		Q_OBJECT

	public:
		QExpressionInputOutput( bool input, QWidget* parent=NULL);
		~QExpressionInputOutput();

		// ��ȡͼ�����ĵ�
		QPoint IconCenter();

		// �Ƿ�Ϊ���ʽ������
		bool IsInput() { return m_input; }

		// ��ȡID
		const string& GetID() { return m_id; }

		// ����ID
		void SetID( const string& id) { m_id = id; }

		// λ���ƶ�
		signal<void(QExpressionInputOutput*)> Signal_OnMoved;

	private:
		string				m_id;
		bool				m_input;
	};

	//------------------------------
	// STControl 2013-3-17 ����
	//------------------------------
	class ShaderTreeControl : public QGroupBox
	{
		Q_OBJECT

	public:
		ShaderTreeControl( QMdiArea* parent=NULL);
		~ShaderTreeControl() {}

		// ��ȡMdiSubWindow
		QMdiSubWindow* GetMdiSubWindow() { return m_mdiSubWindow; }

		// �󶨱��ʽ
		void BindUICoordinate( UICoordinate* coordinate) { m_coordinate = coordinate; }

		// ��ȡ�������
		vector<QExpressionInputOutput*>& GetInputOutputs() { return m_ioputs; }

		// ��ȡID
		const string& GetID() { return m_id; }

	protected:
		// ����¼�
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);

	private slots:
		// ��ʼ�������
		void StartConnect();

		// �������յ�
		void ReConnectEnd();

	protected:
		string				m_id;				// ��ʶ
		OperationState		m_state;			// ״̬
		QMdiSubWindow*		m_mdiSubWindow;
		QLabel*				m_title;			// ����
		QPoint				m_windowPos;
		QPoint				m_mousePos;
		QPoint				m_dPos;

		UICoordinate*		m_coordinate;
		vector<QExpressionInputOutput*> m_ioputs;
	};

	//------------------------------
	// MaterialSlot 2013-3-12 ����
	//------------------------------
	class MaterialSlot : public ShaderTreeControl
	{
	public:
		MaterialSlot( QMdiArea* parent=NULL);
		~MaterialSlot();

		// ����ID
		void SetID( const string& diffuseID, const string& normalID);

	protected:
		QVBoxLayout*				m_verticalLayout;
		QExpressionInputOutput*		m_diffuse;
		QExpressionInputOutput*		m_normal;
	};

	//--------------------------------
	// ConstantColor  2013-3-12 ����
	//--------------------------------
	class ConstantColor : public ShaderTreeControl
	{
		Q_OBJECT

	public:
		ConstantColor( QMdiArea* parent=NULL);
		~ConstantColor();

		// ����ID
		void SetID( const string& oID);

		// �󶨱��ʽ
		void BindExpression( MaterialExpressionConstantColor* expression);

	private slots:
		// ѡ��·��
		void OnSelectColor();

	protected:
		QVBoxLayout*				m_layout;
		QHBoxLayout*				m_layoutInternal;
		QExpressionInputOutput*		m_output;
		QPushButton*				m_colorButton;

		QColor						m_color;
		
		MaterialExpressionConstantColor* m_expression;
	};

	//--------------------------------
	// QBezierCurve 2013-3-17 ����
	//--------------------------------
	class QBezierCurve
	{
	public:
		QBezierCurve();
		~QBezierCurve();
		
		// ���ÿ�ʼ��
		void SetStartPos( const QPoint& start);

		// ���ý�����
		void SetEndPos( const QPoint& end);

		// ��
		void BindStart( QExpressionInputOutput* start);

		// ��
		void BindEnd( QExpressionInputOutput* end);

		// ��Ⱦ
		void paint( QWidget* parent);

		// ����������ƶ�
		void OnMove();

	private:
		// ��������
		void UpdateDisplay();

	public:
		QPoint					m_startPos;
		QPoint					m_endPos;
		QExpressionInputOutput*	m_start;
		QExpressionInputOutput*	m_end;
		vector<QPointF>			m_path;			// ·��
	};
}