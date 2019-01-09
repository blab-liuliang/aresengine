#include "FxEditCamera.h"

namespace Ares
{
	// ���캯��
	FxEditCamera::FxEditCamera() 
		: LiberityViewCamera()
	{
		m_bindLookAt = NULL;
	}

	// ���������λ�� 
	void FxEditCamera::UpdateCameraDir(float relativeZAngle, float relativeYAngle)
	{
		m_verticleAngle += relativeZAngle;	   m_horizonAngle += relativeYAngle;

		m_verticleAngle = min( m_verticleAngle, PI - 0.01f);
		m_verticleAngle = max( m_verticleAngle, 0.01f);

		float tScale = abs( sin( m_verticleAngle)); 
		m_vForward.x = tScale * cos( m_horizonAngle);
		m_vForward.y = tScale * sin( m_horizonAngle);
		m_vForward.z = cos( m_verticleAngle);

		m_vForward = m_matUpMatch.TransformVector3( m_vForward);

		UpdatePosOrLookAt();
		UpdateViewMatrix();	 // ������ͼ����
	}

	BOOL FxEditCamera::FrameMove(float fTime)
	{
		if(m_bindLookAt != NULL &&  *m_bindLookAt != m_vLookAt)		// �󶨹۲���ƶ�
		{
			m_vLookAt = *m_bindLookAt;

			m_needUpdateViewMatrix = TRUE;	
		}

		m_fCurRadius = m_fDefaultRadius;

		UpdatePosOrLookAt();
		UpdateViewMatrix();

		return TRUE;
	}

	void FxEditCamera::SetBindPos(Vector3 *bindPos)
	{
		m_bindLookAt = bindPos;
	}

	void FxEditCamera::Release()
	{
		m_bindLookAt = NULL;
	}

	// ���ù۲��
	void FxEditCamera::SetLookAt(Vector3 *v_pLookAt)
	{
		m_vLookAt = *v_pLookAt;

		UpdatePosOrLookAt();
		UpdateViewMatrix();
	}

	// ����λ�õ�
	void FxEditCamera::SetPos(Vector3* vPos)
	{
		m_vForward = m_vLookAt - *vPos;
		SetDefaultRadius( m_vForward.Length());
		m_vForward.Normalize();

		m_vForward = m_matUpMatch.TransformVector3( m_vForward);

		m_verticleAngle = acos( m_vForward.z);
		float tScale = abs( sin( m_verticleAngle));

		m_horizonAngle = asin( m_vForward.y/ tScale);

		UpdatePosOrLookAt();
		UpdateViewMatrix();
	}

	// ����Ĭ�ϰ뾶
	void FxEditCamera::SetDefaultRadius(float relativeRadius)
	{
		m_fCurRadius	 = relativeRadius;
		m_fDefaultRadius = relativeRadius;

		m_fDefaultRadius = std::min<float>(m_fDefaultRadius, m_fMaxRadius);
		m_fDefaultRadius = std::max<float>(m_fDefaultRadius, m_fMinRadius);
	}

	// ����λ��
	void FxEditCamera::UpdatePosOrLookAt()
	{ 
		m_vPosition = m_vLookAt - m_fCurRadius * m_vForward; 
	}

	// viewProjMatrix
	Matrix44&  FxEditCamera::GetViewProj()
	{
		return m_matViewProj;
	}
}