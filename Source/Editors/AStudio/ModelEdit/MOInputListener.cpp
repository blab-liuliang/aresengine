#include "MOLogic.h"
#include <Engine/InputSystem/OISInputSystem.h>

namespace Ares
{
	using namespace OIS;

	MOInputListener::MOInputListener( HWND hwnd)
	{
		m_inputSystem = OIS::InputSystem::createInputSystem( (size_t)hwnd);
		m_mouse		  = static_cast<OIS::Mouse*>( m_inputSystem->createInputObject( OIS::OISMouse, true));
		m_keyBoard	  = static_cast<OIS::Keyboard*>( m_inputSystem->createInputObject( OIS::OISKeyboard, false));

		m_keyBoard->setEventCallback( this);
	}

	// ע��
	void MOInputListener::RegisterMouseEventCallback( OIS::MouseListener* mouseListener)
	{
		m_mouse->RegisterEventCallback( mouseListener);
	}

	// ע��
	void MOInputListener::UnRegisterEventCallback( OIS::MouseListener* mouseListener)
	{
		m_mouse->UnRegisterEventCallback( mouseListener);
	}

	MOInputListener::~MOInputListener()
	{

	}

	// capture
	void MOInputListener::Capture()
	{
		m_mouse->capture();
		m_keyBoard->capture();
	}

	// ��ȡ���״̬
	const OIS::MouseState& MOInputListener::GetMouseState()
	{ 
		return m_mouse->GetMouseState();
	}

	// �Ƿ���갴��
	bool MOInputListener::IsMouseDown( OIS::MouseButtonID button )
	{
		return m_mouse->GetMouseState().IsButtonDown( button);
	}

	// �����Ƿ���
	bool MOInputListener::IsKeyDown( OIS::KeyCode key)
	{
		return m_keyBoard->isKeyDown( key);
	}

	// ������
	bool MOInputListener::keyPressed(const KeyEvent &arg)
	{
		return false;
	}

	// ���ͷ�
	bool MOInputListener::keyReleased(const KeyEvent &arg)
	{
		return false;
	}
}