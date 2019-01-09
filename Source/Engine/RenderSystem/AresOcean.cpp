#include <Engine/RenderSystem/AresOcean.h>
#include <Engine/AresRoot.h>

namespace Ares
{
	// ���캯��
	Ocean::Ocean()
		: RenderEntity( ED_Ocean)
	{
		// ������Ⱦ����
		RenderMethodPtr rMethod = AResSystem.LoadMethod("Ocean.hlsl");
		m_renderable.GetMaterial()->SetMethod( rMethod);

		// Lod����
		m_lodFactor = MakeShaderParam( 0.98f);
		m_renderable.GetMaterial()->SetParamRef( "G_LodFactor", m_lodFactor);

		// ����0
		m_oceanParams0 = MakeShaderParam( Vector4( 1.f, 4.f, 5.f, 1.5f));
		m_renderable.GetMaterial()->SetParamRef( "G_OceanParams0", m_oceanParams0);
		
		// ����1
		m_oceanParams1 = MakeShaderParam( Vector4( 0.75f, -1.f, -1.f, 0.f));
		m_renderable.GetMaterial()->SetParamRef( "G_OceanParams1", m_oceanParams1);

		// ˮ��ɫ
		m_waterShallowColor = MakeShaderParam( Vector3( 0.f, 0.1f, 0.15f));
		m_renderable.GetMaterial()->SetParamRef( "G_WaterShallowColor", m_waterShallowColor);

		// ��ˮɫ
		m_waterDeepColor = MakeShaderParam( Vector3( 0.f, 0.1f, 0.125f));
		m_renderable.GetMaterial()->SetParamRef( "G_WaterDeepColor", m_waterDeepColor);

		// ��������
		m_fracStrength = MakeShaderParam( 0.03f);
		m_renderable.GetMaterial()->SetParamRef( "G_FracStrenght", m_fracStrength);

		// ��ĭ
		m_texFoam	= MakeShaderParam( AResSystem.SyncLoadDDS( "foam.dds", EAH_GPURead | EAH_Immutable));
		m_renderable.GetMaterial()->SetParamRef( "G_TexFoam", m_texFoam);

		// ˮ�沨��
		m_texWaveBump   = MakeShaderParam( AResSystem.SyncLoadDDS( "wavesbump.dds", EAH_GPURead | EAH_Immutable));
		m_renderable.GetMaterial()->SetParamRef( "G_TexWaveBump", m_texWaveBump);

		// ������ͼ
		m_texReflect	= MakeShaderParam( AResSystem.SyncLoadDDS( "reflect.dds", EAH_GPURead | EAH_Immutable));
		m_renderable.GetMaterial()->SetParamRef( "G_TexReflect", m_texReflect);

		// ��Ⱦ����
		m_renderable.GetMaterial()->SetRenderQueue( RQ_Water);

		// ����Ĭ����ȾBuffer
		SetScreenSpaceGridSize( 100);

		//// ������ ���ù�դ��״̬
		//RasterizerStateDesc desc;
		//desc.m_fillMode = FM_WireFrame;
		//RasterizerStatePtr rasterizerState = ARenderDevice->CreateRasterizerState( desc);
		//m_renderable.GetMaterial()->SetRasterizerState( rasterizerState);
	}

	// ��������
	Ocean::~Ocean()
	{

	}

	// ������Ļ�ռ��ʽ��С
	void Ocean::SetScreenSpaceGridSize( int gridNum)
	{
		A_ASSERT( gridNum * gridNum < 65535);

		m_scrGridNum = gridNum;

		// define elementType
		VertexElementType elementTypePos;
		elementTypePos.push_back( VertexElement(VEU_Position, 0, EF_BGR32F));

		// 1.������������
		RenderLayoutPtr layout = ARenderDevice->CreateRenderLayout();
		layout->SetTopologyType( RenderLayout::TT_TriangleList);

		vector<Vector3> positions; positions.resize( m_scrGridNum*m_scrGridNum);
		vector<WORD>	indices;   indices.reserve( m_scrGridNum*m_scrGridNum * 6);

		// ���㶥��
		float rcpSrcGridSize = 1.f / (float)m_scrGridNum;
		for( int i=0; i<m_scrGridNum; i++)
		{
			for ( int j=0; j<m_scrGridNum; j++)
			{
				UINT  index = i * m_scrGridNum + j;
				positions[index].x = (float)j * rcpSrcGridSize + rcpSrcGridSize;
				positions[index].y = (float)i * rcpSrcGridSize + rcpSrcGridSize;

				// store edges information
				float fx = fabs( positions[index].x * 2.f-1.f);
				float fy = fabs( positions[index].y * 2.f-1.f);

				float fEdgeDisplace = max( fx, fy);
				positions[index].z  =fEdgeDisplace;
			}
		}

		// ��������
		for( int i=0; i<m_scrGridNum-1; i++)
		{
			for ( int j=0; j<m_scrGridNum-1; j++)
			{
				WORD index = static_cast<WORD>( i * m_scrGridNum + j);

				indices.push_back( index);
				indices.push_back( index + m_scrGridNum + 1);
				indices.push_back( index + m_scrGridNum);

				indices.push_back( index);
				indices.push_back( index + 1);
				indices.push_back( index + m_scrGridNum + 1);
			}
		}

		// 2.���ö���
		ElementInitData initVertexData;
		initVertexData.m_rowPitch   = sizeof(Vector3)*positions.size();
		initVertexData.m_slicePitch = 0;
		initVertexData.m_data		= positions.data();
		GraphicBufferPtr vertexPosBuffer = ARenderDevice->CreateVertexBuffer( BU_Dynamic, EAH_GPURead | EAH_Immutable, &initVertexData);
		layout->BindVertexStream( vertexPosBuffer, elementTypePos);

		ElementInitData initIndexData;
		initIndexData.m_rowPitch   = sizeof(WORD)*indices.size();
		initIndexData.m_slicePitch = 0;
		initIndexData.m_data	   = indices.data();
		GraphicBufferPtr indexBuffer = ARenderDevice->CreateIndexBuffer( BU_Dynamic, EAH_GPURead | EAH_Immutable, &initIndexData);
		layout->BindIndexStream( indexBuffer, EF_R16UI);

		m_renderable.SetRenderlayout( layout);
	}

	// ����
	void Ocean::FrameMove( float fTime)
	{
		RenderEntity::FrameMove( fTime);
	}

	// ��ӵ�������Ϣ
	void Ocean::OnAddToScene( Scene* scene)
	{
		RenderEntity::OnAddToScene( scene);

		CameraSystem& cameraSystem = GetCameraSystem();

		// �Զ��󶨲���
		m_renderable.GetMaterial()->SetParamRef( "G_Time",			scene->GetSPABElapsedTime());
		m_renderable.GetMaterial()->SetParamRef( "G_CameraPos",		cameraSystem.GetSPAB( CameraSystem::SP_Pos));
		m_renderable.GetMaterial()->SetParamRef( "G_CameraUp",		cameraSystem.GetSPAB( CameraSystem::SP_Up));
		m_renderable.GetMaterial()->SetParamRef( "G_CameraRight",	cameraSystem.GetSPAB( CameraSystem::SP_Right));
		m_renderable.GetMaterial()->SetParamRef( "G_CameraFront",	cameraSystem.GetSPAB( CameraSystem::SP_Front));
		m_renderable.GetMaterial()->SetParamRef( "G_CameraNearFar", cameraSystem.GetSPAB( CameraSystem::SP_NearFar));
		m_renderable.GetMaterial()->SetParamRef( "G_ViewProj",		cameraSystem.GetSPAB( CameraSystem::SP_ViewProj));
		m_renderable.GetMaterial()->SetParamRef( "G_View",			cameraSystem.GetSPAB( CameraSystem::SP_View));
		m_renderable.GetMaterial()->SetParamRef( "G_TexSceneDepth", GetScene()->GetRenderSystem().GetDeferredRenderingMgr()->GetSPABOpaqueZDistance());
		m_renderable.GetMaterial()->SetParamRef( "G_TexRefraction", GetScene()->GetRenderSystem().GetSPABWaterRefraction());
		m_renderable.GetMaterial()->SetParamRef( "G_SunColor",		GetScene()->GetSPABSunColor());
		m_renderable.GetMaterial()->SetParamRef( "G_SunDir",		GetScene()->GetSPABSunDir());
	}

	// �ύ��ȾԪ��
	void Ocean::SubmitRenderElements( RenderElementMgr& renderElementMgr)
	{
		// �ύ��Ⱦ
		m_renderable.SubmitRenderElements( renderElementMgr);
	}
}