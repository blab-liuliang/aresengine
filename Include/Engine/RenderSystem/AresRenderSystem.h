#pragma once

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <Core/Graphics/AresRenderWindow.h>
#include <Core/Graphics/AresRenderDevice.h>
#include "Engine/Foundation/Ares3DEngine_h.h"
#include "Engine/RenderSystem/DeferredRenderingMgr.h"
#include "Engine/RenderSystem/AresPostProcessChain.h"
#include "Engine/RenderSystem/AresGrayscale.h"
#include "Engine/RenderSystem/AresSpaceDistorted.h"
#include "Engine/RenderSystem/AresFXAA.h"
#include "Engine/RenderSystem/AresToneMapping.h"
#include <Engine/UISystem/MyGUI_RTTexture.h>

using namespace std;
using namespace boost;

namespace Ares
{
	//------------------------------------------
	// RenderSystem 2011-08-04 ����
	// Plugin Interfaces of RenderSystem
	//------------------------------------------
	class IImageProcessManager;
	class ILightManager;
	class VisualShapeMgr;
	class ARES_EXPORT RenderSystem
	{
	public:
		static ShaderParamPtr  SPAB_SunDirection;		// ����⳯��
		static ShaderParamPtr  SPAB_ScreenWidthHeight;	// ��Ļ���

	public:
		// ���캯��
		RenderSystem( Scene& scene);
		~RenderSystem();

		// LoadRenderFactory, Unique
		BOOL LoadRenderFactory( const RenderSettings& settings);

		// ��ȡ��Ⱦ����
		RenderWindow* GetRenderWindow() { return m_renderWindow; }

		// ���Ĵ��ڴ�С
		void ResizeWindow( size_t width, size_t height);

		// ����
		void FrameMove( float elapsedTime);

		// ִ����Ⱦ
		void Render();

		// �ύ��ȾԪ��
		signal<void()> Signal_OnSubmitRenderElements;

	public:
		// ��ȡ��Ⱦ����
		const RenderSettings& GetRenderSettings() const { return m_renderSettings; }

		// Ӧ����Ⱦ����
		void ApplyRenderSettings( const RenderSettings& settings);

		// ��ȡ�ӳ���Ⱦ������ָ��
		const DeferredRenderingMgrPtr& GetDeferredRenderingMgr() { return m_deferredRenderingMgr; }

		// ��ȡ���������
		PostProcessChainPtr& GetPostProcessChain() { return m_postProcessChain; }

		// ��ȡ��Դ������
		ILightManager* GetLightManager(){ return NULL; }

		// ��ȡ��Ⱦ���й�����
		RenderElementMgr& GetRenderElementMgr() { return m_renderElementMgr; }

		// VisualShapeMgr
		VisualShapeMgr& GetVisualShapeMgr() { return *m_visualShapeMgr; }

		// ��ȡȫ��Shader����
		ShaderParamPtr GetSPABWaterRefraction() { return m_spabWaterRefraction; }

		// ��ȡ���ڿ��
		ShaderParamPtr GetSPABWindowWH()	{ return m_spabWindowWH; }

	private:
		// ��ʼ���ӳ���Ⱦ������
		void InitRenderingMgr( size_t width, size_t height);

		// ������(���л�)
		void ExportClass();

		// ��֯��ȾԪ��
		void OrganizeRenderElements();

	private:
		RenderSettings			m_renderSettings;		// ��Ⱦ����
		RenderWindow*			m_renderWindow;			// ��Ⱦ����
		RenderElementMgr		m_renderElementMgr;		// ��Ⱦ���й�����
		DeferredRenderingMgrPtr	m_deferredRenderingMgr;	// �ӳ���Ⱦ������
		PostProcessChainPtr		m_postProcessChain;		// ���������
		VisualShapeMgr*			m_visualShapeMgr;		// ���������������
		GrayscaleFilter*		m_grayScaleFilter;		// �ڰ��˾�
		SpaceDistorted*			m_spaceDistortedFilter;	// �ռ�Ť���˾�
		FXAA*					m_FXAA;					// �����
		ToneMappingPtr			m_toneMapping;			// ɫ��ӳ��
		MyGUI::MyGUIRTTexture*	m_uiRTTexture;			// UI��Ⱦ
		Scene&					m_scene;				// ����

		ShaderParamPtr			m_spabWaterRefraction;	// ������ͼ
		ShaderParamPtr			m_spabWindowWH;		// ���ڿ��
	};
}