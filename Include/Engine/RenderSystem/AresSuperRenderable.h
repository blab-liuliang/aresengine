#ifndef ARES_SUPER_RENDERABLE_H
#define ARES_SUPER_RENDERABLE_H

#include "AresRenderable.h"
#include "SuperMaterial.h"
#include "AresRenderEntity.h"

namespace Ares
{
	//-------------------------------------------
	// SuperRenderable 2013-07-12 ����
	//-------------------------------------------
	class SuperRenderable : public Renderable
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

	public:
		SuperRenderable( RenderEntity* entity);
		virtual ~SuperRenderable();

		// ����RenderLayout
		void UpdateBuffer(RenderLayout::TopologyType topologyType, void* vertices, int vertexSizeInByte, const void* indices, int indicesSizeInByte);

		// ��ȡ������
		UINT GetVertexStreamFlag() { return m_superMaterial->GetVertexStreamFlag(); }

		// �󶨲��ʲ���
		void BindMaterialParameter();

	private:
		// ӳ��VertexElementType
		VertexElementType Mapping( UINT vertexDataFlag);

	public:
		RenderEntity*			m_entity;					// ����ʵ��				
		SuperMaterialPtr		m_superMaterial;			// ��������

		VertexElementType		m_elementType;				// �����ʽ
		GraphicBufferPtr		m_vertexBuffer;				// ������
		GraphicBufferPtr		m_indexBuffer;				// ������	
	};
	typedef s_ptr<SuperRenderable> SuperRenderablePtr;
}

#endif