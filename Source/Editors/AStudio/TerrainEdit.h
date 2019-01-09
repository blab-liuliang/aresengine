#ifndef TERRAIN_EDIT_H
#define TERRAIN_EDIT_H

#include <QtGui/QDockWidget>
#include <Engine/RenderSystem/AresTerrain.h>
#include "ui_TerrainEdit.h"
#include "QRadioImage.h"

using namespace Ares;

namespace QT_UI
{
	#define  MAX_TEXTURE   10

	//----------------------------------------
	// ���α༭Frame    2011-01-11
	//----------------------------------------
	class TerrainEdit : public QWidget, public Ui_TerrainEdit
	{
		Q_OBJECT

	public:
		// ���캯��
		TerrainEdit( QWidget* parent = 0);

		// ���õ�ǰ�༭����
		void SetCurrTerrain( Terrain* pTerrain);

		// ���µ���������ʾ
		void UpdateTerrainTexture();

	private slots:
		// �༭���γߴ����
		void  UpdateTerrainEditSize( int size);

		// �༭��������
		void UpdateTerrainHandleType();

		// �༭��������
		void UpdateTexture();

		// ���ĵ������� 
		void UpdateTexture( QString str);

		// ������������϶�
		void ImportTexBlend( QString str);

		// ����uvScale
		void UpdateUVScale(double uvScale);

		// ѡ����߶�ͼ
		void SelectImportHeightMap();

		// ����߶�ͼ
		void ImportTerrainHeight();

	public:
		QRadioImage*    m_pShowImage;
		QRadioImage*    m_imageRadios[MAX_TEXTURE];
		Terrain*		m_terrain;
	};
}

#endif