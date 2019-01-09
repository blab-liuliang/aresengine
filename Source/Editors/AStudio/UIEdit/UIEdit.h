#pragma once

#include <Engine/UISystem/MyGUI.h>

namespace Ares
{
	//--------------------------------------
	// Ч���༭�߼� 2012-8-20 ����
	//--------------------------------------
	class UiEdit
	{
	public:
		UiEdit();

		// �½�Ч��
		void New();

		// ��
		void Open( const char* layoutPath);

		// ����
		void FrameMove();

		// ִ��
		void Exec();

	private:
		MyGUI::TextBox*		m_label;		// ������<��������>
	};
}