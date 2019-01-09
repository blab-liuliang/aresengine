#include <Engine/RenderSystem/AresFXAA.h>
#include <boost/lexical_cast.hpp>
#include <Engine/AresRoot.h>

namespace Ares
{
	// ���캯��
	FXAA::FXAA(  Scene& scene)
		: FrameFilter( scene)
	{
		// ����Renderable����
		m_renderable.SetRenderlayout( FrameFilter::GetScreenQuadRenderLayout());

		m_srcTexture = MakeShaderParam();
	}

	// ���ò���
	void FXAA::Set( FXAALevel level)
	{
		// ��ʼ������
		ShaderMacros macros;
		macros.push_back( ShaderMacro( "FXAA_PRESET", boost::lexical_cast<string>(level).c_str()));
		RenderMethodPtr rMethod = AResSystem.LoadMethod("FXAA.hlsl");
		m_renderable.GetMaterial()->SetMethod( rMethod);

		m_renderable.GetMaterial()->SetParamRef( "G_WindowWH", m_scene.GetRenderSystem().GetSPABWindowWH());
		m_renderable.GetMaterial()->SetParamRef( "G_DiffuseTex", m_srcTexture);
	}

	// ����Դ����
	bool FXAA::SetSrcTexture( TexturePtr& src)
	{
		*m_srcTexture = src;

		return true;
	}
}