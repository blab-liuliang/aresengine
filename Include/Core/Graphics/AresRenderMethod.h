#pragma once

#include "AresRenderState.h"
#include "AresRenderAPITypedefs.h"

using namespace std;

namespace Ares
{
	// ��������ö��
	enum ShaderParamType
	{
		SPT_Invalid = 0,
		SPT_FloatArray,
		SPT_Texture,
		SPT_SamplerState,
	};

	//----------------------------------
	// ShaderParamDesc 2012-4-11 ����
	//----------------------------------
	struct ShaderParamDesc
	{
		std::string		m_name;
		ShaderParamType	m_type;

		// ���رȽ������
		FORCEINLINE UBOOL operator == ( const ShaderParamDesc& spd) const
		{
			return m_name==spd.m_name && m_type==spd.m_type;
		}
	};
	typedef vector<ShaderParamDesc> ShaderParamDescs;

	//------------------------------------
	// RM::Variant 2012/4/27 ����
	//------------------------------------
	class ShaderParam
	{
	public:
		// constructor
		ShaderParam();
		~ShaderParam();

		// ��������� "="
		void operator = ( float val);

		// ��������� "="
		void operator = ( const vector<float>& val);

		// ��������� "="
		void operator = ( const float2& val);

		// ��������� "="
		void operator = ( const float3& val);

		// ��������� "="
		void operator = ( const float4& val);

		// ��������� "="
		void operator = ( const vector<float4>& val);

		// ��������� "="
		void operator = ( const ColorRGB& val);

		// ��������� "="
		void operator = ( const float4x4& val);

		// ��������� "="
		void operator = ( const vector<float4x4>& val);

		// ��������� "="
		void operator = ( const TexturePtr& val);

		// ��������� "="
		void operator = ( const SamplerStatePtr& val);

		// ��������� "="
		void operator = ( const ShaderParam& v);

		// ��������� "!="
		UBOOL operator != ( const ShaderParam& v) const;

		// �Ƿ����
		bool IsValid() const { return m_type!=SPT_Invalid; }

		// �ж�����
		bool IsType( ShaderParamType type) const { return static_cast<bool>(m_type==type); }

	public:
		ShaderParamType		m_type;			// ����
		int					m_bytes;		// �ֽ���
		int					m_elems;		// Ԫ�ظ���
		union
		{
			void*			m_data;			// ����
			bool*			m_dataBool;		// ��bool��ʽ���в鿴
			int*			m_dataInt;		// ��Int��ʽ���в鿴
			float*			m_dataFloat;	// ��float��ʽ���в鿴
			TexturePtr*		m_texture;		// ����
			SamplerStatePtr*m_samplerState;	// ����״̬
		};
	};

	// Make VisualParam (Factory pattern)
	template<typename T>
	INLINE ShaderParamPtr MakeShaderParam(const T& val)
	{
		ShaderParamPtr vp = ShaderParamPtr( new_ ShaderParam);
		*vp = val;

		return vp;
	}

	// MakeShaderParam
	INLINE ShaderParamPtr MakeShaderParam()
	{
		return ShaderParamPtr( new_ ShaderParam);
	}

	//---------------------------------
	// ShaderType 2012-9-1 ����
	//---------------------------------
	enum ShaderType
	{
		ST_VertexShader  = 0,
		ST_PixelShader,
		ST_GeometryShader,
		ST_ComputeShader,
		ST_HullShader,
		ST_DomainShader,

		ST_NumShaderTypes,
	};

	// �궨��
	struct ShaderMacro
	{
		string  m_name;			// ������
		string	m_definition;	// �궨��

		// ���캯��
		ShaderMacro( const char* name, const char* definition)
			: m_name( name), m_definition( definition)
		{}
	};
	typedef vector<ShaderMacro> ShaderMacros;

	//----------------------------------
	// RenderMethod 2012-4-5 ����
	//----------------------------------
	class RenderMaterial;
	struct RenderMethod
	{
		friend class RenderMaterial;
		typedef std::vector<ShaderParamPtr>			  VisualParamPtrs;
		typedef boost::array<bool, ST_NumShaderTypes> ShaderValidateArray;

	public:
		// ���캯��
		RenderMethod();

		// ����������
		virtual ~RenderMethod() {}

		// ���غ��� *.cgfx
		virtual bool Load(  const char* fileName, const ShaderMacros& macros);

		// ���ڴ����
		virtual bool LoadFromMemory( const void* code, size_t length)=0;

		// ��
		virtual void Bind() {};

		// Ӧ�ò���
		virtual void SetParams(const RenderMaterial& mat)=0;

		// ����ByteCode
		virtual void SaveByteCode( const char* fileName, ShaderType type) {}

	public:
		// �Ƿ����
		bool IsEnabled() { return m_isEnabled; }

		// ��ȡĬ�ϲ�������
		size_t GetParamNum() { return m_curParamValues.size(); }

		// ��ȡ��������
		const ShaderParamDesc& GetParamDesc( int idx) { return m_paramDescs[idx]; }

		// ��ȡĬ�ϲ���
		const ShaderParamPtr& GetVisualParamPtr( size_t i) { return m_curParamValues[i]; }

		// ���ݲ�������ȡ��������
		bool GetParamIdx( size_t& idx, const string& paramName);

	protected:
		string					m_fileName;			// ��Դ����
		bool					m_isEnabled;			// �Ƿ����
		ShaderMacros			m_macros;			// ��
		ShaderParamDescs		m_paramDescs;		// param descs
		VisualParamPtrs			m_curParamValues;	// current param values

		bool					m_hasDiscard;
		bool					m_hasTessellation;
		ShaderValidateArray		m_isShaderValidate;

		RasterizerStatePtr		m_rasterState;		// ��դ��״̬
		DepthStencilStatePtr	m_depthStencilState;// ���״̬
		BlendStatePtr			m_blendState;		// ���״̬		
	};
}