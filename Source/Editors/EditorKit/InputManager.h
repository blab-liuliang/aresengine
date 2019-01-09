#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace Ares
{
	class CInputManager
	{
	public:
		// ���캯��
		CInputManager();

		// ��������
		~CInputManager();

		BOOL Initialize(HWND hWnd);
		void FrameMove( float fTime);

		DIMOUSESTATE* GetMouseState() { return &m_mouseState;};

		// ����ĳ���Ƿ���
		BOOL IsKeyDown( int key) { return m_keys[key] & 0x80; }

		// �ж����ĳ���Ƿ���
		BOOL IsMouseDown(int key);

		// ��ȡlz
		long GetLZ() { return m_LZ; }	

	public:
		LPDIRECTINPUT8       m_pDirectInput;		// DirectInput����
		LPDIRECTINPUTDEVICE8 m_pKeyboard;           // �����豸����
		LPDIRECTINPUTDEVICE8 m_pMouse;              // ����豸����
		DIMOUSESTATE         m_mouseState;			// ���״̬
		DIMOUSESTATE         m_oldMouseState;		// ���״̬

		long				 m_LZ;					// ����м�����
		char m_keys[256];							// ����״̬
	};
}