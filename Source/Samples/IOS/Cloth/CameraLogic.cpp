#include <Core/AresMath.h>
#include "CameraLogic.h"

// �����������ת���� ������ת���� �뾶������������
#define CAMERA_ROTATIONY_SCALAR  0.1f
#define CAMERA_ROTATIONZ_SCALAR  0.3f
#define CAMERA_RADIUS_SCALAR     0.01f

namespace Ares
{
	// ���캯��
	CameraLogic::CameraLogic()
		: CameraSystem()
		, m_vPos( Vector3( 0.f, 5.f, 3.25f))
	{
		m_cameras.assign( NULL);

		m_fSpeed = 2.5f;

		m_cameras[CT_Normal] = new_ CCamera;

		CCamera* pCamera = m_cameras[CT_Normal];
		if( pCamera)
		{
			pCamera->SetPos( &m_vPos);
			pCamera->SetLookAt( Vector3::Zero);
		}

		m_vpOrthoProj = MakeShaderParam( GetOrtho());
	}

	// ��������
	CameraLogic::~CameraLogic()
	{
	}

	// �Ƿ����
	bool CameraLogic::IsValid()
	{
		return true;
	}

	// �������� ���������
	void CameraLogic::FrameMove(float fTime)
	{
		CCamera* pCamera = m_cameras[CT_Normal];
		if ( pCamera)
		{
			pCamera->SetPos( &m_vPos);

			pCamera->FrameMove( fTime);

			UpdateSPAB();
		}
	}

	// ����Shader����
	void CameraLogic::UpdateSPAB()
	{
		m_params.m_skyViewProj = m_cameras[CT_Normal]->GetSkyViewProj();

		*m_spab[SP_View]	  = GetView();
		*m_spab[SP_ViewProj]  = GetViewProj();
		*m_spab[SP_SkyViewProj] = m_cameras[CT_Normal]->GetSkyViewProj();
		*m_spab[SP_Pos]		  = GetPosition();
		*m_spab[SP_Near]	  = GetNear();
		*m_spab[SP_Far]		  = GetFar();
		*m_spab[SP_Direction] = m_cameras[CT_Normal]->GetDirection();
	}

	// ����ProjParams
	void CameraLogic::SetProjParams(float fovW, int screenWidth, int screenHeight, float fNearPlane, float fFarPlane,  RenderDeviceType type)
	{
		CCamera* pCamera = m_cameras[CT_Normal];

		//ICamera* pCamera		   = m_pCameraManager->GetCameraByName( "Normal");
		//ICamera* pCmaeraReflection = m_pCameraManager->GetCameraByName( "Reflection");
		//ICamera* pCameraFollow	   = m_pCameraManager->GetCameraByName( "Follow");

		//pCmaeraReflection->SetProjParams( fovW/aspect, screenWidth, screenHeight, fNearPlane, fFarPlane);
		//pCameraFollow->SetProjParams( fovW/aspect, screenWidth, screenHeight, fNearPlane, fFarPlane);

		// ����ͶӰ����
		float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
		pCamera->SetProjParams(  fovW/aspect, screenWidth, screenHeight, fNearPlane, fFarPlane, type);
	}

	// ����Զ������
	void  CameraLogic::SetNearFar( float fNear, float fFar)
	{
		CCamera* pCamera = m_cameras[CT_Normal];

		//ICamera* pCamera		   = m_pCameraManager->GetCameraByName( "Normal");
		//ICamera* pCmaeraReflection = m_pCameraManager->GetCameraByName( "Reflection");
		//ICamera* pCameraFollow	   = m_pCameraManager->GetCameraByName( "Follow");	

		// ����ͶӰ����
		pCamera->SetNear(  fNear);
		pCamera->SetFar(  fFar);

		// ����ͶӰ����
		//pCmaeraReflection->SetNear(  fNear);
		//pCmaeraReflection->SetFar(  fFar);

		// ����Զ������
		//pCameraFollow->SetNear(  fNear);
		//pCameraFollow->SetFar(  fFar);
	}

	// ���ÿ���
	void  CameraLogic::SetFov( float fov)
	{
		CCamera* pCamera = m_cameras[CT_Normal];
		//ICamera* pCamera		   = m_pCameraManager->GetCameraByName( "Normal");
		//ICamera* pCmaeraReflection = m_pCameraManager->GetCameraByName( "Reflection");
		//ICamera* pCameraFollow	   = m_pCameraManager->GetCameraByName( "Follow");	

		// ����ͶӰ����
		pCamera->SetFov(  fov);
		//pCmaeraReflection->SetFov(  fov);
		//pCameraFollow->SetFov(  fov);
	}

	// �����Ϸ���
	void  CameraLogic::SetUpDir( float x, float y, float z)
	{
		CCamera* pCamera = m_cameras[CT_Normal];
		//ICamera* pCamera		   = m_pCameraManager->GetCameraByName( "Normal");
		//ICamera* pCmaeraReflection = m_pCameraManager->GetCameraByName( "Reflection");
		//ICamera* pCameraFollow	   = m_pCameraManager->GetCameraByName( "Follow");	

		// ����ͶӰ����
		pCamera->SetUpDir(  x, y, z);
		//pCmaeraReflection->SetUpDir(  x, y, z);
		//pCameraFollow->SetUpDir( x, y, z);
	}


	//-------------------------------------------
	// For Render IO
	//-------------------------------------------
	// ��ȡ�۲�ͶӰ����
	Matrix44& CameraLogic::GetViewProj()
	{
		if( m_active==CT_Sky)
			return m_cameras[CT_Normal]->GetSkyViewProj();

		return m_cameras[CT_Normal]->GetViewProj();
	}

	// ��ȡ�����λ��
	Vector3& CameraLogic::GetPosition()
	{
		return (Vector3&)m_cameras[CT_Normal]->GetPosition();
	}

	// ��ȡ������
	float CameraLogic::GetNear()
	{
		return m_cameras[CT_Normal]->GetNear();
	}

	// ��ȡԶ����
	float CameraLogic::GetFar()
	{
		return m_cameras[CT_Normal]->GetFar();
	}

	// ��ȡ����
	Vector3& CameraLogic::GetFacing()
	{
		return m_cameras[CT_Normal]->GetDirection();
	}

	// ��ȡ�۲����
	Matrix44& CameraLogic::GetView()
	{
		if( m_active==CT_Sky)
			return m_cameras[CT_Normal]->GetSkyView();

		return m_cameras[CT_Normal]->GetView();
	}

	// ��ȡͶӰ����
	Matrix44& CameraLogic::GetProj()
	{
		return m_cameras[CT_Normal]->GetProj();
	}

	// ��������
	const Matrix44& CameraLogic::GetOrtho()
	{
		static Matrix44 orthoOffset;

		orthoOffset = m_cameras[CT_Normal]->GetOrtho();

		return orthoOffset;
	}

	// �۲���������
	const Matrix44& CameraLogic::GetViewOrtho()
	{
		static Matrix44 viewProjOffset;

		viewProjOffset = m_cameras[CT_Normal]->GetViewOrtho();

		return viewProjOffset;
	}

	// ���·��������
	void CameraLogic::SwitchToReflectionCamera()
	{
		/*ICamera* pCamera = m_pCameraManager->GetCameraByName( "Normal");

		// ���ȸ���( Ĭ��1.fƽ��)
		Vector3 point ( 0.f, 0.f, 1.f);
		Vector3 normal( 0.f, 0.f, 1.f);
		Plane3   plane( point, normal);*/

		//m_pCameraManager->SwitchToReflectionCamera( pCamera, plane);
	}

	// ��ȡ��������Ѱ��Χ��
	const Rect3& CameraLogic::GetSearchRect()
	{
		return m_cameras[CT_Normal]->GetFrustem().GetAABB();
	}

	// ��ȡ������ƽ��ͷ��
	Frustum3* CameraLogic::GetFrustum()
	{
		return &m_cameras[CT_Normal]->GetFrustem();
	}

	// ��ȡ����ͶӰ
	ShaderParamPtr& CameraLogic::GetVpOrthoProj()
	{
		*m_vpOrthoProj = m_cameras[CT_Normal]->GetOrtho();

		return m_vpOrthoProj;
	}
}