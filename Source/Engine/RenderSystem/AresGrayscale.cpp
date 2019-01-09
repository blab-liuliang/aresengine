#include <Engine/AresRoot.h>
#include <Engine/RenderSystem/AresGrayscale.h>

namespace Ares
{
	// ���캯��
	GrayscaleFilter::GrayscaleFilter( Scene& scene)
		: FrameFilter( scene)
	{
		// ����Renderable����
		m_renderable.SetRenderlayout( FrameFilter::GetScreenQuadRenderLayout());

		// ��ʼ����?
        RenderMethodPtr rMethod = AResSystem.LoadMethod("Grayscale.hlsl");
		m_renderable.GetMaterial()->SetMethod( rMethod);
	}

	// ����Դ����
	bool GrayscaleFilter::SetSrcTexture( TexturePtr& src)
	{
		ShaderParamPtr tParam = MakeShaderParam( src);
		//tParam->SetSamplerState( ARenderDevice->CreateSamplerState( SamplerStateDesc()));
		m_renderable.GetMaterial()->SetParamRef( "DiffuseTex", tParam);

		return true;
	}
}