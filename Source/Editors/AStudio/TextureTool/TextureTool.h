#pragma once

#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsPixmapItem>
#include <Core/Graphics/AresTexture.h>
#include "ui_TextureTool.h"
#include "TextureSetBuild.h"

using namespace Ares;

namespace QT_UI
{
	//------------------------------------
	// ����鿴�༭�� 2012-7-23 ����
	//------------------------------------
	class TextureTool : public QMainWindow, public Ui_TextureTool
	{
		Q_OBJECT

	public:
		// ���캯��
		TextureTool( QWidget* parent=0);

		// ��������
		~TextureTool();

		// ��ʼ��App
		void InitApp();

		// ��ʾ����
		void ShowTexture(  TexturePtr tex);

	private slots:
		// ������
		void Open();

		// �������������
		void AddSubTex();

	private:
		QGraphicsScene			m_graphicsScene;		// ��Ⱦ����
		QGraphicsPixmapItem		m_graphicsItem;			// ��ʾ��
		TextureSetBuild*		m_textureSetBuild;		// ������
	};
}