#include "Physics/Bezier3.h"

namespace Ares
{
	namespace Curves
	{
		//---------------------------------------------------------------
		// Bezier3 2011-07-12  ����
		// ��Ҫ�ο���<<DirectX ʵʱ��Ⱦ�������>> ��21�½� ��������Ƭ
		// 
		// ˵����
		//	��һ����Ƶ�������������(�˴�����ֻ�����ĸ����Ƶ��ʵ��)
		// out ���ص�
		// v1,v2,v3,v4 ���Ƶ�
		// amount      ������
		Vector3 Bezier3( Vector3& out, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float amount)
		{
			// amount
			float  s  = amount;
			float _s = 1.f - amount;

			out = v1 *   _s * _s * _s +
				v2 *  3.f *  s * _s * _s +
				v3 *  3.f *  s *  s * _s +
				v4 *    s *  s *  s;

			return out;
		}

		// ��Bezier3�е�����( ��)
		Vector3 Beizer3Tangent( Vector3& out, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float amount)
		{
			// amount
			float s  = amount;
			float _s = 1.f - amount;
			float s2 = amount * amount;

			float b1 = -3.f * _s   * _s;
			float b2 =  3.f - 12.f * s   + 9.f * s2;
			float b3 =  6.f * s    - 9.f * s2;
			float b4 =  3.f * s2;

			out = v1 * b1 +
				v2 * b2 +
				v3 * b3 +
				v4 * b4;

			return out;
		}
	}
}