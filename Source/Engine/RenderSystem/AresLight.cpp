#include <Engine/RenderSystem/AresLight.h>

namespace Ares
{
	// ���캯��
	Light::Light( EntityTypeDetail typeDetail)
		: Entity( ET_Light, typeDetail),
		  m_color( ColorRGB( 1.f, 2.f, 2.5f))
	{
		switch( m_typeDetail)
		{
		case ED_LightDirection:
			m_lightType = LT_Direction;
			break;

		case ED_LightAmbient:
			m_lightType = LT_Ambient;
			break;

		case ED_LightPoint:
			m_lightType = LT_Point;
			break;

		case ED_LightSpot:
			m_lightType = LT_Spot;
			break;

		default:
			A_ASSERT( FALSE);
			break;
		}

		m_spabColor = MakeShaderParam();
	}

	// ��������
	Light::~Light()
	{
	}

	// ��ȡ����(DirLight)
	const Vector3& Light::GetDirection() const
	{
		A_ASSERT( FALSE);

		return Vector3::Zero;
	}

	// ���ó��� LT_Direction
	void Light::SetDirection( const Vector3& dir)
	{
		A_ASSERT( FALSE);
	}

	//// ��������ֱ���
	//void Light::SetShadowMapResolution( size_t resolution)
	//{
	//	A_ASSERT( FALSE);
	//}

	// ������ɫ
	void Light::SetColor( const ColorRGB& color)
	{
		m_color = color;

		*m_spabColor = float3( m_color.r, m_color.g, m_color.b) * m_color.a;
	}

	// �ж�ĳ���Ƿ��ڹ�Դ��Ӱ��
	bool Light::IsPointIn( const Vector3& pos)
	{
		const Rect3 tWorldBounds = GetWorldBounds();
			
		return tWorldBounds.IsPointIn( pos);
	}
}