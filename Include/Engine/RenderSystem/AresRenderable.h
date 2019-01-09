#pragma once

#include <Core/AresCore.h>

namespace Ares
{
	//------------------------------------
	// ��Ⱦ��� 2012-3-30 ����
	//------------------------------------
	class RenderElementMgr;
	class Renderable
	{
	public:
		Renderable();
		~Renderable();

		// ��Ⱦ
		void Render();

		// ��ȡRenderlayout
		RenderLayoutPtr& GetRenderLayout() { return m_layout; }

		// ��ȡ����
		RenderMaterialPtr&  GetMaterial() { return m_material; }

		// ��ȡ��Ⱦ����
		RenderMethodPtr  GetRenderMethod();

		// �Ƿ���ȫ��ʼ��(��Ⱦ��������)
		bool IsReady();

		// ������Ⱦ���
		void SetReady( bool ready) { m_ready = ready; }

		// ����Renderlayout
		void SetRenderlayout( const RenderLayoutPtr& renderLayout) { m_layout = renderLayout;}

		// ���ò���
		void SetMaterial( const RenderMaterialPtr& mat);

		// �ύ����Ⱦ����
		void SubmitRenderElements( RenderElementMgr& renderElementMgr);

	protected:
		RenderLayoutPtr		m_layout;			// RenderGeometry
		RenderMaterialPtr	m_material;			// RenderMaterial
		bool				m_ready;			// ready to render
	};
}