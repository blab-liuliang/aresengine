#pragma once

#include "ThirdViewCamera.h"

namespace Ares
{
	//-----------------------------------------------------------------
	//  β���ӽ��������2009-12-28 18��02 -- ����
	//-----------------------------------------------------------------
	class CFollowViewerCamera : public LiberityViewCamera
	{
	public:
		CFollowViewerCamera();
		virtual BOOL  FrameMove(float fTime);
		virtual void  UpdateCameraDir(float relativeZAngle, float relativeYAngle);
		virtual void  SetBindPos(Vector3* bindPos);	

		// ���ù۲��
		virtual void SetLookAt(Vector3 *v_pLookAt);

		// ����λ�õ�
		virtual void SetPos(Vector3* vPos);

		// ����Ĭ�ϰ뾶
		void SetDefaultRadius(float relativeRadius);

		virtual void  Release();

	protected:
		virtual void UpdatePosOrLookAt();

	private:
		Vector3* m_bindLookAt;	// Ŀ���
	};
}