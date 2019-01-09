#include <Engine/AresRoot.h>
#include <Engine/RenderSystem/AresModel.h>
#include <Engine/RenderSystem/AresModelIDCard.h>

namespace Ares
{
	// ���캯��
	MeshRenderable::MeshRenderable() 
		: Renderable()
	{
		m_superMaterial = MakeSharePtr( new_ SuperMaterial);
		SetMaterial( m_superMaterial);
	}

	// ��ȡ����������
	int MeshRenderable::GetPrimitiveCount() const
	{
		return m_mesh->GetTriNum();
	}

	// ���캯��
	Model::Model()
		: RenderEntity( ED_Model)
	{
		m_boneTransform	= MakeShaderParam();
		m_lightViewCrop = MakeShaderParam();
	}

	// ��������
	Model::~Model()
	{
	}

	// �ؽ�ģ������
	void Model::IDCard::RebuildModel( Model& model)
	{
		model.m_idcard = IDCardPtr( this);

		// ��������
		if( m_aniPath.size())
			model.m_animationController.SetAnimation( m_aniPath.c_str());
	
		model.m_renderables.resize( m_renderInfos.size());
		for ( size_t i=0; i<m_renderInfos.size(); i++)
		{
			MeshRenderable& renderable		= model.m_renderables[i];
			renderable.m_meshFilePath		= m_renderInfos[i].m_meshFilePath;
			renderable.m_meshIdx			= m_renderInfos[i].m_meshIdx;
			renderable.m_mesh				= AResSystem.LoadMesh( m_renderInfos[i].m_meshFilePath.c_str(), m_renderInfos[i].m_meshIdx);

			// Ĭ��ӵ��������,����
			QWORD usage						= SMU_OutputDiffuse | SMU_OutputNormal | (model.m_animationController.GetAnimation()?SMU_SkeletalMesh:0);
			renderable.m_materialPath		= m_renderInfos[i].m_materialPath.c_str();
			renderable.m_materialIdx		= m_renderInfos[i].m_materialIdx;
			AResSystem.LoadMaterialParameter( renderable.m_superMaterial, renderable.m_materialPath.c_str(), renderable.m_materialIdx, usage);

			model.AutoBindRenderLayout( renderable);

			// ��Χ��
			Rect3 localAABB = model.GetLocalBounds();
			Rect3 meshAABB	= renderable.m_mesh->GetBoundingBox();	
			localAABB.UnionPoint( meshAABB.GetMinPoint());
			localAABB.UnionPoint( meshAABB.GetMaxPoint());
			model.SetLocalBounds( localAABB);
		}
	}

	// ����
	void Model::FrameMove( float fTime)
	{
		RenderEntity::FrameMove( fTime);

		m_animationController.FrameMove( fTime, GetTransform().GetMatrix());

		// ���¹�������
		vector<Matrix44> boneTransform( 60);
		for( size_t i=0; i<m_renderables.size(); i++)
			m_animationController.GetCurrBone( boneTransform.data(), m_renderables[i].m_mesh->GetBoneIdxs());

		*m_boneTransform = boneTransform;
	}

	// �ύ����Ⱦ����( ʹ����Ч ��������)
	void Model::SubmitRenderElements( RenderElementMgr& renderElementMgr)
	{
		for( size_t i=0; i<m_renderables.size(); i++)
			m_renderables[i].SubmitRenderElements( renderElementMgr);
	}

	// ��ȡM1Renderable
	MeshRenderable& Model::GetMeshRenderable( size_t idx)
	{
		A_ASSERT( idx < m_renderables.size());

		return m_renderables[idx];
	}

	// ʹ�ù���ͼ
	bool Model::ApplyLightmap( TexturePtr lightmapTex, const Vector4& lightmapViewport, int meshIdx)
	{
		MeshRenderable& m1Renderable = GetMeshRenderable(meshIdx);
		if( m1Renderable.m_mesh)
		{
			// 2.���ò��ʾ�̬����
			m1Renderable.m_superMaterial->SetParamRef( "LightmapTex" ,	   MakeShaderParam( lightmapTex));
			m1Renderable.m_superMaterial->SetParamRef( "LightmapViewport", MakeShaderParam( lightmapViewport));

			// 1.��������Shader
			QWORD usage	= SMU_OutputDiffuse | SMU_OutputNormal | SMU_StaticLighting | (m_animationController.GetAnimation()?SMU_SkeletalMesh:0);
			AResSystem.LoadMaterialParameter( m1Renderable.m_superMaterial, m1Renderable.m_materialPath.c_str(), m1Renderable.m_materialIdx, usage);

			// 3.ָ���µ�Renderlayout
			AutoBindMaterialParameter( m1Renderable);
			AutoBindRenderLayout( m1Renderable);
		}
		
		return true;
	}

	// �󶨲��ʲ���
	void Model::AutoBindMaterialParameter( MeshRenderable& mr)
	{
		CameraSystem& cameraSystem = GetCameraSystem();

		// ���ز��ʾ�̬����
		if( m_animationController.GetAnimation())
		{				
			mr.m_superMaterial->SetParamRef( "BoneTransforms", m_boneTransform);
		}

		// �Զ��󶨲���
		for( size_t i=0; i< mr.m_superMaterial->GetParamNum(); i++)
		{
			const string autoVaule =  mr.m_superMaterial->GetParamAutoBind( i);
			if( autoVaule.substr( 0, 5)== "SPAB_")
			{
				if( autoVaule == "SPAB_WorldViewProj")
					 mr.m_superMaterial->SetParamRef( i, GetSPAB( RenderEntity::SP_WorldViewProj));
				else if( autoVaule == "SPAB_World")
					 mr.m_superMaterial->SetParamRef( i, GetSPAB( RenderEntity::SP_World));
				else if( autoVaule == "SPAB_View")
					 mr.m_superMaterial->SetParamRef( i, cameraSystem.GetSPAB( CameraSystem::SP_View));
				else if( autoVaule == "SPAB_ViewProj")
					 mr.m_superMaterial->SetParamRef( i, cameraSystem.GetSPAB( CameraSystem::SP_ViewProj));
				else if( autoVaule == "SPAB_SkyViewProj")
					 mr.m_superMaterial->SetParamRef( i, cameraSystem.GetSPAB( CameraSystem::SP_SkyViewProj));
			}
		}
	}

	// ��RenderLayout
	void Model::AutoBindRenderLayout( MeshRenderable& mr)
	{
		// renderlayout
		RenderLayoutPtr layout = mr.m_mesh->BuildRenderLayout( mr.m_superMaterial->GetVertexStreamFlag());

		mr.SetRenderlayout( layout);
	}

	// ��ӵ�������Ϣ
	void Model::OnAddToScene( Scene* scene)
	{
		RenderEntity::OnAddToScene( scene);

		// �Զ��󶨲��ʲ���
		foreach_( MeshRenderable& renderable, m_renderables)
			AutoBindMaterialParameter( renderable);
	}
}