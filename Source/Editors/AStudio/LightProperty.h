#pragma once

#include <QtGui/QWidget>
#include "ui_LightProperty.h"
#include <Engine/RenderSystem/AresLight.h>

using namespace Ares;

namespace QT_UI
{
	//-------------------------------------
	// ��Դ���Ա༭ 2013-8-30
	//-------------------------------------
	class MQLightProperty : public QWidget, public Ui_LightProperty
	{
		Q_OBJECT

	public:
		MQLightProperty( QWidget* parent=0);

		// ���ù�����Դ
		void SetCurrLight( Light* light);

		// ���½�����ʾ
		void UpdateUIDisplay();

	private slots:
		// ѡ���Դ��ɫ
		void SelectColor();

		// ���¹�Դ����
		void UpdateLightData();

	private:
		Light*		m_light;			// ��Դ
		float3		m_tColor;			// ��ʱ��ɫֵ
	};
}