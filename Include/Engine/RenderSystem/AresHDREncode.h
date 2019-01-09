#pragma once

#include <Core/AresMath.h>
#include "Engine/Foundation/Ares3DEngine_h.h"

using namespace boost;

namespace Ares
{
	//-----------------------------------------------------------------------------
	// RGBE8 Encoding/Decoding HDR	2012-7-17 ����
	// The RGBE8 format stores a mantissa per color channel and a shared exponent 
	// stored in alpha. Since the exponent is shared, it's computed based on the
	// highest intensity color component. The resulting color is RGB * 2^Alpha,
	// which scales the data across a logarithmic scale.
	//-----------------------------------------------------------------------------
	class CORE_EXPORT HDREncode
	{
	public:
		static const int	LenEncode  = 16;
		static const int	MaxEncode  = 15;
		static const int    HalfEncode =  8;

	public:
		// ���캯��
		HDREncode();

		// ����RGBE8
		static ColorRGB EncodeRGBE8( const ColorRGB& rgb);

		// ����RGBE8
		static ColorRGB DecodeRGBE8( const ColorRGB& rgbe);

		// ����RGBM8
		static ColorRGB EncodeRGBM8( const ColorRGB& rgb);

		// ����RGBM8
		static ColorRGB DecodeRGBM8( const ColorRGB& rgbe);

	private:
		// ��������
		static int Log2Ceiling( float val);

	private:
		static boost::array<DOUBLE, LenEncode+1> m_powsOfTwo;
	};
}