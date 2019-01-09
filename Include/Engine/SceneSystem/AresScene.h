#pragma once

#include <string>
#include "GPWindow.h"
#include "GPWorld.h"
#include "LightmapMgr.h"
#include <Core/Graphics/AresRenderSettings.h>
#include <Physics/Shapes.h>
#include "Engine/Foundation/Ares3DEngine_h.h"
#include "Engine/RenderSystem/AresRenderSystem.h"
#include "Engine/RenderSystem/AresTerrain.h"
#include <Engine/RenderSystem/ZWriteMgr.h>
#include "Engine/CameraSystem/AresCameraSystem.h"
#include <Physics/PhysicsWorld.h>
#include <Physics/Bullet/btBulletDynamicsCommon.h>

using namespace std;

namespace Ares
{
	// SMapWindow
	struct SNavWindow
	{
		float  m_x;			// ���ĵ�x
		float  m_y;			// ���ĵ�y
		float  m_radius;	// �뾶

		// �Ƿ��ص���Χ��
		bool IsOverlapping( Rect3& rect);
	};

	//---------------------------------
	// Scene 2011-08-16 ����
	//---------------------------------
	class SceneTile;
	class Scene : public CGPWorld
	{
	public:
		friend class SceneTile;
		friend class SceneSystem;
		typedef map<string, EntityPtr> EntityList;
	public:
		~Scene();

		// �½�����
		static Scene* Create( CameraSystem* cameraCallback, const RenderSettings& settings, const char* name, const char* location);

		// ���õ�������(���ĵ�x,y; �뾶radius)
		void SetNavWindow(  float x, float y, float radius);

		// ����
		void FrameMove( float fTime);

		// ��Ⱦ
		void Render();

		// �ύ��ȾԪ��
		void SubmitRenderElements();

	public:
		// ������������
		void SetPhysicsWorld( PhysicsWorldPtr& physicsWorld) { m_physicsWorld=physicsWorld; }

		// ��ȡ��������
		PhysicsWorldPtr& GetPhysicsWorld() { return m_physicsWorld; }

		// ��Ѱ(Frustum Box3)
		void BuildSearchResults( vector<Entity*>& results, const Shape* shape);

		// ��Ѱ��Դ
		void SearchLights( vector<Light*>& lights, DirectionalLightPtr& domainLight);

		// ��ȡ���������о�̬ʵ��
		const EntityList& GetStaticEntitys() const { return m_entitys; }

	public:
		// ��ȡ��Χ��
		bool GetBoundingBoxByLayer( Rect3& box, const char* layer, bool update=false);

	public:
		// ��ȡ��ͼ��
		const char* GetName();

		// �Ƿ���ͣ
		bool IsPaused() const { return !m_isActive; }
		// ����
		void Reset() {}

		// ��ȡ�����ϵͳ
		CameraSystem& GetCameraSystem() { return *m_cameraSystem; }

		// ��ȡ��Ⱦϵͳ
		RenderSystem& GetRenderSystem() { return *m_renderSystem; }

		// ��ȡSPAB
		ShaderParamPtr GetSPABElapsedTime() { return m_spabTime; }
		ShaderParamPtr GetSPABSunColor()	{ return m_spabSunColor; }
		ShaderParamPtr GetSPABSunDir()		{ return m_spabSunDir; }

		// ��ȡ�洢λ��
		const string& GetLocation() const { return m_location; }

		// ��ȡ�����Χ��
		const Rect3& GetWorldBounds() { return m_worldBounds; }

		// ����ʵ������ȡʵ��
		EntityPtr GetEntity( const char* uniqueName);

		// ��ȡ����ͼ������
		LightmapMgr& GetLightmapMgr() { return m_lightmapMgr; }

		// ��ȡ��������ϵͳ
		SceneSystem* GetSceneSystem() { return m_sceneSystem; }

	public:
		// ���õ�ͼ��
		virtual void SetName( const char* name);

		// �������򱣴�λ��
		virtual void SetLocation( const char* location);

		// �����Ƿ�
		void SetActived( bool isActive) { m_isActive = isActive; }

		// ������Դ
		LightPtr CreateLight( const char* uniqueName, LightType type);

		// ���ʵ��
		bool AddEntity( const char* uniqueName, s_ptr<Entity> pEntity, bool isSave=true);

		// ��������Դ
		bool SetDomainLight( LightPtr light, size_t resolution);

		// ��ȡ����Դ
		DirectionalLightPtr GetDomainLight() { return m_domainLight; }

		// ɾ��ʵ��
		void DelEntity( const char* uniqueName);

		// ʵ��䶯�ź�
		signal<void( const Scene&)> Signal_OnEntitysChanged;

	public:
		// ����Tile
		virtual CGPTile* BuildTile( const CGPIndex& index);

		// ����Tile
		virtual void  DestroyTile( const CGPIndex& index);

		// ����
		virtual void Load( const char* fileName);

		// ����
		virtual void Save( const char* fileName=0);

		// ��Ⱦ�������
		void RenderDepth( const Box3& searchBox, const Matrix44& viewCrop);

	private:
		Scene( CameraSystem* cameraCallback, const RenderSettings& settings);

		// ����ʵ��
		void TidyEntityByTile();

		// ���ʵ��
		bool AddEntityToWorldOnly( const char* uniqueName, s_ptr<Entity> pEntity);

	private:
		int						m_version;			// ��ǰ�汾��
		string					m_name;				// ������
		string					m_location;			// λ��

		SNavWindow				m_navWindow;		// ��������

		Rect3					m_worldBounds;		// �����Χ��
		CGPIndex				m_mainGPIdx;		// ��GP����,����tile��С��

		CGPWindow*				m_gpWindow;			// ��������
		
		PhysicsWorldPtr			m_physicsWorld;		// ��������
		btDynamicsWorld*		m_dynamicsWorld;	// Bullet��������

		EntityList				m_entitys;			// ʵ���б�
		DirectionalLightPtr		m_domainLight;		// ����Դ
		LightmapMgr				m_lightmapMgr;		// ����ͼ������ ��������ݡ�
		ZWriteMgr				m_zWriteMgr;		// �����Ⱦ������

		SceneSystem*			m_sceneSystem;

		boost::recursive_mutex	m_qtCritication;	// ����ʵ���б�
		boost::recursive_mutex	m_rtCritication;

		boost::signals2::connection m_submitRenderElementsConnection;	// ��Ⱦ����

		ShaderParamPtr			m_spabTime;			// ����ʱ��
		ShaderParamPtr			m_spabSunDir;		// ����Դ����
		ShaderParamPtr			m_spabSunColor;		// ����Դ��ɫ

		bool					m_isActive;				// ��Ծ״̬
		CameraSystem*			m_cameraSystem;			// �����ϵͳ
		RenderSystem*			m_renderSystem;			// ��Ⱦϵͳ
	};
}