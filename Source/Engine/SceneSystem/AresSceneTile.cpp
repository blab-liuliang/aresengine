#include "Engine/RenderSystem/AresModelIDCard.h"
#include <Engine/SceneSystem/AresSceneTile.h>
#include "Engine/RenderSystem/AresLight.h"
#include <Engine/SceneSystem/QtGPWorld.h>
#include <Engine/SceneSystem/AresScene.h>
#include "Engine/AresRoot.h"
#include <Physics/BvhTriangle3Mesh.h>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

namespace Ares
{
	namespace DB
	{
		//-----------------------------------
		// ʵ����ݱ�ʶ 2013-4-22 ����
		// �����ؽ�ʵ��
		//-----------------------------------
		struct IDCardEntity
		{
			string		m_layer;		// ����
			string		m_name;			// ʵ����
			int			m_type;			// ʵ������
			Transform	m_transform;	// ת��

			// ��ȡ��ݱ�ʶ��
			virtual void ExtractFromEntity( EntityPtr& entity, SceneTile* tile)
			{
				m_layer		= "default";
				m_name		= entity->GetName();
				m_type		= entity->GetTypeDetail();
				m_transform = entity->GetTransform();
			}

			// �ؽ�ʵ��
			virtual void ReBuildEnityToWorld( Scene* world, SceneTile* tile)=0;

			// ���л�
			template <typename Archive> void serialize( Archive& ar, const unsigned int version)
			{
				ar & m_layer;
				ar & m_name;
				ar & m_type;
				ar & m_transform;
			}
		};

		//------------------------------------
		// ģ�ͱ�ʶ 2013-4-22 ����
		//------------------------------------
		struct IDCardModel : public IDCardEntity
		{
			string		m_resPath;		// ��Դ·��

			// ��ȡ��ݱ�ʶ��
			virtual void ExtractFromEntity( EntityPtr& entity, SceneTile* tile)
			{
				IDCardEntity::ExtractFromEntity( entity, tile);

				m_resPath	= dynamic_pointer_cast<Model>( entity)->GetFilePath();
			}

			// �ؽ�ʵ��
			virtual void ReBuildEnityToWorld( Scene* world, SceneTile* tile)
			{
				EntityPtr pEntity = world->GetEntity( m_name.c_str());
				if( !pEntity)
				{
					ModelPtr m1Entity = AResSystem.LoadModel( m_resPath.c_str());
					m1Entity->SetTransform( m_transform);
					world->AddEntity( m_name.c_str(), m1Entity);

					// ���ù���ͼ
					TexturePtr lightmap;
					Vector4	   lightmapViewport;
					if( world->GetLightmapMgr().Query( m_name.c_str(), lightmap, lightmapViewport))
					{
						for( size_t i=0; i<m1Entity->GetMeshRenderableNum(); i++)
							m1Entity->ApplyLightmap( lightmap, lightmapViewport, (int)i);
					}

					pEntity = m1Entity;
				}

				// �򳡾������ʵ��
				//if( pEntity)
				//	tile->AddEntity( m_name.c_str(), pEntity);
				//else
				//	ALogSystem.Warning( "Entity %s����ʧ��", m_name.c_str());
			}

			// ���л�
			template <typename Archive> void serialize( Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<IDCardEntity>(*this);
				ar & m_resPath;
			}
		};

		//------------------------------------
		// ���α�ʶ 2013-4-22 ����
		//------------------------------------
		struct IDCardTerrain : public IDCardEntity
		{
			// ��ȡ��ݱ�ʶ��
			virtual void ExtractFromEntity( EntityPtr& entity, SceneTile* tile)
			{		
				IDCardEntity::ExtractFromEntity( entity, tile);

				TerrainPtr terrain = dynamic_pointer_cast<Terrain>(entity);
				
				string terrainPath;
				FileUtils::ReplaceNameExt( terrainPath, tile->GetLocation().c_str(), (m_name+".terrain").c_str());
				Serialization::SerializeToBinaryFile( terrainPath.c_str(), *terrain);
			}

			// �ؽ�ʵ��
			virtual void ReBuildEnityToWorld(  Scene* world, SceneTile* tile)
			{
				EntityPtr pEntity = world->GetEntity( m_name.c_str());
				if( !pEntity)
				{
					TerrainPtr terrain = TerrainPtr( new_ Terrain);

					string terrainPath;
					FileUtils::ReplaceNameExt( terrainPath, tile->GetLocation().c_str(), (m_name+".terrain").c_str());

					Serialization::UnSerializeFromBinaryFile( terrainPath.c_str(), *terrain);

					pEntity = terrain;
				}

				// �򳡾������ʵ��
				if( pEntity)
					tile->AddEntity( m_name.c_str(), pEntity);
				else
					ALogSystem.Warning( "Entity %s����ʧ��", m_name.c_str());
			}

			// ���л�
			template <typename Archive> void serialize( Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<IDCardEntity>(*this);
			}
		};

		//------------------------------------
		// ������ʶ 2013-4-22 ����
		//------------------------------------
		struct IDCardDirLight : public IDCardEntity
		{
			Vector3			m_direction;
			ColorRGB		m_color;
			Rect3			m_localBounds;
			string			m_lightShaft;

			// ��ȡ��ݱ�ʶ��
			virtual void ExtractFromEntity( EntityPtr& entity, SceneTile* tile)
			{
				IDCardEntity::ExtractFromEntity( entity, tile);
				
				DirectionalLightPtr dirLight = dynamic_pointer_cast<DirectionalLight>( entity);
				if( dirLight)
				{
					m_direction		= dirLight->GetDirection();
					m_color			= dirLight->GetColor();
					m_localBounds	= dirLight->GetLocalBounds();
					m_lightShaft	= dirLight->GetShaftPath();
				}	
			}

			// �ؽ�ʵ��
			virtual void ReBuildEnityToWorld( Scene* world, SceneTile* tile)
			{
				EntityPtr pEntity = world->GetEntity( m_name.c_str());
				if( !pEntity)
				{
					DirectionalLightPtr dirLight = DirectionalLightPtr( new_ DirectionalLight);
					dirLight->SetTransform( m_transform);
					dirLight->SetDirection( m_direction);
					dirLight->SetColor( m_color);
					dirLight->SetLocalBounds( m_localBounds);
					dirLight->SetLightShaft( m_lightShaft.c_str());

					pEntity = dirLight;
				}

				// �򳡾������ʵ��
				if( pEntity)
					tile->AddEntity( m_name.c_str(), pEntity);
				else
					ALogSystem.Warning( "Entity %s����ʧ��", m_name.c_str());
			}

			// ���л�
			template <typename Archive> void serialize( Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<IDCardEntity>(*this);
				ar & m_direction;
				ar & m_color;
				ar & m_localBounds;
				ar & m_lightShaft;
			}
		};

		// ����IDCard
		IDCardEntity* MakeEntityIDCard( EntityTypeDetail type)
		{
			switch( type)
			{
			case ED_Model:			return new_ IDCardModel;
			case ED_Terrain:		return new_ IDCardTerrain;
			case ED_LightDirection: return new_ IDCardDirLight;
			default:				return NULL;
			}
		}
	}

	// ���캯��
	SceneTile::SceneTile( const char* fileLocation)
		: CGPTile()
	{
		m_location = fileLocation;

		m_version = 1;
	}

	// ��������
	SceneTile::~SceneTile()
	{}

	// ���ʵ��
	void SceneTile::AddEntity( const char* uniqueName, s_ptr<Entity> pEntity)
	{
		m_entitys[uniqueName] = pEntity;

		Scene* world = dynamic_cast<Scene*>(m_world);
		if( world && !world->GetEntity( uniqueName))
			world->AddEntityToWorldOnly( uniqueName, pEntity);
	}

	// ɾ��ʵ��
	void SceneTile::DelEntity( const char* name)
	{
		EntityList::iterator it = m_entitys.find( name);
		if( it != m_entitys.end())
			m_entitys.erase( it);
	}

	// ��ȡ��Χ��
	void SceneTile::GetBoundingBoxByLayer( Rect3& box, const char* layer, bool update)
	{
		for ( EntityList::const_iterator entity=m_entitys.begin(); entity!=m_entitys.end(); entity++)
		{
			const Rect3& worldBounds = entity->second->GetWorldBounds();

			box.UnionPoint( worldBounds.GetMinPoint());
			box.UnionPoint( worldBounds.GetMaxPoint());
		}
	}

	// ж������
	void SceneTile::Unload()
	{
		m_entitys.clear();
	}

	// ����
	void SceneTile::Save()
	{
		// ��¼������
		vector<DB::IDCardEntity*> IDCards;
		for( EntityList::iterator it=m_entitys.begin(); it!=m_entitys.end(); it++)
		{
			DB::IDCardEntity* idcard = DB::MakeEntityIDCard( it->second->GetTypeDetail());
			if( idcard)
			{
				idcard->ExtractFromEntity( it->second, this);
				IDCards.push_back( idcard);
			}
		}

		if( IDCards.size())
			Serialization::SerializeToBinaryFile( m_location.c_str(), IDCards);
	}

	// ��������
	void SceneTile::Load()
	{
		try
		{
			m_entitys.clear();
			vector<DB::IDCardEntity*> IDCards;
			Serialization::UnSerializeFromBinaryFile( m_location.c_str(), IDCards);

			// ������֯
			for( size_t i=0; i<IDCards.size(); i++)
				IDCards[i]->ReBuildEnityToWorld( dynamic_cast<Scene*>(m_world), this);
		}
		catch (...)
		{}
	}
}

BOOST_CLASS_EXPORT( Ares::DB::IDCardModel)
BOOST_CLASS_EXPORT( Ares::DB::IDCardTerrain)
BOOST_CLASS_EXPORT( Ares::DB::IDCardDirLight)