#pragma once

#include <Core/AresMath.h>

namespace Ares
{
	namespace Curves
	{
		//---------------------------------------------------------------
		// Bezier3 2011-07-12  ����
		// ��Ҫ�ο���<<DirectX ʵʱ��Ⱦ�������>> ��21�½� ��������Ƭ
		//			 ����˹̹����ʽ ( Bernstein polynomials)
		// 
		// ˵����
		//	��һ����Ƶ�������������(�˴�����ֻ�����ĸ����Ƶ��ʵ��)
		// out ���ص�
		// v1,v2,v3,v4 ���Ƶ�
		// amount      ������
		Vector3 Bezier3( Vector3& out, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float amount);

		// ��Bezier3�е�����
		Vector3 Beizer3Tangent( Vector3& out, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float amount);
	}
}