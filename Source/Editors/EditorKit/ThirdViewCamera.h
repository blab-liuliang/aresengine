#pragma once

#include "BaseCamera.h"

namespace Ares
{
	//-----------------------------------------------------------------
	//  �����˳������(�����ӽ������)��2009-12-28 18��02 -- ����
	//-----------------------------------------------------------------
	class LiberityViewCamera : public Camera
	{
	public:
		LiberityViewCamera();
		virtual BOOL  FrameMove(float fTime);
		virtual void  UpdateCameraDir(float relativeZAngle, float relativeYAngle);
		virtual void  SetYawAngle(float yAngle){ m_horizonAngle = yAngle; UpdateCameraDir(0.0f, 0.0f); UpdatePosOrLookAt();};
		virtual void  SetRollAngle(float zAngle){ m_verticleAngle = zAngle; UpdateCameraDir( 0.0f, 0.0f); UpdatePosOrLookAt();};
		virtual float GetYawAngle(){  return m_horizonAngle; };
		virtual float GetRollAngle(){ return m_verticleAngle; };
		virtual void  SetCurRadius(float fRadius);
		virtual void  ChangeDefaultRadius(float relativeRadius);
		virtual void  SetDefaultRadius(float fRadius);
		virtual void  SetViewParams(Vector3* vPos, Vector3* vLookAt);
		virtual void  SetPos(Vector3* vPos);
		virtual void  SetLookAt(Vector3* v_pLookAt);
		virtual void  Release();

		// Zoom
		virtual void Zoom( float radius);

		// ��ȡ��ǰ�뾶
		virtual float GetCurRadius(){ return m_fCurRadius; }

		// ��ȡĬ�ϰ뾶
		virtual float GetDefaultRadius() { 
			return m_fDefaultRadius; }

	protected:
		virtual void UpdatePosOrLookAt();

	protected:
		float m_fCurRadius;			// ��ǰ�뾶 (�����LookAt�㵱����)
		float m_fDefaultRadius;		// Ĭ�ϰ뾶
		float m_fMinRadius;			// ���������С�뾶
		float m_fMaxRadius;			// ����������뾶

		BOOL  m_needUpdateViewMatrix;
	};
}

