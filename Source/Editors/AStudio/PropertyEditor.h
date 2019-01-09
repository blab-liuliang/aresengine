#ifndef PROPERTY_EDITOR_H
#define PROPERTY_EDITOR_H

#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include "ui_PropertyEditor.h"
#include <Engine/RenderSystem/AresTerrain.h>
#include <QProperty.hpp>
#include <map>

using namespace std;
using namespace Ares;

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class CPropertyEditor : public QDockWidget, public Ui_PropertyEditor
	{
		Q_OBJECT

		typedef map<string, QWidget*> FrameList;
	public:
		// ���캯��
		CPropertyEditor( QWidget* parent = 0);

		// ��ʾ��ǰѡ���������
		void ShowProperty( Entity* entity);

	public:
		// �������ֻ�ȡFrame
		QWidget* GetFrame( const char* frame);

		// ��ʾĳFrame
		void ShowFrame( const char* frame);

		// ��������Frame
		void HideAllFrame();

	private:
		string				m_currName;
		QWidget*			m_currFrame;		// ��ǰ
		FrameList			m_frameList;		// �������Կ������
	};
}

#endif