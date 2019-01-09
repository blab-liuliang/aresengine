#include <Core/AresCore.h>
#include <Engine/SceneSystem/LightmapMgr.h>
#include "Engine/AresRoot.h"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/property_tree/detail/rapidxml.hpp>
#include <Core/3rdParty/RapidXml/rapidxml_utils.hpp>

namespace Ares
{
	// ���캯��
	LightmapMgr::LightmapMgr()
		: m_tsWidth( 1024)
		, m_tsHeight( 1024)
	{}

	// ���캯��
	LightmapMgr::LightmapMgr( int width, int height)
		: m_tsWidth( width)
		, m_tsHeight( height)
	{}

	// ��������
	LightmapMgr::~LightmapMgr()
	{
		SAFE_DELETE_VECTOR( m_texSets);

		m_tileInfos.clear();
	}

	// ��ӹ���ͼ(��ʵ������mesh��������)
	bool LightmapMgr::AddLightmap( const char* uniqueName, TexturePtr& texture)
	{
		A_ASSERT( m_tsWidth>=(int)texture->GetWidth(0) && m_tsHeight>=(int)texture->GetHeight(0));

		// 1.���Ѵ���,��д����
		TileInfoMap::const_iterator it = m_tileInfos.find( uniqueName);
		if( it != m_tileInfos.end())
		{
			const TileInfo& tInfo = it->second;

			return OverWriteLightmapToTextureSet( m_texSets[tInfo.m_setIdx], tInfo.m_tileId, texture);
		}

		// 2.��������ʣ��ռ�
		for ( size_t i=0; i<m_texSets.size(); i++)
		{
			if( AddLightmapToTextureSet( m_texSets[i], i, uniqueName, texture))
				return true;
		}

		// 3.�½�TextureSet ������
		TextureSet* texSet = AllocateTextureSet( m_tsWidth, m_tsHeight);
		A_ASSERT( texSet);
		m_texSets.push_back( texSet);

		return AddLightmapToTextureSet( m_texSets.back(), m_texSets.size()-1, uniqueName, texture);
	}

	// ��ѯ
	bool LightmapMgr::Query( const char* uniqueName, TexturePtr& lightmap, Vector4& lightmapViewPort)
	{
		TileInfoMap::const_iterator it = m_tileInfos.find( uniqueName);
		if( it != m_tileInfos.end())
		{
			int	texIdx = it->second.m_setIdx;
			int	tileId = it->second.m_tileId;

			lightmap		 = m_texSets[texIdx]->GetTexture();
			lightmapViewPort = m_texSets[texIdx]->GetViewport(tileId);

			return true;
		}

		return false;
	}

	// ��ӵ�ָ������
	bool LightmapMgr::AddLightmapToTextureSet( TextureSet* texSet, int setIdx, const char* uniqueName, TexturePtr& texture)
	{
		if( !texSet)
			return false;

		int tileID = texSet->Insert( texture);
		if( tileID != INVALID)
		{
			TileInfo tInfo;
			tInfo.m_uniqueName = uniqueName;
			tInfo.m_setIdx = setIdx;
			tInfo.m_tileId = tileID;

			m_tileInfos[uniqueName] = tInfo;

			return true;
		}
		
		return false;
	}

	// ��д����
	bool LightmapMgr::OverWriteLightmapToTextureSet( TextureSet* texSet, int tileId, TexturePtr& texture)
	{
		int tileIdx = texSet->OverWrite( tileId, texture);
		if( tileIdx!=INVALID)
			return true;

		return false;
	}

	// �������
	void LightmapMgr::Clear()
	{
		m_tileInfos.clear();

		for( size_t i=0; i<m_texSets.size(); i++)
			SAFE_DELETE( m_texSets[i]);

		m_texSets.clear();
	}

	// �½�����
	TextureSet* LightmapMgr::AllocateTextureSet( int width, int height)
	{
		TexturePtr  texture;
		TextureSet* texSet = NULL;

	#ifdef ARES_EDITOR_MODE	
		texture = ARenderDevice->CreateTexture2D( width, height, 1, 1, EF_BC3, 1, 0, EAH_GPURead | EAH_CPUWrite, NULL);
		texture->GenerateMips();

		texSet  = new_ TextureSet( texture);
	#endif	

		return texSet;
	}

	// ���ر��渨�� TileInfo
	struct TileInfoLS
	{
		char	m_uniqueName[64];	// Ψһ��ʶ
		int		m_setIdx;			// ��������
		int		m_tileId;			// �����ID

		// ���캯��
		TileInfoLS()
			: m_setIdx(0), m_tileId(0)
		{
			m_uniqueName[0] = '\0';
		}
	};

	// ����
	bool LightmapMgr::Load( const char* locationPath)
	{
		// д�ļ�
		format txmlFmt( "%slightmap.lmb"); txmlFmt % locationPath ;
		FILE* fileHandle = fopen( txmlFmt.str().c_str(), "rb");
		if( fileHandle)
		{
			// ����TileInfo����
			int tileInfSize = 0;
			fread( &tileInfSize, sizeof(size_t), 1, fileHandle);

			TileInfoLS tileInfoLS;
			for ( int i=0; i<tileInfSize; i++)
			{
				// ����TileInfo
				fread( &tileInfoLS, sizeof(tileInfoLS), 1, fileHandle);

				TileInfo tInfo;
				tInfo.m_uniqueName = tileInfoLS.m_uniqueName;
				tInfo.m_setIdx	   = tileInfoLS.m_setIdx;
				tInfo.m_tileId	   = tileInfoLS.m_tileId;

				m_tileInfos[tInfo.m_uniqueName] = tInfo;
			}

			// ��������˳��
			// ��������˳��
			int texSets = 0;
			fread( &texSets, sizeof(texSets), 1, fileHandle);

			char texsetPath[64];
			for ( int i=0; i<texSets; i++)
			{
				fread( texsetPath, sizeof(char)*64, 1, fileHandle);

				TextureSet* texSet = new_ TextureSet;
				texSet->Load( (string( locationPath)+string(texsetPath)).c_str());
				m_texSets.push_back( texSet);
			}

			fflush( fileHandle);
			fclose( fileHandle);

			return true;
		}

		return false;
	}

	// ����
	bool LightmapMgr::Save( const char* locationPath)
	{
		// д�ļ�
		format txmlFmt( "%slightmap.lmb"); txmlFmt % locationPath ;
		FILE* fileHandle = fopen( txmlFmt.str().c_str(), "wb");
		if( fileHandle)
		{
			// ����TileInfo����
			int tileInfSize = (int)m_tileInfos.size();
			fwrite( &tileInfSize, sizeof(size_t), 1, fileHandle);

			TileInfoLS tileInfoLS;
			for ( TileInfoMap::iterator it=m_tileInfos.begin(); it!=m_tileInfos.end(); it++)
			{
				std::strcpy( tileInfoLS.m_uniqueName, it->second.m_uniqueName.c_str());
				tileInfoLS.m_setIdx = it->second.m_setIdx;
				tileInfoLS.m_tileId = it->second.m_tileId;

				// ����TileInfo
				fwrite( &tileInfoLS, sizeof(tileInfoLS), 1, fileHandle);
			}

			// ��������˳��
			int texSets = (int)m_texSets.size();
			fwrite( &texSets, sizeof(texSets), 1, fileHandle);

			char texsetPath[64];
			for ( size_t i=0; i<m_texSets.size(); i++)
			{
				format tFmt( "lightmap_%d.ts"); tFmt % i;
				std::strcpy( texsetPath, tFmt.str().c_str());

				fwrite( texsetPath, sizeof(char)*64, 1, fileHandle);
			}

			// ����textureset
			for ( size_t i=0; i<m_texSets.size(); i++)
			{
				string tsPath;
				format tsFmt( "lightmap_%d.ts"); tsFmt % i;
				FileUtils::ReplaceNameExt( tsPath, locationPath, tsFmt.str());

				m_texSets[i]->Save( tsPath.c_str());
			}

			fflush( fileHandle);
			fclose( fileHandle);

			return true;
		}

		return false;
	}

	// ����xml��ʽ
	bool LightmapMgr::LoadXml( const char* locationPath)
	{
        using namespace rapidxml;
		using namespace boost::property_tree::detail::rapidxml;

		try
		{
			// ���ļ�
			format txmlFmt( "%slightmap.xml"); txmlFmt % locationPath;
			file<> fdoc( txmlFmt.str().c_str());
			xml_document<>  doc;
			doc.parse<0>( fdoc.data());

			xml_node<>* rootNode =  doc.first_node("lightmaps");
			if( !rootNode)
				return false;

			// ����TileInfo
			m_tileInfos.clear();
			xml_node<>* tileInfosNode = rootNode->first_node( "tile_infos");
			xml_node<>* tileInfoNode  = tileInfosNode->first_node( "tile");
			for ( ; tileInfoNode; tileInfoNode=tileInfoNode->next_sibling( "tile"))
			{
				string attName   = tileInfoNode->first_attribute( "name")->value();
				int    attSetIdx = lexical_cast<int>(tileInfoNode->first_attribute( "set_idx")->value());
				int    attTileId = lexical_cast<int>(tileInfoNode->first_attribute( "tile_id")->value());

				TileInfo tInfo;
				tInfo.m_uniqueName = attName;
				tInfo.m_setIdx     = attSetIdx;
				tInfo.m_tileId	   = attTileId;

				m_tileInfos[attName] = tInfo;
			}

			// ��������˳��
			m_texSets.clear();
			xml_node<>* textureSetsNode = rootNode->first_node( "texture_sets");
			xml_node<>* textureSetNode  = textureSetsNode->first_node("texture_set");
			for ( ; textureSetNode; textureSetNode=textureSetNode->next_sibling("texture_set"))
			{
				string attPath     = textureSetNode->first_attribute("path")->value();
				TextureSet* texSet = new_ TextureSet;
				texSet->Load( (locationPath+attPath).c_str());
				m_texSets.push_back( texSet);
			}
		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	// ����xml��ʽ
	bool LightmapMgr::SaveXml( const char* locationPath)
	{
        using namespace rapidxml;
		using namespace boost::property_tree::detail::rapidxml;

		std::vector<string> saveHelper; saveHelper.reserve(256);

		xml_document<>  doc;
		xml_node<>* xmlNode  = doc.allocate_node(node_pi,doc.allocate_string("xml version='1.0' encoding='utf-8'"));
		xml_node<>* rootNode =  doc.allocate_node(node_element,"lightmaps");  

		doc.append_node( xmlNode);
		doc.append_node( rootNode);

		// ����TileInfo
		if( rootNode)
		{
			xml_node<>* tileInfosNode = doc.allocate_node( node_element, "tile_infos");
			rootNode->append_node( tileInfosNode);

			for ( TileInfoMap::iterator it=m_tileInfos.begin(); it!=m_tileInfos.end(); it++)
			{
				xml_node<>*		 tNode    = doc.allocate_node( node_element, "tile");
				saveHelper.push_back(it->second.m_uniqueName.c_str());
				xml_attribute<>* attName  = doc.allocate_attribute( "name", saveHelper.back().c_str());
				saveHelper.push_back(lexical_cast<string>(it->second.m_setIdx));
				xml_attribute<>* attTexId = doc.allocate_attribute( "set_idx",saveHelper.back().c_str());
				saveHelper.push_back(lexical_cast<string>(it->second.m_tileId));
				xml_attribute<>* attTileId= doc.allocate_attribute( "tile_id",saveHelper.back().c_str());
				
				tNode->append_attribute(attName);
				tNode->append_attribute(attTexId);
				tNode->append_attribute(attTileId);
				tileInfosNode->append_node( tNode);
			}
		}

		// ��������˳��
		if( rootNode)
		{
			xml_node<>* textureSetsNode = doc.allocate_node( node_element, "texture_sets");
			rootNode->append_node( textureSetsNode);

			for ( size_t i=0; i<m_texSets.size(); i++)
			{
				format tFmt( "lightmap_%d.ts"); tFmt % i;

				xml_node<>*		 tNode    = doc.allocate_node( node_element, "texture_set");
				saveHelper.push_back(tFmt.str());
				xml_attribute<>* attName  = doc.allocate_attribute( "path", saveHelper.back().c_str());

				tNode->append_attribute(attName);
				textureSetsNode->append_node( tNode);
			}
		}

		// д�ļ�
		format txmlFmt( "%slightmap.xml"); txmlFmt % locationPath ;
		std::ofstream out( txmlFmt.str().c_str());
#ifdef ARES_PLATFORM_WINDOWS
		//A_ASSERT(FALSE);
        //out << doc;
#else
        A_ASSERT(FALSE);
#endif

		// ����textureset
		for ( size_t i=0; i<m_texSets.size(); i++)
		{
			string tsPath;
			format tsFmt( "lightmap_%d.ts"); tsFmt % i;
			FileUtils::ReplaceNameExt( tsPath, locationPath, tsFmt.str());

			m_texSets[i]->Save( tsPath.c_str());
		}

		return true;
	}
}