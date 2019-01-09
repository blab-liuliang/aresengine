#pragma once

#include <boost/tuple/tuple.hpp>
#include "Engine/RenderSystem/AresRenderEntity.h"

using namespace boost;

namespace Ares
{
	//------------------------------------------------------------
	// �������� 2010-03-28 17:54 -- δ֪   ����
	//------------------------------------------------------------
	class Terrain;
	class TerrainTile
	{
	public:
		// �������ݱ��
		enum VertexStreamFlag
		{
			VSF_Position		= 0,		// POSITION0	λ��
			VSF_Normal,						// NORMAL0	    TEXCOORD0
			VSF_Blend,
			VSF_LightmapUV,
			VSF_Total,	
		};
		typedef map<VertexStreamFlag, GraphicBufferPtr> VertexBufferMap;

	public:
		// ���캯��
		TerrainTile( Terrain* terrain);

		// ��������
		~TerrainTile();

		// ���Renderable
		void AddRenderable( const Renderable& renderable);

		// ��ȡRenderable
		Renderable* GetRenderable();

		// ��ȡ��Χ��
		Rect3 GetLocalBounds() { return m_localBounds; }

		// ����ʵ���Χ��
		void  SetLocalBounds( const Rect3& rect) { m_localBounds = rect; }

		// ���ñ��
		void SetDirty( bool isDirty) { m_dirtyFlag = isDirty; }

		// �ύ����Ⱦ����( ʹ����Ч ��������)
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr);

	public:
		// ӳ��VertexElementType
		static VertexElementType Mapping( VertexStreamFlag vertexStreamFlag);

		// ��ȡ���㻺��
		GraphicBufferPtr GetVertexGraphicsBuffer( VertexStreamFlag flag);

		// ��ȡ��������
		GraphicBufferPtr GetIndexGraphicsBuffer() { return m_indexBuffer; }

		// ���ö��㻺��
		void SetVertexGraphicBuffer( VertexStreamFlag flag, GraphicBufferPtr& buffer);

		// ������������
		void SetIndexGraphicsBuffer( GraphicBufferPtr& buffer) { m_indexBuffer = buffer; }

	public:
		// �󶨲����Զ�����
		void AutoBindParam();

	public:
		bool				m_dirtyFlag;			// ����(��Ҫ����)
		WORD				m_xIndex;				// ��x����ĵڼ�����
		WORD				m_yIndex;				// ��y����ĵڼ����� 
		WORD				m_xVerts;				// X�᷽�򶥵���(������)
		WORD				m_yVerts;				// Y�᷽�򶥵���(������)
		WORD				m_xHBase;				// �ڵ�ͼ��X��ڼ�������
		WORD				m_yHBase;				// �ڵ�ͼ��Y��ڼ�������

		vector<Renderable>	m_renderables;			// ����Ⱦ�Ｏ

		VertexBufferMap		m_vertexBuffers;		// ����Buffer
		GraphicBufferPtr	m_indexBuffer;			// ����Buffer

		Rect3				m_localBounds;			// ���ذ�Χ��
		Terrain*			m_terrain;				// ��������
	};
	typedef s_ptr<TerrainTile> TerrainTilePtr;
}