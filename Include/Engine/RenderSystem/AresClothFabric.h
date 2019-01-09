#pragma once

#include <Physics/MassSpringSystem.h>
#include <Engine/RenderSystem/AresRenderEntity.h>
#include <Engine/RenderSystem/AresSuperRenderable.h>

namespace Ares
{
	//------------------------------------
	// ����֯�� 2013-7-12 ����
	//------------------------------------
	class ClothFabric : public RenderEntity
	{
	public:
		ClothFabric();
		~ClothFabric();

		// ��ȡ�ʵ㵯��ϵͳ
		MassSpringSystem& GetMassSpringSystem() { return m_massSpringSystem; }

	public:
		// ����
		virtual void  FrameMove( float fTime);

		// ��ӵ�������Ϣ
		virtual void OnAddToScene( Scene* scene);

		// �ύ��ȾԪ��
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr);

	private:
		// ����Buffer
		void UpdateBuffer();

	private:
		MassSpringSystem		m_massSpringSystem;		// �ʵ㵯��ϵͳ
		RenderLayoutPtr			m_renderLayout;			// ��Ⱦ������
		SuperRenderablePtr		m_renderable;			// ��Ⱦ
	};
	typedef s_ptr<ClothFabric> ClothFabricPtr;
}