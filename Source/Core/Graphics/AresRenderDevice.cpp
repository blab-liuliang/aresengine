#include "Core/Graphics/AresRenderDevice.h"

namespace Ares
{
	// ���캯��
	RenderDevice::RenderDevice( RenderDeviceType api)
		: m_logSystem( NULL)
		, m_api( api)
	{

	}

	// ��������
	RenderDevice::~RenderDevice()
	{

	}

	// ������־ϵͳ
	void RenderDevice::SetLogSystem( LogSystem* logSystem) 
	{ 
		m_logSystem = logSystem; 
	}

	// ��ȡ��־ϵͳ
	LogSystem& RenderDevice::GetLogSystem() 
	{ 
		A_ASSERT( m_logSystem);

		return *m_logSystem; 
	}

	// BindFrameBuffer
	void RenderDevice::BindFrameBuffer( FrameBufferPtr frameBuffer)
	{
		if( frameBuffer)
		{
			if( frameBuffer->IsDirty() || m_curFrameBuffer!=frameBuffer)
			{
				if( m_curFrameBuffer)
					m_curFrameBuffer->Unbind();

				m_curFrameBuffer = frameBuffer;
				m_curFrameBuffer->Bind();
			}
		}
	}

	// ���ǰFrameBuffer
	void RenderDevice::ResetFrameBuffer()
	{
		if( m_curFrameBuffer)
		{
			m_curFrameBuffer->Unbind();
			m_curFrameBuffer = FrameBufferPtr();
		}
	}

	// ������Ⱦ����
	RenderWindow* RenderDevice::CreateRenderWindow( const RenderSettings& settings)
	{
		//m_renderSettings = settings;

		return NULL;
	}

	// ����Ч���ļ�
	//RenderEffectPtr RenderFactory::CreateEffect( const char* fileName)
	//{
		//EffectPool::iterator it = m_effectPool.find( fileName);
		//if( it==m_effectPool.end())
		//{
		//	RenderEffectPtr effect = RenderEffectPtr( new RenderEffect());
		//	if( effect->Load( fileName))
		//		m_effectPool[fileName] = effect;

		//	return effect;
		//}

		//return it->second;
	//}

	// ��ȡ��ǰFrameBuffer
	FrameBufferPtr RenderDevice::GetCurFrameBuffer() const
	{
		return m_curFrameBuffer;
	}

	// ��ȡ�豸����
	const RenderDeviceCaps& RenderDevice::GetDeviceCaps() const
	{
		return m_deviceCaps;
	}

	//// ��ȡ��Ⱦ����
	//const RenderSettings& RenderDevice::GetRenderSettings() const
	//{
	//	return m_renderSettings;
	//}

	//// Ӧ������
	//void RenderDevice::SetRenderSettings( const RenderSettings& settings)
	//{
	//	// ���ڴ�С�ı�
	//	if( settings.m_width!=m_renderSettings.m_width || settings.m_height!=m_renderSettings.m_height)
	//	{
	//		GetRenderWindow()->Resize( settings.m_width, settings.m_height);
	//	}

	//	m_renderSettings = settings;
	//}
}