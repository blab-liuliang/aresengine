#pragma once

#include <Engine/FxSystem/AresFxObject.h>
#include <Engine/FxSystem/AresFx3DPatch.h>
#include <QtGui/QDockWidget>
#include "ui_FxPropertyEdit.h"
#include "QProperty.hpp"

using namespace Ares;

namespace QT_UI
{
	//----------------------------------------
	// ����鿴�� ������ 2012-8-28
	//----------------------------------------
	class FxPropertyEdit : public QDockWidget, public Ui_FxPropertyEdit
	{
		Q_OBJECT

	public:
		FxPropertyEdit( QWidget* parent = 0);

		// ѡ��FxObject
		void OnSelectFxObject( FxObject* fxObject);

	public slots:
		// ����3D��Ƭ���Ե�����
		void RefreshProperty3DPatchToUI();

		// ���½��������3D��Ƭ
		void RefreshPropertyUITo3DPatch();

		// ��������ϵͳ���Ե�����
		void RefreshPropertyParticleSystemToUI();

		// �������Խ��浽����ϵͳ
		void RefreshPropertyUIToParticleSystem();

	private:
		FxObject*		m_fxObject;					// Ч������
		QProperty*		m_fx3dpatchProperty;		// 3D��Ƭ����
		QProperty*		m_particleSystemProperty;	// ����ϵͳ����
	};
}
