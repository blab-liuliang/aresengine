#pragma once

#include <Engine/InputSystem/OIS.h>
#include <Engine/CameraSystem/AresCameraSystem.h>
#include <Core/Graphics/AresRenderMethod.h>
#include <EditorKit/BaseCamera.h>
#include <EditorKit/ThirdViewCamera.h>

namespace Ares
{
	class CameraLogic : public CameraSystem , public OIS::MouseListener
	{
	public:
		CameraLogic();
		~CameraLogic();

		// ÿ֡����
		void FrameMove(float fTime);

		// ���õ�ǰ�����
		void SetCamera( Camera* camera) { m_cameras[CT_Normal] = camera; }

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

		// ����ƶ���Ϣ
		bool mouseMoved( const OIS::MouseEvent &arg);

		// ��ȡ�����
		//CCamera* GetCameraByName( const char* name) { return m_pCameraManager->GetCameraByName(name); }

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

	public:
		// ��ȡ����ͶӰ
		virtual ShaderParamPtr& GetVpOrthoProj();

	private:
		ShaderParamPtr			m_vpOrthoProj;

		boost::array<Camera*, CT_Total> m_cameras;			
	};
}
