#pragma once

#include "AresFrameFilter.h"

namespace Ares
{
	//-----------------------------------------
	// ToneMapping 2013-8-27 ����
	//-----------------------------------------
	class ToneMapping : public FrameFilter
	{
		// ö��
		enum FrameBufferType
		{
			FBT_FullSize = 0,
			FBT_DownSampled256x256,
			FBT_DownSampled64x64,
			FBT_DownSampled16x16,
			FBT_DownSampled4x4,
			FBT_LuminancePrevious,
			FBT_LuminanceCurrent,
			FBT_LuminanceTemp,
			FBT_FrameBuffers,
		};

	public:
		ToneMapping( Scene& scene);
		~ToneMapping();

		// ����Դ����
		bool SetSrcTexture( TexturePtr& src, FrameBufferPtr& oFrameBuffer);

		// ִ���˾�
		void ToneMapping::Execute();

	private:
		// ת��Ϊ����
		void ConvertToLogLuminance();

		// ��ƽ������
		void AverageLuminance();

		// ��������
		void AdaptiveLuminance();

		// �Զ�����
		void AutoExposure();

		// �������Ƚ��
		void SwapLuminanceFrameBuffer( FrameBufferType type0, FrameBufferType type1);

	private:
		ShaderParamPtr		m_adaptiveSpeed;						// �Զ��ع�����ٶ�
		ShaderParamPtr		m_middleGray;							// �Ҷ�ֵ
		ShaderParamPtr		m_multiplierClamp;						// ��ȷ���ô�
		ShaderParamPtr		m_lumianceTable;						// ���ȼ���
		ShaderParamPtr		m_downSampledOffset[4];					// ��������
		ShaderParamPtr		m_spabTextureFullSize;					// Դ����
		ShaderParamPtr		m_spabTextures[FBT_FrameBuffers];		// ��������

		Renderable			m_luminanceRenderable;					// ԭͼƬת��Ϊ����
		Renderable			m_renderableDownSampled;				// ��ƽ������
		Renderable			m_renderableExpLuminance;				// ������ָ��
		Renderable			m_renderableLuminanceAdaptive;			// ���ȵ���
		Renderable&			m_renderAutoExposure;					// �Զ�����
		TexturePtr			m_textures[FBT_FrameBuffers];			// ��ȾĿ��
		FrameBufferPtr		m_frameBuffers[FBT_FrameBuffers];		// ��Ⱦ����

		FrameBufferPtr*		m_output;								// �����ȾĿ��
	};
	typedef s_ptr<ToneMapping> ToneMappingPtr;
}