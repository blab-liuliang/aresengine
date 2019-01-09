#include "MOAnimationEdit.h"
#include "MOLogic.h"
#include <QtGui/QtGui>
#include <Engine/RenderSystem/AresAnimationController.h>
#include <tolua++/tolua++.h>

using namespace Ares;

namespace QT_UI
{
	// ���캯��
	CAnimationEdit::CAnimationEdit( QWidget* parent/* = 0*/)
		: QDockWidget( parent)
	{
		setupUi( this);

		connect( m_animationList, SIGNAL(activated( const QString &)), this, SLOT( OnClicked()));
		connect( m_animationBox,  SIGNAL(clicked()), this, SLOT( InitAniList()));
		connect( m_loop,          SIGNAL(clicked()), this, SLOT( OnClicked()));

		// ʱ���¼�
		//m_pTimer = new QTimer( this);
		//connect( m_pTimer, SIGNAL( timeout()), this, SLOT( InitAniList()));
		connect( m_test,   SIGNAL( clicked()), this, SLOT( SwitchWeapon()));

		// ����ѡ���¼�
		connect( m_boneHirearchy, SIGNAL( itemSelectionChanged()), this, SLOT( ShowBoneCustomInfo()));

		connect( m_scaleX, SIGNAL( valueChanged(double)), this, SLOT(UpdateBoneCustomInfo()));
		connect( m_scaleY, SIGNAL( valueChanged(double)), this, SLOT(UpdateBoneCustomInfo()));
		connect( m_scaleZ, SIGNAL( valueChanged(double)), this, SLOT(UpdateBoneCustomInfo()));
		connect( m_transX, SIGNAL( valueChanged(double)), this, SLOT(UpdateBoneCustomInfo()));
		connect( m_transY, SIGNAL( valueChanged(double)), this, SLOT(UpdateBoneCustomInfo()));
		connect( m_transZ, SIGNAL( valueChanged(double)), this, SLOT(UpdateBoneCustomInfo()));

		m_iconMap["bone"] = QIcon(":/icon/Icon/bone.png");
	}

	// ��������
	CAnimationEdit::~CAnimationEdit()
	{

	}

	// ����(ģ��ѡ�����)
	void CAnimationEdit::Reset()
	{
		m_animationList->clear();

		//m_pTimer->start( 800);
	}

	// ��ʼ�������б�
	void CAnimationEdit::InitAniList()
	{
		if( m_animationList->count() != 0)
			return;

		ModelPtr tEntity = MOLogic_ModelEdit->GetCurrEntity();
		if( !tEntity)
			return;

		// ����������
		AnimationController* pController = tEntity->GetAnimationController();
		s_ptr<CAresAnimation> pAnimation = pController->GetAnimation();
		if( !pAnimation)
			return;

		int tNum = pAnimation->GetNumAnimationSet();
		for ( int i=0; i<tNum; i++)
		{
			QString name = QString::fromUtf8("����");
			
			m_animationList->addItem( tr(pAnimation->GetAnimationSetName( i))); 
		}

		// ��ʾ�����ṹ
		//ShowBoneHierarchy( pAnimation);

		// ���³���������ʾ
		//ShowBoneGeneralInfo( pAnimation);


		//m_pTimer->stop();
	}

	//// ��ʾ���������ͽṹ
	//void CAnimationEdit::ShowBoneHierarchy( IAresAnimation* animation)
	//{
	//	m_boneHirearchy->clear();

	//	if( !animation)
	//		return;

	//	if( !animation->GetNumBones())
	//		return;

	//	int sib = animation->GetRootBone();
	//	while ( sib != -1)
	//	{
	//		const char* name = animation->GetBoneName( sib);
	//		QTreeWidgetItem* item = new QTreeWidgetItem( m_boneHirearchy,  QStringList(name));
	//		item->setIcon( 0, m_iconMap["bone"]);

	//		AddBone( animation, item, sib);

	//		sib = animation->GetBoneSibingIdx( sib);
	//	}
	//}

	//// ��ӹ���
	//void CAnimationEdit::AddBone( IAresAnimation* animation,QTreeWidgetItem* parentItem,  size_t parentIdx)
	//{
	//	int sib	  = animation->GetBoneFirstChildIdx( parentIdx);
	//	while ( sib != -1)
	//	{
	//		const char* name = animation->GetBoneName( sib);
	//		QTreeWidgetItem* item = new QTreeWidgetItem( parentItem, QStringList(name));
	//		item->setIcon( 0, m_iconMap["bone"]);

	//		// �ݹ�
	//		AddBone( animation, item, sib);

	//		sib = animation->GetBoneSibingIdx( sib);
	//	}
	//}

	// ����
	void CAnimationEdit::OnClicked()
	{
		ModelPtr pEntity = MOLogic_ModelEdit->GetCurrEntity();
		if( pEntity)
		{
			int index = m_animationList->currentIndex();

			// ����������
			AnimationController* pController = pEntity->GetAnimationController();
			//pController->GetAnimationDesc( 0)->m_loop  = true;
			//pController->GetAnimationDesc( 1)->m_loop  = true;
			//pController->GetAnimationDesc( 2)->m_loop  = true;
			//pController->GetAnimationDesc( 3)->m_layer = 1;
			//pController->GetAnimationDesc( 3)->m_loop  = true;
			//pController->GetAnimationDesc( 4)->m_layer = 2;
			//pController->GetAnimationDesc( 4)->m_weight = 0.5f;
			//pController->GetAnimationDesc( 5)->m_layer = 1;

			//pController->GetAnimationDesc(index)->m_loop = m_loop->isChecked();

			//int boneIdx;

			//pController->GetAnimation()->GetBoneIdxByName( "Bip01 Head", boneIdx);
			//pController->GetAnimationDesc(4)->AddMixingTransform( boneIdx);

 			//if( pController->GetAnimationDesc( index)->m_layer != 1)
				pController->CrossFade( index, 0.f);
			//else
				//pController->CrossFadeQueued( index);

			//pController->PlayAnimationByIndex( index, m_loop->isChecked());

			// ����һ��ָ��lua��������ָ��
			//lua_State* ls = lua_open();

			//// ����lua��
			//luaopen_base( ls);
			////luaL_openlibs( ls);
			//tolua_AresScriptSystem_open(ls);

			//// ���ؽű�
			//int re = luaL_dofile( ls, "data\\lua\\blending.lua");

			//// ���ú���
			//lua_getglobal( ls, "playAnimation");
			//tolua_pushusertype( ls, pController, "Ares::IAnimationController");
			//tolua_pushusertype( ls, &index, "size_t");
			//tolua_pushboolean( ls, m_loop->isChecked());

			//const char* errMsg = NULL;
			//int result = lua_pcall( ls, 3, 0, 0);
			//if( result)
			//{
			//	errMsg = lua_tostring( ls, -1);
			//	int breakPoint = 10;
			//}

			//lua_close(ls);
		}
	}

	// ��������
	void CAnimationEdit::SwitchWeapon()
	{
		QString qFileName = QFileDialog::getOpenFileName( this, tr("model file"), "", tr("*.m1"));

		QDir dir( QDir::currentPath());
		qFileName = dir.relativeFilePath( qFileName);

		// ���ı���
		m_weapon->setText( qFileName.toStdString().c_str());

		//MOLogic_Main->SwitchWeapon( qFileName.toStdString().c_str());
	}

	// ��ʾ������Ϣ
	/*void CAnimationEdit::ShowBoneGeneralInfo( IAresAnimation* animation)
	{
		// ����
		m_generalProperty->clear();
		m_generalProperty->setRowCount( 2);
		m_generalProperty->setColumnCount( 2);

		// ����
		QStringList header; 
		header<<"Property"<<"Value"; 
		m_generalProperty->setHorizontalHeaderLabels(header); 

		// ��ʾ��������
		int tNum = animation->GetNumBones();
		char boneNum[1024];
		itoa( tNum, boneNum, 10);
		m_generalProperty->setItem(0,0,new QTableWidgetItem(tr("BoneNum:")));  m_generalProperty->setItem( 0, 1, new QTableWidgetItem( tr( boneNum))); 
	}*/

	// ��ʾ�Զ��������Ϣ
	void CAnimationEdit::ShowBoneCustomInfo()
	{/*
		QTreeWidgetItem* tItem = m_boneHirearchy->currentItem();
		SPtr<IM1Entity> pEntity = g_pLogic->GetCurrEntity();
		if( pEntity)
		{
			// ����������
			IAnimationController* pController = pEntity->GetAnimationController();
			IAresAnimation*		  animation	  = pController->GetAnimation();

			int boneIdx;
			if( animation->GetBoneIdxByName( tItem->text(0).toStdString().c_str(), boneIdx))
			{
				// ��ȡ�Զ������
				Matrix44 tCM;
				pController->GetCustomBone( tCM, boneIdx);

				// ��ʾ
				string text;
				char   str[1024];
				for ( int i=0; i<4; i++)
				{
					sprintf( str, "%8.3f, %8.3f, %8.3f, %8.3f\n", tCM.m[i][0], tCM.m[i][1], tCM.m[i][2], tCM.m[i][3]);

					text += str;
				}

				m_customBone->setText( text.c_str());

				// �ֽ���ת����ƽ��
				Vector3    tScale;
				D3DXQUATERNION tRotate;
				Vector3	   tTrans;
				D3DXMatrixDecompose( &tScale, &tRotate, &tTrans, &tCM);

				// ��ʾ����
				m_scaleX->setValue( tScale.x); 
				m_scaleY->setValue( tScale.y);
				m_scaleZ->setValue( tScale.z);

				m_transX->setValue( tTrans.x);
				m_transY->setValue( tTrans.y);
				m_transZ->setValue( tTrans.z);
			
				// ��ʾ�����ĳ�ʼ����ϵ
				Matrix44 tCoord;
				animation->GetInitBoneTM( tCoord, boneIdx);

				g_pLogic->ShowBoneCoord( tCoord);
			}
		}*/
	}

	// �����Զ��������Ϣ
	void CAnimationEdit::UpdateBoneCustomInfo()
	{/*
		QTreeWidgetItem* tItem = m_boneHirearchy->currentItem();
		if( !tItem)
			return;

		SPtr<IM1Entity> pEntity = g_pLogic->GetCurrEntity();
		if( pEntity)
		{
			// ����������
			IAnimationController* pController = pEntity->GetAnimationController();

			int boneIdx;
			if( pController->GetAnimation()->GetBoneIdxByName( tItem->text(0).toStdString().c_str(), boneIdx))
			{
				// ��ȡ�Զ������
				Matrix44 tCM;
				pController->GetCustomBone( tCM, boneIdx);

				// �ֽ���ת����ƽ��
				Vector3    tScale;
				D3DXQUATERNION tRotate;
				Vector3	   tTrans;
				D3DXMatrixDecompose( &tScale, &tRotate, &tTrans, &tCM);

				// ��ʾ����
				tScale.x = m_scaleX->value();
				tScale.y = m_scaleY->value();
				tScale.z = m_scaleZ->value();

				tTrans.x = m_transX->value();
				tTrans.y = m_transY->value();
				tTrans.z = m_transZ->value();

				D3DXMatrixTransformation( &tCM, NULL, NULL, &tScale, NULL, &tRotate, &tTrans);
				pController->SetCustomBone( boneIdx, tCM);

				// ��ʾ
				string text;
				char   str[1024];
				for ( int i=0; i<4; i++)
				{
					sprintf( str, "%8.3f, %8.3f, %8.3f, %8.3f\n", tCM.m[i][0], tCM.m[i][1], tCM.m[i][2], tCM.m[i][3]);

					text += str;
				}

				m_customBone->setText( text.c_str());
			}
		}*/
	}
}