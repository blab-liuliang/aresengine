#pragma once

#include <Engine/AresRoot.h>

namespace Ares
{
	//-------------------------------------
	// ģ�ͱ༭����Դ�༭�߼� 2013-1-9 ����
	//-------------------------------------
	class LightEditLogic
	{
	public:
		LightEditLogic();

		// ÿ֡����
		void FrameMove();

		// ��ȡ��Դ�б�
		const vector<LightPtr>& GetLights() { return m_lights; }

		// ��ȡ����Դ
		DirectionalLightPtr GetDominantLight() { return m_dominantLight; }

	private:
		DirectionalLightPtr		m_dominantLight;	// ����Դ
		DirectionalLightPtr		m_dirLight;
		vector<LightPtr>		m_lights;			// ��Դ
	};
}