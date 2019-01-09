#pragma once

#include "AeConfig.h"
#include "Function.h"
#include <string>
#include <Engine/RenderSystem/M1/M1Loader.h>

using namespace std;
using namespace Ares;

namespace M1_IGame
{
	struct SExportM1
	{
	public:
		// Save an M1 model
		bool Save();

	public:
		IDCardModel				m_m1;			// ����
		CM1Model		m_model;		// ģ��
		CM1Material		m_material;		// ����	
		CM1Animation	m_animation;	// ����
		CM1CollMesh		m_collidedTri;	// ��ײ��������
	};
}