#pragma once

#include <Engine/ResSystem/AresResSystem.h>

namespace Ares
{
	//-------------------------------------
	// ˮ�ڷű༭�߼�	2011-05-27	����
	//-------------------------------------
	class CWaterEditLogic
	{
	public:
		enum WaterType
		{
			EM_WOW_WATER = 0,
			EM_GPU_GEMS_2_19,	// gpu gems 2 ��19�½�
			EM_WATER_MASK,		// ��������
			EM_MAX_WATER_TYPES,
		};

		// ���캯��
		CWaterEditLogic();

		// �½�ˮ
		void New( const Vector3& pos, WaterType type=EM_GPU_GEMS_2_19);

	private:
		//SPtr<ISurfaceMaterial>  m_pMaterialWater[EM_MAX_WATER_TYPES];
	};
}