#pragma once

#include "AresFxModel.h"
#include "AresFxEmitter.h"
#include "AresFxParticleSystem.h"
#include "AresFxZone.h"
#include "AresFxModifier.h"
#include "SphericEmitter.h"
#include "PointZone.h"
#include "PlaneZone.h"
#include "Box3Zone.h"
#include "Obstacle.h"

namespace Ares
{
	//---------------------------
	// ����ϵͳ 2011-9-13 ����
	//---------------------------
	class FxSystem
	{
//	public:
//		// �½�FxModel
//		FxModel* CreateModel( int enableFlag = FxModel::FLAG_RED | FxModel::FLAG_GREEN | FxModel::FLAG_BLUE, int mutableFlag = FxModel::FLAG_NONE, int randomFlag = FxModel::FLAG_NONE, int interpolateFlag = FxModel::FLAG_NONE);
//
//		// �����������ӷ�����
//		FxSphericEmitter* CreateSphericEmitter( const Vector3& dir = Vector3(0.f, 0.f, -1.f), float angleA=0.f,float angleB=0.f);
//
//		// �½���
//		FxParticleSystem* CreateGroup( FxModel* model, size_t capacity);
//
//		// ����������
//		FxPointZone* CreatePointZone( const Vector3& position = Vector3( 0.f, 0.f, 0.f));
//
//		// ����ƽ������
//		FxPlaneZone* CreatePlaneZone(const Vector3& position=Vector3(0.f,0.f,0.f), const Vector3& normal=Vector3(0.f,0.f,1.f));
//
//		// �����ϰ���
//		IFxObstacle* CreateObstacle( FxZone* zone=NULL, FxModifier::EModifierTrigger trigger=FxModifier::INTERSECT_ZONE, float bouncingRatio = 1.f, float friction=1.f);
//
//	public:
//		// ����PointRender
//		FxPointRender* CreatePointRender();
//
//		// ����QuadRender
//		FxQuadRender* CreateQuadRender();

	private:
	};
}