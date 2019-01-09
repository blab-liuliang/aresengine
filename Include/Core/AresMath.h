#pragma once

#include "AresPlatform.h"

#pragma warning( disable : 4201)
#pragma warning( disable : 4324)

namespace Ares
{
	// Forward declarations
	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix44;
	class Quat;

	// Constants
	#undef  PI
	#define PI 				(3.1415926535897932f)
	#define FLT_SMALL		(1e-5f)
	#define FLT_BIG			(1e+30f)
	#define FLT_TOLERANCE   (1e-6f)
	#define ZERO_TOLERANCE  (1e-06f)

	// �Ƕ�ת����
	#define DEGtoRAD(a) ( (a)*0.01745329252f )

	// clamp
	template<class T> FORCEINLINE T clamp( T v, T low, T high) 
	{ 
		if( low > v) return low; else if (high < v) return high;   return v;
	}

	//--------------------------------------
	// A  2x1 of Floats	2012/1/9 ���� 
	//--------------------------------------
	class Vector2
	{
	public:
		// Constructors
		FORCEINLINE Vector2()
		{}

		// Constructors
		FORCEINLINE Vector2( float inX, float inY) 
			: x( inX), y( inY)
		{ }

		// ���������"-"
		FORCEINLINE Vector2 operator - ( const Vector2& v) const
		{
			return Vector2( x-v.x, y-v.y);
		}

		// ��������� "!="
		FORCEINLINE UBOOL operator != ( const Vector2& v) const
		{
			return x!=v.x || y!=v.y;
		}

		// ����"[]" 
		FLOAT& operator[]( INT i)
		{
			assert( i>=0);
			assert( i<2);

			return v[i];
		}

		// ����"[]" const
		FLOAT operator[]( INT i) const
		{
			assert( i>=0);
			assert( i<2);

			return v[i];
		}

		// ���س���
		FLOAT Length() const
		{
			return appSqrt( x*x + y*y);
		}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & x;
			ar & y;
		}

	public:
		union
		{
			struct
			{
				FLOAT x, y;		// Variables
			};

			struct
			{
				FLOAT v[2];			// Variables
			};
		};
	};

	typedef float	float1;
	typedef Vector2 float2;

	// Calculates the cross product of two vector2s 
	//
	// @param Vec1	1st vector
	// @param Vec2	2nd vector
	// @return cross(Vec1.xy, Vec2.xy)
	FORCEINLINE float Vector2Cross( const Vector2& Vec1, const Vector2& Vec2 )
	{
		return Vec1.x * Vec2.y - Vec2.x * Vec1.y;
	}

	//--------------------------------------
	// A 3x1 floats Vector3 2012/1/6 ����
	//--------------------------------------
	class Vector3
	{
	public:
		static const Vector3 Zero;			// ������
		static const Vector3 XAxis;			// Ĭ��X��
		static const Vector3 YAxis;			// Ĭ��Y��
		static const Vector3 ZAxis;			// Ĭ��Z��

	public:
		// Constructors
		FORCEINLINE Vector3() 
		{ }

		// Constructors
		explicit FORCEINLINE Vector3( FLOAT inF) 
			: x( inF), y( inF), z( inF) 
		{ }

		// Constructors
		FORCEINLINE Vector3( float inX, float inY, float inZ) 
			: x( inX), y( inY), z( inZ) 
		{ }

		// Vector4 to Vector3
		FORCEINLINE Vector3( const Vector4& v);


		// ��������� "+"
		FORCEINLINE Vector3 operator + ( const Vector3& v3) const
		{
			return Vector3( x+v3.x, y+v3.y, z+v3.z);
		}

		// ���������"-"
		FORCEINLINE Vector3 operator - () const
		{
			return Vector3( -x, -y, -z);
		}

		// ��������� "*"
		FORCEINLINE Vector3 operator*( FLOAT scale) const
		{
			return Vector3( x*scale, y*scale, z*scale);
		}

		// ��������� "/"
		FORCEINLINE Vector3 operator / (FLOAT scale) const
		{
			FLOAT rScale = 1.f / scale;

			return Vector3( x*rScale, y*rScale, z*rScale);
		}

		// ���������"-"
		FORCEINLINE Vector3 operator - ( const Vector3& v3) const
		{
			return Vector3( x-v3.x, y-v3.y, z-v3.z);
		}

		// ���رȽ������
		FORCEINLINE UBOOL operator == ( const Vector3& v3) const
		{
			return x==v3.x && y==v3.y && z==v3.z;
		}

		// ��������� "!="
		UBOOL operator != ( const Vector3& v) const
		{
			return x!=v.x || y!=v.y || z!=v.z;
		}

		// ��������� "-="
		FORCEINLINE Vector3 operator -= (const Vector3& v3)
		{
			x -= v3.x; y-= v3.y; z -= v3.z;

			return *this;
		}

		// ��������� "+="
		FORCEINLINE Vector3 operator += (const Vector3& v3)
		{
			x += v3.x; y+= v3.y; z += v3.z;

			return *this;
		}

		// ��������� "/="
		Vector3 operator /= ( FLOAT scale)
		{
			const FLOAT rscale = 1.f / scale;
			x*=rscale; y*=rscale; z*=rscale;

			return *this;
		}

		// ��������� "*="
		Vector3 operator *= ( FLOAT scale)
		{
			x*=scale; y*=scale; z*=scale;

			return *this;
		}

		// ����"[]" 
		FLOAT& operator[]( INT i)
		{
			assert( i>=0);
			assert( i<3);

			return v[i];
		}

		// ����"[]" const
		FLOAT operator[]( INT i) const
		{
			assert( i>=0);
			assert( i<3);

			return v[i];
		}

		// ��λ��
		FORCEINLINE UBOOL Normalize( FLOAT tolerance=FLT_SMALL);

		// ���س���
		FLOAT Length() const
		{
			return appSqrt( x*x + y*y + z*z);
		}

		// ���ȵ�ƽ��
		FLOAT LengthSq() const
		{
			return x*x + y*y + z*z;
		}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & x;
			ar & y;
			ar & z;
		}

	public:
		union
		{
			struct
			{
				FLOAT x, y, z;		// Variables
			};

			struct
			{
				FLOAT v[3];			// Variables
			};
		};

	};

	typedef Vector3	 float3;

	// ��������� "*"
	FORCEINLINE Vector3 operator * ( const Vector3& v1, const Vector3& v2)
	{
		return Vector3( v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
	}

	// ���� "*" ֧�� FLOAT * Vector3
	FORCEINLINE Vector3 operator*( FLOAT scale, const Vector3& v)
	{
		return v * scale;
	}

	// Calculates the cross product of two vector3s 
	//
	// @param Vec1	1st vector
	// @param Vec2	2nd vector
	// @return cross(Vec1.xyz, Vec2.xyz)
	FORCEINLINE Vector3 Vector3Cross( const Vector3& Vec1, const Vector3& Vec2 )
	{
		return Vector3
		(
			Vec1.y * Vec2.z - Vec1.z * Vec2.y,
			Vec1.z * Vec2.x - Vec1.x * Vec2.z,
			Vec1.x * Vec2.y - Vec1.y * Vec2.x
		);
	}


	// Calculates the dot3 product of two vectors and returns a vector with the result in all 4 components.
	// Only really efficient on Xbox 360.
	//
	// @param Vec1	1st vector
	// @param Vec2	2nd vector
	// @return		d = dot3(Vec1.xyz, Vec2.xyz), VectorRegister( d, d, d, d )
	FORCEINLINE FLOAT Vector3Dot( const Vector3& vec1, const Vector3& vec2 )
	{
		return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
	}

	// Calculates the min component
	//
	// @param Vec1	1st vector
	// @param Vec2	2nd vector
	INLINE Vector3 Vector3Min( const Vector3& v1, const Vector3& v2)
	{
		Vector3 result;

		result.x = v1.x < v2.x ? v1.x : v2.x;
		result.y = v1.y < v2.y ? v1.y : v2.y;
		result.z = v1.z < v2.z ? v1.z : v2.z;

		return result;
	}

	// Calculates the abs component
	INLINE Vector3 Vector3Abs( const Vector3& v1)
	{
		Vector3 result;

		result.x = abs(v1.x);
		result.y = abs(v1.y);
		result.z = abs(v1.z);

		return result;
	}

	// Max
	INLINE Vector3 Vector3Max( const Vector3& v1, const Vector3& v2)
	{
		Vector3 result;

		result.x = v1.x > v2.x ? v1.x : v2.x;
		result.y = v1.y > v2.y ? v1.y : v2.y;
		result.z = v1.z > v2.z ? v1.z : v2.z;

		return result;
	}

	//-------------------------------------
	// A 4D homogeneous vector, 4x1 floats, 
	// 16-byte aligned 2012/1/6  ����
	//-------------------------------------
	class Vector4
	{
	public:
		// Constructors
		explicit Vector4( FLOAT inX=0.f, FLOAT inY=0.f, FLOAT inZ=0.f, FLOAT inW=1.f)
			: x(inX), y(inY), z(inZ), w(inW)
		{ }

		// Constructors
		explicit Vector4( const Vector3& inXYZ, float inW=1.f)
			: x(inXYZ.x), y(inXYZ.y), z(inXYZ.z), w(inW)
		{ }

		// ����"[]" 
		FLOAT& operator[]( INT i)
		{
			A_ASSERT( i>=0);
			A_ASSERT( i<4);

			return v[i];
		}

		// ����"[]" 
		FLOAT operator[]( INT i) const
		{
			A_ASSERT( i>=0);
			A_ASSERT( i<4);

			return v[i];
		}

		// ��������� "/="
		Vector4 operator /= ( FLOAT scale)
		{
			const FLOAT rscale = 1.f / scale;
			x*=rscale; y*=rscale; z*=rscale; w*=rscale;

			return *this;
		}

		// ���رȽ������
		FORCEINLINE UBOOL operator == ( const Vector4& v3) const
		{
			return x==v3.x && y==v3.y && z==v3.z && w==v3.w;
		}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & x & y & z & w;
		}

	public:
		union
		{
			struct
			{
				FLOAT x, y, z, w;		// Variables
			};

			struct 
			{
				FLOAT r, g, b, a;
			};

			struct
			{
				FLOAT v[4];			// Variables
			};
		};
	};
	typedef Vector4 float4;

	//------------------------------------
	// Quat 2012/1/6 ���� ��<unreal>
	//------------------------------------
	class Quat
	{
	public:
		static const Quat Identity;		// ��λ��Ԫ��

	public:
		// Constructors
		FORCEINLINE Quat()
		{}

		// Constructors
		FORCEINLINE Quat( FLOAT inX, FLOAT inY, FLOAT inZ, FLOAT inW)
			: x(inX), y(inY),  z(inZ), w(inW)
		{}

		// ��������� "+"
		FORCEINLINE Quat operator + ( const Quat& q) const
		{
			return Quat( x+q.x, y+q.y, z+q.z, w+q.w);
		}

		// ��������� "-"
		FORCEINLINE Quat operator - ( const Quat& q) const
		{
			return Quat( x-q.x, y-q.y, z-q.z, w-q.w);
		}

		// ��������� "="
		FORCEINLINE Quat operator *( float scale) const
		{
			return Quat( x*scale, y*scale, z*scale, w*scale);
		}

		// ��������� "="
		FORCEINLINE bool operator == ( const Quat& Q) const
		{
			return x==Q.x && y==Q.y && z==Q.z && w==Q.w;
		}

		// From Matrix
		FORCEINLINE void FromMatrix( const Matrix44& mat);

		// From Euler angles
		FORCEINLINE void FromEuler( const Vector3& euler);

		// From Axis angle
		FORCEINLINE void FromAxisAngle( const Vector3& axis, FLOAT angle);

		// From Arc <<game programming gems 1>> 2.10
		FORCEINLINE void FromArc( Vector3 begin, Vector3 end);

		// Transform to Matrix
		FORCEINLINE void ToMatrix( Matrix44& mat) const;

		// ��ת����
		FORCEINLINE Vector3 Rotate( const Vector3& v) const;

		// ��λ��
		FORCEINLINE void Normalize();

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & x & y & z & w;
		}

	public:
		FLOAT x, y, z, w;	// Variables; x,y,z,w also doubles as the Axis/Angle format.
	};

	// ��������� "~" ����
	FORCEINLINE Quat operator~(const Quat& q)
	{
		// assert 'this' is unit length
		return Quat( -q.x, -q.y, -q.z, q.w);
	}

	// ��������� "*"
	FORCEINLINE Quat operator * ( const Quat& a, const Quat& b);

	// ��Ԫ�����
	FORCEINLINE float QuatDot( const Quat& a, const Quat& b);

	// ��Ԫ�����Բ�ֵ
	FORCEINLINE Quat QuatLerp( const Quat& from, const Quat& to, float percentage);

	// ��Ԫ����ֵ
	FORCEINLINE Quat QuatSlerp( const Quat& from, const Quat& to, float percentage);

	//--------------------------------------
	// Matrix 2012/1/6  ����
	//--------------------------------------
	class Matrix44
	{
	public:
		static const Matrix44 Zero;			// �����
		static const Matrix44 Identity;		// ��λ����

	public:
		// Constructors
		FORCEINLINE Matrix44();

		// Construction
		FORCEINLINE Matrix44( FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
							  FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
							  FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
							  FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44)
		{
			m[0][0] = _11; m[0][1] = _12;  m[0][2] = _13;  m[0][3] = _14;
			m[1][0] = _21; m[1][1] = _22;  m[1][2] = _23;  m[1][3] = _24;
			m[2][0] = _31; m[2][1] = _32;  m[2][2] = _33;  m[2][3] = _34;
			m[3][0] = _41; m[3][1] = _42;  m[3][2] = _43;  m[3][3] = _44;
		}

		// Set
		FORCEINLINE void Set( FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
							  FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
							  FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
							  FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44)
		{
			m[0][0] = _11; m[0][1] = _12;  m[0][2] = _13;  m[0][3] = _14;
			m[1][0] = _21; m[1][1] = _22;  m[1][2] = _23;  m[1][3] = _24;
			m[2][0] = _31; m[2][1] = _32;  m[2][2] = _33;  m[2][3] = _34;
			m[3][0] = _41; m[3][1] = _42;  m[3][2] = _43;  m[3][3] = _44;
		}

		// Identity
		INLINE void SetIdentity()
		{
			*this = Identity;
		}

		// Origin
		FORCEINLINE void SetOrigin( FLOAT x, FLOAT y, FLOAT z)
		{
			_41 = x; _42 = y; _43 = z;
		}

		// Origin
		FORCEINLINE void SetOrigin( const Vector3& v3)
		{
			_41 = v3.x; _42 = v3.y; _43 = v3.z;
		}

		// BOOL isIdentity
		FORCEINLINE BOOL IsIdentity() const;

		// GetTranspose
		FORCEINLINE Matrix44 GetTranspose() const;

		// ����"[]" 
		FORCEINLINE Vector4& operator[]( INT i);

		// ����"[]" 
		FORCEINLINE const Vector4& operator[]( INT i) const;

		// ��������� "*"
		FORCEINLINE Matrix44 operator * ( FLOAT f) const;

		// ���������"+"
		FORCEINLINE Matrix44 operator + ( const Matrix44& mat) const;

		// ���������"+="
		FORCEINLINE Matrix44 operator += ( const Matrix44& mat);

		// ���������"-"
		FORCEINLINE Matrix44 operator - ( const Matrix44& mat) const;

		// Concatenation operator
		FORCEINLINE Matrix44 operator* ( const Matrix44& other) const;

		// Concatenation operator
		FORCEINLINE Matrix44 operator*=( const Matrix44& other);

		// Transform a location
		FORCEINLINE Vector3 TransformVector3( const Vector3& v) const;

		// Homogeneous transform
		FORCEINLINE Vector4 TransformVector4( const Vector4& v) const;

	public:
		union
		{
			struct 
			{
				FLOAT m[4][4];
			};

			struct 
			{
				FLOAT _11, _12, _13, _14;
				FLOAT _21, _22, _23, _24;
				FLOAT _31, _32, _33, _34;
				FLOAT _41, _42, _43, _44;
			};
		};
	};
	typedef Matrix44 float4x4;

	// ���� "*" ֧�� FLOAT * Matrix44
	FORCEINLINE Matrix44 operator*( FLOAT scale, const Matrix44& v)
	{
		return v * scale;
	}

	// Set Scaling
	FORCEINLINE void Matrix44Scaling( Matrix44& result, FLOAT scale);

	// Set Scaling
	FORCEINLINE void Matrix44Scaling( Matrix44& result,const Vector3& scale);

	// Set Scaling
	FORCEINLINE void Matrix44Scaling( Matrix44& result,FLOAT sx, FLOAT sy, FLOAT sz);

	// Set Translation
	FORCEINLINE void Matrix44Translation( Matrix44& result, FLOAT xOffset, FLOAT yOffset, FLOAT zOffset);

	// Set Translation
	FORCEINLINE void Matrix44Translation( Matrix44& result, const Vector3& offset);

	// Matrix44ViewLH
	FORCEINLINE void Matrix44ViewLH( Matrix44& result, const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis, const Vector3& origin);

	// Inverse Fast path, doesn't check for nil matrices in final release builds
	const Matrix44& Matrix44Inverse( Matrix44& result, const Matrix44& src);

	// Matrix44ViewDirLH
	void Matrix44ViewDirLH( Matrix44& result, const Vector3& eye, const Vector3& viewDir, const Vector3& up);

	// Matrix44LookAtLH
	void Matrix44ViewAtLH( Matrix44& result, const Vector3& eye, const Vector3& viewAt, const Vector3& up);

	// Matrix44OrthoLH
	void Matrix44OrthoLH( Matrix44& result, float w, float h, float nearZ, float farZ);

	// Matrix44OrthoLH_D3DX
	void Matrix44OrthoLH_D3DX( Matrix44& result, float w, float h, float nearZ, float farZ);

	// Matrix44OrthoLH_OpenGL
	void Matrix44OrthoLH_OpenGL( Matrix44& result, float w, float h, float nearZ, float farZ);

	// Matrix44PerspectiveFovLH_D3DX
	void Matrix44PerspectiveFovLH_D3DX( Matrix44& result, FLOAT fovH, FLOAT aspect, FLOAT nearZ, FLOAT farZ);

	// Matrix44PerspectiveFovLH_OpenGL
	void Matrix44PerspectiveFovLH_OpenGL( Matrix44& result, FLOAT fov, FLOAT aspect, FLOAT nearZ, FLOAT farZ);

	// Matrix44RotationX
	void Matrix44RotationX( Matrix44& result, FLOAT radian);

	// Matrix44RotationY
	void Matrix44RotationY( Matrix44& result, FLOAT radian);

	// Matrix44RotationZ
	void Matrix44RotationZ( Matrix44& result, FLOAT radian);

	// Matrix44RotationAxisAngle
	void Matrix44RotationAxisAngle( Matrix44& result, const Vector3& axis, FLOAT angle);

	// Matrix44RotationAxis
	void Matrix44RotationAxis( Matrix44& result, const Vector3& dirFrom, const Vector3& dirTo);

	// Matrix44RotationYawPitchRoll
	void Matrix44RotationYawPitchRoll( Matrix44& result, FLOAT yaw, FLOAT pitch, FLOAT roll);

	//-----------------------------------------------
	// Transform 2010-05-27 13:24  ����
	//-----------------------------------------------
	struct Transform
	{
	public:
		Transform();
		Transform( const Transform& src);
		Transform( const Quat& rot, const Vector3& orig);

		// ���������"+"
		Transform operator + ( const Transform& tf) const;

		// ��������� "+="
		Transform operator += ( const Transform& tf);

		// ���������"-"
		Transform operator - ( const Transform& tf) const;

		// ��������� "="
		Transform& operator = (const Transform& src);

		// ��������� "*"
		Transform operator* (float scale) const;

		// ��������� "="
		Transform operator* ( const Transform& other) const;

		// ��������
		void SetScale( float scale);

		// ��ȡ����
		const Vector3& GetScale() { return m_scale; }

		// ������ת(ԭ����,��ǰ����)
		void  SetRotation( const Vector3& origDir, const Vector3& curDir);

		// ��ת(��ԭ���Ļ��������)
		void  AddRotation(  const Vector3& axis, FLOAT angle); 

		// ����λ��
		void  SetTrans( float x, float y, float z);

		// ����λ��
		void  SetTrans( const Vector3& pos);

		// ������ת
		void SetQuat( const Quat& quat) { m_rotation = quat; }

		// ���þ���
		void SetMatrix( const Matrix44& mat);

		// Transform a location
		Vector3 TransformVector3( const Vector3& v) const;

		// ����
		void SetIdentity();

		// �Ƿ�Ϊ��λ��
		bool IsIdentity();

		//// X�ᷴת
		//void InvXAxis();

		//// Y�ᷴת
		//void InvYAxis();

		//// Z�ᷴת
		//void InvZAxis();

	public:
		// ��ת
		const Quat&	GetQuat() const { return m_rotation; }

		// ƽ��
		const Vector3& GetTrans() const { return m_origin; }

		// �������
		const Matrix44 GetMatrix() const;

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_rotation;
			ar & m_origin;
		}

	public:
		bool			m_dirtyFlag;	// ����
		Quat			m_rotation;		// ��ת
		Vector3			m_origin;		// λ��
		Vector3			m_scale;		// ����
	};

	// ��������� "~" ����
	FORCEINLINE Transform operator~(const Transform& src)
	{
		Transform result;
		result.m_rotation = ~src.m_rotation;
		result.m_origin	  = result.m_rotation.Rotate( -src.m_origin);

		return result;
	}

	//------------------------------------
	// ColorRGB 2012/3/31 ����
	//------------------------------------
	class ColorRGB
	{
	public:
		// mask
		enum Mask
		{
			MASK_Red   = 1UL << 3,
			MASK_Green = 1UL << 2,
			MASK_Blue  = 1UL << 1,
			MASK_Alpha = 1UL << 0,
			MASK_All   = MASK_Red | MASK_Green | MASK_Blue | MASK_Alpha
		};

		static const ColorRGB Red;		// ��
		static const ColorRGB Green;	// ��	
		static const ColorRGB Blue;		// ��
		static const ColorRGB White;	// ��
		static const ColorRGB Black;	// ��

	public:
		// Constructors
		FORCEINLINE ColorRGB() {}

		// Constructors
		FORCEINLINE ColorRGB( FLOAT inR, FLOAT inG, FLOAT inB, FLOAT inA=1.f)
			: r( inR) , g( inG), b( inB), a( inA)
		{ }

		// Constructors
		FORCEINLINE ColorRGB( int inR, int inG, int inB, int inA=255)
		{
			const FLOAT f = 1.0f / 255.f;

			r = f * (FLOAT)(BYTE)( inR);
			g = f * (FLOAT)(BYTE)( inG);
			b = f * (FLOAT)(BYTE)( inB);
			a = f * (FLOAT)(BYTE)( inA);
		}

		// ��������� "="
		FORCEINLINE ColorRGB( DWORD dw)
		{
			const FLOAT f = 1.0f / 255.f;

			r = f * (FLOAT)(BYTE)(dw >> 16);
			g = f * (FLOAT)(BYTE)(dw >>  8);
			b = f * (FLOAT)(BYTE)(dw >>  0);
			a = f * (FLOAT)(BYTE)(dw >> 24);
		}

		// ת��ΪDWORD
		FORCEINLINE DWORD ToDWORD() const
		{
			DWORD dwR = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (DWORD) (r * 255.0f + 0.5f);
			DWORD dwG = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (DWORD) (g * 255.0f + 0.5f);
			DWORD dwB = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (DWORD) (b * 255.0f + 0.5f);
			DWORD dwA = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (DWORD) (a * 255.0f + 0.5f);

			return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
		}


		// ��������� "="
		FORCEINLINE void operator = ( const ColorRGB& c)
		{
			r=c.r;  g=c.g; b=c.b; a=c.a;
		}

		// ��������� "/"
		FORCEINLINE ColorRGB operator / (FLOAT scale) const
		{
			FLOAT rScale = 1.f / scale;

			return ColorRGB( r*rScale, g*rScale, b*rScale, a*rScale);
		}

		// ��������� "*"
		FORCEINLINE ColorRGB operator*( FLOAT scale) const
		{
			return ColorRGB( r*scale, g*scale, b*scale, a*scale);
		}

		// ��������� "+="
		ColorRGB operator += (const ColorRGB& c)
		{
			r+=c.r; g+=c.g; b+=c.b; a+=c.a;

			return *this;
		}

		// ��������� "!="
		UBOOL operator != ( const ColorRGB& c) const
		{
			return r!=c.r || g!=c.g || b!=c.b || a!=c.a;
		}

		// ��������� "*="
		ColorRGB operator *= ( FLOAT scale)
		{
			r*=scale; g*=scale; b*=scale; a*=scale;

			return *this;
		}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & r & g & b & a;
		}

	public:
		FLOAT r, g, b, a;		// ��ɫͨ��
	};

 	//----------------------------------------
 	//  CoordinateSystem 2012-5-15 ����
 	//----------------------------------------
	class CoordinateSystem
	{
	public:
		// Constructors
		FORCEINLINE CoordinateSystem() {}

		// Constructors
		FORCEINLINE CoordinateSystem( const Vector3& origin, const Vector3& axisX, const Vector3& axisY, const Vector3& axisZ)
			: m_origin( origin) , m_axisX( axisX), m_axisY( axisY), m_axisZ( axisZ)
		{}

		// Constructors (LH)
		FORCEINLINE void FromMatrixLH( const Matrix44& world, bool normalize=true)
		{
			m_origin = Vector3( world._41, world._42, world._43);

			m_axisX  = Vector3( world._11, world._12, world._13) + m_origin;
			m_axisY  = Vector3( world._21, world._22, world._23) + m_origin;
			m_axisZ  = Vector3( world._31, world._32, world._33) + m_origin;

			if( normalize)
			{
				m_axisX.Normalize();
				m_axisY.Normalize();
				m_axisZ.Normalize();
			}
		}

	public:
		Vector3		m_origin;	// ԭ��
		Vector3		m_axisX;	// x����
		Vector3		m_axisY;	// y����
		Vector3		m_axisZ;	// z����
	};

	//  Calculate normal
	void TBNComputeNormal( Vector3* normals, const Vector3* positions, int numVertex, const int* tris, int numTris);

	// Calculate normal
	void TBNComputeNormal( Vector3* normals, const Vector3* positions, int numVertex, const WORD* tris, int numTris);

	//  Calculate tangent binormal
	void TBNComputeTangentBinormal( Vector3* tangents, Vector3* binormals, const Vector3* positions, const Vector2* uvs, const Vector3* normals, int numVertex, const int* tris, int numTris);

	//------------------------------------
	// Int3 2013-4-26 ����
	//------------------------------------
	class Int2
	{
	public:
		// Constructors
		FORCEINLINE Int2() {}
		FORCEINLINE Int2( INT inX, INT inY) 
		{
			v[0] = inX; 
			v[1] = inY; 
		}

		// ����"[]" const
		INT operator[]( INT i) const
		{
			assert( i>=0);
			assert( i<2);

			return v[i];
		}

		// ����"[]" 
		INT& operator[]( INT i)
		{
			assert( i>=0);
			assert( i<2);

			return v[i];
		}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & x;
			ar & y;
		}

	public:
		union
		{
			struct 
			{
				INT x, y;
			};

			struct 
			{
				INT v[2];
			};
		};

	};

	//------------------------------------
	// Int3 2013-4-26 ����
	//------------------------------------
	class Int3
	{
	public:
		// Constructors
		FORCEINLINE Int3() {}
		FORCEINLINE Int3( INT inX, INT inY, INT inZ) 
		{
			v[0] = inX; 
			v[1] = inY; 
			v[2] = inZ; 
		}

		// ����"[]" const
		INT operator[]( INT i) const
		{
			assert( i>=0);
			assert( i<3);

			return v[i];
		}

		// ����"[]" 
		INT& operator[]( INT i)
		{
			assert( i>=0);
			assert( i<3);

			return v[i];
		}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & x;
			ar & y;
			ar & z;
		}

	public:
		union
		{
			struct 
			{
				INT x, y, z;
			};

			struct 
			{
				INT v[3];
			};
		};
		
	};

	//------------------------------------
	// Int4 2013-4-26 ����
	//------------------------------------
	struct Int4
	{
	public:
		// ����"[]" const
		INT operator[]( INT i) const
		{
			assert( i>=0);
			assert( i<4);

			return v[i];
		}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & v[0] & v[1] & v[2] & v[3];
		}

	public:
		INT v[4];
	};
}

#include "AresMath.inl"