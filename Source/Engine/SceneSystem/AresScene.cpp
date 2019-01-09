#include "Engine/RenderSystem/AresRenderSystem.h"
#include <Engine/SceneSystem/GPWindow.h>
#include <Engine/SceneSystem/AresSceneTile.h>
#include <Engine/SceneSystem/AresScene.h>
#include <Engine/PhysicsSystem/AresCollisionObjectUserData.h>
#include <Core/AresChar.h>
#include <Physics/Intersect.h>
#include <Physics/DistLine3Point3.h>
#include <Engine/AresRoot.h>
#include <Engine/RenderSystem/AresTerrainTile.h>
#include <Physics/Collide.h>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#define TILE_SIZE 64

namespace Ares
{
	// �Ƿ��ص���Χ��
	bool SNavWindow::IsOverlapping( Rect3& rect)
	{
		if( m_x-m_radius>rect.m_max.x || m_x+m_radius<rect.m_min.x || m_y-m_radius>rect.m_max.y || m_y+m_radius<rect.m_min.y)
			return false;

		return true;
	}

	// ���캯��
	Scene::Scene(  CameraSystem* cameraCallback, const RenderSettings& settings)
		: m_cameraSystem( cameraCallback)
		, m_isActive( false)
	{
		m_renderSystem = new_ RenderSystem( *this);
		m_renderSystem->LoadRenderFactory( settings);

		m_version = 1;
		m_gpWindow= new_ CGPWindow;

		m_mainGPIdx.Set( 0, 0, TILE_SIZE, TILE_SIZE);
		m_gpWindow->SetWorld( this);

		m_physicsWorld = MakeSharePtr( new_ PhysicsWorld);

		m_submitRenderElementsConnection = m_renderSystem->Signal_OnSubmitRenderElements.connect( boost::bind<void>(&Scene::SubmitRenderElements, this));

		m_spabTime		= MakeShaderParam( float(0.f));
		m_spabSunDir	= MakeShaderParam( Vector3::ZAxis);
		m_spabSunColor	= MakeShaderParam( ColorRGB::Black);
	}

	// ��������
	Scene::~Scene()
	{
		// �����������
		m_physicsWorld.reset();

		// �Ͽ��źŲ�
		Signal_OnEntitysChanged.disconnect_all_slots();

		m_renderSystem->Signal_OnSubmitRenderElements.disconnect( m_submitRenderElementsConnection);
	}

	// �½�����
	Scene* Scene::Create( CameraSystem* cameraCallback, const RenderSettings& settings, const char* name, const char* location)
	{
		Scene* scene = new_ Scene( cameraCallback, settings);
		if( name && location)
		{
			scene->SetName( name);
			scene->SetLocation( location);
		}

		return scene;
	}

	// ���õ�������(���ĵ�x,y; �뾶radius)
	void Scene::SetNavWindow(  float x, float y, float radius)
	{
		m_navWindow.m_x = x;
		m_navWindow.m_y = y;
		m_navWindow.m_radius = radius;

		m_gpWindow->UpdatePosition( x, y, true);
		m_gpWindow->UpdateRadius( m_navWindow.m_radius);
	}

	// ����
	void Scene::FrameMove( float fTime)
	{
		if( m_isActive)
		{
			if( m_cameraSystem)
				m_cameraSystem->FrameMove( fTime);

			if( m_renderSystem)
				m_renderSystem->FrameMove( fTime);

			// ����ShaderParam
			m_spabTime->m_dataFloat[0] += fTime;


			for( EntityList::iterator it = m_entitys.begin(); it!=m_entitys.end(); it++)
			{
				it->second->FrameMove( fTime);
			}

			m_physicsWorld->FrameMove( fTime);
		}
	}

	// ��Ⱦ
	void Scene::Render()
	{
		if( m_isActive && m_renderSystem)
			m_renderSystem->Render();
	}

	// �ύ��ȾԪ��
	void Scene::SubmitRenderElements()
	{
		RenderElementMgr&	elementMgr	 = m_renderSystem->GetRenderElementMgr();
		static vector<Entity*> results;
		BuildSearchResults( results, m_cameraSystem->GetFrustum());
		foreach_( Entity* entity, results)
		{
			if( !entity)
				continue;

			switch( entity->GetType())
			{
			case ET_Render:
				{
					entity->SubmitRenderElements( elementMgr);
				}
				break;

			case ET_Light:
				{
					Light* light = dynamic_cast<Light*>(entity);
					if( entity->GetTypeDetail()==ED_LightDirection)
					{
						elementMgr.SetDomainLight( m_domainLight);

						*m_spabSunColor = m_domainLight->GetColor();
						*m_spabSunDir   = m_domainLight->GetDirection();
					}
					else
						elementMgr.AddLight( light);

					light->SubmitRenderElements( elementMgr);
				}
				break;
			}
		}
	}

	// ��Ⱦ�������
	void Scene::RenderDepth( const Box3& searchBox, const Matrix44& viewCrop)
	{
		vector<Entity*> entitys;
		BuildSearchResults( entitys, &searchBox);

		m_zWriteMgr.Write( entitys, viewCrop);
	}

	// ��Ѱ
	void Scene::BuildSearchResults( vector<Entity*>& results, const Shape* shape)
	{
		results.clear();

		A_ASSERT( shape->GetShapeType()==ST_Frustum || shape->GetShapeType()==ST_Rect3 || shape->GetShapeType()==ST_Box3);

		vector<CollisionObject*> objects;
		m_physicsWorld->RegionQueryCollisionObjects( objects, shape);
		for ( size_t i=0; i<objects.size(); i++)
		{
			CollisionObject::UserData* userData = objects[i]->GetUserData();
			if( userData)
			{
				switch( userData->m_type)
				{
				case COU_EntityFilter:
					{
						COUserDataEntityFilter* filter = dynamic_cast<COUserDataEntityFilter*>( userData);
						if( filter)
							results.push_back( filter->m_entity);
					}
					break;
				}
			}
		}
	}

	// ��Ѱ��Դ
	void Scene::SearchLights( vector<Light*>& lights, DirectionalLightPtr& domainLight)
	{
		domainLight = m_domainLight;

		for ( EntityList::iterator it=m_entitys.begin(); it!=m_entitys.end(); it++)
		{
			if( it->second->GetType() == ET_Light)
			{
				if( !domainLight || ( domainLight->GetName() != it->second->GetName()))
					lights.push_back( dynamic_cast<Light*>( it->second.get()));
			}
		}
	}

	// ��ȡ��ͼ��
	const char* Scene::GetName()
	{
		return m_name.c_str();
	}

	// ����ʵ������ȡʵ��
	s_ptr<Entity> Scene::GetEntity( const char* uniqueName)
	{
		ENTER_CRITICAL_SECTION( tHoder, m_qtCritication);

		EntityList::const_iterator it = m_entitys.find( uniqueName);
		if( it != m_entitys.end())
		{
			return it->second;
		}

		return s_ptr<Entity>();
	}

	// ���õ�ͼ��
	void Scene::SetName( const char* name)
	{
		m_name = name;
	}

	// ���ʵ��
	bool Scene::AddEntity( const char* uniqueName, s_ptr<Entity> pEntity, bool isSave)
	{
		if( !pEntity)
			return false;

		AddEntityToWorldOnly( uniqueName, pEntity);

		if( !isSave)
			return true;

		// ��ӵ�������
		const Rect3& worldbounds = pEntity->GetWorldBounds();
		if( pEntity->GetLocalBounds() == Rect3::Infinity)
		{
			SceneTile* pTile = dynamic_cast<SceneTile*>( GetTile( CGPIndex::Global));
			if( pTile)
				pTile->AddEntity( uniqueName, pEntity);
		}
		else
		{
			int minX  = ((int)worldbounds.m_min.x /*- m_size.m_posX*/) / m_mainGPIdx.GetWidth();
			int maxX = ((int)worldbounds.m_max.x /*- m_size.m_posX*/) / m_mainGPIdx.GetWidth();
			int minY  = ((int)worldbounds.m_min.y /*- m_size.m_posY*/) / m_mainGPIdx.GetHeight();
			int maxY = ((int)worldbounds.m_max.y /*- m_size.m_posY*/) / m_mainGPIdx.GetHeight();

			for ( int i=minX; i<=maxX; i++)
			{
				for( int j=minY; j<=maxY; j++)
				{
					CGPIndex tIdx = m_mainGPIdx.GetIndex( i, j);
					SceneTile* pTile = dynamic_cast<SceneTile*>(GetTile( tIdx));
					if( pTile)
						pTile->AddEntity( uniqueName, pEntity);
				}
			}
		}		

		SetAutoUnload( false);

		Signal_OnEntitysChanged( *this);

		return true;
	}

	// ��������Դ
	bool Scene::SetDomainLight( LightPtr light, size_t resolution)
	{
		if( light->GetLightType() == LT_Direction)
		{
			m_domainLight = dynamic_pointer_cast<DirectionalLight>(light);
			m_domainLight->GetCSMMgr()->SetShadowMapResolution( resolution);
			m_domainLight->GetCSMMgr()->SetScene( this);

			return true;
		}

		ALogSystem.Warning( "Only Direction light can be set as domain light!");

		return false;
	}

	// ���ʵ��
	bool Scene::AddEntityToWorldOnly( const char* uniqueName, s_ptr<Entity> pEntity)
	{
		ENTER_CRITICAL_SECTION( tHoder, m_qtCritication);

		if( GetEntity( uniqueName))
			return false;

		pEntity->SetName( uniqueName);
		m_entitys[uniqueName] = pEntity;

		// ʵ����Ϣ
		pEntity->OnAddToScene( this);

		// 
		if( pEntity->GetTypeDetail()==ED_LightDirection)
		{
			DirectionalLightPtr dirLight = dynamic_pointer_cast<DirectionalLight>( pEntity);
			if( dirLight)
				SetDomainLight( dirLight, 2048);
		}

		return true;
	}

	// ɾ��ʵ��(��ǰʵ���Χ����NavWindow���غ������ü���Ϊ1)
	void Scene::DelEntity( const char* uniqueName)
	{
		EntityList::iterator eit=m_entitys.find( uniqueName);
		if( eit!=m_entitys.end())
		{
			// ������������ж��
			if( m_physicsWorld)
				m_physicsWorld->RemoveCollisionObject( &(eit->second->GetCollSift()));

			m_entitys.erase(eit);
		}

		// �������п�
		for( GPTileMap::iterator it=m_tilesMap.begin(); it!=m_tilesMap.end(); it++)
		{
			SceneTile* pTile = dynamic_cast<SceneTile*>( it->second);
			if( pTile)
			{
				pTile->DelEntity( uniqueName);
			}
		}

		// �����Զ�ж��
		SetAutoUnload( false);

		Signal_OnEntitysChanged( *this);
	}

	// �������򱣴�λ��
	void Scene::SetLocation( const char* location)
	{
		m_location = location;
	}

	// ����ʵ��
	//ModelPtr Scene::CreateModel( const char* uniqueName, const char* filePath)
	//{
	//	ModelPtr model = MakeSharePtr( new_ Model);
	//	AddEntity( uniqueName, model);

	//	Model::IDCard* idcard = NULL;
	//	Serialization::UnSerializeFromBinaryFile( filePath, idcard);
	//	model->SetFilePath( filePath);
	//	idcard->RebuildModel( *model);

	//	return model;
	//}

	// ������Դ
	LightPtr Scene::CreateLight( const char* uniqueName, LightType type)
	{
		LightPtr result;
		switch( type)
		{
		case LT_Direction:
			result = MakeSharePtr( new_ DirectionalLight);
			break;
		}

		AddEntity( uniqueName, result);

		return result;
	}

	// inline
	// ��ȡ��Χ��
	bool Scene::GetBoundingBoxByLayer( Rect3& box, const char* layer, bool update)
	{
		if( !update)
		{
			int a = 10;
		}
		else
		{
			for( GPTileMap::const_iterator it=m_tilesMap.begin(); it!=m_tilesMap.end(); it++)
			{
				SceneTile* qtGPTile = dynamic_cast<SceneTile*>(it->second);
				if( qtGPTile)
					qtGPTile->GetBoundingBoxByLayer( box, layer, update);
			}
		}

		return true;
	}

	// ����Tile
	CGPTile* Scene::BuildTile( const CGPIndex& index)
	{
		if( !IsValidIndex( index))
			return 0;

		// tile�ļ����·��
		char tileLocation[256];
		sprintf( tileLocation,"%s%d_%d.tile", m_location.c_str(), index.GetX(), index.GetY());

		SceneTile* pTile = new_ SceneTile( tileLocation);

		return pTile;
	}

	// ����Tile
	void  Scene::DestroyTile( const CGPIndex& index)
	{
		CGPWorld::DestroyTile( index);

		ENTER_CRITICAL_SECTION( tHoder, m_qtCritication);

		// ������ü���Ϊ1��ʵ��
		for( EntityList::iterator it=m_entitys.begin(); it!=m_entitys.end(); )
		{
			// ���ʵ��
            Rect3 bouding = it->second->GetWorldBounds();
			if( it->second.unique() && !m_navWindow.IsOverlapping( bouding))
				m_entitys.erase(it++);
			else
				++it;
		}
	}

	// ����ʵ��
	void Scene::TidyEntityByTile()
	{
		for( EntityList::iterator eit=m_entitys.begin(); eit!=m_entitys.end(); eit++)
		{
			// �������п�
			for( GPTileMap::iterator it=m_tilesMap.begin(); it!=m_tilesMap.end(); it++)
			{
				SceneTile* pTile = dynamic_cast<SceneTile*>( it->second);
				if( pTile)
				{
					pTile->DelEntity( eit->first.c_str());

					AddEntity( eit->first.c_str(), eit->second);
				}
			}
		}
	}

	// ����
	void Scene::Load( const char* fileName)
	{
		// ��������
		ifstream ifs( fileName);
		if( ifs.is_open())
		{
			//SSize tSize;

			boost::archive::binary_iarchive biarchive( ifs);
			biarchive >> m_version >> m_name /*>> tSize*/ >> m_mainGPIdx;

			ifs.close();

			// ������֯
			//this->SetSize( tSize);

			string twLocation;
			FileUtils::ReplaceNameExt( twLocation, fileName,"");
			SetLocation( twLocation.c_str());

			// ���ع���ͼ
			string lightmapPath = m_location + "lightmap/";
			GetLightmapMgr().LoadXml( lightmapPath.c_str());
		}
	}

	// ����
	void Scene::Save( const char* fileName)
	{
		// ����ʵ��
		TidyEntityByTile();

		// 1.д�ļ�
		string tLocationName = fileName ? fileName : m_location + m_name;
		ofstream ofs( tLocationName.c_str());
		if( ofs.is_open())
		{
			boost::archive::binary_oarchive biarchive( ofs);
			biarchive << m_version << m_name /*<< m_size*/ << m_mainGPIdx;

			ofs.close();
		}

		// 2.�������ͼ
		GetLightmapMgr().SaveXml( (m_location + "lightmap/").c_str());

		// 4.������������
		for( GPTileMap::const_iterator it=m_tilesMap.begin(); it!=m_tilesMap.end(); it++)
		{
			SceneTile* qtGPTile = dynamic_cast<SceneTile*>(it->second);

			qtGPTile->Save();
		};

		SetAutoUnload( true);
	}

	//// ���ص�������
	//void  Scene::LoadTerrain( const char* terLocation)
	//{
	//	char tTerLocation[512];
	//	changeExt( tTerLocation, terLocation, ".ter");
	//	if( INVALID_FILE_ATTRIBUTES != GetFileAttributesA( tTerLocation))
	//	{
	//		// ���ڵ���
	//		TerrainPtr  pTerrain = AResSystem.MakeTerrain();
	//		if( pTerrain)
	//		{
	//			SetTerrain( pTerrain);

	//			pTerrain->Load( tTerLocation);
	//		}
	//	}
	//}
}