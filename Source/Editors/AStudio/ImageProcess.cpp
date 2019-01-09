#include <QtGui/QtGui>
#include "ImageProcess.h"
#include "SCLogic.h"

using namespace Ares;

namespace QT_UI
{
	// ���캯��
	CImageProcess::CImageProcess( QWidget* parent/* = 0*/)
		: QDockWidget( parent)
	{
		// ����Ĭ�ϱ༭��ʽ
		setupUi( this);

		//g_pLogic->m_pImageProcessMgr->AddImageProgress( IImageProcessManager::EM_NIGHT_VIGION);

		connect( m_pFilter, SIGNAL( lostFocus()), this, SLOT( FilterLostFocus()));

		// ��ӿɴ����ͼ����ʽ
		m_pImageProcessList->setEditTriggers( QAbstractItemView::SelectedClicked);
		QListWidgetItem* pItem = NULL;

		// ҹ��
		pItem = new QListWidgetItem( "Night Vision", m_pImageProcessList);
		pItem->setCheckState( Qt::Unchecked);

		// ҹ��
		pItem = new QListWidgetItem( "Radial Blur", m_pImageProcessList);
		pItem->setCheckState( Qt::Unchecked);

		// Bloom
		pItem = new QListWidgetItem( "Bloom", m_pImageProcessList);
		pItem->setCheckState( Qt::Unchecked);

		// Under Water
		pItem = new QListWidgetItem( "Under Water", m_pImageProcessList);
		pItem->setCheckState( Qt::Unchecked);

		// �ȳ���
		//pItem = new QListWidgetItem( "Heat Vision", m_pImageProcessList);
		//pItem->setCheckState( Qt::Unchecked);

		// Bloom
		pItem = new QListWidgetItem( "Old TV", m_pImageProcessList);
		pItem->setCheckState( Qt::Unchecked);

		// �Ҷ�
		pItem = new QListWidgetItem( "Gray Scale", m_pImageProcessList);
		pItem->setCheckState( Qt::Unchecked);

		// �����
		pItem = new QListWidgetItem( "Volume Fog", m_pImageProcessList);
		pItem->setCheckState( Qt::Unchecked);

		connect( m_pImageProcessList, SIGNAL(itemClicked( QListWidgetItem*)), this, SLOT( OnClicked( QListWidgetItem*)));
	}

	// ����Filter���� 
	void CImageProcess::FilterLostFocus()
	{
		m_pFilter->setText( "Filter");
	}

	//// ת��
	//static Ares::IImageProcessManager::ImageProcessType Transform( QString&  text)
	//{
	//	if( text == "Night Vision")
	//		return IImageProcessManager::EM_NIGHT_VIGION;
	//	else if( text == "Radial Blur")
	//		return IImageProcessManager::EM_RADIAL_BLUR;
	//	else if( text == "Volume Fog")
	//		return IImageProcessManager::EM_FOG;
	//	else if( text == "Bloom")
	//		return IImageProcessManager::EM_BLOOM;
	//	else if ( text == "Under Water")
	//		return IImageProcessManager::EM_UNDER_WATER;
	//	else if( text == "Old TV")
	//		return IImageProcessManager::EM_OLD_TV;

	//	return IImageProcessManager::EM_GRAY_SCALE;
	//}

	// ˫��
	void CImageProcess::OnClicked( QListWidgetItem* pItem)
	{
		if( pItem->checkState() == Qt::Checked)
		{
			pItem->setCheckState( Qt::Unchecked);

			//Logic_ImageProcess->DisableImageProcess( Transform( pItem->text()));
		}
		else
		{
			pItem->setCheckState( Qt::Checked);
			//Logic_ImageProcess->EnableImageProcess( Transform( pItem->text()));
		}
	}
}