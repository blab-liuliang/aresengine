#include "OGLESPlatform.h"
#include <Core/AresCore.h>
#include "OGLESRenderWindow.h"
#include "OGLESRenderLayout.h"

namespace Ares
{
	//-----------------------------------
	// OGLESRenderDevice 2013-02-05 ����
	//-----------------------------------
	class OGLESRenderDevice : public RenderDevice, public Singleton<OGLESRenderDevice>
	{
		typedef map<SamplerStateDesc,    SamplerStatePtr>	 SamplerStatePool;
		typedef map<RasterizerStateDesc, RasterizerStatePtr> RasterizerStatePool;
		typedef map<BlendStateDesc,		 BlendStatePtr>		 BlendStatePool;
	public:
		OGLESRenderDevice();
		~OGLESRenderDevice();

	public:
		// ��ʼ֡
		virtual void BeginFrame();

		// ����֡
		virtual void EndFrame();

		// ������Ⱦ����
		virtual RenderWindow* CreateRenderWindow( const RenderSettings& settings);

		// ��ȡ��Ⱦ����
		virtual RenderWindow* GetRenderWindow() { return m_renderWindow; }

	public:
		// ��ȡ����
		virtual const char* GetName() const;

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
		virtual TexturePtr CreateTexture2D( UINT width, UINT height, UINT numMipMaps, UINT arraySize, ElementFormat format, UINT sampleCount, UINT sampleQuality, UINT accessHint, ElementInitData* const initData);

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
		virtual RenderViewPtr Create2DDepthStencilRenderView( UINT widht, UINT height, ElementFormat format, UINT sampleCount, UINT sampleQuality);

		// �������View
		virtual RenderViewPtr Create2DDepthStencilRenderView( TexturePtr& texture, int firstArrayIndex, int arraySize, int level);

		// ��ȾRenderable
		virtual void Render(  RenderLayout* layout, RenderMaterial* material);

		// OPENGL ���
	public:
		// �󶨻���
		void BindBuffer( GLenum target, GLuint buffer);

		// ɾ������
		void DeleteBuffers( GLsizei n, const GLuint* buffers);

		// ��Fbo
		void BindFrameBufferObject( GLuint fbo, bool force=false);

		// ��ȡ��ǰ֡�������
		GLuint GetCurFrameBufferObject() { return m_curFbo; }

	private:
		OGLESRenderWindow*		m_renderWindow;			// ��Ⱦ����

		SamplerStatePool		m_ssPool;				// ��դ��״̬��
		RasterizerStatePool		m_rsPool;				// �������״̬��

		map<GLenum, GLuint>		m_bindedBuffer;			// ����
		bool					m_fbSRGBCache;			// ֡�������SRGB
		GLuint					m_curFbo;				// ��ǰ֡�������

		RenderLayout*			m_preLayout; 
		RenderMaterial*			m_preMaterial;
	};

	#define PDRenderDevice OGLESRenderDevice::GetSingleton()
	#define PDLogSystem	   PDRenderDevice.GetLogSystem()
}