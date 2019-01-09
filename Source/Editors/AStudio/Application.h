#pragma once

#include <WTypes.h>
#include <Core/Graphics/AresRenderWindow.h>
#include "SCLogic.h"
#include "ModelEdit/MOLogic.h"

using namespace Ares;

//--------------------------------------------
// DLӦ�ó���  2010-05-07 18:23    ����
//--------------------------------------------
class Application
{
public:
	Application();
	~Application();

	// ��ʼ��
	virtual bool Init();

	// ��ʼ�������༭���߼�
	void InitSCLogic( HWND hwnd);

	// ��ʼ��ģ�ͱ༭���߼�
	void InitMOLogic( HWND hwnd);

	// ����ʼ
	void  Exec();

	// ÿ֡����
	virtual void FrameMove(float fTime);

	// ��Ⱦ
	virtual void Render(float fTime);

private:
	SCLogic*		m_scLogic;
	MOLogic*		m_moLogic;
};

extern Application* G_Application;