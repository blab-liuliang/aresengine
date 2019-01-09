#pragma once

#include <map>
#include <Physics/PhysicsWorld.h>
#include <Engine/RenderSystem/AresVisualShape.h>
#include <Physics/Bullet/btBulletDynamicsCommon.h>

using namespace std;

namespace Ares
{
	//---------------------------------
	// �������縨����ʾ 2013-9-10 ����
	//---------------------------------
	class BulletDebugDrawer
	{
	public:
		BulletDebugDrawer( Scene* scene, btDynamicsWorld* dynamicsWorld);
		~BulletDebugDrawer();

		// ����
		void FrameMove( float timeStep);

	private:
		// ��ȡVisualShape
		VisualShape* GetVisualShape();

		// ��Ⱦ
		void Draw( Matrix44& m, const btCollisionShape* shape, const btVector3& color, const btVector3& worldBoundsMin, const btVector3& worldBoundsMax);

	private:
		Scene*					m_scene;				// ����
		btDynamicsWorld*		m_dynamicsWorld;		// ��������
		int						m_numActive;			// ��ǰ�����
		vector<VisualShape*>	m_visualShapes;			// ������
	};
}