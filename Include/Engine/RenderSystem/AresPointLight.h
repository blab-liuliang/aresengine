#pragma once

#include "AresLight.h"

namespace Ares
{
	//---------------------------------------------------
	// ���Դ  ILightPoint 2010-08-25  ����
	//---------------------------------------------------
	class PointLight : public Light
	{
	public:
		// ���캯��
		PointLight();

		// ��ȡ˥����ʽ( a, b*d, c*d*d)ϵ��a, b ,c������ dΪ��Դλ�õ�����ľ���
		const Vector3& GetAttenuate() { return m_attenuate; }

		// ����˥����
		void SetAttenuate( float a, float b, float c);

		// �ύ��ȾԪ��
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr) {}

	private:
		Vector3		m_attenuate;
	};
}