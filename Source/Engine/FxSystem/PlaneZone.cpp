#include <Engine/FxSystem/PlaneZone.h>

//BOOST_CLASS_EXPORT( Ares::FxPlaneZone)

namespace Ares
{
	// constructor
	FxPlaneZone::FxPlaneZone(const Vector3& position, const Vector3& normal)
		: FxZone( position)
	{
		SetNormal( normal);
	}

	// Checks whether a point is within the zone
	bool FxPlaneZone::Contains( const Vector3& point) const
	{
		return false;
	}

	// Check whether a line intersects the zone
	bool FxPlaneZone::Intersects( const Vector3& v0, const Vector3& v1, Vector3* intersection, Vector3* normal)const
	{
		float dist0 = Vector3Dot( m_tNormal, v0 - m_tfPosition);
		float dist1 = Vector3Dot( m_tNormal, v1 - m_tfPosition);

		// ���������ͬ��,���ཻ
		if( (dist0 <= 0.f) == (dist1 <= 0.f))
			return false;

		// ���ཻ��
		if( intersection)
		{
			// ��֤����һֵ
			if( dist0 <= 0.f)
				dist0 = -dist0;
			else 
				dist1 = -dist1;

			// ƽ�����ķ���
			if( normal)
				*normal = m_tNormal;

			float ti = dist0 / (dist0 + dist1);

			Vector3 tDir = v1 - v0;
			float tLength = tDir.Length();

			tLength *= ti;
			ti = tLength < 0.001f ? 0.f : ti * ( tLength - 0.001f) / tLength;

			(*intersection) = v0 + tDir * ti;
		}

		return true;
	}

	// Generates a position inside this zone for a given particle
	void FxPlaneZone::GeneratePosition( FxParticle& particle, bool full) const
	{

	}

	// ���÷���
	void FxPlaneZone::SetNormal( const Vector3& normal)
	{
		m_normal = normal;
		m_normal.Normalize();
		m_tNormal = m_normal;
	}
}