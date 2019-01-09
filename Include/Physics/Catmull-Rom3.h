#pragma once

#include <Core/AresMath.h>

namespace Ares
{
	namespace Curves
	{
		//---------------------------------------------------------------
		// Catmull_Rom3 2011-07-12  ����
		// ��Ҫ�ο���<<game programming gems 1>> 3.4-A*�����Ż�
		// 
		// ˵����
		//     Catmull-Rom��������ʹ�ռ��еĵ����б��ƽ��,��������һ��
		// �ܹ�����ԭʼ·�������п��Ƶ������(����Bezier����,��Ȼ�Ƚ�ƽ
		// �����ǲ��ܾ������еĿ��Ƶ�)��
		//	   Catmull-Rom��ʽҪ��4�������,Ȼ�����һ��λ�ڵ�2��͵�3��
		// ֮��Ĺ⻬���ߡ�
		//     Ϊ�˵õ���1�������͵ڶ��������֮��ĵ�,�����Ϊ�������
		// �����1��������,���������2��͵�3�㡣Ϊ�˻�õ�3��͵�4��֮��
		// �ĵ�,������Ϊ���������2��͵�3�㣬Ȼ�������4�����Ρ�
		// out ���ص�
		// v1,v2,v3,v4 ���Ƶ�
		// amount      ������
		Vector3 CatmullRom3( Vector3& out, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float amount);

		// ��CatmullRom3 ����
		Vector3 CatmullRom3Tangent( Vector3& out, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float amount);
	}
}