#include "SCLogic.h"
#include <Core/AresMath.h>

// �����������ת���� ������ת���� �뾶������������
#define CAMERA_ROTATIONY_SCALAR  0.1f
#define CAMERA_ROTATIONZ_SCALAR  0.3f
#define CAMERA_RADIUS_SCALAR     0.01f

namespace Ares
{
	// ���캯��
	CameraLogic::CameraLogic()
		: CameraSystem()
	{
		m_cameras.assign( NULL);

		m_vpOrthoProj = MakeShaderParam();
	}

	// ��������
	CameraLogic::~CameraLogic()
	{
	}

	// �Ƿ����
	bool CameraLogic::IsValid()
	{
		POINT cp;		// ��ǰ���λ��
		RECT  cr;		// ��������
		GetCursorPos( &cp);
		ScreenToClient( SELogic_RenderSystem.GetRenderSettings().m_hwnd, &cp);
		GetClientRect(  SELogic_RenderSystem.GetRenderSettings().m_hwnd, &cr);

		if( cp.x<cr.left || cp.x>cr.right)
			return false;

		if( cp.y<cr.top || cp.y>cr.bottom)
			return false;

		return true;
	}

	// ����ƶ���Ϣ
	bool CameraLogic::mouseMoved( const OIS::MouseEvent &arg)
	{
		LiberityViewCamera* pCamera = dynamic_cast<LiberityViewCamera*>( m_cameras[CT_Normal]);
		if ( pCamera)
		{
			if( SCLogic_Input->IsMouseDown(OIS::MB_Right))		// ����ƶ����Ҽ�����
			{
				pCamera->UpdateCameraDir( SCLogic_Input->GetMouseState().Y.rel * CAMERA_RADIUS_SCALAR, SCLogic_Input->GetMouseState().X.rel * CAMERA_ROTATIONZ_SCALAR * CAMERA_ROTATIONY_SCALAR);
			}

			if(SCLogic_Input->GetMouseState().Z.rel )
			{
				pCamera->ChangeDefaultRadius( (float)SCLogic_Input->GetMouseState().Z.rel );
			}
		}

		return true;
	}

	// �������� ���������
	void CameraLogic::FrameMove(float fTime)
	{
		UpdateSPAB();
	}

	// ����Shader����
	void CameraLogic::UpdateSPAB()
	{
		if( m_cameras[CT_Normal])
		{
			m_params.m_skyViewProj = m_cameras[CT_Normal]->GetSkyViewProj();

			*m_spab[SP_View]	  = GetView();
			*m_spab[SP_ViewProj]  = GetViewProj();
			*m_spab[SP_SkyViewProj] = m_cameras[CT_Normal]->GetSkyViewProj();
			*m_spab[SP_Pos]		  = GetPosition();
			*m_spab[SP_NearFar]	  = float2( GetNear(), GetFar());
			*m_spab[SP_Right]	  = GetFrustum()->GetRight();
			*m_spab[SP_Up]		  = GetFrustum()->GetUp();
			*m_spab[SP_Front]	  = GetFacing();
			*m_spab[SP_Direction] = m_cameras[CT_Normal]->GetDirection();
		}
	}

	// ����Զ������
	void  CameraLogic::SetNearFar( float fNear, float fFar)
	{
		Camera* pCamera = m_cameras[CT_Normal];
		if( pCamera)
		{
			// ����ͶӰ����
			pCamera->SetNear(  fNear);
			pCamera->SetFar(  fFar);
		}
	}

	// ���ÿ���
	void  CameraLogic::SetFov( float fov)
	{
		if( m_cameras[CT_Normal])
		{
			m_cameras[CT_Normal]->SetFov( fov);
		}
	}

	// �����Ϸ���
	void  CameraLogic::SetUpDir( float x, float y, float z)
	{
		Camera* pCamera = m_cameras[CT_Normal];
		if( pCamera)
		{
			// ����ͶӰ����
			pCamera->SetUpDir(  x, y, z);
		}
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