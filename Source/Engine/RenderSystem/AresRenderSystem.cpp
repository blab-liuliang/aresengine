#include <Engine/RenderSystem/AresVisualShape.h>
#include <Engine/FxSystem/AresFx3DPatch.h>
#include <Engine/FxSystem/AresFxParticleSystem.h>
#include <Engine/UISystem/MyGUI_LayoutManager.h>
#include <Engine/UISystem/AresUISystem.h>
#include <Core/AresPlatform.h>
#include "Engine/AresRoot.h"

namespace Ares
{
	ShaderParamPtr  RenderSystem::SPAB_SunDirection;
	ShaderParamPtr  RenderSystem::SPAB_ScreenWidthHeight;

	// ����RenderFactory, Unique
	BOOL RenderSystem::LoadRenderFactory( const RenderSettings& settings)
	{
		if( ARenderDevice)
		{
			// ��¼��Ⱦ����
			m_renderSettings = settings;

			ARenderDevice->SetLogSystem( &ALogSystem);

			// ��������
			m_renderWindow = ARenderDevice->CreateRenderWindow( settings);

			// ��ʼ���ӳ���Ⱦ������
			InitRenderingMgr( settings.m_width, settings.m_height);

			// ������
			ExportClass();

			*SPAB_ScreenWidthHeight = Vector2( 1.f/settings.m_width, 1.f/settings.m_height);

			// Ӧ������
			ApplyRenderSettings( settings);

			return TRUE;
		}

		ALogSystem.Error( "RenderDevice Has Not Been Initialized!");

		return FALSE;
	}

	// ���캯��
	RenderSystem::RenderSystem( Scene& scene)
		: m_uiRTTexture( NULL)
		, m_renderWindow( NULL)
		, m_scene( scene)
	{
		Vector3 sunDir( -0.5f, -0.5f, -0.5f);
		sunDir.Normalize();
		SPAB_SunDirection		= MakeShaderParam( sunDir);
		SPAB_ScreenWidthHeight	= MakeShaderParam();
		m_spabWaterRefraction   = MakeShaderParam();
		m_spabWindowWH			= MakeShaderParam( float4( 1024.f, 768.f, 1.f/1024.f, 1.f/768.f));

		m_visualShapeMgr		= new_ VisualShapeMgr( m_scene);	 
	}

	// ��������
	RenderSystem::~RenderSystem()
	{
		SAFE_DELETE( m_FXAA);
	}

	// ��ʼ���ӳ���Ⱦ������
	void RenderSystem::InitRenderingMgr( size_t width, size_t height)
	{
		m_deferredRenderingMgr	= MakeSharePtr( new_ DeferredRenderingMgr( width, height, m_scene));
		m_postProcessChain		= MakeSharePtr( new_ PostProcessChain( width, height, m_scene));

		// ����
		m_grayScaleFilter		= new_ GrayscaleFilter( m_scene);
		m_spaceDistortedFilter	= new_ SpaceDistorted( m_scene);
		m_FXAA					= new_ FXAA( m_scene);
		m_toneMapping			= MakeSharePtr( new_ ToneMapping( m_scene));

		m_FXAA->Set( m_renderSettings.m_fxaa);
	}

	// ������(���л�)
	void RenderSystem::ExportClass()
	{
		Fx3DPatch			patch;
		FxParticleSystem	particle;
	}

	// ���Ĵ��ڴ�С
	void RenderSystem::ResizeWindow( size_t width, size_t height)
	{
		if( m_renderSettings.m_width!=width || m_renderSettings.m_height!=height)
		{
			// ���ڴ�С����
			m_renderWindow->Resize( width, height);

			// �ӳ���ȾGBuffer����
			m_deferredRenderingMgr->Resize( width, height);

			// �����в���Buffer����
			m_postProcessChain->Resize( width, height);

			m_renderSettings.m_width = width;
			m_renderSettings.m_width = height;

			if( m_renderSettings.m_useMyGUI)
			{
				// ��Ⱦ����
				m_uiRTTexture = new_ MyGUI::MyGUIRTTexture(  m_renderWindow->GetFrameBuffer());
				*SPAB_ScreenWidthHeight = Vector2( 1.f/width, 1.f/height);
			}

			*m_spabWindowWH  = float4( float(width), float(height), 1.f/float(width), 1.f/float(height));
		}
	}

	// Ӧ����Ⱦ����
	void RenderSystem::ApplyRenderSettings( const RenderSettings& settings)
	{
		// FXAA
		if( m_renderSettings.m_fxaa != settings.m_fxaa)
		{
			m_renderSettings.m_fxaa = settings.m_fxaa;
			m_FXAA->Set( m_renderSettings.m_fxaa);
		}

		// Tonemapping
		if( m_renderSettings.m_toneMapping != settings.m_toneMapping)
		{
			m_renderSettings.m_toneMapping = settings.m_toneMapping;
		}
	}

	// ��֯��ȾԪ��
	void RenderSystem::OrganizeRenderElements()
	{
		m_renderElementMgr.Reset();

		m_visualShapeMgr->SubmitRenderElements( m_renderElementMgr);

		Signal_OnSubmitRenderElements();
	}

	// ����
	void RenderSystem::FrameMove( float elapsedTime)
	{
		m_visualShapeMgr->FrameMove();
	}

	// ִ����Ⱦ
	void RenderSystem::Render()
	{
		A_ASSERT( m_renderWindow);

		//MyGUI::AUiLayerMgr.resizeView( MyGUI::IntSize( m_renderSettings.m_width, m_renderSettings.m_height));
		CameraSystem& cameraSystem = m_scene.GetCameraSystem();

		// ��֯��Ⱦ����
		OrganizeRenderElements();

		if( ARenderDevice->GetType() == D3D11)
		{
			ARenderDevice->BeginFrame();

			const vector<Light*>&		lights		= m_renderElementMgr.GetLights();
			const DirectionalLightPtr&  domainLight = m_renderElementMgr.GetDomainLight();

			// �ӳ���Ⱦ
			{
				// ����Shadowmap
				if( domainLight)
				{
					Frustum3 frustum100 = *cameraSystem.GetFrustum();
					domainLight->GetCSMMgr()->RefreshShadowMaps( frustum100, 3);
				}

				m_deferredRenderingMgr->BeginDeferredPhase( ColorRGB( 0.298f, 0.298f,0.322f));

				m_renderElementMgr.Render( RQ_Sky);
				m_renderElementMgr.Render( RQ_Opacity);
				m_renderElementMgr.Render( RQ_Terrain);

				m_deferredRenderingMgr->EndDeferredPhase( m_renderWindow->GetFrameBuffer(), lights, domainLight);	
			}

			// ��Ⱦˮ, ����������ͼ
			if( !m_renderElementMgr.IsEmpty( RQ_Water))
			{
				*m_spabWaterRefraction = m_renderWindow->GetBackbufferTextureCopy();
				m_renderElementMgr.Render( RQ_Water);
			}

			// ��͸������,�Լ��������
			m_renderElementMgr.Render( RQ_TransparentEffect);

			// ������ʾ
			if( m_renderSettings.m_auxiliaryDisplay)
				m_renderElementMgr.Render( RQ_AuxiliaryDisplay);

			{
			//	/* ����
			//	if( Logic_ModelEdit->GetCurrEntity())
			//	{
			//		vector<EntityPtr> entitys;
			//		entitys.push_back( Logic_ModelEdit->GetCurrEntity());
			//		RenderViewPtr depthView = ADeferredRenderingMgr->GetOpaqueGBuffer()->GetRenderView( FrameBuffer::ATT_DepthStencil);
			//		APostProcessChain->GetFloodColor()->Process( entitys, depthView, ARenderDevice->GetRenderWindow()->GetFrameBuffer());
			//	}*/
			}

			// �ϵ�����
			if( domainLight && domainLight->IsUseLightShaft())
			{
				float2 lightcoord = domainLight->GetShaftCenterCoord();
				if( lightcoord.x>-0.2f && lightcoord.x<1.2f && lightcoord.y>-0.2f && lightcoord.y<1.2f)
				{
					GodRaySource source;
					source.m_entity = domainLight->GetLightShaft();
					source.m_output = m_renderWindow->GetFrameBuffer();
					source.m_depth	= m_deferredRenderingMgr->GetOpaqueGBuffer()->GetRenderView( FrameBuffer::ATT_DepthStencil);
					source.m_center = lightcoord;

					m_postProcessChain->GetGodRayPostProcess()->Process( source);
				}
			}

			// �ռ�Ť��
			if( !m_renderElementMgr.IsEmpty( RQ_SpaceDistorted) && m_renderSettings.m_spaceDistorted)
			{
				// 2.׼���ռ�Ť��ͼƬ
				ARenderDevice->BindFrameBuffer( m_spaceDistortedFilter->GetDistortedFrameBuffer());
				m_spaceDistortedFilter->GetDistortedFrameBuffer()->Clear( ColorRGB( 0.f, 0.f, 0.f, 0.f), 1, 0, CBM_Color);

				m_renderElementMgr.Render( RQ_SpaceDistorted);

				ARenderDevice->BindFrameBuffer( m_renderWindow->GetFrameBuffer());

				// ִ�пռ�Ť��
                TexturePtr backBuffer = m_renderWindow->GetBackbufferTextureCopy();
				m_spaceDistortedFilter->SetSrcTexture( backBuffer);
				m_spaceDistortedFilter->Execute();
			}

			// GrayScale
			//if( m_grayScaleFilter)
			//{
			//	// ִ�пռ�Ť��
			//	m_grayScaleFilter->SetSrcTexture( m_renderWindow->GetBackbufferTextureCopy());
			//	m_grayScaleFilter->Execute();
			//}

			//  FXAA
			if( m_renderSettings.m_fxaa != FXAA_Off)
			{	
				m_FXAA->SetSrcTexture( m_renderWindow->GetBackbufferTextureCopy());
				m_FXAA->Execute();
			}

			// ToneMapping
			if( m_renderSettings.m_toneMapping!=TML_Off)
			{
				m_toneMapping->SetSrcTexture( m_renderWindow->GetBackbufferTextureCopy(), m_renderWindow->GetFrameBuffer());
				m_toneMapping->Execute();
			}

			// ������Ⱦ
			if( m_renderSettings.m_useMyGUI)
			{
				if( m_uiRTTexture)
					AUiSystem.Render( m_uiRTTexture);
			}
		
			// ������Ⱦ
			m_renderWindow->SwapBuffers();

			ARenderDevice->EndFrame();
		}
		else
		{
			ARenderDevice->BeginFrame();

			ARenderDevice->BindFrameBuffer( m_renderWindow->GetFrameBuffer());
			m_renderWindow->GetFrameBuffer()->Clear( ColorRGB( 0.298f, 0.298f,0.322f), 1, 0);

			m_renderElementMgr.Render( RQ_AuxiliaryDisplay);

			m_renderWindow->SwapBuffers();

			ARenderDevice->EndFrame();
		}
	}
}