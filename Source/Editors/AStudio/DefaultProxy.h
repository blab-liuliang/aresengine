#pragma once

#include <EditorKit/BaseCamera.h>

namespace Ares
{
	//----------------------------------------------
	// Ĭ�ϳ������������ 2013-8-8 ����
	//----------------------------------------------
	class DefaultProxy
	{
	public:
		DefaultProxy();
		~DefaultProxy();

		// ����
		void Active();

		// ����
		void FrameMove( float elapsedTime);

		// �����ٶ�
		void SetSpeed( float speed) { m_fSpeed = speed; }

		// ��ȡλ��
		const Vector3& GetPosition() { return m_vPos; }

		// ��ȡ�����
		Camera* GetCamera() { return m_camera; }

	private:
		Camera*		m_camera;
		Vector3		m_vPos;
		float		m_fSpeed;
	};
}