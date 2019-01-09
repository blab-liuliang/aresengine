//#include "LightMapRasterizer.h"
//#include "Scene/SceneLightObject.h"
//
//namespace LORD
//{
//	// ������
//	struct IndexerHelper
//	{
//	public:
//		// ���캯��
//		IndexerHelper( ui32 width, ui32 height, ui32 wIdx, ui32 hIdx)
//			: m_width(width), m_height(height), m_wIdx(wIdx), m_hIdx(hIdx)
//		{}
//
//		// ��ȡ�������
//		ui32 getRelativeIdx( int rw, int rh) const
//		{
//			return ( m_hIdx+rh)*m_width + m_wIdx + rw;
//		}
//
//		// �ж������Ƿ���Ч
//		bool isValidIdx( int rw, int rh) const
//		{
//			return rw+m_wIdx>=0&&rw+m_wIdx<m_width&&rh+m_hIdx>=0&&rh+m_hIdx<m_height;
//		}
//
//	private:
//		ui32	m_width;
//		ui32	m_height;
//		ui32	m_wIdx;
//		ui32	m_hIdx;
//	};
//
//	// ������
//	struct GaussianHelper
//	{
//	public:
//		// ���캯��
//		GaussianHelper( float radius)
//		{
//			radius = std::min<float>( radius, 50);
//			m_rho				= radius / 3.f;
//			m_halfDimension		= static_cast<int>(Math::Ceil( radius));
//			m_dimension			= m_halfDimension * 2 + 1;
//
//			// Ԥ����distribution
//			initDistribution( m_rho);
//		}
//
//		// ��ȡ��˹ģ��������(��������)
//		float getDistribution( int dx, int dy)
//		{
//			return m_distribution[dx+m_halfDimension][dy+m_halfDimension];
//		}
//
//		// ��ȡ�뾶
//		int getHalfDimension() { return m_halfDimension; }
//
//	private:
//		// ��ʼ���ֲ���
//		void initDistribution( float rho)
//		{
//			float g = 1.f / (2.f*Math::PI*rho*rho);
//
//			// Ԥ����distribution
//			for ( int dx=-m_halfDimension; dx<=m_halfDimension; dx++)
//				for ( int dy=-m_halfDimension; dy<=m_halfDimension; dy++)
//				{
//					m_distribution[dx+m_halfDimension][dy+m_halfDimension]  = g * std::exp( -(dx*dx+dy*dy) / (2*rho*rho));
//				}
//		}
//
//	private:
//		float			m_rho;
//		int				m_dimension;				// ά��
//		int				m_halfDimension;			// 0.5ά��
//		float			m_distribution[101][101];	// �ֲ���
//	};
//
//	// �߹��캯��
//	LightmapRasterizer::Edge::Edge( const PixelInput& v1, const PixelInput& v2)
//	{
//		if( v1.m_uv.y < v2.m_uv.y)
//		{
//			m_v1 = v1;
//			m_v2 = v2;
//		}
//		else
//		{
//			m_v1 = v2;
//			m_v2 = v1;
//		}
//	}
//
//	// ��������� "-"
//	LightmapRasterizer::PixelInput LightmapRasterizer::PixelInput::operator + ( const PixelInput& pi) const
//	{
//		PixelInput result;
//		result.m_uv		  = m_uv + pi.m_uv;
//		result.m_position = m_position + pi.m_position;
//		result.m_normal   = m_normal   + pi.m_normal;
//
//		return result;
//	}
//
//	// ��������� "-"
//	LightmapRasterizer::PixelInput LightmapRasterizer::PixelInput::operator - ( const PixelInput& pi) const
//	{
//		PixelInput result;
//		result.m_uv		  = m_uv - pi.m_uv;
//		result.m_position = m_position - pi.m_position;
//		result.m_normal   = m_normal   - pi.m_normal;
//
//		return result;
//	}
//
//	// ��������� "*"
//	LightmapRasterizer::PixelInput LightmapRasterizer::PixelInput::operator * ( float scale) const
//	{
//		PixelInput result;
//		result.m_uv = m_uv * scale;
//		result.m_position = m_position * scale;
//		result.m_normal   = m_normal   * scale;
//
//		return result;
//	}
//
//	// ��
//	LightmapRasterizer::Span::Span(const LightmapRasterizer::PixelInput &v1, const LightmapRasterizer::PixelInput &v2)
//	{
//		if( v1.m_uv.x<v2.m_uv.x)
//		{
//			m_v1 = v1;
//			m_v2 = v2;
//		}
//		else
//		{
//			m_v1 = v2;
//			m_v2 = v1;
//		}
//	}
//
//	// ���캯��
//	LightmapRasterizer::LightmapRasterizer()
//	{
//
//	}
//
//	// ��������
//	LightmapRasterizer::~LightmapRasterizer()
//	{
//
//	}
//
//	// ����֡������
//	void LightmapRasterizer::setFramebuffer( uint width, uint height)
//	{
//		m_width = width;
//		m_height= height;
//
//		m_frameBuffer.resize( width*height, Color::BLACK);
//	}
//
//	// ����
//	void LightmapRasterizer::draw( vector<VertexInput>::type& vertices, vector<Word>::type& indices, const Scene::GameObjectList& ltList)
//	{
//		LordAssert( indices.size()%3 == 0);
//
//		// ���ñ���ɫ(��)
//		clear( Color( 0, 0, 0, 0));
//
//		int numFaces = indices.size() / 3;
//
//#pragma omp parallel for
//		for ( int i=0; i<numFaces; i++)
//		{
//			int offset = i*3;
//
//			drawTriangle( vertices[indices[offset+0]], vertices[indices[offset+1]], vertices[indices[offset+2]], ltList);
//		}
//
//		edgePadding();
//		gaussianBlur();
//	}
//
//	// ������ɫ��
//	void LightmapRasterizer::execVertexShader( PixelInput& out, const VertexInput& input)
//	{
//		if (input.m_uniqueUV.x < 0.0f || input.m_uniqueUV.x >1.0f || input.m_uniqueUV.y < 0.0f || input.m_uniqueUV.y >1.0f)
//		{
//			LordException("LightMap UV is not correct!");
//		}
//		out.m_uv.x     = input.m_uniqueUV.x * m_width;
//		out.m_uv.y     = input.m_uniqueUV.y * m_height;
//		out.m_normal   = input.m_normal;
//		out.m_position = input.m_position;// * ;
//	}
//
//	// ���֡����
//	void LightmapRasterizer::clear( const Color& color)
//	{
//		for ( size_t i=0; i<m_frameBuffer.size(); i++)
//			m_frameBuffer[i] = color;
//	}
//
//	// ����������
//	void LightmapRasterizer::drawTriangle( const VertexInput& v0, const VertexInput& v1, const VertexInput& v2, const Scene::GameObjectList& ltList)
//	{
//		PixelInput pV0, pV1, pV2;
//
//		execVertexShader( pV0, v0);
//		execVertexShader( pV1, v1);
//		execVertexShader( pV2, v2);
//
//		// ������
//		Edge edges[3] = { Edge( pV0, pV1), Edge( pV1, pV2), Edge( pV2, pV0) };
//
//		int maxLenght = 0;
//		int longEdge  = 0;
//
//		// find edge with the greatest length in the y axis
//		for( int i=0; i<3; i++)
//		{
//			int lenght = static_cast<int>( edges[i].Y2() - edges[i].Y1());
//			if( lenght>maxLenght)
//			{
//				maxLenght = lenght;
//				longEdge  = i;
//			}
//		}
//
//		int shortEdge1 = (longEdge+1) % 3;
//		int shortEdge2 = (longEdge+2) % 3;
//
//		// draw spans between edges; the long edge can be drawn
//		// with the shorter edges to draw the full triangle
//		drawSpansBetweenEdges( edges[longEdge], edges[shortEdge1], ltList);
//		drawSpansBetweenEdges( edges[longEdge], edges[shortEdge2], ltList);
//	}
//
//	// ��������֮�������
//	void LightmapRasterizer::drawSpansBetweenEdges( const Edge& e1, const Edge& e2, const Scene::GameObjectList& ltList)
//	{
//		// calculate difference between the y coordinates of the first edge and return if 0
//		float e1ydiff = (float)(e1.Y2() - e1.Y1());
//		if(e1ydiff == 0.0f)
//			return;
//
//		// calculate difference between the y coordinates of the second edge and return if 0
//		float e2ydiff = (float)(e2.Y2() - e2.Y1());
//		if(e2ydiff == 0.0f)
//			return;
//
//		// calculate differences between the x coordinates
//		// and colors of the points of the edges
//		PixelInput e1diff = (e1.m_v2 - e1.m_v1);
//		PixelInput e2diff = (e2.m_v2 - e2.m_v1);
//
//		// calculate factors to use for interpolation
//		// with the edges and the step values to increase
//		// them by after drawing each span
//		float factor1 = (float)(e2.Y1() - e1.Y1()) / e1ydiff;
//		float factorStep1 = 1.0f / e1ydiff;
//		float factor2 = 0.0f;
//		float factorStep2 = 1.0f / e2ydiff;
//
//		// loop through the lines between the edges and draw spans
//		for(int y = static_cast<int>(e2.Y1()); y < static_cast<int>(e2.Y2()); y++) 
//		{
//			// create and draw span
//			PixelInput spanV1 = e1.m_v1 + (e1diff * factor1);
//			PixelInput spanV2 = e2.m_v1 + (e2diff * factor2);
//			Span span( spanV1, spanV2);
//			drawSpan(span, y, ltList);
//
//			// increase factors
//			factor1 += factorStep1;
//			factor2 += factorStep2;
//		}
//	}
//
//	// ��������
//	void LightmapRasterizer::drawSpan(const Span &span, int y, const Scene::GameObjectList& ltList)
//	{
//		int xdiff = span.X2() - span.X1();
//		if(xdiff == 0)
//			return;
//
//		PixelInput colordiff = span.m_v2 - span.m_v1;
//
//		float factor = 0.0f;
//		float factorStep = 1.0f / (float)xdiff;
//
//		// draw each pixel in the span
//		for(int x = span.X1(); x < span.X2(); x++) 
//		{
//			PixelInput pi = span.m_v1 + colordiff * factor;
//
//			Color color = execPixelShader( pi, ltList );
//
//			setPixel(x, y, color);
//
//			factor += factorStep;
//		}
//	}
//
//	// ������ɫ��
//	Color LightmapRasterizer::execPixelShader( const PixelInput& input, const Scene::GameObjectList& ltList)
//	{
//		// ����Դ
//		const Color& mainColor = SceneManager::Instance()->getMainLightColor();
//		const Vector3& mainLDir = SceneManager::Instance()->getMainLightDir();
//		float ml = Math::Clamp( mainLDir.dot(input.m_normal), 0.f, 1.f);
//		Color result = mainColor*ml;
//
//		// ���Դ
//		for (Scene::GameObjectList::const_iterator it=ltList.begin(); it!=ltList.end(); ++it)
//		{
//			SceneLightObject* pLight = static_cast<SceneLightObject*>(*it);
//			const Vector3& pos = pLight->getPosition();
//			const Color& color = pLight->getColor();
//			float radius = pLight->getRadius();
//			float Brightness = pLight->getBrightness();
//			float falloff = pLight->getFalloff();
//
//			Vector3 dir = (pos - input.m_position);
//			float length = dir.len();
//			dir/=length;
//
//			float dif = Math::Clamp(dir.dot(input.m_normal), 0.1f, 1.0f);
//			float inner = radius*0.5f;
//			float rate = Math::Clamp((length-inner)/(inner*falloff), 0.0f, 1.0f);
//			float Attenuation =  Math::Clamp(1-rate*rate, 0.0f, 0.5f);
//			result += color*dif * Brightness * Attenuation;
//		}
//
//		// ������
//		result += SceneManager::Instance()->getAmbientColor();
//
//		// ����alphaֵ
//		result.a = 1.f;
//
//		return result;
//	}
//
//	void LightmapRasterizer::setPixel( uint x, uint y, const Color &color)
//	{
//		if(x >= m_width || y >= m_height)
//			return;
//
//		m_frameBuffer[y * m_width + x] = color;
//	}
//
//	// ��Ե��չ 
//	// �ο���http://wiki.polycount.com/EdgePadding
//	void LightmapRasterizer::edgePadding( int extendPixel)
//	{
//		Color*	out = m_frameBuffer.data();
//
//		// ��ʱ����
//		vector<Color>::type colors( m_width*m_height); 
//		LordAssert( colors.size()==m_frameBuffer.size());
//		memcpy( colors.data(), m_frameBuffer.data(), sizeof(Color)*m_width*m_height);
//
//		// ��Ե��չ����
//#pragma omp parallel for
//		for ( uint w=0; w<m_width; w++)
//		{
//			for ( uint h=0; h<m_height; h++)
//			{
//				// ��ȡ��ǰ������ɫ
//				IndexerHelper tIHelper( m_width, m_height, w, h);
//				Color&		  curPixel    = out[tIHelper.getRelativeIdx(0, 0)];
//				float		  tTotalPer   = Math::EPSILON;
//				Color		  tTotalColor = Color::BLACK;
//				int			  curLen	  = 0xFFFFF;
//				if( curPixel.a == 0.f)
//				{
//					// ��Ѱ��Χ���ص�,����¼��������ɫֵ
//					for ( int ew=-extendPixel; ew<=extendPixel; ew++)
//					{
//						for ( int eh=-extendPixel; eh<=extendPixel; eh++)
//						{
//							int sIdx = tIHelper.getRelativeIdx( ew, eh);								
//							if( tIHelper.isValidIdx( ew, eh) && colors[sIdx].a!=0.f)
//							{
//								int sqrLen = ew*ew+eh*eh;
//								if( curLen > sqrLen)
//								{
//									curLen = sqrLen;
//									tTotalPer	= 1.f;
//									tTotalColor = colors[sIdx];
//								}
//								else if( curLen==sqrLen)
//								{
//									tTotalPer	+= 1.f;
//									tTotalColor += colors[sIdx];
//								}
//							}
//						}
//					}
//
//					// �޸ĵ�ǰ��Ӱ�����ɫֵ
//					curPixel   = tTotalColor/tTotalPer;
//					curPixel.a = 1.f;
//				}
//			}
//		}
//	}
//
//	// ģ������
//	void LightmapRasterizer::gaussianBlur( float radius/*=2.f*/)
//	{
//		Color*	out = m_frameBuffer.data();
//
//		vector<Color>::type colors( m_width * m_height);
//		LordAssert( colors.size()==m_frameBuffer.size());
//		memcpy( colors.data(), m_frameBuffer.data(), sizeof(Color)*m_width*m_height);
//
//		GaussianHelper tGaussianHelper( radius);
//
//		// ִ��ģ�ʹ���
//#pragma omp parallel for
//		for ( uint x=0; x<m_width; x++)
//		{
//			for ( uint y=0; y<m_height; y++)
//			{
//				float		  tTotalPer  = Math::EPSILON;
//				Color		  tTotalColor= Color::BLACK;
//				int			  halfDim	 = tGaussianHelper.getHalfDimension();
//				IndexerHelper tIHelper( m_width, m_height, x, y);
//				Color&		  curPixel	 = out[tIHelper.getRelativeIdx( 0, 0)];
//
//				for ( int dx=-halfDim; dx<=halfDim; dx++)
//				{
//					for ( int dy=-halfDim; dy<=halfDim; dy++)
//					{
//						int curIdx = tIHelper.getRelativeIdx( dx, dy);
//						if( tIHelper.isValidIdx(dx, dy))
//						{
//							float dsb   = tGaussianHelper.getDistribution( dx, dy);
//							tTotalPer  += dsb;
//							tTotalColor+= colors[curIdx] * dsb;
//						}
//					}
//				}
//
//				curPixel   = tTotalColor/tTotalPer;
//				curPixel.a = 1.f;
//			}
//		}
//	}
//}
