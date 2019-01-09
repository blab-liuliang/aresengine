#include <Engine/RenderSystem/ZRenderable.h>
#include <Engine/AresRoot.h>

namespace Ares
{
	// ���캯��
	ZRenderable::ZRenderable( bool isZTest)
	{
		ShaderMacros macros;
		if( isZTest)
			macros.push_back( ShaderMacro("ZTESTSUPPORT", ""));

        RenderMethodPtr rMethod = AResSystem.LoadMethod("ZPrestatic.hlsl", macros);
		m_material.SetMethod( rMethod);

		m_worldViewProj = MakeShaderParam();
		m_material.SetParamRef( "WorldViewProj", m_worldViewProj);

		if( isZTest)
		{
			m_maskTexture   = MakeShaderParam();
			m_material.SetParamRef( "G_DiffuseTex", m_maskTexture);
		}
	}

	// ��������
	ZRenderable::~ZRenderable()
	{

	}

	// ��������
	void ZRenderable::SetMaskTexture( ShaderParamPtr mask)
	{
		*m_maskTexture = *(mask->m_texture);
	}

	// ��Ⱦ
	void ZRenderable::Render( const Matrix44& worldViewProj)
	{
		*m_worldViewProj = worldViewProj;

		if( m_layout && m_material.GetMethod())
		{
			ARenderDevice->Render( m_layout.get(), &m_material);
		}
	}
}