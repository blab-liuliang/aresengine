#pragma once

#include "AresFrameFilter.h"
#include "FloodColorRenderMgr.h"
#include "AresGaussianBlur.h"

namespace Ares
{
	//------------------------------------
	// FloodColor 2013-3-6 ����
	//------------------------------------
	class FloodColor : public FrameFilter
	{
	public:
		FloodColor( Scene& scene);
		~FloodColor();

		// ���Ĵ��ڴ�С
		void Resize( size_t width, size_t height);

		// ִ���˾�
		void Process( vector<EntityPtr>& entitys, RenderViewPtr& iDepth, FrameBufferPtr& output);

	private:
		size_t					m_bufferWidth;			// ��
		size_t					m_bufferHeight;			// ��
		FloodColorRenderMgr		m_floodRenderMgr;		// ��Ⱦ������

		TexturePtr				m_frameTexture;			// ����
		FrameBufferPtr			m_frameBuffer;			// ֡����

		ShaderParamPtr			m_bufferTexture;		// ��ģ������ 
		GaussianBlurPtr			m_gaussianBlur;			// ��˹ģ��
	};
	typedef s_ptr<FloodColor> FloodColorPtr;
}