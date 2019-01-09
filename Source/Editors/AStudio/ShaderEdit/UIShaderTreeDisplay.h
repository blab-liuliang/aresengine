#ifndef DX9_MDI_AREA_H
#define DX9_MDI_AREA_H

#include "ShaderTreeControl.h"
#include "ShaderTreeConnectMgr.h"
#include <Engine/RenderSystem/SuperMaterialShaderTree.h>
#include <QtGui/QMdiArea>
#include "ui_ShaderTreeDisplay.h"

class Application;
namespace Ares
{
	//-----------------------------------
	// Dx9MdiArea dx��ʾ����
	//-----------------------------------
	class CTabWidget;
	class UIShaderTreeDisplay : public QMdiArea, public Ui_ShaderTreeDisplay
	{
		Q_OBJECT

	public:
		UIShaderTreeDisplay( QWidget* parent = NULL);
		~UIShaderTreeDisplay();

		//// ��ʼ��Ⱦ
		//void BeginRender();

		// ����shadertree��ʾ
		void UpdateShaderTreeDisplay();

		// ��ȡInputOutput
		QExpressionInputOutput* GetInputOutput( const string& id);

		// ��ȡ���ʽ�ؼ�
		ShaderTreeControl* GetExpressionControl( const string& id);

		// ��ȡ���ӹ�����
		ShaderTreeConnectMgr& GetConnectMgr() { return m_shaderTreeConnectMgr; }

		// ����,������н���
		void Reset();

	private:
		// �Ƴ����ʽ
		void RemoveUselessQExpression( MaterialShaderTree* shaderTree);

	protected:
		// �����¼�
		void paintEvent(QPaintEvent *);

		// ��ק�����¼�
		void dragEnterEvent( QDragEnterEvent* event);
		
		// ��ק�ͷ��¼�
		void dropEvent( QDropEvent * event);

	private slots:

		// ��Ⱦ
		void  Render();

		// �����豸
		void  ResetDevice();

	private:
		QSize					m_dx9Size;			// �������С
		//QTimer*					m_pTimer;			// ��ʱ��

	public:
		QWidget*				m_pDx9Widget;		// dx9��ʾ
		CTabWidget*				m_pTabWidget;		// shader��ʾ

		// 1.Material slot
		ST::MaterialSlot*					m_materialSlot;
		vector<ST::ShaderTreeControl*>		m_shaderTreeControls;		// ���ʽ����
		ShaderTreeConnectMgr				m_shaderTreeConnectMgr;		// ���ӹ�����
	};
}

#endif