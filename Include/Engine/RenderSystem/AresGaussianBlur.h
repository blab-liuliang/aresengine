#pragma once

#include <vector>
#include "AresFrameFilter.h"

using namespace std;

namespace Ares
{
	//--------------------------------------
	// BlurTexOffseter 2013-2-26 ����
	//--------------------------------------
	struct BlurTexOffseter
	{
		UINT				m_width;		// ����ͼ��
		UINT				m_height;		// ����ͼ��
		int					m_kernelSize;
		int					m_kernelRadius;
		ShaderParamPtr		m_texOffset;

		static const float  WeightTable1x1[1];	// 1x1Ȩ�ر�
		static const float	WeightTable3x3[9];	// 3x3Ȩ�ر�
		static const float	WeightTable7x7[49];	// 7x7Ȩ�ر�

		// ���캯��
		BlurTexOffseter();

		// ���ò���
		void SetInput( UINT width, UINT height, const float* weightTable, int tableMembers);

		// ���ò���
		void SetInput( TexturePtr texture, const float* weightTable, int tableMembers);
	};

	//--------------------------------------
	// ģ���� 2013-2-25 ����
	//--------------------------------------
	class GaussianBlur : public FrameFilter
	{
	public:
		static const float WeightTable1x49[49]; // ģ��Ȩ�ر�

	public:
		GaussianBlur( Scene& sceneSystem, bool hdrTexture=false);
		~GaussianBlur();

		// ִ��ģ��
		virtual void Execute();

		// ��������
		void SetInput( TexturePtr& oTexture, const TexturePtr& iTexture, const float* weightTable, int tableMembers);

	private:
		vector<float4>		m_texOffsetX;
		vector<float4>		m_texOffsetY;
		ShaderParamPtr		m_texOffset;
		ShaderParamPtr		m_blurTexture;			// ��ģ������

		TexturePtr			m_inputTexture;			// ��������
		TexturePtr			m_middleTexture;		// �м�׶�����
		FrameBufferPtr		m_middleFrameBuffer;	
		FrameBufferPtr		m_finalFrameBuffer;
	};
	typedef s_ptr<GaussianBlur> GaussianBlurPtr;
}