#pragma once

#include <stdio.h>
#include <Core/3rdParty/Vpx/vpx_encoder.h>
#include <Core/3rdParty/Vpx/vp8cx.h>

namespace Ares
{
	//-------------------------------
	// Webm������ 2013-1-19 ����
	//-------------------------------
	class Vp8Encoder
	{
	public:
		Vp8Encoder();
		~Vp8Encoder();

		// ���ÿ�
		bool SetWidth( long width);

		// ���ø�
		bool SetHeight( long height);

		// ��ʼ
		bool Begin( const char* filePath);

		// ����֡����
		bool AppendFrame();

		// ����
		bool End();

	private:
		// д�ļ�ͷ
		void write_file_header();

		// д֡ͷ
		void write_frame_header( const vpx_codec_cx_pkt_t* pkt);

		// д��������
		void write_image();

	private:
		long				m_width;	// ��Ƶ��
		long				m_height;	// ��Ƶ��

		FILE*				m_file;	// ���
		vpx_codec_ctx_t		m_codec;
		vpx_image_t			m_image;
		vpx_codec_enc_cfg_t	m_config;	// ����
		int					m_frameNum;	// ֡����
		int					m_flags;	// ���
		vpx_fixed_buf_t		m_stats;
	};
}