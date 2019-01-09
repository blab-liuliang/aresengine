#pragma once

#include <Core/AresCore.h>
#include "D3D11AdapterList.h"
#include "D3D11RenderWindow.h"
#include "D3D11GraphicsBuffer.h"

using namespace std;

namespace Ares
{
	//------------------------------------
	// D3D11RenderDevice 2012-02-11 ����
	//------------------------------------
	class D3D11RenderDevice : public RenderDevice, public Singleton<D3D11RenderDevice>
	{
		typedef map<ElementFormat,vector<pair<UINT, UINT>>> RenderTargetFormat;
	public:
		D3D11RenderDevice();
		~D3D11RenderDevice();

	public:
		// ��ʼ֡
		virtual void BeginFrame();

		// ����֡
		virtual void EndFrame();

		// ��ȾRenderable
		virtual void Render( RenderLayout* layout, RenderMaterial* material);

		// ������Ⱦ����
		virtual RenderWindow* CreateRenderWindow( const RenderSettings& settings);

	public:
		// ��ȡ����
		virtual const char* GetName() const;

		// ��ȡActiveAdapter
		D3D11Adapter* GetActiveAdapter() const;

		// ��ȡD3DDevice
		ID3D11DevicePtr& GetD3DDevice() { return m_d3d11Device; }

		// ��ȡimmediateContext
		ID3D11DeviceContextPtr& GetD3DDeviceImmContext() { return m_d3d11ImmContex; }

		// ��ȡFeatureLevel
		D3D_FEATURE_LEVEL GetDeviceFeatureLevel() const { return m_d3dFeatureLevel; }

	public:
		// ������Ⱦ״̬
		void ResetRenderStates();

		// ����D3D11Device
		void SetDevice( ID3D11DevicePtr& device, ID3D11DeviceContextPtr& immCtx, D3D_FEATURE_LEVEL featureLevel);

	public:
		// ����RenderLayout
		virtual RenderLayoutPtr CreateRenderLayout();

		// ����Ч���ļ� "*.hlsl"
		virtual RenderMethodPtr CreateRenderMethod();

		// ��������������
		virtual GraphicBufferPtr CreateIndexBuffer( BufferUsage usage, UINT accessHint, const ElementInitData* initData, ElementFormat format=EF_UnKnown);

		// �������㻺����
		virtual GraphicBufferPtr CreateVertexBuffer( BufferUsage usage, UINT accessHint,const ElementInitData* initData, ElementFormat format=EF_UnKnown);

		// ����1D����
		virtual TexturePtr CreateTexture1D( UINT widht, UINT numMipMaps, UINT arraySize, ElementFormat format, UINT sampleCount, UINT sampleQuality, UINT accessHine, const ElementInitData* initData);

		// ����2D����
		virtual TexturePtr CreateTexture2D(UINT width, UINT height, UINT numMipMaps, UINT arraySize, ElementFormat format, UINT sampleCount, UINT sampleQuality, UINT accessHint, ElementInitData* const initData);

		// ����FrameBuffer
		virtual FrameBufferPtr CreateFrameBuffer();

		// �����������״̬
		virtual SamplerStatePtr CreateSamplerState( const SamplerStateDesc& desc);

		// ������դ��״̬
		virtual RasterizerStatePtr& CreateRasterizerState( const RasterizerStateDesc& desc);

		// �������ģ��״̬
		virtual DepthStencilStatePtr CreateDepthStencilState( const DepthStencilStateDesc& desc);

		// �������״̬ 
		virtual BlendStatePtr CreateBlendState( const BlendStateDesc& desc);

		// ����RenderView
		virtual RenderViewPtr Create2DRenderView( TexturePtr texture, int firstArrayIndex, int arraySize, int levle);

		// �������View
		virtual RenderViewPtr Create2DDepthStencilRenderView( UINT width, UINT height, ElementFormat format, UINT sampleCount, UINT sampleQuality);

		// �������View
		virtual RenderViewPtr Create2DDepthStencilRenderView( TexturePtr& texture, int firstArrayIndex, int arraySize, int level);

	public:
		// ���ù�դ��״̬
		void RSSetState( const ID3D11RasterizerStatePtr& ras);

		// �������ģ�建��״̬
		void OMSetDepthStencilState( const ID3D11DepthStencilStatePtr& ds, UINT stencilRef);

		// ���û��״̬
		void OMSetBlendState( const ID3D11BlendStatePtr& bs, const ColorRGB blendFactor, UINT sampleMask);

		// ����SRV
		void DetachSRV( void* rtvSrc, UINT rtFirstSubres, UINT rtNumsubRes);

		// �����ӿ�
		void RSSetViewports( UINT numViewPorts, const D3D11_VIEWPORT* viewPorts);

		// ���ö�����ɫ��
		void VSSetShader( const ID3D11VertexShaderPtr& shader);

		// ������������ɫ��
		void PSSetShader( const ID3D11PixelShaderPtr& shader);

		// ���ü�����ɫ��
		void GSSetShader( const ID3D11GeometryShaderPtr& shader);

		// ���ü�����ɫ��
		void CSSetShader( const ID3D11ComputeShaderPtr& shader);

		// ����Hull��ɫ��
		void HSSetShader( const ID3D11HullShaderPtr& shader);

		// ����Domain��ɫ��
		void DSSetShader( const ID3D11DomainShaderPtr& shader);

		// ���ó���Buffer
		void SetConstantBuffers( const vector<ID3D11BufferPtr>& cbs, ShaderType shaderType);

		// ������Դ
		void SetShaderResources( const vector<ID3D11ShaderResourceViewPtr>& res, ShaderType shaderType);

		// ���ò���״̬
		void SetSamplers( const vector<ID3D11SamplerStatePtr>& samplers, ShaderType shaderType);

		// ������������
		void SetTopologyType( D3D11_PRIMITIVE_TOPOLOGY topologyType);

	private:
		// �����Ⱦ�豸����
		void FillRenderDeviceCaps();

		// �Ƿ񶥵��ʽ֧��
		bool IsVertexFormatSupport( ElementFormat eleformat);

		// �Ƿ�֧�������ʽ
		bool IsTextureFormatSupport( ElementFormat eleformat);

		// �Ƿ�֧��RenderTarget��ʽ
		bool IsRenderTargetFormatSupport( ElementFormat eleformat, UINT sampleCount, UINT sampleQuality);

	private:
		UINT						m_numBuffers;				// ��ǰBuffer����
		D3D11AdapterList			m_adapterList;				// �������б�

		IDXGIFactory1Ptr			m_giFactory;				// IDXGIFactory1
		ID3D11DevicePtr				m_d3d11Device;				// D3D11Device
		ID3D11DeviceContextPtr		m_d3d11ImmContex;			// D3D11ImmContex
		D3D_FEATURE_LEVEL			m_d3dFeatureLevel;			// D3DFeatureLevel

		D3D11_PRIMITIVE_TOPOLOGY	m_topologyTypeCache;		// ��������
		ID3D11RasterizerStatePtr	m_rasterizerStateCache;		// ��դ״̬����
		ID3D11DepthStencilStatePtr  m_depthStencilStateCache;	// ���ģ��״̬����
		UINT						m_stencilRefCache;			
		ID3D11BlendStatePtr			m_blendStateCache;
		ColorRGB					m_blendFactorCache;
		UINT						m_sampleMaskCache;
		ID3D11VertexShaderPtr		m_vertexShaderCache;		// ������ɫ������
		ID3D11PixelShaderPtr		m_pixelShaderCache;			// ������ɫ������
		ID3D11GeometryShaderPtr		m_geometryShaderCache;		// ������ɫ������
		ID3D11ComputeShaderPtr		m_compueShaderCache;		// ������ɫ������
		ID3D11HullShaderPtr			m_hullShaderCache;			// Hull��ɫ������
		ID3D11DomainShaderPtr		m_domainShderCache;			// Domain��ɫ������

		set<ElementFormat>			m_vertexFormats;			// ֧�ֵĸ�ʽ
		set<ElementFormat>			m_textureFormats;			// ֧�ֵ������ʽ
		RenderTargetFormat			m_renderTargetFormats;		// ��ȾĿ��֧�ֵ������ʽ

		vector<D3D11RenderWindow*>	m_renderWindows;			// ��Ⱦ����
		RenderLayout*				m_preLayout; 
		RenderMaterial*				m_preMaterial;
	};

	#define PDRenderDevice D3D11RenderDevice::GetSingleton()
	#define PDLogSystem	   PDRenderDevice.GetLogSystem()
}