#pragma once

#include "AresFrameFilter.h"
#include "AresGaussianBlur.h"

namespace Ares
{
	//------------------------------
	// ���� 2013-3-1 ����
	//------------------------------
	class DepthOfField : public FrameFilter
	{
	public:
		DepthOfField( Scene& scene);
		virtual ~DepthOfField();

		// ���Ĵ��ڴ�С
		void Resize( size_t width, size_t height);

		// ִ���˾�
		void Process( FrameBufferPtr output);

		// ��ȡFrameBuffer
		FrameBufferPtr& GetFrameBuffer() { return m_frameBuffer; }
	
	private:
		FrameBufferPtr		m_frameBuffer;
		TexturePtr			m_frameTexture;
		TexturePtr			m_frameDepth;
		BlurTexOffseter		m_blurTexOffseter;	// ��˹ģ��
		ShaderParamPtr		m_zInv;				// zInv;
		ShaderParamPtr		m_depthOfField;		// ����
		ShaderParamPtr		m_bufferTexture;	// ִ�о����ͼƬ
		ShaderParamPtr		m_depthTexture;		// ���ͼƬ
	};
	typedef s_ptr<DepthOfField> DepthOfFieldPtr;
}