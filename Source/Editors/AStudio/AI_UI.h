#pragma once

#include <QtGui/QMainWindow>
#include <Physics/AresStaticMeshTiledBuilder.h>
#include "QPropertyModel.h"
#include "ui_AI.h"

using namespace Ares;

namespace QT_UI
{
	//----------------------------------------
	// ģ�ͱ༭�� ������ 2010-12-30
	//----------------------------------------
	class CAIUI : public QMainWindow, public Ui_AI
	{
		Q_OBJECT

	public:
		// ���캯��
		CAIUI( QWidget* parent = 0);

	public slots:
		// ��ʾPolyRef
		void SetPolyRef( unsigned int startPoly, unsigned int endPoly);

		// ���¿�ʼλ����ʾ
		void SetStartPos( Vector3 startPos);

		// ���½���λ����ʾ
		void SetEndPos( Vector3 endPos);

		// ���浼������
		void SaveNavMesh();

	private slots:
		// Build NavMesh
		void BuildNavMesh();

		// �������򹹽���������
		void BuildNavMeshByRegion();

		// Ѱ·
		void PathFind();

		// Show
		void Show();

		// ˢ��BuildParam
		void RefreshBuildParam();

	private:
		CStaticMeshTiledBuilder::SBuildParam m_buildParam;
		QPropertyModel*						 m_pModel;			// ʹ�õ�Model
	};
}