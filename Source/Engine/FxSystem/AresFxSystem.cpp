//#include <Engine/FxSystem/AresFxSystem.h>
//#include <Engine/FxSystem/Model.h>
//#include <Engine/FxSystem/AresFxFlow.h>
//#include "SPhericEmitter.h"
//#include "PointZone.h"
//#include "PlaneZone.h"
//#include <Engine/FxSystem/Obstacle.h>
//#include <Engine/FxSystem/AresFxPointRender.h>
//
//namespace Ares
//{
//	// �½�FxModel
//	FxModel* FxSystem::CreateModel( int enableFlag, int mutableFlag, int randomFlag, int interpolateFlag)
//	{
//		FxModel* model = new_ FxModel( enableFlag, mutableFlag, randomFlag, interpolateFlag);
//	
//		return model;
//	}
//
//	// �����������ӷ�����
//	FxSphericEmitter* FxSystem::CreateSphericEmitter(  const Vector3& dir, float angleA, float angleB)
//	{
//		FxSphericEmitter* emitter = new_ FxSphericEmitter( dir, angleA, angleB);
//
//		return emitter;
//	}
//
//	// �½���
//	FxParticleSystem* FxSystem::CreateGroup(  FxModel* model, size_t capacity)
//	{
//		//FxFlow* group = new FxFlow( model, capacity);
//
//		//return group;
//		return NULL;
//	}
//
//	// ����������
//	FxPointZone* FxSystem::CreatePointZone( const Vector3& position)
//	{
//		FxPointZone* zone = new_ FxPointZone( position);
//
//		return zone;
//	}
//
//	// ����ƽ������
//	FxPlaneZone* FxSystem::CreatePlaneZone(const Vector3& position, const Vector3& normal)
//	{
//		FxPlaneZone* zone = new_ FxPlaneZone( position, normal);
//		
//		return zone;
//	}
//
//	// �����ϰ���
//	IFxObstacle* FxSystem::CreateObstacle( FxZone* zone, FxModifier::EModifierTrigger trigger, float bouncingRatio, float friction)
//	{
//		CObstacle* obstacle = new_ CObstacle( zone, trigger, bouncingRatio, friction);
//
//		return obstacle;
//	}
//
//	// ����PointRender
//	FxPointRender* FxSystem::CreatePointRender()
//	{
//		FxPointRender* pointRender = new_ FxPointRender;
//
//		A_ASSERT( pointRender);
//
//		return pointRender;
//	}
//
//	// ����QuadRender
//	FxQuadRender* FxSystem::CreateQuadRender()
//	{
//		FxQuadRender* quadRender = new_ FxQuadRender;
//
//		A_ASSERT( quadRender);
//
//		return quadRender;
//	}
//}