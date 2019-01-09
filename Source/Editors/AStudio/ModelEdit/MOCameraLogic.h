#pragma once

#include <Engine/InputSystem/OIS.h>
#include <Engine/CameraSystem/AresCameraSystem.h>
#include <Core/Graphics/AresRenderMethod.h>
#include <EditorKit/BaseCamera.h>
#include <EditorKit/FxEditCamera.h>

namespace Ares
{
	//------------------------------------------------
	// ������߼� 2012-8-20 ����
	//------------------------------------------------
	class MOCameraLogic : public CameraSystem , public OIS::MouseListener
	{
	public:
		MOCameraLogic();
		~MOCameraLogic();

		// ÿ֡����
		void FrameMove(float fTime);

		// ����ͶӰ����
		void  SetProjParams( float fovW,  int screenWidth, int screenHeight, float fNearPlane, float fFarPlane);

		// �����Ϸ���
		void  SetUpDir( float x, float y, float z);

		// ����Զ������
		void  SetNearFar( float fNear, float fFar);

		// ���ÿ���
		void  SetFov( float fov);

		// ���ù۲��
		void SetLookAt( const Vector3& lookAt);

		// ����Ĭ�ϰ뾶
		void SetDefaultRadius( float radius);

		// ���ScreenOffset
		void AddScreenOffset( float xOffset, float yOffset);

		// ʹ�۲���λ����Ļ�м�
		void Zoom( const Rect3 bounds);

		// ����Shader����
		virtual void UpdateSPAB();

	public:
		// �Ƿ����
		virtual bool IsValid();

		// ����ƶ���Ϣ
		bool mouseMoved( const OIS::MouseEvent &arg);

		// ����ƶ�
		void OnMouseMove();

		// RenderIO
	public:
		// ��ȡ������
		virtual float GetNear();

		// ��ȡԶ����
		virtual float GetFar();

		// ��ȡ�ҳ���
		Vector3	GetRight();

		// ��ȡ����
		virtual Vector3& GetFacing();

		// ��ȡ�۲����
		virtual Matrix44& GetView();

		// ��ȡͶӰ����
		virtual Matrix44& GetProj();

		// ��ȡ��Ļƫ��
		Matrix44& GetOffset() { return m_screenOffset; }

		// ��������
		virtual const Matrix44& GetOrtho();

		// �۲���������
		virtual const Matrix44& GetViewOrtho();

		// ��ȡ�۲�ͶӰ����
		virtual Matrix44& GetViewProj();

		// ��ȡ�����λ��
		virtual Vector3& GetPosition();

		// ��ȡ��������Ѱ��Χ��
		virtual const Rect3& GetSearchRect();

		// ��ȡ������ƽ��ͷ��
		virtual Frustum3* GetFrustum();

		// �����ٶ�
		void SetSpeed( float speed) { m_fSpeed = speed; }

	private:
		// ��ȡ�����
		FxEditCamera* GetNormalCamera();

	public:
		// ��ȡ����ͶӰ
		ShaderParamPtr& GetVpOrthoProj();

	public:
		Vector3					m_vPos;
		Vector3					m_bindLookAt;
		float					m_fSpeed;

		ShaderParamPtr			m_vpViewProj;
		ShaderParamPtr			m_vpOrthoProj;

		float					m_xOffset;
		float					m_yOffset;
		Matrix44				m_screenOffset;

		boost::array<Camera*, CT_Total> m_cameras;
	};
}
