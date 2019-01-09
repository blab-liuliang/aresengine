#pragma once

#include "AresMesh.h"
#include <Core/Graphics/AresRenderMaterial.h>
#include "SuperMaterialCompiler.h"

namespace Ares
{
	// SuperMaterialUsage
	enum SuperMaterialUsage
	{
		SMU_OutputDiffuse   = 1<<0,
		SMU_OutputNormal    = 1<<1,
		SMU_OutputDepth		= 1<<2,
		SMU_StaticLighting	= 1<<3,
		SMU_SkeletalMesh	= 1<<4,
		SMU_Total			= 5,
	};

	//-------------------------------------
	// �������� 2012-12-19 ����
	//-------------------------------------
	class SuperMaterial : public RenderMaterial
	{
	public:
		struct IDCard
		{
			// ����
			struct Parameter
			{
				string	m_name;					// ��������
				string	m_type;					// ��������
				string	m_value;				// ����ֵ

				// ���캯��
				Parameter() {}
				Parameter( const char* name, const char* type, const char* value)
					: m_name( name), m_type( type), m_value( value)
				{}

				// ���л�
				template <typename Archive> void serialize( Archive& ar, const unsigned int version)
				{
					ar & m_name;
					ar & m_type;
					ar & m_value;
				}
			};

			BITFIELD				m_renderQueue;				// ��Ⱦ����
			string					m_shader;					// shader
			vector<Parameter>		m_parameters;				// ����
			DepthStencilStateDesc	m_depthStencilStateDesc;	// ���ģ��״̬

			// ��ȡֵ
			Parameter* Parameters( const string& name);

			// �س�ʼ������
			void ReBuildSuperMaterial( SuperMaterial& superMaterial, QWORD usage);

			// ���л�
			template <typename Archive> void serialize( Archive& ar, const unsigned int version)
			{
				ar & m_renderQueue;
				ar & m_shader;
				ar & m_parameters;
				ar & m_depthStencilStateDesc;
			}
		};
		typedef s_ptr<IDCard> IDCardPtr;

	public:
		// Constructors
		SuperMaterial();

		/** Get vertex stream flag that the material used
		 */
		UINT GetVertexStreamFlag();

		// Set the shadertree path
		void SetShaderTreePath( const char* path);

		/**	Sets the given usage flag
		 *	@param  usage			 - The usage flag to set
		 *	@return BOOL			 - TURE if the material can be used for rendering with the given type
		 */
		void SetUsage( QWORD usage) { m_usage = usage; }

		/** Gets the value associated with the given usage flag. */
		QWORD GetUsage( SuperMaterialUsage usage) const { return m_usage; }

		/** Compiles shader for the given platform*/
		void Compile();

	public:
		// Get ztest mask texture
		ShaderParamPtr GetZTestMaskTexture();

	private:
		// Generate Shader By ShaderTree
		string GenerateShaderByShaderTree( const char* shaderTreePath);

	public:
		QWORD						m_usage;						// ����
		//BITFIELD					m_bOutputDiffuse:1;					// ���������
		//BITFIELD					m_bOutputNormal:1;					// �������
		BITFIELD					m_bOutputDepth:1;					// ������

		BITFIELD					m_bUsedWithStaticLighting:1;		// ��̬����
		BITFIELD					m_bUsedWithSkeletalMesh:1;			// ��������
		BITFIELD					m_bUsedAsSpecialEngineMaterial:1;
		BITFIELD					m_bWireframe:1;						// ������ʾ
		BITFIELD					m_bFallbackMaterial:1;				// �Ƿ�Ϊ��ȴ����

		string						m_shadertreePath;					// ������·��
		SMShaderTreePtr				m_shaderTree;						// ������
	};
	typedef s_ptr<SuperMaterial> SuperMaterialPtr;
}