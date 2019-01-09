#include "ReflectionCamera.h"

namespace Ares
{
	// ��ȡ�۲�ͶӰ����
	Matrix44&  CReflectionCamera::GetViewProj()
	{
		// ��Ϊ�Ǿ���, ��ת������ͷ����ϵ��Ҫ�������ҶԵ��Ķ���.
		Matrix44 matMirror;
		Matrix44Scaling( matMirror, -1.f, 1.f, 1.f);
	
		m_matViewProj = m_matView * matMirror * m_matProj;

		return m_matViewProj;
	}

	// ��ȡ�������պо���
	Matrix44&  CReflectionCamera::GetSkyViewProj()
	{
		static Matrix44 mirrorSkyBox;
		Matrix44Scaling( mirrorSkyBox, -1.f, 1.f, 1.f);

		// ������պо���
		mirrorSkyBox = m_matSkyView * mirrorSkyBox * m_matUnitProj;

		return mirrorSkyBox;
	}
}