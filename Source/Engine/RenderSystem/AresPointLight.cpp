#include <Engine/RenderSystem/AresPointLight.h>

namespace Ares
{
	// ���캯��
	PointLight::PointLight() 
		: Light( ED_LightPoint) 
	{
		SetAttenuate( 1.f, 1.f, 1.f);
	}

	// ����˥����
	void PointLight::SetAttenuate( float a, float b, float c)
	{
		Rect3 localBounds;
		localBounds.UnionPoint( Vector3( -10.f, -10.f, -10.f));
		localBounds.UnionPoint( Vector3(  10.f,  10.f,  10.f));

		SetLocalBounds( localBounds);
	}
}