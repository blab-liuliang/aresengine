#include <QtGui/QtGui>
#include "WaterEdit.h"
#include "SCLogic.h"

using namespace Ares;

namespace QT_UI
{
	// ���캯��
	CWaterEdit::CWaterEdit( QWidget* parent/* = 0*/)
		: QDockWidget( parent)
	{
		setupUi( this);

		connect( m_putWater, SIGNAL(toggled(bool)), this, SLOT( PutWater(bool)));
	}

	// ����ˮ
	void CWaterEdit::PutWater(bool checked)
	{
		// ��������ˮ״̬
		if( checked)
		{
			SCLogic_Main->SetHandleType( EM_HT_PUT_WATER);
		}
	}
}