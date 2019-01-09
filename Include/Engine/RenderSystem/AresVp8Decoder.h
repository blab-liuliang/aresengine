#pragma once

#include <Core/3rdParty/Vpx/vpx_decoder.h>
#include <Core/3rdParty/Vpx/vp8dx.h>

namespace Ares
{
	//----------------------------------
	// Vp8������ 2013-1-18 ����
	//----------------------------------
	class Vp8Decoder
	{
	public:
		Vp8Decoder();
		~Vp8Decoder();

		// �򵥽���(������)
		void SimpleDecode();

	private:
		// ������ʾ
		void ReportError( vpx_codec_ctx_t& codec);
	};
}