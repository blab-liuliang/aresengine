#include "MOLogic.h"
#include <Core/AresMath.h>
#include <Engine/AresRoot.h>

// �����������ת���� ������ת���� �뾶������������
#define CAMERA_ROTATIONY_SCALAR  0.1f
#define CAMERA_ROTATIONZ_SCALAR  0.3f
#define CAMERA_RADIUS_SCALAR     0.005f

namespace Ares
{
	// ���캯��
	MOCameraLogic::MOCameraLogic()
		: CameraSystem()
		, m_vPos( Vector3( 0.f, 20.f, 10.f))
		, m_bindLookAt( Vector3( 0.f, 0.f, 0.f))
		, m_xOffset( 0.f)
		, m_yOffset( 0.f)
	{
		m_screenOffset.SetIdentity();
		m_fSpeed = 5.f;


		m_cameras[CT_Normal] = new_ FxEditCamera;
		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);
		if( pCamera)
		{
			pCamera->SetPos( &m_vPos);
			pCamera->SetLookAt( &Vector3( 0.f, 0.f, 0.f));
			pCamera->SetBindPos( &m_bindLookAt);
		}

		m_vpViewProj  = MakeShaderParam( GetViewProj());
		m_vpOrthoProj = MakeShaderParam( GetOrtho());
	}

	// ��������
	MOCameraLogic::~MOCameraLogic()
	{
	}

	// �Ƿ����
	bool MOCameraLogic::IsValid()
	{
		POINT cp;		// ��ǰ���λ��
		RECT  cr;		// ��������
		GetCursorPos( &cp);
		ScreenToClient( MOLogic_RenderSystem.GetRenderSettings().m_hwnd, &cp);
		GetClientRect( MOLogic_RenderSystem.GetRenderSettings().m_hwnd, &cr);

		if( cp.x<cr.left || cp.x>cr.right)
			return false;

		if( cp.y<cr.top || cp.y>cr.bottom)
			return false;

		return true;
	}

	// ����ƶ���Ϣ
	bool MOCameraLogic::mouseMoved( const OIS::MouseEvent &arg)
	{
		OnMouseMove();

		return true;
	}

	// ����ƶ�
	void MOCameraLogic::OnMouseMove()
	{
		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);
		if ( pCamera)
		{
			if( MOLogic_Input->IsMouseDown(OIS::MB_Right))		// ����ƶ����Ҽ�����
			{
				pCamera->UpdateCameraDir( MOLogic_Input->GetMouseState().Y.rel * CAMERA_RADIUS_SCALAR, MOLogic_Input->GetMouseState().X.rel * CAMERA_ROTATIONY_SCALAR * CAMERA_ROTATIONY_SCALAR);
			}

			if( MOLogic_Input->IsMouseDown(OIS::MB_Left))
			{
				pCamera->ChangeDefaultRadius( ((float)MOLogic_Input->GetMouseState().Y.rel) * 0.0025f * MOLogic_ModelEdit->GetModelRadius());
				pCamera->UpdateCameraDir( 0.f, MOLogic_Input->GetMouseState().X.rel * CAMERA_ROTATIONY_SCALAR * CAMERA_ROTATIONY_SCALAR);
			}

			if( MOLogic_Input->IsMouseDown( OIS::MB_Middle))
			{
				float xOffset = MOLogic_Input->GetMouseState().X.rel *  2.f / MOLogic_RenderWindow->GetWidth();
				float yOffset = MOLogic_Input->GetMouseState().Y.rel * -2.f / MOLogic_RenderWindow->GetHeight();
				AddScreenOffset( xOffset, yOffset);
			}
			else if(MOLogic_Input->GetMouseState().Z.rel )
				pCamera->ChangeDefaultRadius( ((float)MOLogic_Input->GetMouseState().Z.rel) * -0.0015f * MOLogic_ModelEdit->GetModelRadius());
		}
	}

	// �������� ���������
	void MOCameraLogic::FrameMove(float fTime)
	{
		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);
		if ( pCamera)
		{
			pCamera->FrameMove( fTime);

			UpdateSPAB();
		}
	}

	// ����Shader����
	void MOCameraLogic::UpdateSPAB()
	{
		*m_spab[SP_View]		= GetView();
		*m_spab[SP_ViewProj]	= GetViewProj();
		*m_spab[SP_SkyViewProj] = m_cameras[CT_Normal]->GetSkyViewProj();
		*m_spab[SP_Pos]			= GetPosition();
		*m_spab[SP_NearFar]		= float2( GetNear(), GetFar());
		*m_spab[SP_Direction]	= m_cameras[CT_Normal]->GetDirection();
	}

	// ����Ĭ�ϰ뾶
	void MOCameraLogic::SetDefaultRadius( float radius)
	{
		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);
		if( pCamera)
			pCamera->SetDefaultRadius( radius);
	}

	// ʹ�۲���λ����Ļ�м�
	void MOCameraLogic::Zoom( const Rect3 bounds)
	{
		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);
		if( pCamera)
		{
			float   radius = ((bounds.GetMinPoint()-bounds.GetMaxPoint()).Length() * 0.5f);
			Vector3 center = ((bounds.GetMinPoint()+bounds.GetMaxPoint()) * 0.5f);

			pCamera->Zoom( radius);
				
			SetLookAt( center);
			AddScreenOffset( -m_xOffset, -m_yOffset);
		}
	}

	// ���ù۲��
	void MOCameraLogic::SetLookAt( const Vector3& lookAt)
	{
		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);
		if( pCamera)
		{
			m_bindLookAt = lookAt;
		}
	}

	// ���ScreenOffset
	void MOCameraLogic::AddScreenOffset( float xOffset, float yOffset)
	{
		m_xOffset += xOffset;
		m_yOffset += yOffset;

		Matrix44Translation( m_screenOffset, m_xOffset, m_yOffset, 0.f);
	}

	// ����ProjParams
	void MOCameraLogic::SetProjParams( float fovW, int screenWidth, int screenHeight, float fNearPlane, float fFarPlane)
	{
		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);

		// ����ͶӰ����
		float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
		pCamera->SetProjParams(  fovW/aspect, screenWidth, screenHeight, fNearPlane, fFarPlane, D3D11);
	}

	// ����Զ������
	void  MOCameraLogic::SetNearFar( float fNear, float fFar)
	{
		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);

		// ����ͶӰ����
		pCamera->SetNear(  fNear);
		pCamera->SetFar(  fFar);
	}

	// ���ÿ���
	void  MOCameraLogic::SetFov( float fov)
	{
		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);

		// ����ͶӰ����
		pCamera->SetFov(  fov);
	}

	// �����Ϸ���
	void  MOCameraLogic::SetUpDir( float x, float y, float z)
	{
		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);

		// ����ͶӰ����
		pCamera->SetUpDir(  x, y, z);
	}


	//-------------------------------------------
	// For Render IO
	//-------------------------------------------
	// ��ȡ�۲�ͶӰ����
	Matrix44& MOCameraLogic::GetViewProj()
	{
		static Matrix44 viewProjOffset;

		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);

		viewProjOffset = pCamera->GetViewProj() * m_screenOffset;

		return viewProjOffset;
	}

	// ��ȡ����ͶӰ
	ShaderParamPtr& MOCameraLogic::GetVpOrthoProj()
	{
		*m_vpOrthoProj = GetOrtho();

		return m_vpOrthoProj;
	}

	// ��������
	const Matrix44& MOCameraLogic::GetOrtho()
	{
		static Matrix44 orthoOffset;

		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);

		orthoOffset = pCamera->GetOrtho() * m_screenOffset;

		return orthoOffset;
	}

	// �۲���������
	const Matrix44& MOCameraLogic::GetViewOrtho()
	{
		static Matrix44 viewProjOffset;

		FxEditCamera* pCamera = dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);

		viewProjOffset = pCamera->GetViewOrtho()  * m_screenOffset;

		return viewProjOffset;
	}

	// ��ȡ�����
	FxEditCamera* MOCameraLogic::GetNormalCamera()
	{
		return dynamic_cast<FxEditCamera*>( m_cameras[CT_Normal]);
	}

	// ��ȡ�����λ��
	Vector3& MOCameraLogic::GetPosition()
	{
		return (Vector3&)GetNormalCamera()->GetPosition();
	}

	// ��ȡ������
	float MOCameraLogic::GetNear()
	{
		return GetNormalCamera()->GetNear();
	}

	// ��ȡ�ҳ���
	Vector3	MOCameraLogic::GetRight()
	{
		return GetNormalCamera()->GetRight();
	}

	// ��ȡԶ����
	float MOCameraLogic::GetFar()
	{
		return GetNormalCamera()->GetFar();
	}

	// ��ȡ����
	Vector3& MOCameraLogic::GetFacing()
	{
		return GetNormalCamera()->GetDirection();
	}

	// ��ȡ�۲����
	Matrix44& MOCameraLogic::GetView()
	{
		return GetNormalCamera()->GetView();
	}

	// ��ȡͶӰ����
	Matrix44& MOCameraLogic::GetProj()
	{
		return GetNormalCamera()->GetProj();
	}	

	// ��ȡ��������Ѱ��Χ��
	const Rect3& MOCameraLogic::GetSearchRect()
	{
		return GetNormalCamera()->GetFrustem().GetAABB();
	}

	// ��ȡ������ƽ��ͷ��
	Frustum3* MOCameraLogic::GetFrustum()
	{
		return &GetNormalCamera()->GetFrustem();
	}
}