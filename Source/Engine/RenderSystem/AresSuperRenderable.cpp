#include <Engine/RenderSystem/AresSuperRenderable.h>
#include <Engine/AresRoot.h>

#define MVF_Position	EF_BGR32F			// λ�ø�ʽ
#define MVF_DiffuseUV	EF_GR32F			// ���������������ʽ
#define MVF_LightmapUV	EF_GR32F			// ����ͼUV��ʽ
#define MVF_Normal		EF_BGR32F
#define MVF_Tangent		EF_BGR32F
#define MVF_Binormal	EF_BGR32F
#define MVF_Color		EF_BGR32F
#define MVF_Blendweight	EF_ABGR32F
#define MVF_BlendIdx	EF_ABGR32F

namespace Ares
{
	// ���캯��
	SuperRenderable::SuperRenderable( RenderEntity* entity)
		: m_entity( entity)
	{
		// ����
		m_superMaterial = MakeSharePtr( new_ SuperMaterial);
		SetMaterial( m_superMaterial);

		//----------------------��ʱ
		m_superMaterial->SetRenderQueue( RQ_Opacity);
		m_superMaterial->SetShaderTreePath( "DiffuseTexture.ast");
		m_superMaterial->SetUsage( SMU_OutputDiffuse | SMU_OutputNormal | SMU_OutputDepth);
		m_superMaterial->Compile();

		// �������
		TexturePtr texture = AResSystem.SyncLoadDDS( "cloth.dds", EAH_GPURead | EAH_Immutable);

		m_superMaterial->SetParamRef( "DiffuseTex", MakeShaderParam( texture));

		m_superMaterial->SetParamAutoBind("World", "SPAB_World");
		m_superMaterial->SetParamAutoBind("View", "SPAB_View");
		m_superMaterial->SetParamAutoBind("ViewProj", "SPAB_ViewProj");
			
		// ����
		m_layout = ARenderDevice->CreateRenderLayout(); A_ASSERT( m_layout);

		// ������
		m_vertexBuffer = ARenderDevice->CreateVertexBuffer( BU_Static, EAH_CPUWrite | EAH_GPURead, NULL);

		m_elementType = Mapping( m_superMaterial->GetVertexStreamFlag());
		m_layout->BindVertexStream( m_vertexBuffer, m_elementType);

		m_indexBuffer = ARenderDevice->CreateIndexBuffer( BU_Dynamic, EAH_CPUWrite | EAH_GPURead, NULL);
		m_layout->BindIndexStream( m_indexBuffer, EF_R16UI);
	}

	// ��������
	SuperRenderable::~SuperRenderable()
	{

	}

	// �󶨲��ʲ���
	void SuperRenderable::BindMaterialParameter()
	{
		if( !m_entity || !m_entity->GetScene()) return;

		CameraSystem& cameraSystem = m_entity->GetCameraSystem();

		// �Զ��󶨲���
		for( size_t i=0; i< m_superMaterial->GetParamNum(); i++)
		{
			const string autoVaule =  m_superMaterial->GetParamAutoBind( i);
			if( autoVaule.substr( 0, 5)== "SPAB_")
			{
				if( autoVaule == "SPAB_WorldViewProj")
					m_superMaterial->SetParamRef( i, m_entity->GetSPAB( RenderEntity::SP_WorldViewProj));
				else if( autoVaule == "SPAB_World")
					m_superMaterial->SetParamRef( i, m_entity->GetSPAB( RenderEntity::SP_World));
				else if( autoVaule == "SPAB_View")
					m_superMaterial->SetParamRef( i, cameraSystem.GetSPAB( CameraSystem::SP_View));
				else if( autoVaule == "SPAB_ViewProj")
					m_superMaterial->SetParamRef( i, cameraSystem.GetSPAB( CameraSystem::SP_ViewProj));
				else if( autoVaule == "SPAB_SkyViewProj")
					m_superMaterial->SetParamRef( i, cameraSystem.GetSPAB( CameraSystem::SP_SkyViewProj));
			}
		}
	}

	// ����RenderLayout
	void SuperRenderable::UpdateBuffer(RenderLayout::TopologyType topologyType, void* vertices, int vertexSizeInByte, const void* indices, int indicesSizeInByte)
	{
		m_layout->SetTopologyType( topologyType);

		// 2.���¶�������
		if( m_vertexBuffer && vertexSizeInByte)
		{
			m_vertexBuffer->Resize( vertexSizeInByte);
			GraphicsBuffer::Modifier tModifier( m_vertexBuffer, BA_WriteOnly);

			tModifier.Set( vertices, vertexSizeInByte);
		}

		// ����
		if( m_indexBuffer && indicesSizeInByte)
		{
			m_indexBuffer->Resize( indicesSizeInByte);
			GraphicsBuffer::Modifier tModifier( m_indexBuffer, BA_WriteOnly);

			tModifier.Set( indices, indicesSizeInByte);
		}
	}

	// ӳ��VertexElementType
	VertexElementType SuperRenderable::Mapping(  UINT vertexDataFlag)
	{
		VertexElementType result;

		if( vertexDataFlag & VSF_Position)
			result.push_back( VertexElement(VEU_Position,     0, MVF_Position));	

		if( vertexDataFlag & VSF_DiffuseUV)
			result.push_back( VertexElement(VEU_TextureCoord, 0, MVF_DiffuseUV));


		if( vertexDataFlag & VSF_LightmapUV)
			result.push_back( VertexElement(VEU_TextureCoord, 1, MVF_LightmapUV));

		if( vertexDataFlag & VSF_Normal)
			result.push_back( VertexElement(VEU_Normal,	0, MVF_Normal));

		if( vertexDataFlag & VSF_TangentBinormal)
		{
			result.push_back( VertexElement(VEU_Tangent,  0, MVF_Tangent));
			result.push_back( VertexElement(VEU_Binormal, 0, MVF_Binormal));
		}

		if( vertexDataFlag & VSF_Color)
			result.push_back( VertexElement(VEU_Color, 0, MVF_Color));

		if( vertexDataFlag & VSF_BoneInfulence)
		{
			result.push_back( VertexElement(VEU_BlendWeight, 0, MVF_Blendweight));
			result.push_back( VertexElement(VEU_BlendIndex, 0, MVF_BlendIdx));
		}

		return result;
	}
}