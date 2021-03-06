//---------------------------------------------------------------------------
//	AresVcWin32.h : Ares definitions for visual c++ sp2 running under Win32.
//	Copyright 2012-2015	 ���� All Rights Reserved
//---------------------------------------------------------------------------
// Platform compiler definitions
#ifdef __GCC32__
#define __GCC32__ 1
#endif

//#if !_WINDOWS_
//#error _WINDOWS not defined
//#endif
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <xmmintrin.h>
#include <assert.h>

	// Function type macros
#define FORCEINLINE  __attribute__((always_inline))           	// Force code to be inline
#define INLINE		inline			// inline

// Unsigned base types
typedef unsigned char	   BYTE;		// 8-bit unsigned
typedef unsigned short     WORD;		// 16-bit unsigned
typedef unsigned int       UINT;		// 32-bit unsigned
typedef unsigned int       DWORD;		// 32-bit unsigned
typedef unsigned long long QWORD;		// 64-bit unsigned

// Signed base types
typedef signed char	 SBYTE;
typedef signed int	 INT;		// 32-bit signed
typedef signed int   LONG;		// 32-bit signed long integer.

// Other base types
typedef INT		BOOL;				// Boolean 0 (false) or 1(true)
typedef UINT	UBOOL;				// Boolean 0 (false) or 1(true)
typedef float	FLOAT;				// 32-bit IEEE floating point
typedef double	DOUBLE;				// 64-bit IEEE double.

// The SCALAR type abstracts floating point numbers, to easily
// swith between double and single floating point precision
#if defined(USE_DOUBLE_PRECISION)
	typedef double  SCALAR;
#else
	typedef float	SCALAR;
#endif

// Standard constants
#undef FALSE
#undef TRUE
#undef NULL

#define FALSE    0
#define TRUE     1
#define NULL     0
#define INVALID -1

	// Alignment
#define MS_ALIGN(n) __attribute__((aligned(n)))
//__declspec(align(n))

#if __GNUC__ || __INTEL_COMPILER
#define __HAS_SSE__ 1
#endif

	// Enable vector intrinsics if possible
#ifndef ENABLE_VECTORINTRINSICS
#if ( PS3 || XBOX || ( __HAS_SSE__ && !__GNUC__ && !defined( __cplusplus_cli ) && !__INTEL_COMPILER ) )
#if !_WIN64		// @todo win64: Enable this after we've updated MMX code to SSE2 where appropriate
	/** Turning this on enables the cross-platform intrinsic code path in the engine. */
#define ENABLE_VECTORINTRINSICS 0
#endif
#endif
#endif

//------------------------
// �궨��
//------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_VECTOR
#define SAFE_DELETE_VECTOR(v) {	for ( size_t i=0; i<v.size(); i++) SAFE_DELETE( v[i]); v.clear();}
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif
#ifndef SAFE_FREE
#define SAFE_FREE(p)      { if(p) { free(p); (p)=NULL; } }
#endif

#define A_ASSERT(expr)    assert(expr)
//#define V_ASSERT(expr)   { HRESULT hr=expr; assert(hr); }

//#define SPtr	boost::shared_ptr

//#ifdef _DEBUG
//#define ARES_DEBUG_MODE 1
//#else
//#define ARES_DEBUG_MODE 0
//#endif

//#define SUCCEEDED(hr)   (((HRESULT)(hr)) >= 0)
//#define FAILED(hr)      (((HRESULT)(hr)) < 0)

//#define S_OK			((HRESULT)0L)

// MathLibrary
FORCEINLINE FLOAT appTan( FLOAT value) { return tanf(value); }

//
// MSM: Fast float square root using SSE
// Accurate to within 1 LSB
//
FORCEINLINE FLOAT appSqrt( FLOAT f)
{
	// DB: crt's sqrt is ~60% faster than the below code and is defined for near-zero values.
	return sqrt( f);
/*
#if FALSE
	const FLOAT fZero = 0.0f;
	const FLOAT fThree = 3.0f;
	const FLOAT fOneHalf = 0.5f;
	FLOAT temp;

	__asm
	{
		movss	xmm1,[F]
		rsqrtss xmm0,xmm1			// 1/sqrt estimate (12 bits)

			// Newton-Raphson iteration (X1 = 0.5*X0*(3-(Y*X0)*X0))
			movss	xmm3,[fThree]
		movss	xmm2,xmm0
			mulss	xmm0,xmm1			// Y*X0
			mulss	xmm0,xmm2			// Y*X0*X0
			mulss	xmm2,[fOneHalf]		// 0.5*X0
		subss	xmm3,xmm0			// 3-Y*X0*X0
			mulss	xmm3,xmm2			// 0.5*X0*(3-Y*X0*X0)

			movss	xmm4,[fZero]
		cmpss	xmm4,xmm1,4			// not equal

			mulss	xmm3,xmm1			// sqrt(f) = f * 1/sqrt(f)

			andps	xmm3,xmm4			// seet result to zero if input is zero

			movss	[temp],xmm3
	}

	return temp;
#endif
*/
}

//
// MSM: Fast float inverse square root using SSE
// Accurate to within 1 LSB
FORCEINLINE FLOAT appInvSqrt( FLOAT f)
{
/*
#if ENABLE_VECTORINTRINSICS
	static const __m128 fThree   = _mm_set_ss( 3.0f );
	static const __m128 fOneHalf = _mm_set_ss( 0.5f );
	__m128 Y0, X0, Temp;
	FLOAT temp;

	Y0 = _mm_set_ss( f );
	X0 = _mm_rsqrt_ss( Y0 );	// 1/sqrt estimate (12 bits)

	// Newton-Raphson iteration (X1 = 0.5*X0*(3-(Y*X0)*X0))
	Temp = _mm_mul_ss( _mm_mul_ss(Y0, X0), X0 );	// (Y*X0)*X0
	Temp = _mm_sub_ss( fThree, Temp );				// (3-(Y*X0)*X0)
	Temp = _mm_mul_ss( X0, Temp );					// X0*(3-(Y*X0)*X0)
	Temp = _mm_mul_ss( fOneHalf, Temp );			// 0.5*X0*(3-(Y*X0)*X0)
	_mm_store_ss( &temp, Temp );

	return temp;

#elif _WIN64
*/
	// NOTE: This is only really used when included from C++/CLI source files in 64-bit
	// @todo win64: Use a more efficient implementation here!
	return 1.0f / sqrtf( f );

/*
#else
	// x86 ASM
	const FLOAT fThree = 3.0f;
	const FLOAT fOneHalf = 0.5f;
	FLOAT temp;

	__asm
	{
		movss	xmm1,[f]
		rsqrtss	xmm0,xmm1			// 1/sqrt estimate (12 bits)

			// Newton-Raphson iteration (X1 = 0.5*X0*(3-(Y*X0)*X0))
			movss	xmm3,[fThree]
		movss	xmm2,xmm0
			mulss	xmm0,xmm1			// Y*X0
			mulss	xmm0,xmm2			// Y*X0*X0
			mulss	xmm2,[fOneHalf]		// 0.5*X0
		subss	xmm3,xmm0			// 3-Y*X0*X0
			mulss	xmm3,xmm2			// 0.5*X0*(3-Y*X0*X0)
			movss	[temp],xmm3
	}
	return temp;
#endif
*/
}

