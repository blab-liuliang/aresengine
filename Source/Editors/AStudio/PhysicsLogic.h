#pragma once

#include <Engine/AresRoot.h>
#include <Physics/PhysicsWorld.h>

namespace Ares
{
	//---------------------------------------
	// �����߼�(��ǰ������ײ) 2012-08-13 ����
	//---------------------------------------
	class  PhysicsLogic 
	{
	public:
		PhysicsLogic();
		~PhysicsLogic();

		// ����ѡ
		bool Pick( Vector3* intersectPos, float* pDist);

		// ��ȡ��Ļ��ѡ����
		void GetPickRay( Vector3& rayOrig, Vector3& rayDir);

		// ���CollisionObject

	private:
		VisualSegment3*			m_segment;
	};
}