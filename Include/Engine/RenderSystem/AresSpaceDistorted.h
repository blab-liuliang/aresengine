#pragma once

#include "AresFrameFilter.h"

namespace Ares
{
	//------------------------------------
	// �ռ�Ť�� 2012-8-30 ����
	//------------------------------------
	class SpaceDistorted : public FrameFilter
	{
	public:
		// ���캯��
		SpaceDistorted( Scene& scene);

		// ����Դ����
		bool SetSrcTexture( TexturePtr& src);

	public:
		// ֱ������DistortedTexture
		void SetDistortedTexture( const TexturePtr& texture) { m_distortedTexture = texture; }

		// ��ȡDistortedTexture
		TexturePtr GetDistortedTexture() { return m_distortedTexture; }

		// ��DistortedFrameBuffer
		FrameBufferPtr GetDistortedFrameBuffer() { return m_distortedFrameBuffer; }

	private:
		TexturePtr		m_distortedTexture;			// ���Ť��λ��
		FrameBufferPtr	m_distortedFrameBuffer;		// ���ڸ���Ť������
	};
}