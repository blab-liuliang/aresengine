#pragma once

#include <vector>
#include <Core/AresMath.h>

using namespace std;

namespace Ares
{
	// FxKeyFrame
	struct FxKeyFrame 
	{
		float		m_time;			// ʱ���
		ColorRGB	m_color;
	};

	//--------------------------------
	// FxInterpolater 2013-1-25 ����
	//--------------------------------
	class FxInterpolater
	{
	public:
		// ��ӹؼ�֡
		void AddKeyFrame();

		// ��ֵ��ɫ
		bool InterplateColor( ColorRGB& color, float life);

	private:
		vector<FxKeyFrame>	m_keyFrames;		// �ؼ�֡
	};
}