#pragma once

#include <map>
#include <string>
#include "Engine/RenderSystem/AresTextureSet.h"

using namespace std;

namespace Ares
{
	//---------------------------------
	// ��������ͼ������ 2012-7-7 ����
	//     ���,ɾ��,�ϲ�,����
	//---------------------------------
	class CORE_EXPORT LightmapMgr
	{
	public:
		// TextureTile
		struct TileInfo
		{
			string  m_uniqueName;	// Ψһ��ʶ
			int		m_setIdx;		// ��������
			int		m_tileId;		// �����ID
		};
		typedef map<string, TileInfo> TileInfoMap;

	public:
		LightmapMgr();
		LightmapMgr( int width, int height);
		~LightmapMgr();

		// ��ӹ���ͼ(��ʵ������mesh��������)
		bool AddLightmap( const char* uniqueName, TexturePtr& texture);

		// ��ѯ
		bool Query( const char* uniqueName, TexturePtr& lightmap, Vector4& lightmapViewPort);

		// �������
		void Clear();

		// ����
		bool Load( const char* locationPath);

		// ����
		bool Save( const char* locationPath);

		// ����xml��ʽ
		bool LoadXml( const char* locationPath);

		// ����xml��ʽ
		bool SaveXml( const char* locationPath);

	private:
		// �½�����
		TextureSet* AllocateTextureSet( int width, int height);

		// ��ӵ�ָ������
		bool AddLightmapToTextureSet( TextureSet* texSet, int setIdx, const char* uniqueName, TexturePtr& texture);

		// ��д����
		bool OverWriteLightmapToTextureSet( TextureSet* texSet, int tileId, TexturePtr& texture);

	private:
		int						m_tsWidth;		// TextureSet��
		int						m_tsHeight;		// TextureSet��
		TileInfoMap				m_tileInfos;	// ����Ϣ
		vector<TextureSet*>		m_texSets;		// ����
	};
}