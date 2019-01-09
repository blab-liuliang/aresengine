#include <Engine/CameraSystem/AresCameraSystem.h>

namespace Ares
{
	// ���캯��
	CameraSystem::CameraSystem()
		: m_active( CT_Normal)
	{
		for( int type=SP_View; type<SP_Total; type++)
		{
			m_spab[type] = MakeShaderParam();
		}
	}

	// ��������
	CameraSystem::~CameraSystem()
	{

	}

	// ��ȡ�۲������ת����
	Matrix44 CameraSystem::GetViewRotationInverse()
	{
		Matrix44 rotView = GetView();
		rotView._41 = rotView._42 = rotView._43 = 0.f;

		Matrix44 invView;
		Matrix44Inverse( invView, rotView);

		return invView;
	}

	// ��ȡshader�󶨲���
	ShaderParamPtr CameraSystem::GetSPAB( SPType type) const
	{
		return m_spab[type];
	}

	// ���û�Ծ�����
	void CameraSystem::SetActive( CameraType type)
	{
		m_active = type;
	}
}