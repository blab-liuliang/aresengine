#pragma once

#include "AresRenderQueue.h"
#include "Engine/RenderSystem/AresLight.h"
#include "Engine/RenderSystem/AresDirectionalLight.h"

namespace Ares
{
	//---------------------------------
	// ��Ⱦ���й�����, 2011-04-20 ����
	// ְ��
	//		1.״̬�ı�
	//		2.����
	//---------------------------------
	class RenderElementMgr
	{
	public:
		// ��պ���
		void Reset();

		// ִ�ж�����Ⱦ
		void Render( RenderQueueFlag flag);

		// ��ӵ���Ⱦ����
		void AddRenderable( RenderLayoutPtr& layout, RenderMaterial* material);

		// �����Ƿ�Ϊ��
		bool IsEmpty( RenderQueueFlag flag);

	public:
		// ��ȡ��Դ
		const vector<Light*>& GetLights() const { return m_lights; }

		// ��ӹ�Դ
		void AddLight( Light* light) { m_lights.push_back( light); }

		// ��ȡ����Դ
		const DirectionalLightPtr& GetDomainLight() const { return m_dominantLight; }

		// ��������Դ
		void SetDomainLight( DirectionalLightPtr& light) { m_dominantLight=light; }

	private:
		vector<Light*>							m_lights;			// ��Դ
		DirectionalLightPtr						m_dominantLight;	// ����Դ
		boost::array<RenderQueue, RQ_Max>		m_rendrQueues;		// ��Ⱦ����
	};
}