#pragma once

namespace Ares
{
	//-----------------------------------------------
	// ActionInterface 2013-9-5 ����
	// Basic interface to allow actions such as 
	// vehicles to be updated inside a PhysicsWorld
	//-----------------------------------------------
	class RigidBody;
	class PhysicsWorld;
	class ActionInterface
	{
	public:
		virtual ~ActionInterface() {}

		// ��̬����
		static RigidBody& GetFixedBody();

		// ����
		virtual void UpdateAction( PhysicsWorld* physicsWorld, float deltaTimeStep)=0;
	};
}