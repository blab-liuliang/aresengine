#pragma once

#include "../../Foundation/AresComponent.h"

namespace Ares
{
	//------------------------------------
	// ��Ⱦ��� 2012-3-30 ����
	//------------------------------------
	class ARES_EXPORT ComponentRender : public Component
	{
	public:
		// ���캯��
		ComponentRender();

		// ��������
		~ComponentRender();

	protected:
		RenderLayout	m_layout;
		RenderMaterial	m_material;
	};
}