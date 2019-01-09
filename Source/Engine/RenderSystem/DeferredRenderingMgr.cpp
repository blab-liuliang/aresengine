#include <Engine/AresRoot.h>

namespace Ares
{
	// ���캯��
	DeferredRenderingMgr::DeferredRenderingMgr( size_t width, size_t height, Scene& scene)
		: m_gbufferheight( INVALID)
		, m_gBufferWidth( INVALID)
		, m_scene( scene)
	{
		m_deferredLighting = MakeSharePtr( new_ DeferredLighting( scene));
		m_deferredShading  = MakeSharePtr( new_ DeferredShading( scene));
		m_gaussianBlur     = MakeSharePtr( new_ GaussianBlur( scene, true));

		m_spabOpaqueGBufferZDistance = MakeShaderParam();

		Resize( width, height);
	}

	// ��������
	DeferredRenderingMgr::~DeferredRenderingMgr()
	{

	}

	// ���Ĵ��ڴ�С
	void DeferredRenderingMgr::Resize( size_t width, size_t height)
	{
		if( m_gBufferWidth!=width || m_gbufferheight!=height)
		{
			m_opaqueGBuffer				= ARenderDevice->CreateFrameBuffer();
			m_opaqueGBufferRT0Diffuse	= ARenderDevice->CreateTexture2D( width, height, 1, 1, EF_ARGB8, 1, 0, EAH_GPURead | EAH_GPUWrite, NULL);
			m_opaqueGBufferRT1Normal	= ARenderDevice->CreateTexture2D( width, height, 1, 1, EF_ARGB8, 1, 0, EAH_GPURead | EAH_GPUWrite, NULL);
			m_opaqueGBufferZDistance	= ARenderDevice->CreateTexture2D( width, height, 1, 1, EF_R32F,  1, 0, EAH_GPURead | EAH_GPUWrite, NULL);
			m_opaqueGBuffer->AttachRenderView( FrameBuffer::ATT_Color0,	   ARenderDevice->Create2DRenderView( m_opaqueGBufferRT0Diffuse, 0, 1, 0));
			m_opaqueGBuffer->AttachRenderView( FrameBuffer::ATT_Color1,	   ARenderDevice->Create2DRenderView( m_opaqueGBufferRT1Normal, 0, 1, 0));
			m_opaqueGBuffer->AttachRenderView( FrameBuffer::ATT_Color2,	   ARenderDevice->Create2DRenderView( m_opaqueGBufferZDistance, 0, 1, 0));

			// ��ɫ������
			*m_spabOpaqueGBufferZDistance = m_opaqueGBufferZDistance;

			// ��Ȼ���
			FrameBufferPtr windowFramwBuffer = m_scene.GetRenderSystem().GetRenderWindow()->GetFrameBuffer();
			if( windowFramwBuffer)
				m_opaqueGBuffer->AttachRenderView( FrameBuffer::ATT_DepthStencil, windowFramwBuffer->GetRenderView( FrameBuffer::ATT_DepthStencil));

			m_lightingBuffer			= ARenderDevice->CreateFrameBuffer();
			m_lightingTexture			= ARenderDevice->CreateTexture2D( width, height, 1, 1, EF_ABGR16F, 1, 0, EAH_GPURead | EAH_GPUWrite, NULL);
			m_lightingBuffer->AttachRenderView( FrameBuffer::ATT_Color0,   ARenderDevice->Create2DRenderView( m_lightingTexture, 0, 1, 0));

			m_gBufferWidth = width;
			m_gbufferheight= height;
		}
	}

	// ִ�й��ս׶�
	void DeferredRenderingMgr::ExecLightingPhase( const vector<Light*>& lights, const LightPtr& dominantLight)
	{
		// ���Ϊ��ɫ
		m_lightingBuffer->Clear( ColorRGB::Black, 1, 0, CBM_Color);

		// ��LightingBuffer
		ARenderDevice->BindFrameBuffer( m_lightingBuffer);

		m_deferredLighting->SetInput( m_opaqueGBufferRT1Normal, m_opaqueGBufferZDistance, lights, dominantLight);

		m_deferredLighting->Execute();
	}

	// ִ����ɫ�׶�
	void DeferredRenderingMgr::ExecShadingPhase()
	{
		// ���ս������ģ������
		// m_gaussianBlur->SetInput( m_lightingTexture, m_lightingTexture, GaussianBlur::WeightTable1x49, 49);
		// m_gaussianBlur->Execute();

		// ��ӹ���Ч��
		m_deferredShading->SetInput( m_opaqueGBufferRT0Diffuse, m_opaqueGBufferRT1Normal, m_lightingTexture, m_opaqueGBufferZDistance);
		m_deferredShading->Execute();
	}

	// �����ӳ���Ⱦ�׶�
	void DeferredRenderingMgr::BeginDeferredPhase( const ColorRGB& gbufferbackcolor)
	{
		float maxDistance  = m_scene.GetCameraSystem().GetFar();
		ColorRGB clearColor0( gbufferbackcolor.r, gbufferbackcolor.g, gbufferbackcolor.b, 0.f);
		ColorRGB clearColor1( maxDistance, maxDistance, maxDistance, maxDistance);

		// ��GBuffer
		ARenderDevice->BindFrameBuffer( GetOpaqueGBuffer());
		GetOpaqueGBuffer()->Clear( clearColor0, 1, 0);
		GetOpaqueGBuffer()->ClearMRTColor( clearColor0, FrameBuffer::ATT_Color1);
		GetOpaqueGBuffer()->ClearMRTColor( clearColor1, FrameBuffer::ATT_Color2);
	}

	// �����ӳ���Ⱦ�׶�
	void DeferredRenderingMgr::EndDeferredPhase( const FrameBufferPtr& output, const vector<Light*>& lights, const LightPtr& dominantLight)
	{
		// 1.ִ�й��ս׶�
		ExecLightingPhase( lights, dominantLight);

		// 2.��ԭFrameBuffer
		ARenderDevice->BindFrameBuffer( output); 

		// 3.��ɫ�׶�
		ExecShadingPhase();
	}
}