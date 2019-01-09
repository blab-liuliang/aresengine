#pragma once

#include "BaseCamera.h"
#include <Engine/CameraSystem/AresCameraSystem.h>
#include <Core/Graphics/AresRenderMethod.h>

namespace Ares
{
	class CameraLogic : public CameraSystem
	{
	public:
		CameraLogic();
		~CameraLogic();

		// ÿ֡����
		void FrameMove(float fTime);

		// ����ͶӰ����
		void  SetProjParams( float fovW, int screenWidth, int screenHeight, float fNearPlane, float fFarPlane, RenderDeviceType type);

		// �����Ϸ���
		void  SetUpDir( float x, float y, float z);

		// ����Զ������
		void  SetNearFar( float fNear, float fFar);

		// ���ÿ���
		void  SetFov( float fov);

		// ����Shader����
		virtual void UpdateSPAB();

	public:
		// �Ƿ����
		virtual bool IsValid();

		// RenderIO
	public:
		// ��ȡ������
		virtual float GetNear();

		// ��ȡԶ����
		virtual float GetFar();

		// ��ȡ����
		virtual Vector3& GetFacing();

		// ��ȡ�۲����
		virtual Matrix44& GetView();

		// ��ȡͶӰ����
		virtual Matrix44& GetProj();

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

		// ���·��������
		virtual void SwitchToReflectionCamera();

		// �����ٶ�
		void SetSpeed( float speed) { m_fSpeed = speed; }

	public:
		// ��ȡ����ͶӰ
		virtual ShaderParamPtr& GetVpOrthoProj();

	private:
		Vector3					m_vPos;
		float					m_fSpeed;

		ShaderParamPtr			m_vpOrthoProj;

		boost::array<CCamera*, CT_Total> m_cameras;
	};
}
