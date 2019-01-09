#pragma once

#include <Core/AresPlatform.h>
#include <Engine/InputSystem/OIS.h>

namespace Ares
{
	//---------------------------------------
	// ��������� 2012-8-17 ����
	//---------------------------------------
	class InputListener : public OIS::MouseListener, public OIS::KeyListener
	{
	public:
		InputListener( HWND hwnd);
		~InputListener();

	public:
		// capture
		void Capture();

		// ע��
		void RegisterMouseEventCallback( OIS::MouseListener* mouseListener);

		// �Ƿ���갴��
		bool IsMouseDown( OIS::MouseButtonID button );

		// ��ȡ���״̬
		const OIS::MouseState& GetMouseState();

		// �����Ƿ���
		bool IsKeyDown( OIS::KeyCode key);

	public:
		// ����ƶ�
		virtual bool mouseMoved( const OIS::MouseEvent &arg);

		// ��갴��
		virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id);

		// ����ͷ�
		virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id);

		// ������
		bool keyPressed(const OIS::KeyEvent &arg);

		// ���ͷ�
		bool keyReleased(const OIS::KeyEvent &arg);

	private:
		OIS::InputSystem*		m_inputSystem;		// ����ϵͳ
		OIS::Mouse*				m_mouse;			// ������
		OIS::Keyboard*			m_keyBoard;			// ���̶���
	};

	// �������Ƿ���
	bool IsMLBDown();

	// ����Ҽ��Ƿ���
	bool IsMRBDown();

	// �Ƿ���
	bool IsKeyDown(  OIS::KeyCode key);
}
