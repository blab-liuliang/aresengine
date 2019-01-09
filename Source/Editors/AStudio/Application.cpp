#include "Application.h"
#include <Core/AresCore.h>
#include <Engine/AresRoot.h>

Application* G_Application=NULL;

// ���캯��
Application::Application()
{
	G_Application = this;

	Init();

	m_scLogic = NULL;
	m_moLogic = NULL;
}

// ��������
Application::~Application()
{
	SAFE_DELETE( m_moLogic);
	SAFE_DELETE( m_scLogic);
}

// ��ʼ��
bool Application::Init()
{
	// �½�Root
	ResPaths paths;
	paths.push_back("data\\shader\\");
	paths.push_back("data\\shader\\official\\");
	paths.push_back("data\\texture\\");
	paths.push_back("data\\model\\");
	paths.push_back("data\\model\\scene");
	paths.push_back("data\\fx\\texture\\");
	new_ Root( D3D11, paths);

	return true;
}

// ��ʼ�������༭���߼�
void Application::InitSCLogic( HWND hwnd)
{
	m_scLogic = new_ SCLogic( hwnd);
}

// ��ʼ��ģ�ͱ༭���߼�
void Application::InitMOLogic( HWND hwnd)
{
	m_moLogic = new_ MOLogic( hwnd);
}

// ����ʼ
void Application::Exec()
{
	static DWORD lastTime   = timeGetTime();

	// ����delta Time
	DWORD curTime     = timeGetTime();
	DWORD elapsedTime = curTime - lastTime;

	// logic update
	FrameMove( elapsedTime * 0.001f);

	// Call the main render function
	Render( elapsedTime * 0.001f);

	lastTime          = curTime;
}

// ÿ֡����
void Application::FrameMove(float fTime)
{
	if( m_scLogic && !m_scLogic->IsPaused())
		m_scLogic->FrameMove( fTime);

	if( m_moLogic && !m_moLogic->IsPaused())
		m_moLogic->FrameMove( fTime);

	// ����
	ARoot->FrameMove( fTime);
}

// Ӧ�ó�����Ⱦ
void Application::Render(float fTime)
{
	// ��Ⱦ����
	ARoot->Render();
}