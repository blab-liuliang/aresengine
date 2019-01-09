#pragma once

#include <Core/AresPlatform.h>
#include <Engine/InputSystem/OIS.h>

namespace Ares
{
	//---------------------------------------
	// ��������� 2012-8-17 ����
	//---------------------------------------
	class MOInputListener : public OIS::KeyListener
	{
	public:
		MOInputListener( HWND hwnd);
		~MOInputListener();

	public:
		// capture
		void Capture();

		// ע��
		void RegisterMouseEventCallback( OIS::MouseListener* mouseListener);

		// ע��
		void UnRegisterEventCallback( OIS::MouseListener* mouseListener);

		// �Ƿ���갴��
		bool IsMouseDown( OIS::MouseButtonID button );

		// ��ȡ���״̬
		const OIS::MouseState& GetMouseState();

		// �����Ƿ���
		bool IsKeyDown( OIS::KeyCode key);

	public:
		// ������
		bool keyPressed(const OIS::KeyEvent &arg);

		// ���ͷ�
		bool keyReleased(const OIS::KeyEvent &arg);

	private:
		OIS::InputSystem*		m_inputSystem;		// ����ϵͳ
		OIS::Mouse*				m_mouse;			// ������
		OIS::Keyboard*			m_keyBoard;			// ���̶���
	};
}
