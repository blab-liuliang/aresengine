#pragma once

#include <QtGui/QtGui>
#include <QtGui/QMainWindow>
#include "ui_LightMap.h"
#include "GpuLightMapBake.h"

using namespace Ares;

namespace QT_UI
{
	//---------------------------------------
	// ����ͼ�決������� 20102-6-20 ����
	//---------------------------------------
	class Lightmap : public QMainWindow, public Ui_Lightmap
	{
		Q_OBJECT

	public:
		// ���캯��
		Lightmap( QWidget* parent = 0);

		// ��������
		~Lightmap();

	public slots:
		// �決������
		void Bake();

		// �決
		void BakeSelected();

		// ��ȫ����ʾ

		// ������ʾ
	};
}