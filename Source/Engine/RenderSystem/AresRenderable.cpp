#include "Engine/RenderSystem/AresRenderable.h"
#include "Engine/AresRoot.h"
#include <Engine/SceneSystem/AresScene.h>
#include <Engine/RenderSystem/AresRenderElementMgr.h>

namespace Ares
{
	// ���캯��
	Renderable::Renderable()
	{
		m_material = MakeSharePtr( new_ SuperMaterial);
	}

	// ��������
	Renderable::~Renderable()
	{}

	// ��Ⱦ
	void Renderable::Render()
	{
		if( IsReady())
		{
			ARenderDevice->Render( m_layout.get(), m_material.get());
		}
	}

	// �Ƿ���ȫ��ʼ��(��Ⱦ��������)
	bool Renderable::IsReady()
	{ 
		return m_layout && m_material;
	}

	// ��ȡ��Ⱦ����
	RenderMethodPtr Renderable::GetRenderMethod()
	{
		return m_material->GetMethod();
	}

	// ���ò���
	void Renderable::SetMaterial( const RenderMaterialPtr& mat) 
	{ 
		m_material = mat; 
	}

	// �ύ����Ⱦ����
	void Renderable::SubmitRenderElements( RenderElementMgr& renderElementMgr)
	{
		A_ASSERT( m_material->GetRenderQueue());
	
		renderElementMgr.AddRenderable( m_layout, m_material.get());
	}
}