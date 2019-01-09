#ifndef ARES_CLOTH_FABRIC_BUILDER_H
#define ARES_CLOTH_FABRIC_BUILDER_H

#include <vector>
#include <Core/AresTransform.h>
#include <Physics/MassSpringSystem.h>
#include "AresClothFabric.h"

using namespace std;

namespace Ares
{
	// GridClothBuilder 2013-7-11
	class GridClothBuilder
	{
	public:
		// ���캯��
		GridClothBuilder( ClothFabric& cloth, int width, int height, const Transform& transform);

	private:
		// ��������,��ȡ����
		bool GetMassIndex( int& index, int w, int h);

		// ��ӵ���
		void AddSpring( MassSpringSystem::Spring& spring);

	public:
		int									m_width;			// ��
		int									m_height;			// ��
		vector<WORD>						m_triIndices;		// ����������
		vector<MassSpringSystem::MassPoint>	m_massPoints;		// �ʵ�
		vector<MassSpringSystem::Spring>	m_springs;			// ����
	};
}

#endif