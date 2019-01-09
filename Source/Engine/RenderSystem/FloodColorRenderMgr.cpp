#include <Engine/RenderSystem/FloodColorRenderMgr.h>
#include <Engine/AresRoot.h>

namespace Ares
{
	// ��Ⱦ����
	void FloodColorRenderMgr::Write( vector<EntityPtr>& entitys)
	{
		// ����FloodLightRenderalbe
		RefreshRenderableWrite( entitys);

		// ִ�з�����Ⱦ
		ExecFloodLightWrite( entitys);
	}

	// ����FloodLightRenderalbe
	void FloodColorRenderMgr::RefreshRenderableWrite( vector<EntityPtr>& entitys)
	{
		// ����ZRenderable
		for( size_t i=0; i<entitys.size(); i++)
		{
			A_ASSERT( entitys[i]);

			if( entitys[i]->GetType() == ET_Render /*&& entitys[i]->IsStatic()*/)
			{
				// �½�ZPreRenderables
				if( entitys[i]->GetTypeDetail() == ED_Model)
				{
					ModelPtr model = dynamic_pointer_cast<Model>(entitys[i]);
					if( model)
						RefreshRenderableWrite( model);
				}
				//else if( entitys[i]->GetTypeDetail() == ED_TerrainTile)
				//{
				//	TerrainTile* tile = dynamic_cast<TerrainTile*>(entitys[i].get());
				//	if( tile)
				//		BuildRenderableZPre( tile);
				//}
			}
		}
	}

	// ˢ��ģ�ͷ���Renderable
	void FloodColorRenderMgr::RefreshRenderableWrite( ModelPtr& model)
	{
		if( m_renderables.find( model) != m_renderables.end())
			return;

		size_t renderableNum = model->GetMeshRenderableNum();
		for ( size_t i=0; i<renderableNum; i++)
		{
			const MeshRenderable& m1Renderable = model->GetMeshRenderable(i);

			UINT vsf = Mesh::VSF_Position;
			RenderLayoutPtr layout = m1Renderable.m_mesh->BuildRenderLayout( vsf);

			FloodColorRenderable* renderable = new_ FloodColorRenderable;
			renderable->SetRenderlayout( layout);

			m_renderables.insert( make_pair( model, renderable));
		}
	}

	// ִ�з�����Ⱦ
	void FloodColorRenderMgr::ExecFloodLightWrite( vector<EntityPtr>& entitys)
	{
		Matrix44 worldViewProj;
		for( size_t i=0; i<entitys.size(); i++)
		{
			//Transform transform = ;
			//transform.SetScale( 1.1f);
			CameraSystem& cameraSystem = entitys[i]->GetCameraSystem();

			worldViewProj = entitys[i]->GetTransform().GetMatrix() * cameraSystem.GetViewProj();

			// ִ����Ⱦ
			MultimapFR::iterator endIt = m_renderables.upper_bound( entitys[i]);
			for( MultimapFR::iterator it=m_renderables.lower_bound( entitys[i]); it!=endIt; it++)
			{
				it->second->Render( worldViewProj);
			}
		}
	}
}