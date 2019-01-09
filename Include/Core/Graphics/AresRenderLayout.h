#pragma once

#include <vector>
#include "AresElementFormat.h"
#include "AresGraphicsBuffer.h"
#include "AresRenderAPITypedefs.h"

using namespace std;

namespace Ares
{
	enum VertexElementUsage
	{
		VEU_Position = 0,
		VEU_Normal,
		VEU_Color,
		VEU_BlendWeight,
		VEU_BlendIndex,
		VEU_TextureCoord,
		VEU_Tangent,
		VEU_Binormal
	};

	//-------------------------------------
	// �����ʽ 2012-4-1(���˽�) ����
	//-------------------------------------
	struct VertexElement
	{
		ElementFormat		m_format;
		VertexElementUsage	m_usage;
		BYTE				m_usageIdx;		// ����

		// ���캯��
		VertexElement() {}

		// ���캯��
		VertexElement( VertexElementUsage usage, BYTE usageIdx, ElementFormat format)
			: m_usage( usage), m_usageIdx( usageIdx), m_format( format)
		{}

		// ��С(Bytes)
		BYTE GetSize() const
		{
			return NumFormatBytes( m_format);
		}

		// ��������� "=="
		friend bool operator == ( const VertexElement& lve, const VertexElement& rve)
		{
			return std::memcmp( &lve, &rve, sizeof(VertexElement))==0;
		}		   
	};
	typedef vector<VertexElement> VertexElementType;

	//-------------------------------------
	// ��Ⱦ���� 2012-3-31 ����
	//-------------------------------------
	class CORE_EXPORT RenderLayout
	{
	public:
		// ��������
		enum TopologyType
		{
			TT_PointList,
			TT_LineList,
			TT_LineStrip,
			TT_TriangleList,
			TT_TriangleStrip,
			TT_LineListAdj,
			TT_LineStripAdj,
			TT_TriangleListAdj,
			TT_TriangleStripAdj,
			TT_1_CtrlPtPatchList,
			TT_2_CtrlPtPatchList,
			TT_3_CtrlPtPatchList,
			TT_4_CtrlPtPatchList,
			TT_5_CtrlPtPatchList,
			TT_6_CtrlPtPatchList,
			TT_7_CtrlPtPatchList,
			TT_8_CtrlPtPatchList,
			TT_9_CtrlPtPatchList,
			TT_10_CtrlPtPatchList,
			TT_11_CtrlPtPatchList,
			TT_12_CtrlPtPatchList,
			TT_13_CtrlPtPatchList,
			TT_14_CtrlPtPatchList,
			TT_15_CtrlPtPatchList,
			TT_16_CtrlPtPatchList,
			TT_17_CtrlPtPatchList,
			TT_18_CtrlPtPatchList,
			TT_19_CtrlPtPatchList,
			TT_20_CtrlPtPatchList,
			TT_21_CtrlPtPatchList,
			TT_22_CtrlPtPatchList,
			TT_23_CtrlPtPatchList,
			TT_24_CtrlPtPatchList,
			TT_25_CtrlPtPatchList,
			TT_26_CtrlPtPatchList,
			TT_27_CtrlPtPatchList,
			TT_28_CtrlPtPatchList,
			TT_29_CtrlPtPatchList,
			TT_30_CtrlPtPatchList,
			TT_31_CtrlPtPatchList,
			TT_32_CtrlPtPatchList
		};

		enum StreamType
		{
			ST_Geometry,
			ST_Instance,
		};

		// ������
		struct StreamUnit
		{
			UINT				m_stride;		// ���С
			UINT				m_frequency;	// Ƶ��
			StreamType			m_type;			// ʵ������
			VertexElementType	m_elementType;	// �����ʽ(�����ʽ)
			GraphicBufferPtr	m_stream;		// ��������

			// �Ƿ񶥵��ʽ��ͬ
			bool IsElementTypeEqueal( const VertexElementType& type);
		};

	public:
		// ���캯��
		RenderLayout();

		// ��������
		virtual ~RenderLayout();

		// ��ȡ��������
		TopologyType GetTopologyType() const { return m_topologyType; }

		// ������������
		virtual void SetTopologyType( TopologyType type) { m_topologyType = type; }

		// ��������
		virtual void BindIndexStream( const GraphicBufferPtr& IndexStream, ElementFormat format);

		// �󶨶�����
		virtual void BindVertexStream( const GraphicBufferPtr& vertexStream, const VertexElementType& vertexElements, StreamType stype=ST_Geometry, UINT frequency=1);

	public:
		// ��ȡ��������
		UINT GetNumVertices() const;

		// ��ȡ����������
		UINT GetNumVertexStreams() const { return static_cast<UINT>(m_vertexStreams.size()); }

		// ��ȡ������
		const GraphicBufferPtr GetVertexStream( const VertexElementType& elementType);

		// ��ȡ������
		const GraphicBufferPtr& GetVertexStream( UINT index) { return m_vertexStreams[index].m_stream; }

		// ��ȡ��������ʽ
		const VertexElementType& GetVertexStreamFormat( UINT index) const { return m_vertexStreams[index].m_elementType; }

		// ��ȡ����Stride
		UINT GetVertexStreamStride( UINT index) const { return m_vertexStreams[index].m_stride; }

		// �Ƿ�ʹ������
		bool IsUseIndices() const { return GetNumIndices()!=0; }

		// ��ȡ��������
		UINT GetNumIndices() const;

		// ��ȡ����
		const GraphicBufferPtr GetIndicesStream() { return m_indexStream; }

		// ������������
		void SetNumIndices( UINT numIndices) { m_forceNumIndices = numIndices; }

		// ��ȡ��ʼ����λ��
		UINT GetStartIndexLocation() const { return m_startIndexLocation; }

		// ���ÿ�ʼ����λ��
		void SetStartIndexLocation( UINT startIndexLocation) { m_startIndexLocation = startIndexLocation; }

		// ��ȡ��������λ��
		UINT GetStartVertexLocation() const { return m_startVertexLocation; }

	protected:
		TopologyType		m_topologyType;		// ��������

		vector<StreamUnit>	m_vertexStreams;	// ������
		StreamUnit			m_instanceStream;	// ʵ������

		GraphicBufferPtr	m_indexStream;		// ������
		ElementFormat		m_indexFormat;		// ������ʽ(UINT16 or UINT32)

		UINT				m_forceNumVertices;	// �ⲿ����
		UINT				m_forceNumIndices;	// �ⲿ����
		UINT				m_forceNumInstances;

		UINT				m_startVertexLocation;
		UINT				m_startIndexLocation;
		UINT				m_baseVertexLocation;
		UINT				m_startInstanceLocation;
	};
}