#pragma once

#include "ThirdViewCamera.h"

namespace Ares
{
	//----------------------------------------------
	// ��Ч�༭��ר�� 2012-8-20 ����
	//----------------------------------------------
	class FxEditCamera : public LiberityViewCamera
	{
	public:
		FxEditCamera();
		virtual BOOL  FrameMove(float fTime);
		virtual void  UpdateCameraDir(float relativeZAngle, float relativeYAngle);
		virtual void  SetBindPos(Vector3* bindPos);	

		// ���ù۲��
		virtual void SetLookAt(Vector3 *v_pLookAt);

		// ����λ�õ�
		virtual void SetPos(Vector3* vPos);

		// ����Ĭ�ϰ뾶
		void SetDefaultRadius(float relativeRadius);

		// viewProjMatrix
		virtual Matrix44&  GetViewProj();

		// �ͷ���Դ
		virtual void  Release();

	protected:
		virtual void UpdatePosOrLookAt();

	private:
		Vector3*	m_bindLookAt;	// Ŀ���
	};
}