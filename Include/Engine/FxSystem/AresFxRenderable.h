#pragma once

#include <Core/Graphics/AresTexture.h>
#include "Engine/RenderSystem/AresRenderable.h"
#include <Core/AresSerialization.h>

namespace Ares
{
	//---------------------------------
	// FxParticleRender 2013-1-23 ����
	//---------------------------------
	class FxRenderable : public Renderable
	{
	public:
		// �����ʽ
		struct VertexFormat
		{
			float3   m_position;		// ����λ��
			ColorRGB m_color;			// ����ɫ
			float2   m_texcoord;		// ��ͼ����
		};

	public:
		FxRenderable();

		// ������Ⱦ����
		void UpdateBuffer( RenderLayout::TopologyType topologyType,const VertexFormat* vertices, int vertexSizeInByte, WORD* indices, int indicesSizeInByte);

		// ����Ϊ�����
		void SetBillBoard( bool isBillBoard) { m_isBillBoard=isBillBoard; }

		// ����Ϊ�ռ�Ť��
		void SetRenderQueue( BITFIELD renderQueue);

		// ��������
		void SetTexture( const char* texturePath);

		// ��ȡ��ǰ����
		const char* GetTexture() { return m_texture.c_str(); }

		// �Ƿ�Ϊ�����
		bool IsBillBoard() const { return m_isBillBoard; }

		// ����
		void FrameMove( float elpasedTime,  FxEntity* fxEntity, FxObject* fxObject);

		// ���л�
		BOOST_SERIALIZATION_SPLIT_MEMBER()
		template< typename Archive> void save( Archive& ar, const unsigned int version) const
		{
			BITFIELD renderQueue = m_material->GetRenderQueue();

			ar & m_texture;
			ar & m_isBillBoard;
			ar & renderQueue;
		}
		template< typename Archive> void load( Archive& ar, const unsigned int version)
		{
			string   texture;
			BITFIELD renderQueue;

			ar & texture;
			ar & m_isBillBoard;
			ar & renderQueue;

			SetTexture( texture.c_str());
			SetRenderQueue( renderQueue);
		}

	private:
		VertexElementType	m_elementType;			// ����

		string				m_texture;				// ����·��
		ShaderParamPtr		m_spabWVP;				// �������

		bool				m_isBillBoard;			// �Ƿ�Ϊ�����
	};
	typedef s_ptr<FxRenderable>	FxRenderablePtr;
	typedef FxRenderable::VertexFormat FxVertexFormat;
}