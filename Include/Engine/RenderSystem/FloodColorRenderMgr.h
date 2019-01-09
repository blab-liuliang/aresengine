#pragma once

#include <Engine/RenderSystem/AresModel.h>
#include <Engine/RenderSystem/FloodColorRenderable.h>

namespace Ares
{
	//--------------------------------
	// ����Ч�� 2013-3-6 ����
	//--------------------------------
	class FloodColorRenderMgr
	{
		typedef multimap<EntityPtr, FloodColorRenderable*> MultimapFR;
	public:
		// ��Ⱦ����
		void Write( vector<EntityPtr>& entitys);

	private:
		// ����FloodLightRenderalbe
		void RefreshRenderableWrite( vector<EntityPtr>& entitys);

		// ˢ��ģ�ͷ���Renderable
		void RefreshRenderableWrite( ModelPtr& model);

		// ִ�з�����Ⱦ
		void ExecFloodLightWrite( vector<EntityPtr>& entitys);

	private:
		MultimapFR		m_renderables;
	};
}