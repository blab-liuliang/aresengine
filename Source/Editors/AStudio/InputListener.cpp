#include "SCLogic.h"
#include <Engine/InputSystem/OISInputSystem.h>

namespace Ares
{
	using namespace OIS;

	InputListener::InputListener( HWND hwnd)
	{
		m_inputSystem = OIS::InputSystem::createInputSystem( (size_t)hwnd);
		m_mouse		  = static_cast<OIS::Mouse*>( m_inputSystem->createInputObject( OIS::OISMouse, true));
		m_keyBoard	  = static_cast<OIS::Keyboard*>( m_inputSystem->createInputObject( OIS::OISKeyboard, false));
	
		m_mouse->RegisterEventCallback( this);
		m_keyBoard->setEventCallback( this);
	}

	InputListener::~InputListener()
	{

	}

	// ע��
	void InputListener::RegisterMouseEventCallback( OIS::MouseListener* mouseListener)
	{
		m_mouse->RegisterEventCallback( mouseListener);
	}

	// capture
	void InputListener::Capture()
	{
		m_mouse->capture();
		m_keyBoard->capture();
	}

	// ��ȡ���״̬
	const OIS::MouseState& InputListener::GetMouseState()
	{ 
		return m_mouse->GetMouseState();
	}

	// �Ƿ���갴��
	bool InputListener::IsMouseDown( OIS::MouseButtonID button )
	{
		return m_mouse->GetMouseState().IsButtonDown( button);
	}

	// �����Ƿ���
	bool InputListener::IsKeyDown( OIS::KeyCode key)
	{
		return m_keyBoard->isKeyDown( key);
	}

	// ����ƶ�
	bool InputListener::mouseMoved( const MouseEvent &arg)
	{
		return false;
	}

	// ��갴��
	bool InputListener::mousePressed( const MouseEvent &arg, MouseButtonID id)
	{
		return false;
	}

	// ����ͷ�
	bool InputListener::mouseReleased( const MouseEvent &arg, MouseButtonID id)
	{
		return false;
	}

	// ������
	bool InputListener::keyPressed(const KeyEvent &arg)
	{
		return false;
	}

	// ���ͷ�
	bool InputListener::keyReleased(const KeyEvent &arg)
	{
		return false;
	}

	// �������Ƿ���
	bool IsMLBDown()
	{
		return SCLogic_Input->IsMouseDown(OIS::MB_Left);
	}

	// ����Ҽ��Ƿ���
	bool IsMRBDown()
	{
		return SCLogic_Input->IsMouseDown(OIS::MB_Right);
	}

	// �Ƿ���
	bool IsKeyDown(  OIS::KeyCode key)
	{
		return SCLogic_Input->IsKeyDown( key);
	}
}