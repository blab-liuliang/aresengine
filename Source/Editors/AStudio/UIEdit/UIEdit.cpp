#include "UIEdit.h"
#include <boost/array.hpp>
#include <Engine/AresRoot.h>

namespace Ares
{
	// ���캯��
	UiEdit::UiEdit()
		: m_label( NULL)
	{
	}

	// �½�Ч��
	void UiEdit::New()
	{
		
	}

	// ��
	void UiEdit::Open( const char* layoutPath)
	{
		using namespace MyGUI;

		const VectorWidgetPtr& layout = AUiLayoutMgr.loadLayout( layoutPath);
	}

	// ����
	void UiEdit::FrameMove()
	{
	}

	// ִ��
	void UiEdit::Exec()
	{
	}
}