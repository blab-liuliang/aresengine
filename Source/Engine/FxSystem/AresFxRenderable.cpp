#include <Engine/AresRoot.h>
#include <Engine/FxSystem/AresFxRenderable.h>
#include <Engine/FxSystem/AresFxParticleSystem.h>
#include <Engine/SceneSystem/AresScene.h>

namespace Ares
{
	FxRenderable::FxRenderable()
		: Renderable()
		, m_isBillBoard( false)
	{
		// ��Ⱦ����
		m_material->SetRenderQueue( RQ_TransparentEffect);

		// ���ʳ�ʼ��
		m_spabWVP = MakeShaderParam( Matrix44::Identity);
        RenderMethodPtr renderMethod = AResSystem.LoadMethod("FxRender.hlsl");
		m_material->SetMethod( renderMethod);
		m_material->SetParamRef( "WorldViewProj", m_spabWVP);

		// ���ù�դ��״̬
		RasterizerStateDesc desc;
		desc.m_cullMode = CM_None;
		RasterizerStatePtr rasterizerState = ARenderDevice->CreateRasterizerState( desc);
		m_material->SetRasterizerState( rasterizerState);

		// �������״̬
		DepthStencilStateDesc dsDesc;
		dsDesc.m_depthWriteMask = false;
		DepthStencilStatePtr depthStencilState = ARenderDevice->CreateDepthStencilState( dsDesc);
		m_material->SetDepthStencilState( depthStencilState);

		// ���״̬ 
		BlendStateDesc bDesc;
		bDesc.m_blendEnable.assign( true);
		bDesc.m_blendOp.assign( BOP_Add);
		bDesc.m_srcBlend.assign( ABF_SrcAlpha);
		bDesc.m_destBlend.assign( ABF_InvSrcAlpha);
		bDesc.m_blendOpAlpha.assign( BOP_Add);
		bDesc.m_srcBlendAlpha.assign( ABF_One);
		bDesc.m_destBlendAlpha.assign( ABF_Zero);
		bDesc.m_colorWriteMask.assign( ColorRGB::MASK_All);
		BlendStatePtr blendState = ARenderDevice->CreateBlendState( bDesc);
		m_material->SetBlendState( blendState, ColorRGB(0.f,0.f,0.f), 0xffffffff);

		// ��ʼ��RenderLayout
		m_layout = ARenderDevice->CreateRenderLayout(); A_ASSERT( m_layout);
		m_layout->SetTopologyType( RenderLayout::TT_TriangleList);

		GraphicBufferPtr posUVBuffer = ARenderDevice->CreateVertexBuffer( BU_Static, EAH_CPUWrite | EAH_GPURead, NULL);

		m_elementType.push_back( VertexElement( VEU_Position,	  0, EF_BGR32F));
		m_elementType.push_back( VertexElement( VEU_TextureCoord, 0, EF_ABGR32F));
		m_elementType.push_back( VertexElement( VEU_TextureCoord, 1, EF_GR32F));

		m_layout->BindVertexStream( posUVBuffer, m_elementType);

		GraphicBufferPtr indexBuffer = ARenderDevice->CreateIndexBuffer( BU_Dynamic, EAH_CPUWrite | EAH_GPURead, NULL);
		m_layout->BindIndexStream( indexBuffer, EF_R16UI);
	}

	// ������Ⱦ����
	void FxRenderable::UpdateBuffer( RenderLayout::TopologyType topologyType,const VertexFormat* vertices, int vertexSizeInByte, WORD* indices, int indicesSizeInByte)
	{
		A_ASSERT( m_layout);

		m_layout->SetTopologyType( topologyType);

		// 2.���¶�������
		GraphicBufferPtr vertexBuffer = m_layout->GetVertexStream( m_elementType);
		if( vertexBuffer && vertexSizeInByte)
		{
			vertexBuffer->Resize( vertexSizeInByte);
			GraphicsBuffer::Modifier tModifier( vertexBuffer, BA_WriteOnly);

			tModifier.Set( vertices, vertexSizeInByte);
		}

		// ����
		GraphicBufferPtr indexBuffer = m_layout->GetIndicesStream();
		if( indexBuffer && indicesSizeInByte)
		{
			indexBuffer->Resize( indicesSizeInByte);
			GraphicsBuffer::Modifier tModifier( indexBuffer, BA_WriteOnly);

			tModifier.Set( indices, indicesSizeInByte);
		}
	}

	// ����
	void FxRenderable::FrameMove( float elpasedTime, FxEntity* fxEntity, FxObject* fxObject)
	{
		CameraSystem& cameraSystem = fxEntity->GetScene()->GetCameraSystem();

		Matrix44 world = fxObject->GetTransform()->GetMatrix();
		if( fxEntity)
			world = fxEntity->GetTransform().GetMatrix() * world;

		if( m_isBillBoard)
			*m_spabWVP = cameraSystem.GetViewRotationInverse() * world * cameraSystem.GetViewProj();
		else
			*m_spabWVP = world * cameraSystem.GetViewProj();
	}

	// ����Ϊ�ռ�Ť��
	void FxRenderable::SetRenderQueue( BITFIELD renderQueue)
	{
		GetMaterial()->SetRenderQueue( renderQueue);
	}

	// ��������
	void FxRenderable::SetTexture( const char* texturePath)
	{
		m_texture = texturePath;

		TexturePtr texture = AResSystem.SyncLoadDDS( texturePath, EAH_GPURead | EAH_Immutable);
		if( texture)
			m_material->SetParamRef( "g_diffuse", MakeShaderParam( texture));
	}
}