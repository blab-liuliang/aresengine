#include <Engine/RenderSystem/AresVisualShape.h>
#include <Engine/AresRoot.h>

namespace Ares
{
	// ���캯�� 
	VisualShape::VisualShape( Scene& scene, VisualShapeType type)
		: Renderable()
		, m_type( type)
		, m_isFixedSize( false)
		, m_visible( false)
		, m_scene( scene)
	{
        RenderMethodPtr rMethod = AResSystem.LoadMethod("visualshape.hlsl");
		m_material->SetMethod( rMethod);

		// ��������
		m_worldViewProj = MakeShaderParam( m_transform.GetMatrix());
		m_material->SetParamRef( "g_worldViewProj", m_worldViewProj);

		m_spWorld      = MakeShaderParam();
		m_material->SetParamRef( "G_World", m_spWorld);

		// ��������⳯��
		m_material->SetParamRef( "g_sunDir", RenderSystem::SPAB_SunDirection);

		// �߶���ɫ 
		m_color = MakeShaderParam( ColorRGB( 1.f, 1.f, 1.f));
		m_material->SetParamRef( "g_color", m_color);

		// ���ƫ��
		m_depthBias = MakeShaderParam( 0.f);
		m_material->SetParamRef( "DepthBias", m_depthBias);

		// �Ƿ�ʹ�÷���
		m_useNormal = MakeShaderParam( 0.f);
		m_material->SetParamRef( "g_useNormal", m_useNormal);

		// ��Ⱦ����
		m_material->SetRenderQueue( RQ_AuxiliaryDisplay);	
	}

	// ��������
	VisualShape::~VisualShape()
	{
	}

	// ����
	void VisualShape::FrameMove()
	{
		CameraSystem& cameraSystem = m_scene.GetCameraSystem();

		*m_spWorld = m_transform.GetMatrix();

		if( m_isFixedSize)
			*m_worldViewProj = m_transform.GetMatrix() * cameraSystem.GetViewOrtho();
		else
			*m_worldViewProj = m_transform.GetMatrix() * cameraSystem.GetViewProj();
	}

	// ���ù̶���С
	void VisualShape::SetSizeFixed( bool isFixed, float sizePixel/*=100.f*/) 
	{ 
		m_isFixedSize = isFixed; 

		//m_transform.SetScale( 100.f);
	}

	// ����RenderLayout
	void VisualShape::Set(RenderLayout::TopologyType topologyType, Vector3* positions, int vertexSizeInByte, const void* indices, int indicesSizeInByte, ElementFormat indiceFormat/*=EF_R16UI*/, Vector3* normals/*=0*/, DWORD* colors/*=NULL*/)
	{
		// define elementType
		VertexElementType elementTypePos;
		elementTypePos.push_back( VertexElement(VEU_Position, 0, EF_BGR32F));

		VertexElementType elementTypeNormal;
		elementTypeNormal.push_back( VertexElement(VEU_Normal, 0, EF_BGR32F));

		VertexElementType elementTypeColor;
		elementTypeColor.push_back( VertexElement( VEU_Color, 0, EF_ARGB8));

		vector<Vector3> tNormals;
		if( !normals)
		{
			tNormals.resize( vertexSizeInByte/sizeof(Vector3));
			normals = tNormals.data();
		}
		else
			*m_useNormal = 1.f;

		vector<DWORD> tColors;
		if( !colors)
		{
			tColors.resize( vertexSizeInByte/sizeof(Vector3), ColorRGB::White.ToDWORD());
			colors = tColors.data();
		}

		if( !m_layout)
		{
			// 1.������������
			m_layout = ARenderDevice->CreateRenderLayout();
			m_layout->SetTopologyType( topologyType);

			// 2.���ö���
			ElementInitData initVertexData;
			initVertexData.m_rowPitch   = vertexSizeInByte;
			initVertexData.m_slicePitch = 0;
			initVertexData.m_data		= positions;
			GraphicBufferPtr vertexPosBuffer = ARenderDevice->CreateVertexBuffer( BU_Dynamic, EAH_CPUWrite | EAH_GPURead, &initVertexData);
			m_layout->BindVertexStream( vertexPosBuffer, elementTypePos);

			// 2.���÷���
			ElementInitData initNormalData;
			initNormalData.m_rowPitch   = vertexSizeInByte;
			initNormalData.m_slicePitch = 0;
			initNormalData.m_data		= normals;
			GraphicBufferPtr normalBuffer = ARenderDevice->CreateVertexBuffer( BU_Dynamic, EAH_CPUWrite | EAH_GPURead, &initNormalData);
			m_layout->BindVertexStream( normalBuffer, elementTypeNormal);

			// 3.������ɫ
			ElementInitData initColorData;
			initColorData.m_rowPitch	= vertexSizeInByte/sizeof(Vector3) * sizeof(DWORD);
			initColorData.m_slicePitch	= 0;
			initColorData.m_data		= colors;
			GraphicBufferPtr colorBuffer = ARenderDevice->CreateVertexBuffer( BU_Dynamic, EAH_CPUWrite | EAH_GPURead, &initColorData);
			m_layout->BindVertexStream( colorBuffer, elementTypeColor);

			// ����
			if( indices)
			{
				ElementInitData initIndexData;
				initIndexData.m_rowPitch   = indicesSizeInByte;
				initIndexData.m_slicePitch = 0;
				initIndexData.m_data	   = indices;
				GraphicBufferPtr indexBuffer = ARenderDevice->CreateIndexBuffer( BU_Dynamic, EAH_CPUWrite | EAH_GPURead, &initIndexData);
				m_layout->BindIndexStream( indexBuffer, indiceFormat);
			}
		}
		else
		{
			m_layout->SetTopologyType( topologyType);

			// 2.���¶�������
			GraphicBufferPtr vertexPosBuffer = m_layout->GetVertexStream( elementTypePos);
			if( vertexPosBuffer)
			{
				vertexPosBuffer->Resize( vertexSizeInByte);
				GraphicsBuffer::Modifier tModifier( vertexPosBuffer, BA_WriteOnly);

				tModifier.Set( positions, vertexSizeInByte);
			}

			// 2.���·�������
			GraphicBufferPtr normalBuffer = m_layout->GetVertexStream( elementTypeNormal);
			if( normalBuffer)
			{
				vertexPosBuffer->Resize( vertexSizeInByte);
				GraphicsBuffer::Modifier tModifier( normalBuffer, BA_WriteOnly);

				tModifier.Set( normals, vertexSizeInByte);
			}

			// 3.������ɫ����
			GraphicBufferPtr colorBuffer = m_layout->GetVertexStream( elementTypeColor);
			if( colorBuffer)
			{
				colorBuffer->Resize( vertexSizeInByte / sizeof(Vector3) * sizeof(DWORD));
				GraphicsBuffer::Modifier tModifier( colorBuffer, BA_WriteOnly);

				tModifier.Set( colors, vertexSizeInByte / sizeof(Vector3) * sizeof(DWORD));
			}

			// ����
			if( indices)
			{
				GraphicBufferPtr indexBuffer = m_layout->GetIndicesStream();
				if( indexBuffer)
				{
					indexBuffer->Resize( indicesSizeInByte);
					GraphicsBuffer::Modifier tModifier( indexBuffer, BA_WriteOnly);

					tModifier.Set( indices, indicesSizeInByte);
				}
			}
		}
	}

	//-----------------------------------
	// Line
	//-----------------------------------
	// ���캯��
	VisualSegment3::VisualSegment3( Scene& scene)
		: VisualShape( scene)
	{	
	}

	// ����
	void VisualSegment3::Set( const Segment3& segment)
	{
		m_segment = segment;

		// create vertex buffer
		Vector3 positions[] =
		{
			m_segment.GetVertex1(),
			m_segment.GetVertex0(),
		};

		VisualShape::Set( RenderLayout::TT_LineList, positions, sizeof(positions), NULL, 0);
	}

	// �����߶β���( vertex0, vertex1)
	void VisualSegment3::Set(  float x0, float y0, float z0, float x1, float y1, float z1)
	{
		Segment3 segment( Vector3( x0, y0, z0), Vector3( x1, y1, z1));

		Set( segment);
	}

	//----------------------------------------
	// Բ  2010-08-05   ����
	//----------------------------------------
	// ���캯��
	VisualCycle3::VisualCycle3( Scene& scene)
		: VisualShape( scene)
	{
	}

	// ���ð뾶
	void VisualCycle3::SetRadius( float _radius)
	{
		// ��������
		Vector3 positions[25];
		WORD    indices[25];

		for ( int i=0; i<25; i++)
		{
			float theta = ( 2 * PI * i) / 24.0f;

			positions[i].x = 0.0f;
			positions[i].y = sinf(theta) * _radius;
			positions[i].z = cosf(theta) * _radius;
		}

		// index data
		for ( int i=0; i<25; i++)
			indices[i] =  i; 

		VisualShape::Set( RenderLayout::TT_LineStrip, positions, sizeof(positions), indices, sizeof(indices), EF_R16UI);
	}

	// ��������
	void VisualCycle3::SetFace( Vector3& face)
	{
		m_transform.SetRotation( Vector3::XAxis, face);
	}

	// ���캯��
	VisualCapsule::VisualCapsule( Scene& scene)
		: VisualShape( scene, VST_Capsule)
	{}

	// ���ò���
	void VisualCapsule::SetShape( float height, float radius)
	{
		m_capsuleInternal = Capsule3( Segment3( Vector3::Zero, Vector3( 0.f, 0.f, height)), radius);

		const int column = 25;				// Ĭ������
		const int segment= 5;				// �ָ�����
		const int row	 = (segment+1)*2;	// Ĭ������

		vector<Vector3> positions(column*row);
		vector<WORD>    indices(column*(row-1)*6);

		// �°���
		int pOffset = 0;
		for ( int i=-segment; i<=0; i++)
		{
			float segmentLen = m_capsuleInternal.m_radius * -sqrtf((float)-i/segment);
			float radius	 = sqrtf( m_capsuleInternal.m_radius*m_capsuleInternal.m_radius - segmentLen*segmentLen);
			float height	 = m_capsuleInternal.m_segment.GetVertex0().z + segmentLen;

			for( int j=0; j<column; j++)
			{
				//int   idx   = column * -i + j;
				float theta = ( 2 * PI * j) / 25.0f;

				positions[pOffset].x = sinf(theta) * radius;
				positions[pOffset].y = cosf(theta) * radius;
				positions[pOffset].z = height;

				pOffset++;
			}
		}

		// �ϰ���
		for ( int i=0; i<=segment; i++)
		{
			float segmentLen = m_capsuleInternal.m_radius * sqrtf((float)i / segment);
			float radius	 = sqrtf( m_capsuleInternal.m_radius*m_capsuleInternal.m_radius - segmentLen*segmentLen);
			float height	 = m_capsuleInternal.m_segment.GetVertex1().z + segmentLen;

			for( int j=0; j<column; j++)
			{
				//int   idx	= column*row/2 + column * i + j;
				float theta = ( 2 * PI * j) / 25.0f;

				positions[pOffset].x = sinf(theta) * radius;
				positions[pOffset].y = cosf(theta) * radius;
				positions[pOffset].z = height;

				pOffset++;
			}
		}

		// indices
		int	kOffset = 0;
		for ( int i=0; i<row-1; i++)
		{
			for ( int j=0; j<column; j++)
			{
				int tj = (j+1)%column;

				indices[kOffset+0] = i==0 ? 0 : i*column+j;
				indices[kOffset+1] = (i+2==row) ? column*row-1:(i+1)*column+j;
				indices[kOffset+2] = (i+2==row) ? column*row-1:(i+1)*column+tj;
				indices[kOffset+3] = i==0 ? 0 : i*column+j;
				indices[kOffset+4] = (i+2==row) ? column*row-1:(i+1)*column+tj;
				indices[kOffset+5] = i==0 ? 0 : i*column+tj;
				kOffset += 6;
			}
		}

		// ���㷨��
		vector<Vector3>	normals(column*row);
		TBNComputeNormal( normals.data(), positions.data(), positions.size(), indices.data(), indices.size()/3);

		// ����ֵ
		VisualShape::Set( RenderLayout::TT_TriangleList, positions.data(), sizeof(Vector3)*positions.size(), indices.data(), sizeof(WORD)*indices.size(), EF_R16UI, normals.data());
	}

	// ���ò���
	void VisualCapsule::SetShape( const Capsule3& capsule)
	{
		SetShape( capsule.m_segment.Length(), capsule.m_radius);	

		// �޸��������(����ת��ƽ��)
		GetTransform()->SetRotation( Vector3::ZAxis, capsule.m_segment.m_dir);
		GetTransform()->SetTrans( capsule.m_segment.GetVertex0());
	}

	// ��ȡ����
	Capsule3 VisualCapsule::GetCapsule()
	{
		Vector3 v0     = m_transform.GetMatrix().TransformVector3( m_capsuleInternal.m_segment.GetVertex0());
		Vector3 v1     = m_transform.GetMatrix().TransformVector3( m_capsuleInternal.m_segment.GetVertex1());
		float   radius = m_capsuleInternal.m_radius;

		return Capsule3( Segment3( v0, v1), radius);
	}

	//----------------------------------------
	// ����  2010-08-05 �޸�
	//----------------------------------------
	// ���캯��
	VisualRect3::VisualRect3( Scene& scene)
		: VisualShape( scene)
	{
	}

	// ����
	void VisualRect3::Set( const Rect3& rect)
	{
		m_rect = rect;

		vector<Vector3> positions; positions.resize( 8);
		m_rect.GetEightPoints( positions);

		WORD indices[] =  { 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 3, 7, 2, 6 };

		VisualShape::Set( RenderLayout::TT_LineList, positions.data(), positions.size() * sizeof(Vector3), indices, sizeof(indices), EF_R16UI);
	}

	// ���캯��
	VisualBox3::VisualBox3( Scene& scene)
		: VisualShape( scene)
	{}

	// ���������Χ��
	void VisualBox3::Set(const Box3& box)
	{
		int indices[] =  { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7,  4, 0, 3, 4, 3, 7, 5, 1, 2, 5, 2, 6, 4, 0, 1, 4, 1, 5, 7, 3, 2, 7, 2, 6};

		boost::array<Vector3, 8> positions;
		box.BuildEightPoints( positions.data());

		vector<Vector3>	normals( positions.size());
		TBNComputeNormal( normals.data(), positions.data(), positions.size(), indices, 12);

		VisualShape::Set( RenderLayout::TT_TriangleStrip, positions.data(), positions.size() * sizeof(Vector3), indices, sizeof(indices), EF_R32UI, normals.data(), NULL);
		
		//WORD indices[] =  { 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 3, 7, 2, 6 };

		//VisualShape::Set( RenderLayout::TT_LineList, positions.data(), positions.size() * sizeof(Vector3), indices, sizeof(indices), EF_R16UI);
	}


	//----------------------------------------
	// Բ׶
	//----------------------------------------
	// ���캯��
	VisualCone3::VisualCone3( Scene& scene)
		: VisualShape( scene)
	{
	}

	// ���ò���
	void VisualCone3::SetRadiusAndHeight( float _radius, float _height)
	{
		// ��������
		Vector3 positions[27];
		WORD    indices[150];

		for ( int i=0; i<25; i++)
		{
			float theta = ( 2 * PI * i) / 24.0f;

			positions[i].x = 0.0f;
			positions[i].y = sinf(theta) * _radius;
			positions[i].z = cosf(theta) * _radius;
		}
		positions[25] = Vector3( 0.0f, 0.0f, 0.0f);
		positions[26] = Vector3( _height, 0.0f, 0.0f);

		for ( int i=0; i<25; i++)
		{
			float theta = ( 2 * PI * i) / 24.0f;

			indices[i * 6]     =  i; 
			indices[i * 6 + 1] =  i+1; 
			indices[i * 6 + 2] =  25; 
			indices[i * 6 + 3] =  i; 
			indices[i * 6 + 4] =  26;
			indices[i * 6 + 5] =  i+1; 
		}

		VisualShape::Set( RenderLayout::TT_TriangleList, positions, sizeof(positions), indices, sizeof(indices), EF_R16UI);
	}

	// ��������
	void VisualCone3::SetFace(Vector3& face)
	{
		m_transform.SetRotation( Vector3::XAxis, face);
	}

	// construct function
	VisualShapeMgr::VisualShapeMgr( Scene& scene)
		: m_scene( scene)
	{
		//m_renderQueue = RenderQueueMgr::OpenRenderQueue( "VisualShape");
	}

	// deconstructor
	VisualShapeMgr::~VisualShapeMgr()
	{

	}

	// �������������
	VisualShape* VisualShapeMgr::CreateVisualShape( int layer)
	{
		VisualShape* shape = new_ VisualShape( m_scene);
		if ( shape)
		{
			m_shapes.insert( make_pair( layer, shape));

			return shape;
		}

		return NULL;
	}

	// �����߶�
	VisualSegment3* VisualShapeMgr::CreateSegment( int layer)
	{
		VisualSegment3* shape = new_ VisualSegment3( m_scene);
		if ( shape)
		{
			m_shapes.insert( make_pair( layer, shape));

			return shape;
		}

		return NULL;
	}

	// ����Բ׶��
	VisualCone3* VisualShapeMgr::CreateCone( int layer)
	{
		VisualCone3* shape = new_ VisualCone3( m_scene);
		if ( shape)
		{
			m_shapes.insert( make_pair( layer, shape));

			return shape;
		}

		return NULL;
	}

	// ����Բ(2D)
	VisualCycle3* VisualShapeMgr::CreateCycle( int layer)
	{
		VisualCycle3* shape = new_ VisualCycle3( m_scene);
		if ( shape)
		{
			m_shapes.insert( make_pair( layer, shape));

			return shape;
		}

		return NULL;
	}

	// ��������
	VisualCapsule* VisualShapeMgr::CreateCapsule( int layer)
	{
		VisualCapsule* shape = new_ VisualCapsule( m_scene);
		if( shape)
		{
			m_shapes.insert( make_pair( layer, shape));

			return shape;
		}

		return NULL;
	}

	// ����Box
	VisualRect3* VisualShapeMgr::CreateRect3( int layer)
	{
		VisualRect3* shape = new_ VisualRect3( m_scene);
		if ( shape)
		{
			m_shapes.insert( make_pair( layer, shape));

			return shape;
		}

		return NULL;
	}

	// ���������Χ��
	VisualBox3* VisualShapeMgr::CreateBox3( int layer)
	{
		VisualBox3* shape = new_ VisualBox3( m_scene);
		if ( shape)
		{
			m_shapes.insert( make_pair( layer, shape));

			return shape;
		}

		return NULL;
	}

	// ɾ��
	bool VisualShapeMgr::DeleteVisualShape( VisualShape* shape)
	{
		for( VisualShapeList::iterator it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			if( it->second == shape)
			{
				// δɾ��(BUG)
				it->second->SetVisible( false);

				m_shapes.erase( it);

				return true;
			}
		}

		return false;
	}

	// ����
	void VisualShapeMgr::FrameMove()
	{
		// ��Ⱦ���еĻ�����
		for( VisualShapeList::const_iterator it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			if( it->second->IsVisible())
				it->second->FrameMove();
		}
	}

	// ��Ⱦ
	void VisualShapeMgr::SubmitRenderElements( RenderElementMgr& renderElementMgr)
	{
		// ��Ⱦ���еĻ�����
		for( VisualShapeList::const_iterator it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			if( it->second->IsVisible())
				it->second->SubmitRenderElements( renderElementMgr);
		}
	}
}