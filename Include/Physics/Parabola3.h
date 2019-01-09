#pragma once

#include <vector>
#include <Core/AresMath.h>
#include "Rect3.h"

using namespace std;

namespace Ares
{
	//-----------------------------------
	// ProjectileMotion3 2013-3-14 ����
	//-----------------------------------
	struct Parabola3
	{
		Vector3		m_orig;			// ���
		Vector3		m_v0;			// ����
		Vector3		m_g;			// ����

		// construction
		Parabola3( const Vector3& orig,  const Vector3& v0, const Vector3& g);

		// get turn point
		float GetTurnPos( Vector3& oPos); 

		// build curent pos by time
		void BuildPos( Vector3& oPos, float t) const;

		// interpolate
		void Interpolate( vector<Vector3>& oPos, float t0, float t1, size_t intepolateNum) const;

		// ����AABB��Χ����
		void BuildAABBArray( vector<Rect3>& aabbArrays, const Transform& trans, float t0, float t1, size_t num) const;

		// �������ľ���
		float DistanceTo( const Vector3& p) const;

		// ִ��ת��
		void DoTransform( const Transform& transform);
	};
}