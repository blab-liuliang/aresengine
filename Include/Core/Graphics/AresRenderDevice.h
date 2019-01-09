#pragma once

#include "AresTexture.h"
#include "AresRenderState.h"
#include "AresRenderWindow.h"
#include "AresFrameBuffer.h"
#include "AresRenderSettings.h"
#include "AresRenderDeviceCaps.h"
#include "AresRenderAPITypedefs.h"
#include "AresGraphicsBuffer.h"
#include "AresRenderMaterial.h"
#include "Core/AresLogSystem.h"

using namespace std;

namespace Ares
{
	//--------------------------------
	// RenderDevice 2012-02-11 ����
	//--------------------------------
	class RenderDevice
	{
		typedef map<SamplerStateDesc,    SamplerStatePtr>	 SamplerStatePool;
		typedef map<RasterizerStateDesc, RasterizerStatePtr> RasterizerStatePool;
		typedef map<BlendStateDesc,		 BlendStatePtr>		 BlendStatePool;
	public:
		RenderDevice( RenderDeviceType api);
		virtual ~RenderDevice();

		// ��ʼ֡
		virtual void BeginFrame()=0;

		// ����֡
		virtual void EndFrame()=0;

		// ������־ϵͳ
		void SetLogSystem( LogSystem* logSystem);

		// ��ȡ��־ϵͳ
		LogSystem& GetLogSystem();

		// ��ȡ����
		virtual const char* GetName() const=0;

		// ��ȡ��ǰFrameBuffer
		FrameBufferPtr GetCurFrameBuffer() const;

		// ��ȡ��ǰ��դ��״̬
		const RasterizerStatePtr GetCurRasterState() const { return m_curRasterState; } 

		// ��ȡ��ǰ���״̬
		const DepthStencilStatePtr GetCurDepthStencilState() const { return m_curDepthState; }

		// ��FrameBuffer
		void BindFrameBuffer( FrameBufferPtr frameBuffer);

		// ���ǰFrameBuffer
		void ResetFrameBuffer();

	public:
		// ������Ⱦ����
		virtual RenderWindow* CreateRenderWindow( const RenderSettings& settings);

		// ����״̬����
		void SetStateObjects();

	public:
		// ����Ч���ļ� "*.glsl"
		virtual RenderMethodPtr CreateRenderMethod()=0;

		// ����RenderLayout
		virtual RenderLayoutPtr CreateRenderLayout()=0;

		// ��������������
		virtual GraphicBufferPtr CreateIndexBuffer( BufferUsage usage, UINT accessHint, const ElementInitData* initData, ElementFormat format=EF_UnKnown)=0;

		// �������㻺����
		virtual GraphicBufferPtr CreateVertexBuffer( BufferUsage usage, UINT accessHint,const ElementInitData* initData, ElementFormat format=EF_UnKnown)=0;

		// ����1D����
		virtual TexturePtr CreateTexture1D( UINT widht, UINT numMipMaps, UINT arraySize, ElementFormat format, UINT sampleCount, UINT sampleQuality, UINT accessHine, const ElementInitData* initData)=0;

		// ����2D����
		virtual TexturePtr CreateTexture2D( UINT width, UINT height, UINT numMipMaps, UINT arraySize, ElementFormat format, UINT sampleCount, UINT sampleQuality, UINT accessHint, ElementInitData* const initData)=0;

		// ����FrameBuffer
		virtual FrameBufferPtr CreateFrameBuffer()=0;

		// �����������״̬
		virtual SamplerStatePtr CreateSamplerState( const SamplerStateDesc& desc)=0;

		// ������դ��״̬
		virtual RasterizerStatePtr& CreateRasterizerState( const RasterizerStateDesc& desc)=0;

		// �������ģ��״̬
		virtual DepthStencilStatePtr CreateDepthStencilState( const DepthStencilStateDesc& desc)=0;

		// �������״̬ 
		virtual BlendStatePtr CreateBlendState( const BlendStateDesc& desc)=0;

		// ����RenderView
		virtual RenderViewPtr Create2DRenderView( TexturePtr texture, int firstArrayIndex, int arraySize, int levle)=0;

		// �������View
		virtual RenderViewPtr Create2DDepthStencilRenderView( UINT widht, UINT height, ElementFormat format, UINT sampleCount, UINT sampleQuality)=0;

		// �������View
		virtual RenderViewPtr Create2DDepthStencilRenderView( TexturePtr& texture, int firstArrayIndex, int arraySize, int level)=0;

	public:
		// ��ȡ�豸����
		RenderDeviceType GetType() const { return m_api; }

		// ��ȡ�豸����
		const RenderDeviceCaps& GetDeviceCaps() const;

		// ��ȾRenderable
		virtual void Render(  RenderLayout* layout, RenderMaterial* material)=0;

	protected:
		RenderDeviceType		m_api;					// ��Ⱦ�豸����	
		RenderDeviceCaps		m_deviceCaps;			// �豸����
		FrameBufferPtr			m_curFrameBuffer;		// ��ǰFrameBuffer
		RasterizerStatePtr		m_curRasterState;		// ��ǰ��դ��״̬
		DepthStencilStatePtr	m_curDepthState;		// ��ǰ���״̬

		SamplerStatePool		m_ssPool;				// ��դ��״̬��
		RasterizerStatePool		m_rsPool;				// �������״̬��
		BlendStatePool			m_bsPool;				// ���״̬��
		LogSystem*				m_logSystem;			// ��־ϵͳ		
	};
    
#ifdef ARES_PLATFORM_IOS
    // �������
    void  DllStartRenderFactory( RenderDevice*& ptr);
#endif
}