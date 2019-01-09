#include <Engine/AresRoot.h>
#include <Engine/Foundation/AresPlugin.h>
#include <Engine/SceneSystem/AresScene.h>
#ifdef ARES_PLATFORM_WINDOWS
#include <Core/AresDynLibManager.h>
#elif defined ARES_PLATFORM_IOS
#include <Core/Graphics/AresRenderDevice.h>
#endif

namespace Ares
{
	template<> Root* Singleton<Root>::m_singleton = NULL;

	// ���캯��
	Root::Root( RenderDeviceType api, const ResPaths& res)
		: m_resSystem(NULL)
		//, m_renderSystem(NULL)
		, m_fxSystem(NULL)
		, m_uiSystem(NULL)
		, m_soundSystem(NULL)
		, m_logSystem(NULL)
		, m_renderDevice( NULL)
	{
		// ��־ϵͳ
		BuildLogSystem();

		// ��Դϵͳ
		BuildResSystem( res);

		// Ч��ϵͳ

		// ����ϵͳ
		BuildSoundSystem();

		// ������Ⱦ�豸
		BuildRenderDevice( api);
	}

	Root::~Root()
	{
		SAFE_DELETE( m_resSystem);
		SAFE_DELETE( m_fxSystem);
		SAFE_DELETE( m_uiSystem);
		SAFE_DELETE( m_soundSystem);
		SAFE_DELETE( m_logSystem);
		SAFE_DELETE( m_renderDevice);
	}

	//// ��ʼ��
	//bool Root::Init( CameraSystem* cameraCallback, const RenderSettings& settings, const ResPaths& res)
	//{
	//	bool result = true;

	//	// ��־ϵͳ
	//	//result &= BuildLogSystem() ? true : false;

	//	// ��Դ����ϵͳ
	//	//BuildResSystem( res);

	//	// ��Ⱦϵͳ
	//	//result &= BuildRenderSystem( cameraCallback, settings) ? true : false;

	//	// Ч��ϵͳ
	//	//result &= BuildFxSystem() ? true : false;

	//	// ����ϵͳ
	//	//result &= BuildUiSystem() ? true : false;

	//	// ��������ϵͳ
	//	//result &= BuildSceneSystem( cameraCallback) ? true : false;

	//	// ����ϵͳ
	//	//result &= BuildSoundSystem() ? true : false;

	//	return result;
	//}

	// �߼�ģ��
	void Root::FrameMove( float elpasedTime)
	{
		//if( m_uiSystem)
		//	m_uiSystem->frameEvent( elpasedTime);

		if( elpasedTime == 0.f)
			return;

		foreach_( Scene* scene, m_scenes)
		{
			scene->FrameMove( elpasedTime);
		}
	}

	// ��Ⱦ
	void Root::Render()
	{
		foreach_( Scene* scene, m_scenes)
		{
			scene->Render();
		}
	}

	// ������Ⱦ�豸
	RenderDevice* Root::BuildRenderDevice( RenderDeviceType api)
	{
		typedef void (*CREATER_RENDER_FACTORY)(RenderDevice*&);

#ifdef ARES_PLATFORM_WINDOWS
		static CDynLibManager*	dynLibMgr = new_ CDynLibManager;		// ��̬�������

		CDynLib* pLib = NULL;
#if ARES_DEBUG_MODE
		if( api==D3D11)
			pLib = dynLibMgr->Load( "Plugin_D3D11.dll");
		else if( api==OPENGL)
			pLib = dynLibMgr->Load( "Plugin_OpenGL.dll");
		else if( api==OPENGLES)
			pLib = dynLibMgr->Load( "Plugin_OpenGLES.dll");
#else
		if( api==D3D11)
			pLib = dynLibMgr->Load( "Plugin_D3D11.dll");
		else if( api==OPENGL)
			pLib = dynLibMgr->Load( "Plugin_OpenGL.dll");
		else if( api==OPENGLES)
			pLib = dynLibMgr->Load( "Plugin_OpenGLES.dll");
#endif
		if( pLib)
		{
			CREATER_RENDER_FACTORY pFunc = (CREATER_RENDER_FACTORY)pLib->GetSymbol("DllStartRenderFactory");
			if( pFunc)
				(*pFunc)( m_renderDevice);
		}

#elif defined ARES_PLATFORM_IOS
		// ������ں���
		DllStartRenderFactory( m_renderDevice);
#endif

		A_ASSERT( m_renderDevice->GetType() == api);

		return m_renderDevice;
	}

	// ������Чϵͳ
	FxSystem* Root::BuildFxSystem()
	{
		if( !m_fxSystem)
		{
			m_fxSystem = new_ FxSystem;

			A_ASSERT( m_fxSystem);
		}

		return m_fxSystem;
	}

	// ��������ϵͳ
	MyGUI::Gui*  Root::BuildUiSystem()
	{
		if( !m_uiSystem)
		{
			m_uiSystem = new_ MyGUI::Gui();

			A_ASSERT( m_uiSystem);
		}

		return m_uiSystem;
	}

	// ������������ϵͳ
	Scene* Root::BuildScene( CameraSystem* cameraCallback, const RenderSettings& settings, const char* name, const char* location)
	{
		Scene* scene = Scene::Create( cameraCallback, settings, name, location);

		m_scenes.push_back( scene);

		return scene;
	}

	// ��������ϵͳ
	SoundSystem* Root::BuildSoundSystem()
	{
		if( !m_soundSystem)
		{
			m_soundSystem = SoundSystem::Create();

			A_ASSERT( m_soundSystem);
		}

		return m_soundSystem;
	}

	// ������Դ����ϵͳ
	ResSystem* Root::BuildResSystem( const ResPaths& res)
	{
		if( !m_resSystem)
		{
			m_resSystem = new_ ResSystem( res);

			A_ASSERT(  m_resSystem);
		}

		return m_resSystem;
	}

	// ������־ϵͳ
	LogSystem* Root::BuildLogSystem()
	{
		if( !m_logSystem)
		{
			m_logSystem = new_ LogSystem;

			A_ASSERT( m_logSystem);
		}

		return m_logSystem;
	}

	//!
	//! ��ȡ��Դ����ϵͳ		
	ResSystem& Root::GetResSystem()
	{
		A_ASSERT( m_resSystem);

		return *m_resSystem;
	}

	// ��ȡ��Ⱦ����
	RenderDevice* Root::GetRenderDevice()
	{
		return m_renderDevice;
	}

	//// ��ȡ��Ⱦϵͳ
	//RenderSystem& Root::GetRenderSystem()
	//{
	//	A_ASSERT( m_renderSystem);

	//	return *m_renderSystem;
	//}

	// ��ȡ������Чϵͳ
	FxSystem& Root::GetFxSystem()
	{
		A_ASSERT( m_fxSystem);

		return *m_fxSystem;
	}

	// ��ȡ����ϵͳ
	MyGUI::Gui& Root::GetUiSystem()
	{
		A_ASSERT( m_uiSystem);

		return *m_uiSystem;
	}

	// ��ȡʵ��ϵͳ
	Scene& Root::GetScene( size_t index)
	{
		A_ASSERT(index < m_scenes.size());

		return *m_scenes[index];
	}

	// ��ȡ����ϵͳ
	SoundSystem& Root::GetSoundSystem()
	{
		A_ASSERT( m_soundSystem);

		return *m_soundSystem;
	}

	// ��־ϵͳ
	LogSystem& Root::GetLogSystem()
	{
		A_ASSERT( m_logSystem);

		return *m_logSystem;
	}
}