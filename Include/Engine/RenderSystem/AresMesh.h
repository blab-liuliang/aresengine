#pragma once

#include <Core/AresCore.h>
#include <Physics/Shapes.h>

using namespace std;

namespace Ares
{
	//---------------------------------------
	// Mesh 2010-09-21   ����
	//---------------------------------------
	class Mesh
	{	
	public:
		// VertexStreamFlag
		enum VertexStreamFlag
		{
			VSF_Position		= 1<<0,		// POSITION0	λ��
			VSF_DiffuseUV		= 1<<1,		// TEXCOORD0	��������ͼuv
			VSF_LightmapUV		= 1<<2,		// TEXCOORD1	����ͼuv
			VSF_Normal			= 1<<3,		// NORMAL0		����
			VSF_TangentBinormal	= 1<<4,		// TANGENT0		����	 BINORMAL0	����		
			VSF_Color			= 1<<5,		// COLOR0		����ɫ
			VSF_BoneInfulence	= 1<<6,		// BLENDWEIGHT0	����Ȩ�� BLENDINDICES0��������
			VSF_Total			= 7,	
		};
		typedef map<VertexStreamFlag, GraphicBufferPtr> VertexBufferMap;

		// BoneInfluence :vertex bone weights
		struct BoneInfluence
		{		
			Vector4    m_weights;
			Vector4    m_indexs;

			// ���л�
			template <typename Archive> void serialize( Archive& ar, const unsigned int version)
			{
				ar & m_weights & m_indexs;
			}
		};

		// IDCard
		struct IDCard
		{
			string			m_name;				// ����
			float			m_lightmapWidth;	// ����ͼ��
			float			m_lightmapHeight;	// ����ͼ��
			Rect3			m_boundingBox;		// ��Χ��

			vector<Vector3>	m_positions;		// λ������
			vector<Vector3>	m_normals;			// ��������
			vector<DWORD>	m_colors;			// ��ɫ����
			vector<Vector2> m_uvsDiffuse;		// ��������������
			vector<Vector2> m_uvsLightmap;		// ����ͼ��������
			vector<int>		m_boneIdxs;			// ��������
			vector<BoneInfluence>m_boneInfluence;// ��������Ȩ��
			vector<Int3>	m_faces;			// ������

			// Constructor
			IDCard()
				: m_lightmapWidth( 0)
				, m_lightmapHeight( 0)
			{}

			// ����Mesh
			void ReBuildMesh( Mesh& mesh);

			// ���л�
			template <typename Archive> void serialize( Archive& ar, const unsigned int version)
			{
				ar & m_name;
				ar & m_lightmapWidth;
				ar & m_lightmapHeight;
				ar & m_boundingBox;

				ar & m_positions;
				ar & m_normals;
				ar & m_colors;
				ar & m_uvsDiffuse;
				ar & m_uvsLightmap;
				ar & m_boneIdxs;
				ar & m_boneInfluence;
				ar & m_faces;
			}
		};
		typedef s_ptr<IDCard> IDCardPtr;
		friend  struct IDCard;

	public:
		Mesh(); 

		// ����RenderLayout flyweight
		RenderLayoutPtr BuildRenderLayout( UINT vertexDataFlag);

		// ��ȡ���㻺��
		GraphicBufferPtr GetVertexGraphicsBuffer( VertexStreamFlag flag);

		// ��ȡ��������
		GraphicBufferPtr GetIndexGraphicsBuffer( int& startIndex, int& primitiveCount);

		// ��ȡ��Χ��
		const Rect3& GetBoundingBox() const { return m_idcard->m_boundingBox; }

		// ��ȡ��������
		const vector<int>& GetBoneIdxs() { return m_idcard->m_boneIdxs; }

		// ��ȡ��������
		virtual size_t GetVertexNum() { return m_idcard->m_positions.size(); }

		// ��ȡ����������
		virtual size_t GetTriNum() { return m_idcard->m_faces.size(); }

		// ��ȡIDCard
		IDCardPtr& GetIDCard() { return m_idcard; }

		// ӳ��VertexElementType
		static VertexElementType Mapping( VertexStreamFlag vertexStreamFlag);

	private:
		IDCardPtr					m_idcard;				// ��ʶ��Ϣ
		VertexBufferMap				m_vertexBuffers;		// ����Buffer
		GraphicBufferPtr			m_indexBuffer;			// ����Buffer
	};
	typedef s_ptr<Mesh> MeshPtr;
}