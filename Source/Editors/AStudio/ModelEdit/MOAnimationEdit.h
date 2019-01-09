#pragma once

#include <string>
#include <QtGui/QDockWidget>
#include <QTimer>
#include "ui_MOAnimationEdit.h"

using namespace std;

namespace QT_UI
{
	//------------------------------------------
	// CAnimationEdit �������� 2011-07-12 ����
	//------------------------------------------
	class IAresAnimation;
	class CAnimationEdit  : public QDockWidget, public Ui_AnimationEdit
	{
		Q_OBJECT

		typedef map<string, QIcon>  IconMap;
	public:
		// ���캯��
		CAnimationEdit( QWidget* parent = 0);

		// ��������
		~CAnimationEdit();

	public slots:
		// ����(ģ��ѡ�����)
		void Reset();

	private slots:
		// ��ʼ�������б�
		void InitAniList();

		// ����
		void OnClicked();

		// ��������
		void SwitchWeapon();

		// ��ʾ�Զ��������Ϣ
		void ShowBoneCustomInfo();

	private slots:
		// �����Զ��������Ϣ
		void UpdateBoneCustomInfo();

	private:
		//// ��ʾ���������ͽṹ
		//void ShowBoneHierarchy( IAresAnimation* animation);

		//// ��ʾ������Ϣ
		//void ShowBoneGeneralInfo( IAresAnimation* animation);

		//// ��ӹ���
		//void AddBone( IAresAnimation* animation, QTreeWidgetItem* parentItem, size_t index);

	private:
		//QTimer*             m_pTimer;		// ��ʱ��
		IconMap				m_iconMap;		// ͼ��
	};
}