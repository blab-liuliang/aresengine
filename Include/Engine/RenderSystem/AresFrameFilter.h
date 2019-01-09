#pragma once

#include <boost/noncopyable.hpp>
#include "Engine/RenderSystem/AresRenderable.h"

namespace Ares
{
	//------------------------------------------
	// ֡�˾� 2012-8-8  ����
	//------------------------------------------
	class Scene;
	class FrameFilter : boost::noncopyable
	{
	public:
		virtual ~FrameFilter();

		// ִ���˾�
		virtual void Execute();

	public:
		// ��ȡScreenQuadRenderLayout
		static RenderLayoutPtr& GetScreenQuadRenderLayout();

	protected:
		FrameFilter( Scene& scene);

	protected:
		Renderable				m_renderable;
		Scene&					m_scene;		// ��������ϵͳ
	};
}