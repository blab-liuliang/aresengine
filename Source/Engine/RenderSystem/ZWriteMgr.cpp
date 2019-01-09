#include <Engine/RenderSystem/ZWriteMgr.h>
#include <Engine/AresRoot.h>

namespace Ares
{
	// д���
	void ZWriteMgr::Write( vector<Entity*>& entitys, const Matrix44& viewProj)
	{
		// ����ZRenderable
		RefreshRenderableZWrite( entitys);

		// ִ��ZWrite
		ExecZWrite( entitys, viewProj);
	}

	// ˢ��Renderable
	void ZWriteMgr::RefreshRenderableZWrite( vector<Entity*>& entitys)
	{
		// ����ZRenderable
		for( size_t i=0; i<entitys.size(); i++)
		{
			if( entitys[i]->GetType() == ET_Render /*&& entitys[i]->IsStatic()*/)
			{
				// �½�ZPreRenderables
				if( entitys[i]->GetTypeDetail() == ED_Model)
				{
					Model* model = dynamic_cast<Model*>(entitys[i]);
					if( model)
						RefreshRenderableZWrite( model);
				}
				else if( entitys[i]->GetTypeDetail() == ED_Terrain)
				{
					Terrain* terrain = dynamic_cast<Terrain*>( entitys[i]);
					if( terrain)
						RefreshRenderableZWrite( terrain);
				}
			}
		}
	}

	// ˢ��ģ��Renderable
	void ZWriteMgr::RefreshRenderableZWrite( Model* model)
	{
		if( m_zRenderables.find( model) != m_zRenderables.end())
			return;

		size_t renderableNum = model->GetMeshRenderableNum();
		for ( size_t i=0; i<renderableNum; i++)
		{
			MeshRenderable& m1Renderable = model->GetMeshRenderable(i);

			if( true)
			{
				UINT vsf = Mesh::VSF_Position | Mesh::VSF_DiffuseUV;
				RenderLayoutPtr layout = m1Renderable.m_mesh->BuildRenderLayout( vsf);

				ZRenderable* zRenderable = new_ ZRenderable( true);
				zRenderable->SetRenderlayout( layout);
				zRenderable->SetMaskTexture( m1Renderable.m_superMaterial->GetZTestMaskTexture());

				m_zRenderables[model][i] =zRenderable;
			}
			else
			{
				UINT vsf = Mesh::VSF_Position;
				RenderLayoutPtr layout = m1Renderable.m_mesh->BuildRenderLayout( vsf);

				ZRenderable* zRenderable = new_ ZRenderable;
				zRenderable->SetRenderlayout( layout);

				m_zRenderables[model][i] =zRenderable;
			}

		}
	}

	// ���µ���ZWriteRenderable
	void ZWriteMgr::RefreshRenderableZWrite( Terrain* terrain)
	{/*
		const Terrain::TileList& tileList = terrain->GetTileList();
		for( size_t i=0; i<tileList.size(); i++)
		{
			RenderLayoutPtr layout = ARenderDevice->CreateRenderLayout();
			layout->SetTopologyType( RenderLayout::TT_TriangleStrip);

			layout->BindVertexStream( tileList[i]->GetVertexGraphicsBuffer( TerrainTile::VSF_Position), TerrainTile::Mapping( TerrainTile::VSF_Position));
			layout->BindIndexStream( tileList[i]->GetIndexGraphicsBuffer(), EF_R16UI);

			ZRenderable* zRenderable = new_ ZRenderable;
			zRenderable->SetRenderlayout( layout);

			m_zRenderables[terrain][i] = zRenderable;
		}*/
	}

	// ִ��д���
	void ZWriteMgr::ExecZWrite( vector<Entity*>& entitys, const Matrix44& viewProj)
	{
		Matrix44 worldViewProj;
		for( size_t i=0; i<entitys.size(); i++)
		{
			worldViewProj = entitys[i]->GetTransform().GetMatrix() * viewProj;

			// ִ����Ⱦ
			MultimapZR::iterator it= m_zRenderables.find( entitys[i]);
			if( it!=m_zRenderables.end())
			{
				for( map<size_t, ZRenderable*>::iterator it1 = it->second.begin(); it1!=it->second.end(); it1++)
				{
					it1->second->Render( worldViewProj);
				}
			}
		}
	}
}