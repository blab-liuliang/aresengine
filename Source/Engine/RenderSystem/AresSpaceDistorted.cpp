#include <Engine/AresRoot.h>
#include <Engine/RenderSystem/AresSpaceDistorted.h>

namespace Ares
{
	// ���캯��
	SpaceDistorted::SpaceDistorted( Scene& scene)
		: FrameFilter( scene)
	{
		// ����Renderable����
		m_renderable.SetRenderlayout( FrameFilter::GetScreenQuadRenderLayout());

		// ��ʼ����?
        RenderMethodPtr rMethod = AResSystem.LoadMethod("SpaceDistorted.hlsl");
		m_renderable.GetMaterial()->SetMethod( rMethod);

		// ����DistortedTexture DistortedFrameBuffer
		const RenderWindow* window = m_scene.GetRenderSystem().GetRenderWindow();
		m_distortedFrameBuffer	= ARenderDevice->CreateFrameBuffer();
		m_distortedTexture	= ARenderDevice->CreateTexture2D( window->GetWidth(), window->GetHeight(), 1, 1, EF_ARGB8, 1, 0, EAH_GPURead | EAH_GPUWrite, NULL);
		m_distortedFrameBuffer->AttachRenderView( FrameBuffer::ATT_Color0,	   ARenderDevice->Create2DRenderView( m_distortedTexture, 0, 1, 0));
	};

	// ����Դ����
	bool SpaceDistorted::SetSrcTexture( TexturePtr& src)
	{
		ShaderParamPtr tParam = MakeShaderParam( src);
		m_renderable.GetMaterial()->SetParamRef( "DiffuseTex", tParam);

		ShaderParamPtr tDistorted = MakeShaderParam( m_distortedTexture);
		m_renderable.GetMaterial()->SetParamRef( "DistortedTex", tDistorted);

		return true;
	}
}