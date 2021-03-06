#pragma once

#include <Core/AresMath.h>

namespace Ares
{
	namespace Curves
	{
		//---------------------------------------------------------------
		// Catmull_Rom3 2011-07-12  帝林
		// 主要参考：<<game programming gems 1>> 3.4-A*审美优化
		// 
		// 说明：
		//     Catmull-Rom样条可以使空间中的点序列变得平滑,它产生了一条
		// 能够经过原始路径中所有控制点的曲线(不像Bezier曲线,虽然比较平
		// 滑但是不能经过所有的控制点)。
		//	   Catmull-Rom公式要求4个输入点,然后给出一条位于第2点和第3点
		// 之间的光滑曲线。
		//     为了得到第1个输入点和第二个输入点之间的点,你可以为这个函数
		// 输入第1个点两次,接着输入第2点和第3点。为了获得第3点和第4点之间
		// 的点,可以先为函数输入第2点和第3点，然后输入第4点两次。
		// out 返回点
		// v1,v2,v3,v4 控制点
		// amount      控制量
		Vector3 CatmullRom3( Vector3& out, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float amount);

		// 求CatmullRom3 切线
		Vector3 CatmullRom3Tangent( Vector3& out, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float amount);
	}
}