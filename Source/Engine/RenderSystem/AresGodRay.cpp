#include <Engine/AresRoot.h>
#include <Engine/RenderSystem/AresGodRay.h>
#include <Core/Graphics/AresRenderView.h>

namespace Ares
{
	// ���캯��
	GodRay::GodRay(  size_t width, size_t height, Scene& scene)
		: FrameFilter( scene)
		, m_gBufferWidth( 0)
		, m_gbufferheight( 0)
	{
		// ����Renderable����
		m_renderable.SetRenderlayout( FrameFilter::GetScreenQuadRenderLayout());

		// ��ʼ������
		RenderMaterialPtr material( new_ SuperMaterial);
        RenderMethodPtr   rMethod = AResSystem.LoadMethod("GodRay.hlsl");
		material->SetMethod( rMethod);

		// ����
		SamplerStateDesc ssDesc;
		ssDesc.m_addrModeU = TAM_Clamp;
		ssDesc.m_addrModeV = TAM_Clamp;
		ssDesc.m_addrModeW = TAM_Clamp;
		m_spWrapSampler = MakeShaderParam( ARenderDevice->CreateSamplerState( ssDesc));
		material->SetParamRef( "WrapSampler", m_spWrapSampler);


		m_spGodCenter  = MakeShaderParam();
		m_spGodTexture = MakeShaderParam();

		material->SetParamRef( "GodTexture", m_spGodTexture);
		material->SetParamRef( "GodCenter",	m_spGodCenter);

		// ���״̬ 
		BlendStateDesc bDesc;
		bDesc.m_blendEnable.assign( true);
		bDesc.m_blendOp.assign( BOP_Add);
		bDesc.m_srcBlend.assign( ABF_One);
		bDesc.m_destBlend.assign( ABF_One);
		bDesc.m_blendOpAlpha.assign( BOP_Add);
		bDesc.m_srcBlendAlpha.assign( ABF_One);
		bDesc.m_destBlendAlpha.assign( ABF_Zero);
		bDesc.m_colorWriteMask.assign( ColorRGB::MASK_All);
		BlendStatePtr blendState = ARenderDevice->CreateBlendState( bDesc);
		material->SetBlendState( blendState, ColorRGB(0.f,0.f,0.f), 0xffffffff);

		DepthStencilStateDesc dDesc;
		dDesc.m_depthEnable = false;
		dDesc.m_depthWriteMask = false;
		DepthStencilStatePtr depthStencilState = ARenderDevice->CreateDepthStencilState( dDesc);
		material->SetDepthStencilState( depthStencilState);

		m_renderable.SetMaterial( material);

		Resize( width, height);
	}

	// ���Ĵ��ڴ�С
	void GodRay::Resize( size_t width, size_t height)
	{
		if( m_gBufferWidth!=width || m_gbufferheight!=height)
		{
			UINT tWidth  = static_cast<UINT>( static_cast<float>(width)/* / 4.f*/);
			UINT tHeight = static_cast<UINT>( static_cast<float>(height)/* / 4.f*/);

			m_godFrameBuffer			= ARenderDevice->CreateFrameBuffer();
			m_godTexture				= ARenderDevice->CreateTexture2D( width,   height, 1, 1, EF_ARGB8,  1, 0, EAH_GPURead | EAH_GPUWrite, NULL);
			m_godFrameBuffer->AttachRenderView( FrameBuffer::ATT_Color0, ARenderDevice->Create2DRenderView( m_godTexture, 0, 1, 0));

			m_gBufferWidth = width;
			m_gbufferheight= height;
		}
	}

	// �������Buffer
	void GodRay::BindDepthBuffer( RenderViewPtr& depth)
	{
		m_godFrameBuffer->AttachRenderView( FrameBuffer::ATT_DepthStencil, depth);
	}

	// �����ӳ���Ⱦ�׶�
	void GodRay::Process(  GodRaySource& source)
	{
		RenderElementMgr&	elementMgr = m_scene.GetRenderSystem().GetRenderElementMgr();

		// ��ձ�������
		BindDepthBuffer( source.m_depth);
		m_godFrameBuffer->Clear( ColorRGB( 0.f, 0.f, 0.f, 0.f), 1, 0, CBM_Color);

		// 1.�����GodMap
		ARenderDevice->BindFrameBuffer( m_godFrameBuffer);

		elementMgr.Render( RQ_GodRay);

		// 2.�����֡
		ARenderDevice->BindFrameBuffer( source.m_output);

		*m_spGodCenter	= source.m_center;
		*m_spGodTexture = m_godTexture;

		FrameFilter::Execute();
	}
}