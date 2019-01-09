#pragma  once

#include <Physics/Shapes.h>
#include <Core/Graphics/AresRenderDevice.h>
#include <string>

using namespace std;

namespace Ares
{
	//-----------------------------------------------------------------
	//  �����������������ر����� + ���ٵĲ��� -- ����
	//-----------------------------------------------------------------
	class CCamera
	{
	public:
		// ö��
		enum CameraType
		{
			CAMERA_TYPE_BASE, 
			CAMERA_TYPE_FOLLOW_VIEWER, 
			CAMERA_TYPE_LIBERITY_VIEW,
			CAMERA_TYPE_FXEDIT,
			EM_CAMERA_REFLECTION,
		};

		// ���캯��
		CCamera();
		
		// ��������
		virtual void  SetName( const char* name) { m_name = name; }

		// ��ȡ����
		virtual const char* GetName() { return m_name.c_str(); }

		// ���ó��ò���
		virtual void  SetViewParams( Vector3* vPos, Vector3* vLookAt, Vector3* vUp);

		// ����ͶӰ�������
		virtual void  SetProjParams(float fovH, int screenWidth, int screenHeight, float fNearPlane, float fFarPlane, RenderDeviceType type);

		// ���ý�����
		virtual void  SetNear( float _near);

		// ����Զ����
		virtual void  SetFar( float _far);

		// ���ÿ���
		virtual void  SetFov( float fov);
		
		// ����EyePoint
		virtual void  SetPos(Vector3* vPos);
		
		// ���ù۲��
		virtual void  SetLookAt( const Vector3& lookAt);	

		// �����Ϸ���
		virtual void  SetUpDir( float x, float y, float z);

		// ��ȡ������
		virtual float GetNear() { return m_fNearPlane; }

		// ��ȡԶ����
		virtual float GetFar() { return m_fFarPlane; }

		// ��ȡ��ǰ�뾶
		virtual float GetCurRadius() { return 0.f;};

		// ��ȡĬ�ϰ뾶
		virtual float GetDefaultRadius() { return 0.f;}

		// ��ȡ�����λ��
		virtual const Vector3& GetPosition() const { return m_vPosition; }

		// ��ȡ�����ƽ��ͷ��
		virtual Frustum3& GetFrustem() { return m_frustem; }

		// �ҷ���
		virtual Vector3 GetRight() const;

		// ���۲��
		virtual const Vector3& GetLookAt() const { return m_vLookAt; }

		// ��ȡ�Ϸ���
		virtual const Vector3& GetUp() const { return m_vUp; }

		// ��ͼ����
		virtual Matrix44&  GetView(){ return m_matView; }

		// ͶӰ����
		virtual Matrix44&  GetProj(){ return m_matProj; }

		// viewProjMatrix
		virtual Matrix44&  GetViewProj();

		// ��������
		virtual const Matrix44& GetOrtho();

		// �۲���������
		virtual const Matrix44& GetViewOrtho();

		// ��ȡ��������View
		virtual Matrix44& GetSkyView() { return m_matSkyView; }

		// ��ȡ�������պо���
		virtual Matrix44&  GetSkyViewProj() { return m_matSkyViewProj; }

		// ��ȡ����
		virtual Vector3&  GetDirection(){ return m_vForward; }

		// ��ȡˮƽ����Ƕ�
		virtual float GetHorizonAngle() { return m_horizonAngle; }

		// ����
		virtual BOOL  FrameMove(float fTime);

	protected:
		// ����ViewMatrix	
		void  UpdateViewMatrix();

		// ����ProjMatrix
		void  RefreshProjOrthoMatrix();

	private:
		// ����SearchRect
		void RecalcMatrices();

	protected:
		string			m_name;				// �������	
		Vector3			m_vPosition;		// �����λ��
		Vector3			m_vLookAt;			// �ӵ�
		Vector3			m_vUp;				// �Ϸ���

		Vector3			m_vForward;			// ����
		float			m_horizonAngle;		// ˮƽ��ת�Ƕ�(˳ʱ��)
		float			m_verticleAngle;	// ��ֱ��ת�Ƕ�(˳ʱ��)

		float			m_fovH;				// FOV�н�
		float			m_fAspect;			// �ݺ��
		float			m_fNearPlane;		// ��ƽ��
		float			m_fFarPlane;		// Զƽ��
		float			m_screenWidth;		// ��Ļ��(����)
		float			m_screenHeight;		// ��Ļ��(����)

		Matrix44		m_matView;			// ��ͼ�任����
		Matrix44		m_matProj;			// ͶӰ�任����
		Matrix44		m_matViewProj;		// �۲�ͶӰ����
		Matrix44		m_matUnitProj;		// 
		Matrix44		m_matSkyView;		// ��պй۲����
		Matrix44		m_matSkyViewProj;	// ��պй۲�ͶӰ����
		Matrix44		m_inverseProj;		// ͶӰ����������

		Matrix44		m_matOrtho;
		Matrix44		m_matViewOrtho;

		Matrix44		m_matUpMatch;		// �����Ϸ�����

		Frustum3		m_frustem;			// �����ƽ��ͷ��
		RenderDeviceType m_deviceType;			// ��Ⱦ�豸����
	};
}