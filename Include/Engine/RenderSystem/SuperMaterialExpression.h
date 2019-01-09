#pragma once

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <Core/AresCore.h>
#include <Core/Graphics/AresTexture.h>

using namespace std;

namespace Ares
{
	// ����
	class MaterialCompiler;
	class MaterialExpression;

	// UI����ϵ
	struct UICoordinate
	{
		Vector2		m_pos;		// �ڽ�����λ��,����������ʾ

		// ���캯��
		UICoordinate() : m_pos( 0.f, 0.f)
		{}

		// ����λ��
		void Set( int x, int y)
		{
			m_pos.x = static_cast<float>(x);
			m_pos.y = static_cast<float>(y);
		}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_pos;
		}
	};

	// ���ʽ����
	struct ExpressionInput
	{
		string				m_id;			// ��ʶ
		MaterialExpression*	m_expression;	// ���ʽ
		bool				m_mask;
		bool				m_maskR;
		bool				m_maskG;
		bool				m_maskB;
		bool				m_maskA;

		// ���캯��
		ExpressionInput();

		// ��������
		virtual ~ExpressionInput();

		// ����
		INT Compile( MaterialCompiler& compiler);

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_id;
			ar & m_mask;
			ar & m_maskR;
			ar & m_maskG;
			ar & m_maskB;
			ar & m_maskA;
		}
	};

	// ColorMaterialInput


	// ExpressionOutput
	struct ExpressionOutput
	{
		int			m_numComponents;	// ����
		float4		m_value;			// ����

		// ���캯��
		ExpressionOutput() 
		{}

		// ���캯��
		ExpressionOutput( int numComponents)
			: m_numComponents( numComponents)
		{};

		// ���ò���
		void Set( int numComponents)
		{
			m_numComponents = numComponents;
		}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_numComponents;
			ar & m_value;
		}
	};

	// ���ʽ����
	enum ExpressionType
	{
		ET_ConstantVector,
		ET_ConstantColor,
		ET_TextureSample,
	};

	//-------------------------------------------
	// MaterialExpression 2012-12-20 ����
	//-------------------------------------------
	class MaterialExpression
	{
	public:
		MaterialExpression() {}
		MaterialExpression( ExpressionType type);
        virtual ~MaterialExpression() {}

		// ��ȡ���
		const ExpressionOutput& GetOutput() const { return m_output; }

		// ��ȡ����
		virtual void GetInputs( vector<ExpressionInput*>& inputs) const=0;

		// ���� ����ChunkIndex
		virtual INT Compile( MaterialCompiler& compiler) { return INVALID; }

		// ����˵��
		virtual string GetCaption() const { return "Expression"; }

		// ��ȡID
		const string& GetID() const { return m_id; }

		// ��ȡ����
		const ExpressionType GetType() { return m_type; }

		// ��ȡλ��
		UICoordinate& GetUICoordinate() { return m_uiCoordinate; }

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_id;
			ar & m_type;
			ar & m_uiCoordinate;
			ar & m_output;
		}

	public:
		std::string			m_id;				// ��ʶ
		ExpressionType		m_type;				// ���ʽ����
		UICoordinate		m_uiCoordinate;		// �ڽ�����λ��,����������ʾ

		ExpressionOutput	m_output;			// ÿ�����ʽֻ��һ�����(����GameStart3D, ����Unreal����)
	};

	//---------------------------------
	// ���� 2013-3-12 ����
	//---------------------------------
	class MaterialExpressionConstantVector : public MaterialExpression
	{
	public:
		MaterialExpressionConstantVector() {}
		MaterialExpressionConstantVector( int numComponents);

		// ��ȡ����
		virtual void GetInputs( vector<ExpressionInput*>& inputs) const {}

		// ����
		virtual INT Compile( MaterialCompiler& compile);

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
#ifdef ARES_PLATFORM_WINDOWS
			ar & boost::serialization::base_object<MaterialExpression>(*this);
#endif
		}
	};

	//---------------------------------
	// ������ɫ 2013-3-25 ����
	//---------------------------------
	class MaterialExpressionConstantColor : public MaterialExpression
	{
	public:
		MaterialExpressionConstantColor();

		// ��ȡ����
		virtual void GetInputs( vector<ExpressionInput*>& inputs) const {}

		// ����
		virtual INT Compile( MaterialCompiler& compile);

		// ������ɫ
		void SetValue( const ColorRGB& color);

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
#ifdef ARES_PLATFORM_WINDOWS
			ar & boost::serialization::base_object<MaterialExpression>(*this);
#endif
		}
	};

	//---------------------------------
	// TextureSample 2013-3-11 ����
	//---------------------------------
	class MaterialExpressionTextureSample : public MaterialExpression
	{
	public:
		// ����
		virtual INT  Compile( MaterialCompiler& compile);

		// ����˵��
		virtual string GetCaption() const { return "Texture Sample"; }

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
#ifdef ARES_PLATFORM_WINDOWS
			ar & boost::serialization::base_object<MaterialExpression>(*this);
#endif
		}

	public:
		TexturePtr			m_texture;			// ʹ������
		ExpressionInput		m_coordinates;		// uv coordinates stream
												// ����
												// ������ʽ
	};

	//----------------------------------------------
	// MaterialExpressionConnection 2013-3-13 ����
	//----------------------------------------------
	class MaterialExpressionConnection
	{
	public:
		MaterialExpressionConnection() {}
		MaterialExpressionConnection( const string& expression, const string& input)
			: m_expression( expression), m_input( input)
		{}
	
		// ��������
		virtual ~MaterialExpressionConnection() {}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_input;
			ar & m_expression;
		}

	public:
		string		m_input;
		string		m_expression;
	};

	//---------------------------------
	// ���ʲ� 2013-3-25 ����
	//---------------------------------
	class MaterialExpressionSlot
	{
	public:
		MaterialExpressionSlot();

		// ��ȡλ��
		UICoordinate& GetUICoordinate() { return m_uiCoordinate; }

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_id;
			ar & m_uiCoordinate;
			ar & m_diffuseColor;
			ar & m_normal;
		}

	public:
		string				m_id;				// ��ʶ
		UICoordinate		m_uiCoordinate;		// �ڽ�����λ��,����������ʾ
		//ExpressionInput	m_varialbe;			// ����
		ExpressionInput		m_diffuseColor;		// ������
		ExpressionInput		m_normal;			// ����
	};
}
