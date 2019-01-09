#pragma once

#include <map>
#include <set>
#include <Engine/RenderSystem/AresRenderEntity.h>
#include <Engine/RenderSystem/AresLight.h>
#include <Engine/RenderSystem/AresDirectionalLight.h>
#include <Engine/RenderSystem/AresModel.h>
#include <Engine/SceneSystem/AresScene.h>
#include <Engine/RenderSystem/AresHDREncode.h>
#include <Engine/RenderSystem/AresGrayscale.h>

using namespace std;

namespace Ares
{
	//-------------------------------------
	// ����ͼӲ���決������ 2012-6-20 ����
	//-------------------------------------
	class GpuLightmapBakerMgr
	{
		typedef set<RenderEntity*>			  TaskSet;
		typedef multimap<Entity*, Renderable> MultimapRB;
	public:
		// ���캯��
		GpuLightmapBakerMgr();

		// �������
		void AddTask( RenderEntity* entity);

	public:
		// ��ȾLightmap
		void Render();

		// ���캯��
		void SetLightmapSize( int size);

		// �決RenderEntity
		void Baking( RenderEntity* renderEntity, Scene* scene);

		// �決�����
		void DirectionalBaking( RenderEntity* renderEntity, DirectionalLight* dirLight, Scene* scene);

		// ���·�������ͼ(ֻ�о�̬Ͷ����)
		void UpdateDirLightDepthMapForBake( DirectionalLight* dirLight, Scene* scene);

		// ִ�к決Lightmap
		void BakeLightmap(  DirectionalLight* dirLight, RenderEntity* renderEntity);

	private:
		// ��ӹ���ͼ��������
		void AddLightmapToScene( const char* name);

		// ��������
		void ModifyMaterial( RenderEntity* renderEntity);

		// ����ZPre Renderable
		bool BuildRenderableZPre( TerrainTile* terrainTile);

		// �決�������޸ĵ��ο����ò���
		bool ModifyMaterialUseLightmap( TerrainTile* terrainTile);

		// ����ZPre Renderable for model
		bool BuildRenderableZPre( Model* model);

		// �決�������޸�ģ�����ò���
		void ModifyMaterialUseLightmap( Model* model);

		// ��Ѱ��Ⱦ���Renderable
		void SearchRenderableZPre( vector<pair< Entity*, Renderable*>>& results, Scene* scene, const Box3& r3);

		// ����Bake Renderable
		bool BuildRenderableBake( TerrainTile* terrainTile);

		// ����Bake Renderable
		bool BuildRenderableBake( Model* model);

		// ��Ѱ���պ決Renderable
		void SearchRenderableBake(  vector<pair< Entity*, Renderable*>>& results, RenderEntity* renderEntity);

		// �������ͼ��С
		int GetLightmapSize( RenderEntity* renderEntity, int meshIdx=0);

	private:
		MultimapRB		m_zPreRenderables;		// Z��ȸ���(�༭��ʹ��)
		MultimapRB		m_bakeRenaderables;		// ִ�к決

		FrameBufferPtr	m_lightmapFrame;		// ����ͼFrameBuffer
		TexturePtr		m_lightmapTexture;		// ��������

		ShaderParamPtr	m_lightWorldViewPorj;	// ��Դ�ռ�����۲�ͶӰ����

		TaskSet			m_tasks;				// �決����

		int				m_lightmapResolution;	// ����ͼ�ֱ���
	};
}