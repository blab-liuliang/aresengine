//#ifndef _LIGHTMAPRASTERIZER_H_ 
//#define _LIGHTMAPRASTERIZER_H_
//
//#include <Core/AresMath.h>
//
//namespace LORD
//{ 
//	/**
//	 * ���ƹ�դ��,����ͼ�決ʹ��
//	 * �ο���http://joshbeam.com/articles/triangle_rasterization 
//	 */
//	class  LightmapRasterizer
//	{
//	public:
//		// �����ʽ(�������)
//		struct VertexInput
//		{
//			Vector3		m_position;		// λ��
//			Vector3		m_normal;		// ���㷨��
//			Vector2		m_uv;			// ������UV
//			Vector2		m_uniqueUV;		// ����ͼUV
//		};
//
//		// �����ʽ(���ؼ���)
//		struct PixelInput
//		{
//			Vector2	 m_uv;				// ��������
//			Vector3	 m_position;		// λ��
//			Vector3	 m_normal;			// ����
//
//			// ��������� "-"
//			PixelInput operator + ( const PixelInput& pi) const;
//
//			// ��������� "-"
//			PixelInput operator - ( const PixelInput& pi) const;
//
//			// ��������� "*"
//			PixelInput operator * ( float scale) const;
//		};
//
//		// ��
//		struct Edge
//		{
//			PixelInput m_v1;
//			PixelInput m_v2;	// λ�÷�������
//
//			Edge( const PixelInput& v1, const PixelInput& v2);
//
//			// ��������
//			float X1() const { return m_v1.m_uv.x; }
//			float X2() const { return m_v2.m_uv.x; }
//			float Y1() const { return m_v1.m_uv.y; }
//			float Y2() const { return m_v2.m_uv.y; }
//		};
//
//		// һ������
//		struct Span
//		{
//			PixelInput m_v1, m_v2;
//
//			Span(const PixelInput &v1, const PixelInput &v2);
//
//			// ��������
//			int X1() const { return static_cast<int>( m_v1.m_uv.x); }
//			int X2() const { return static_cast<int>( m_v2.m_uv.x); }
//		};
//
//	public:
//		LightmapRasterizer();
//		~LightmapRasterizer();
//
//		// ����֡������
//		void setFramebuffer( uint width, uint height);
//
//		// ����
//		void draw( vector<VertexInput>::type& vertices, vector<Word>::type& indices, const Scene::GameObjectList& ltList);
//
//		// ��ȡ��ɫֵ
//		const vector<Color>::type& getFrameBuffer() const { return m_frameBuffer; }
//
//	protected:
//		// ������ɫ��
//		virtual void execVertexShader( PixelInput& out, const VertexInput& input);
//
//		// ������ɫ��
//		virtual Color execPixelShader( const PixelInput& input, const Scene::GameObjectList& ltList);
//
//	private:
//		// ���֡����
//		void clear( const Color& color);
//
//		// ����������
//		void drawTriangle( const VertexInput& v0, const VertexInput& v1, const VertexInput& v2, const Scene::GameObjectList& ltList);
//
//		// ��������֮�������
//		void drawSpansBetweenEdges( const Edge& e1, const Edge& e2, const Scene::GameObjectList& ltList);
//
//		// ��������
//		void drawSpan(const Span &span, int y, const Scene::GameObjectList& ltList);
//
//		// ��������ֵ
//		void setPixel( uint x, uint y, const Color &color);
//
//		// ��Ե��չ 
//		void edgePadding( int extendPixel=4);
//
//		// ģ������
//		void gaussianBlur( float radius=4.f);
//
//	private:
//		uint				m_width;		// ��
//		uint				m_height;		// ��
//		vector<Color>::type	m_frameBuffer;	// ֡����
//
//		Matrix4				m_world;		// �������
//	};
//}
//
//#endif