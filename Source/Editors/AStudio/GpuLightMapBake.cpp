#include "GpuLightMapBake.h"
#include <Engine/AresRoot.h>
#include <Engine/RenderSystem/AresCpuTextureFilter.h>
#include "SCLogic.h"
#include <boost/progress.hpp>
#include <boost/timer.hpp>

namespace Ares
{
	// ���캯��
	GpuLightmapBakerMgr::GpuLightmapBakerMgr()
		: m_lightmapResolution( 0)
	{
		m_lightWorldViewPorj = MakeShaderParam( Matrix44::Identity);
	}

	// ���캯��
	void GpuLightmapBakerMgr::SetLightmapSize( int size)
	{
		A_ASSERT( size>0 && size<=4096);

		if( m_lightmapResolution != size)
		{
			// ��ʼ����ͼFrameBuffer
			RenderViewPtr depthView = ARenderDevice->Create2DDepthStencilRenderView( size, size, EF_D32F, 1, 0);
			m_lightmapFrame			= ARenderDevice->CreateFrameBuffer();
			m_lightmapTexture		= ARenderDevice->CreateTexture2D( size, size, 1, 1, EF_ARGB8, 1, 0, EAH_GPURead | EAH_GPUWrite, NULL);
			m_lightmapFrame->AttachRenderView( FrameBuffer::ATT_Color0,	   ARenderDevice->Create2DRenderView( m_lightmapTexture, 0, 1, 0));
			m_lightmapFrame->AttachRenderView( FrameBuffer::ATT_DepthStencil,depthView);

			m_lightmapResolution = size;
		}
	}

	// �������
	void GpuLightmapBakerMgr::AddTask( RenderEntity* entity)
	{
		m_tasks.insert( entity);
	}

	// ��ȾLightmap
	void GpuLightmapBakerMgr::Render()
	{
		RenderDevice* device = ARenderDevice;

		if( m_tasks.size())
		{
			Scene* scene = SCLogic_Scene;

			// ִ�к決
			for ( TaskSet::iterator it=m_tasks.begin(); it!=m_tasks.end(); it++)
			{
				// ִ�к決
				Baking( *it, scene);

				// ��ӵ�������
				AddLightmapToScene( (*it)->GetName());

				// ��������
				ModifyMaterial( *it);
			}

			m_tasks.clear();
		}

	}

	// ��ӹ���ͼ��������
	void GpuLightmapBakerMgr::AddLightmapToScene( const char* name)
	{
		// �˾�����
		CpuTextureFilter::EdgePadding( m_lightmapTexture, HDREncode::EncodeRGBM8(ColorRGB( 0.f, 0.f, 0.f)), 4, true);
		CpuTextureFilter::GaussianBlur( m_lightmapTexture, 2.f);

		// �򳡾��в�������
		SCLogic_Scene->GetLightmapMgr().AddLightmap( name, m_lightmapTexture);
	}

	// ��������
	void GpuLightmapBakerMgr::ModifyMaterial( RenderEntity* renderEntity)
	{
		switch( renderEntity->GetTypeDetail())
		{
		case ED_Model:
			{
				Model* model = dynamic_cast<Model*>(renderEntity);
				if( model)
					ModifyMaterialUseLightmap( model);
			}
			break;

		case ED_Terrain:
			{
				TerrainTile* terrainTile = dynamic_cast<TerrainTile*>( renderEntity);
				if( terrainTile)
					ModifyMaterialUseLightmap( terrainTile);
			}
			break;
		}
	}

	// �決RenderEntity
	void GpuLightmapBakerMgr::Baking( RenderEntity* renderEntity, Scene* scene)
	{	
		A_ASSERT( renderEntity);

		// �������ͼ���
		Rect3 worldBoundBox = renderEntity->GetWorldBounds();
		float widthHeight   = std::sqrtf( worldBoundBox.GetSurfaceArea());

		// ������Χ�����й�Դ
		DirectionalLightPtr     domainLight;
		static vector<Light*> lights;
		scene->SearchLights( lights, domainLight);
		lights.push_back( domainLight.get());	

		for ( size_t i=0; i<lights.size(); i++)
		{
			switch( lights[i]->GetTypeDetail())
			{
			case ED_LightAmbient:
				{

				}
				break;

			case ED_LightDirection:
				{
					// ��ȾLightmap                                       
					DirectionalBaking( renderEntity, dynamic_cast<DirectionalLight*>(lights[i]), scene);
				}
				break;
			}
		}
	}

	// �決�����
	void GpuLightmapBakerMgr::DirectionalBaking( RenderEntity* renderEntity, DirectionalLight* dirLight, Scene* scene)
	{
		//scene->RefreshCSMMgrDepth( dirLight->GetCSMMgr(), renderEntity->GetWorldBounds());

		// ����Ӱ�������С
		dirLight->GetCSMMgr()->RefreshShadowMaps( renderEntity->GetWorldBounds());

		//dirLight->GetCSMMgr()->SetFocusRegion( renderEntity->GetWorldBounds());

		// �����Ƿ�ʹ��DepthMap; ����DepthMap
		//UpdateDirLightDepthMapForBake( dirLight, scene);

		// ���ݷ���������RenderEntity���ʽ��й��ռ���
		BakeLightmap( dirLight, renderEntity);
	}

	// ���·�������ͼ(ֻ�о�̬Ͷ����)
	void GpuLightmapBakerMgr::UpdateDirLightDepthMapForBake( DirectionalLight* dirLight, Scene* scene)
	{
		/*
		// ����DepthMapΪ��ǰFrameBuffer
		ARenderDevice->BindFrameBuffer( dirLight->GetDepthBuffer());
		dirLight->GetDepthBuffer()->Clear( ColorRGB( 1.f, 1.f, 1.f, 1.f), 1.f, 0);

		// ��Ⱦ
		vector<pair< Entity*, Renderable*>> zPres;
		SearchRenderableZPre( zPres, scene, dirLight->GetSearchBox3());
		for ( size_t i=0; i<zPres.size(); i++)
		{	
			Matrix44 world    = zPres[i].first->GetTransform().GetMatrix();
			Matrix44 viewCrop = dirLight->GetViewCropMatrix();
			Matrix44 wvc	  = world * viewCrop;

			*m_lightWorldViewPorj = wvc;

			zPres[i].second->Render();
		}

		// �ָ�ԭ��Buffer
		ARenderDevice->BindFrameBuffer( ARenderDevice->GetRenderWindow()->GetFrameBuffer());

		*/
		// test save texture
		//AResSystem.SyncSaveTexture( dirLight->GetDepthTexture(), "D:\\lightdepth.dds");
	}

	// �������ͼ��С
	int GpuLightmapBakerMgr::GetLightmapSize( RenderEntity* renderEntity, int meshIdx)
	{
		//switch( renderEntity->GetTypeDetail())
		//{
		//case ED_Terrain:
		//	{
		//		TerrainTile* tile = dynamic_cast<TerrainTile*>(renderEntity);
		//	}
		//	break;

		//case ED_Model:
		//	{
		//		Model* model = dynamic_cast<Model*>( renderEntity);
		//		if( model)
		//		{
		//			const MeshRenderable& m1Renderable = model->GetModelRenderable(meshIdx);
		//			IDCardMesh*					  rawMesh	   = m1Renderable.m_rawMesh;
		//			if( rawMesh)
		//			{
		//				// �����С
		//				SM1Face face = rawMesh->m_pFaces[0];
		//				Vector3 v0   = (Vector3&)rawMesh->m_positions[face.m_uiIndices[0]];
		//				Vector3 v1   = (Vector3&)rawMesh->m_positions[face.m_uiIndices[1]];
		//				Vector2	uv0	 = (Vector2&)rawMesh->m_lightmapTexCoords[face.m_uiIndices[0]];
		//				Vector2 uv1  = (Vector2&)rawMesh->m_lightmapTexCoords[face.m_uiIndices[1]];

		//				// ÿ��λ4������
		//				float pixelNum = (v1-v0).Length() * 10.f;
		//				float segNum   = 1.f / (uv0-uv1).Length();

		//				// ��֤����ͼ��СΪ4�ı���, ���ֵ������1024
		//				//return std::max<int>( 16, std::min<int>( 1024, static_cast<int>(segNum * pixelNum / 4.f * 4.f)));
		//			}
		//		}
		//	}
		//	break;
		//}

		return 256;
	}

	// �決lightmap
	void GpuLightmapBakerMgr::BakeLightmap(  DirectionalLight* dirLight, RenderEntity* renderEntity)
	{
		// ���ù���ͼ�ߴ�
		int size = GetLightmapSize( renderEntity);
		SetLightmapSize( size);

		// ����DepthMapΪ��ǰFrameBuffer
		ARenderDevice->BindFrameBuffer( m_lightmapFrame);
		m_lightmapFrame->Clear( HDREncode::EncodeRGBM8( ColorRGB( 0.f, 0.f, 0.f)), 1.f, 0);

		// ��Ⱦ
		static vector<pair< Entity*, Renderable*>> bakes;
		SearchRenderableBake( bakes, renderEntity);
		for ( size_t i=0; i<bakes.size(); i++)
		{	
			// ����shader����
			bakes[i].second->GetMaterial()->SetParamRef( "g_world",		   renderEntity->GetSPAB( RenderEntity::SP_World));
			bakes[i].second->GetMaterial()->SetParamRef( "g_lightViewProj", dirLight->GetCSMMgr()->GetSPAB( CSMMgr::SP_ViewCropRemap));
			bakes[i].second->GetMaterial()->SetParamRef( "g_lightDir",	   dirLight->GetSPAB( DirectionalLight::SP_Direction));
			bakes[i].second->GetMaterial()->SetParamRef( "g_lightColor",	   dirLight->GetSPAB( DirectionalLight::SP_Color));
			bakes[i].second->GetMaterial()->SetParamRef( "DepthTex",		   dirLight->GetCSMMgr()->GetSPAB( CSMMgr::SP_DepthMap));
			//bakes[i].second->GetMaterial().SetParamRef( "WrapSampler",		); �����Σ��������Ĭ��ֵ...

			bakes[i].second->Render();
		}

		// �ָ�ԭ��Buffer
		ARenderDevice->BindFrameBuffer( SELogic_RenderSystem.GetRenderWindow()->GetFrameBuffer());
	}

	// ��Ѱ���պ決Renderable
	void GpuLightmapBakerMgr::SearchRenderableBake(  vector<pair< Entity*, Renderable*>>& results, RenderEntity* renderEntity)
	{
		results.clear();

		if( renderEntity->GetType() == ET_Render && renderEntity->IsStatic())
		{
			switch( renderEntity->GetTypeDetail())
			{
			case ED_Terrain:
				{
					TerrainTile* tile = dynamic_cast<TerrainTile*>(renderEntity);
					if( tile)
						BuildRenderableBake( tile);
				}
				break;

			case ED_Model:
				{
					Model* model = dynamic_cast<Model*>(renderEntity);
					if( model)
						BuildRenderableBake( model);
				}
				break;
			}

			MultimapRB::iterator begIt = m_bakeRenaderables.lower_bound( renderEntity);
			MultimapRB::iterator endIt = m_bakeRenaderables.upper_bound( renderEntity);

			if( begIt != endIt)
			{
				for( MultimapRB::iterator it=begIt; it!=endIt; it++)
					results.push_back( make_pair(it->first, &it->second));
			}
		}
	}

	// ��Ѱ��Ⱦ���Renderable
	void GpuLightmapBakerMgr::SearchRenderableZPre( vector<pair< Entity*, Renderable*>>& results, Scene* scene, const Box3& r3)
	{
		Rect3 r3AABB;
		r3.BuildAABB( r3AABB, Transform());

		vector<EntityPtr> entitys;
		//scene->BuildSearchResults( entitys, r3AABB, NULL/*, r3*/);

		// ���ҹ�Դ
		for( size_t i=0; i<entitys.size(); i++)
		{
			if( entitys[i]->GetType() == ET_Render && entitys[i]->IsStatic())
			{
				// �½�ZPreRenderables
				if( entitys[i]->GetTypeDetail() == ED_Terrain)
				{
					TerrainTile* tile = dynamic_cast<TerrainTile*>(entitys[i].get());
					if( tile)
						BuildRenderableZPre( tile);
				}
				else if( entitys[i]->GetTypeDetail() == ED_Model)
				{
					Model* model = dynamic_cast<Model*>(entitys[i].get());
					if( model)
						BuildRenderableZPre( model);
				}

				MultimapRB::iterator begIt = m_zPreRenderables.lower_bound( entitys[i].get());
				MultimapRB::iterator endIt = m_zPreRenderables.upper_bound( entitys[i].get());

				if( begIt != endIt)
				{
					for( MultimapRB::iterator it=begIt; it!=endIt; it++)
						results.push_back( make_pair(it->first, &it->second));
				}
			}
		}
	}

	// ����ZPre Renderable
	bool GpuLightmapBakerMgr::BuildRenderableZPre(TerrainTile* terrainTile)
	{
		//if( m_zPreRenderables.find( terrainTile) != m_zPreRenderables.end())
		//	return false;

		//// Renderlayout
		//RenderLayoutPtr layout = ARenderDevice->CreateRenderLayout();
		//layout->SetTopologyType( RenderLayout::TT_TriangleStrip);
		//layout->BindIndexStream( terrainTile->GetIndexGraphicsBuffer(), EF_R16UI);
		//layout->BindVertexStream( terrainTile->GetVertexGraphicsBuffer( TerrainTile::VSF_Position), TerrainTile::Mapping( TerrainTile::VSF_Position));

		//// Rendermaterial
		//RenderMaterial zPreMaterial;
		//zPreMaterial.SetMethod( AResSystem.LoadMethod("ZPrestatic.hlsl"));
		//zPreMaterial.SetParamRef( "WorldViewProj", m_lightWorldViewPorj);

		//Renderable renderable;
		//renderable.SetRenderlayout( layout);
		//renderable.SetMaterial( zPreMaterial);

		//m_zPreRenderables.insert( make_pair( terrainTile, renderable));

		return true;
	}

	// ����ZPre Renderable for model
	bool GpuLightmapBakerMgr::BuildRenderableZPre( Model* model)
	{
		if( m_zPreRenderables.find( model) != m_zPreRenderables.end())
			return false;

		// Rendermaterial
		RenderMaterialPtr zPreMaterial( new SuperMaterial);
		zPreMaterial->SetMethod( AResSystem.LoadMethod("ZPrestatic.hlsl"));
		zPreMaterial->SetParamRef( "WorldViewProj", m_lightWorldViewPorj);

		size_t renderableNum = model->GetMeshRenderableNum();
		for ( size_t i=0; i<renderableNum; i++)
		{
			const MeshRenderable& m1Renderable = model->GetMeshRenderable(i);

			UINT vsf = Mesh::VSF_Position;
			RenderLayoutPtr layout = m1Renderable.m_mesh->BuildRenderLayout( vsf);

			Renderable renderable;
			renderable.SetRenderlayout( layout);
			renderable.SetMaterial( zPreMaterial);

			m_zPreRenderables.insert( make_pair( model, renderable));
		}

		return true;
	}

	// �決�������޸�ģ�����ò���
	void GpuLightmapBakerMgr::ModifyMaterialUseLightmap( Model* model)
	{
		TexturePtr lightmapTex;
		Vector4    lightmapViewport;
		SCLogic_Scene->GetLightmapMgr().Query( model->GetName(), lightmapTex, lightmapViewport);

		model->ApplyLightmap( lightmapTex, lightmapViewport, 0);
	}

	// �決�������޸ĵ��ο����ò���
	bool GpuLightmapBakerMgr::ModifyMaterialUseLightmap( TerrainTile* terrainTile)
	{
		//TexturePtr lightmapTex;
		//Vector4    lightmapViewport;
		//SCLogic_Map->GetScene()->GetLightmapMgr().Query( terrainTile->GetName(), lightmapTex, lightmapViewport);

		//Renderable* renderable = terrainTile->GetRenderable( "main", "terrain");
		//if( renderable)
		//{
		//	SamplerStateDesc ssDesc;
		//	ssDesc.m_addrModeU		= TAM_Clamp;
		//	ssDesc.m_addrModeV		= TAM_Clamp;
		//	ssDesc.m_addrModeW		= TAM_Clamp;
		//	SamplerStatePtr  ssPtr = ARenderDevice->CreateSamplerState( ssDesc);

		//	ShaderParamPtr lightmap= MakeShaderParam( m_lightmapTexture);
		//	//lightmap->SetSamplerState( ssPtr);
		//	renderable->GetMaterial().SetParamRef( "LightmapSamp",lightmap);

		//	ShaderParamPtr slightmapViewport = MakeShaderParam( lightmapViewport);
		//	renderable->GetMaterial().SetParamRef( "LightmapViewport", slightmapViewport);

		//	return true;
		//}

		return false;
	}

	// ����Bake Renderable
	bool GpuLightmapBakerMgr::BuildRenderableBake( TerrainTile* terrainTile)
	{
		//if( m_bakeRenaderables.find( terrainTile) != m_bakeRenaderables.end())
		//	return false;

		//// Renderlayout
		//RenderLayoutPtr layout = ARenderDevice->CreateRenderLayout();
		//layout->SetTopologyType( RenderLayout::TT_TriangleStrip);
		//layout->BindIndexStream( terrainTile->GetIndexGraphicsBuffer(), EF_R16UI);
		//layout->BindVertexStream( terrainTile->GetVertexGraphicsBuffer( TerrainTile::VSF_Position),		TerrainTile::Mapping( TerrainTile::VSF_Position));
		//layout->BindVertexStream( terrainTile->GetVertexGraphicsBuffer( TerrainTile::VSF_LightmapUV),   TerrainTile::Mapping( TerrainTile::VSF_LightmapUV));
		//layout->BindVertexStream( terrainTile->GetVertexGraphicsBuffer( TerrainTile::VSF_Normal),		TerrainTile::Mapping( TerrainTile::VSF_Normal));

		//// Rendermaterial
		//RenderMaterial bakeMaterial;
		//bakeMaterial.SetMethod( AResSystem.LoadMethod( "data\\cg\\lightmapbake_dirlight.hlsl"));

		//Renderable renderable;
		//renderable.SetRenderlayout( layout);
		//renderable.SetMaterial( bakeMaterial);

		//m_bakeRenaderables.insert( make_pair( terrainTile, renderable));

		return true;
	}

	// ����Bake Renderable
	bool GpuLightmapBakerMgr::BuildRenderableBake( Model* model)
	{
		if( m_bakeRenaderables.find( model) != m_bakeRenaderables.end())
			return false;

		// Rendermaterial
		RenderMaterialPtr bakeMaterial( new_ SuperMaterial);
		bakeMaterial->SetMethod( AResSystem.LoadMethod("data\\shader\\lightmapbake_dirlight.hlsl"));

		size_t renderableNum = model->GetMeshRenderableNum();
		for ( size_t i=0; i<renderableNum; i++)
		{
			const MeshRenderable& m1Renderable = model->GetMeshRenderable(i);

			UINT vsf = Mesh::VSF_Position | Mesh::VSF_LightmapUV | Mesh::VSF_Normal;
			RenderLayoutPtr layout = m1Renderable.m_mesh->BuildRenderLayout( vsf);

			Renderable renderable;
			renderable.SetRenderlayout( layout);
			renderable.SetMaterial( bakeMaterial);

			m_bakeRenaderables.insert( make_pair( model, renderable));
		}

		return true;
	}
}