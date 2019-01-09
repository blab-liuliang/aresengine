#include "OGLRenderDevice.h"
#include "OGLGraphicsBuffer.h"
#include "OGLRenderLayout.h"
#include "OGLRenderView.h"
#include "OGLTexture.h"
#include "OGLFrameBuffer.h"
#include "OGLRenderState.h"
#include "OGLRenderMethod.h"
#include "OGLPlatform.h"

namespace Ares
{
	template<> OGLRenderDevice* Singleton<OGLRenderDevice>::m_singleton = NULL;

	// ���캯��
	OGLRenderDevice::OGLRenderDevice()
		: m_renderWindow( NULL)
		, m_preLayout( NULL)
		, m_preMaterial( NULL)
	{

	}

	// ��������
	OGLRenderDevice::~OGLRenderDevice()
	{

	}

	// ��ȡ����
	const char* OGLRenderDevice::GetName() const
	{
		return "OGL";
	}

	// ��ʼ֡
	void OGLRenderDevice::BeginFrame()
	{
		//ResetRenderStates();
	}

	// ����֡
	void OGLRenderDevice::EndFrame()
	{

	}

	// ������Ⱦ����
	RenderWindow* OGLRenderDevice::CreateRenderWindow( const RenderSettings& settings)
	{
		RenderDevice::CreateRenderWindow( settings);
		if( !m_renderWindow)
		{
			// ����豸����
			FillRenderDeviceCaps();

			m_renderWindow = new_ OGLRenderWindow( settings);

			// ������Ⱦ״̬
			//ResetRenderStates();

			// ��FrameBuffer
			BindFrameBuffer( m_renderWindow->GetFrameBuffer());
		}

		return m_renderWindow;
	}

	// ����RenderLayout
	RenderLayoutPtr OGLRenderDevice::CreateRenderLayout()
	{
		return RenderLayoutPtr( new_ OGLRenderLayout());
	}

	// ����Ч���ļ� "*.hlsl"
	RenderMethodPtr OGLRenderDevice::CreateRenderMethod()
	{
		return RenderMethodPtr( new_ OGLRenderMethod());
	}

	// ��������������
	GraphicBufferPtr OGLRenderDevice::CreateIndexBuffer( BufferUsage usage, UINT accessHint, const ElementInitData* initData, ElementFormat format)
	{
		return GraphicBufferPtr( new_ OGLGraphicsBuffer( usage, accessHint, GL_ELEMENT_ARRAY_BUFFER, initData));
	}

	// �������㻺����
	GraphicBufferPtr OGLRenderDevice::CreateVertexBuffer( BufferUsage usage, UINT accessHint,const ElementInitData* initData, ElementFormat format)
	{
		return GraphicBufferPtr( new_ OGLGraphicsBuffer( usage, accessHint, GL_ARRAY_BUFFER, initData));
	}

	// ����1D����
	TexturePtr OGLRenderDevice::CreateTexture1D( UINT widht, UINT numMipMaps, UINT arraySize, ElementFormat format, UINT sampleCount, UINT sampleQuality, UINT accessHine, const ElementInitData* initData)
	{
		return TexturePtr();
	}

	// ����2D����
	TexturePtr OGLRenderDevice::CreateTexture2D( UINT width, UINT height, UINT numMipMaps, UINT arraySize, ElementFormat format, UINT sampleCount, UINT sampleQuality, UINT accessHint, ElementInitData* const initData)
	{
		return TexturePtr( new_ OGLTexture2D( width, height, numMipMaps, arraySize, format, sampleCount, sampleQuality, accessHint, initData));
	}

	// ����FrameBuffer
	FrameBufferPtr OGLRenderDevice::CreateFrameBuffer()
	{
		return FrameBufferPtr( new_ OGLFrameBuffer( this));
	}

	// �����������״̬
	SamplerStatePtr OGLRenderDevice::CreateSamplerState( const SamplerStateDesc& desc)
	{
		SamplerStatePool::iterator it = m_ssPool.find( desc);
		if( it==m_ssPool.end())
		{
			SamplerStatePtr samplerState = SamplerStatePtr( new_ OGLSamplerState( desc));
			if( samplerState)
				m_ssPool[desc] = samplerState;

			return samplerState;
		}

		return it->second;
	}

	// ������դ��״̬
	RasterizerStatePtr& OGLRenderDevice::CreateRasterizerState( const RasterizerStateDesc& desc)
	{
		RasterizerStatePool::iterator it = m_rsPool.find( desc);
		if( it==m_rsPool.end())
		{		
			m_rsPool[desc] = RasterizerStatePtr( new_ OGLRasterizerState( desc));

			return m_rsPool[desc];
		}

		return it->second;
	}

	// �������ģ��״̬
	DepthStencilStatePtr OGLRenderDevice::CreateDepthStencilState( const DepthStencilStateDesc& desc)
	{
		return DepthStencilStatePtr( new_ OGLDepthStencilState( desc));
	}

	// �������״̬ 
	BlendStatePtr OGLRenderDevice::CreateBlendState( const BlendStateDesc& desc)
	{
		return BlendStatePtr( new_ OGLBlendState( desc));
	}

	// ����RenderView
	RenderViewPtr OGLRenderDevice::Create2DRenderView( TexturePtr texture, int firstArrayIndex, int arraySize, int levle)
	{
		return RenderViewPtr( new_ OGLTexture2DRenderView( texture, firstArrayIndex, levle));
	}

	// �������View
	RenderViewPtr OGLRenderDevice::Create2DDepthStencilRenderView( UINT widht, UINT height, ElementFormat format, UINT sampleCount, UINT sampleQuality)
	{
		return RenderViewPtr( new_ OGLDepthStencilRenderView( widht, height, format, sampleCount, sampleQuality));
	}

	// �������View
	RenderViewPtr OGLRenderDevice::Create2DDepthStencilRenderView( TexturePtr& texture, int firstArrayIndex, int arraySize, int level)
	{
		return RenderViewPtr();
	}

	// ��ȾRenderable
	void OGLRenderDevice::Render(  RenderLayout* layout, RenderMaterial* material)
	{
		OGLRenderLayout* preRenderLayout = dynamic_cast<OGLRenderLayout*>( m_preLayout);
		OGLRenderLayout* curRenderLayout = dynamic_cast<OGLRenderLayout*>( layout);
		OGLRenderMethod* glslMethod	     = dynamic_cast<OGLRenderMethod*>( material->GetMethod().get());

		A_ASSERT( glslMethod);

		if( glslMethod->IsEnabled() && curRenderLayout)
		{
			// ���ò���(BindProgram, ���ò���״̬)
			material->SetActive();

			// ���Ƽ�����
			curRenderLayout->Render( preRenderLayout, glslMethod);

			m_preLayout   = layout;
			m_preMaterial = material;
		}
	}

	// �󶨻���
	void OGLRenderDevice::BindBuffer( GLenum target, GLuint buffer)
	{
		map<GLenum, GLuint>::iterator it = m_bindedBuffer.find( target);
		if( (it==m_bindedBuffer.end()) || (it->second!=buffer))
		{
			OGLDebug( glBindBuffer( target, buffer));

			m_bindedBuffer[target] = buffer;
		}
	}

	// ɾ������
	void OGLRenderDevice::DeleteBuffers( GLsizei n, const GLuint* buffers)
	{
		for ( GLsizei i=0; i<n; i++)
		{
			map<GLenum, GLuint>::iterator it = m_bindedBuffer.find( buffers[i]);
			if( it!=m_bindedBuffer.end())
				m_bindedBuffer.erase( it);
		}

		OGLDebug( glDeleteBuffers( n, buffers));
	}

	// ��ɫ
	void OGLRenderDevice::EnableFrameBufferSRGB( bool srgb)
	{
		if( m_fbSRGBCache != srgb)
		{
			if( glloader_GL_ARB_framebuffer_sRGB)
			{
				if( srgb)
					glEnable( GL_FRAMEBUFFER_SRGB);
				else
					glEnable( GL_FRAMEBUFFER_SRGB);
			}

			m_fbSRGBCache = srgb;
		}
	}

	// ��Fbo
	void OGLRenderDevice::BindFrameBufferObject( GLuint fbo, bool force)
	{
		if( force || (m_curFbo!=fbo))
		{
			glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fbo);

			m_curFbo = fbo;
		}
	}

	// ��ȡ�豸����
	void OGLRenderDevice::FillRenderDeviceCaps()
	{
		GLint temp;

		glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &temp);
		m_deviceCaps.m_maxVertexStreams = static_cast<BYTE>( temp);
	}
}