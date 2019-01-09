#pragma once

#include <d3d11.h>
#include <Core/Graphics/AresRenderLayout.h>
#include <Core/Graphics/AresElementFormat.h>
#include <Core/Graphics/AresRenderState.h>
#include <Core/Graphics/AresRenderLayout.h>
#include <Core/Graphics/AresTexture.h>
#include <Core/Graphics/AresFrameBuffer.h>

using namespace std;

namespace Ares
{
	//-----------------------------------
	// D3D11 ӳ�� 2012-3-8<��Ů��> ����
	//-----------------------------------
	class D3D11Mapping
	{
	public:
		// ӳ����ɫMask
		static BYTE MappingColorMask( BYTE mask);

		// ӳ�����Mask
		static UINT MappingDepthStencilClearMask( UINT mask);

		// ӳ����ģʽ
		static D3D11_BLEND Mapping( AlphaBlendFactor factor);

		// ӳ���Ϻ���
		static D3D11_BLEND_OP Mapping( BlendOperation bop);

		// ��������ӳ��
		static D3D11_MAP Mapping( TextureMapAccess tma, Texture::TextureType type, UINT accessHint, UINT numMipmaps);

		// ӳ�����ģʽ
		static D3D11_FILL_MODE Mapping( FillMode mode);

		// ӳ������FilterOperation
		static D3D11_FILTER Mapping( TextureFilterOp filter);

		// ӳ�����ģʽ
		static D3D11_CULL_MODE Mapping( CullMode mode);

		// ӳ��ģ�����
		static D3D11_STENCIL_OP Mapping( StencilOperation op);

		// ӳ����ȱȽϺ���
		static D3D11_COMPARISON_FUNC Mapping( CompareFunction func);

		// ӳ�����WriteMask
		static D3D11_DEPTH_WRITE_MASK Mapping( bool depthWriteMask);

		// ӳ�������ַѭ��ģʽ
		static D3D11_TEXTURE_ADDRESS_MODE Mapping( TextureAddressingMode mode);

		// ӳ���ʽ
		static DXGI_FORMAT MappingFormat( ElementFormat format);

		// ��ʽӳ��
		static ElementFormat MappingFormat( DXGI_FORMAT d3dformat);

		// ӳ����������
		static D3D11_PRIMITIVE_TOPOLOGY Mapping( RenderLayout::TopologyType type);

		// ӳ��InputElementDesc
		static void MappingInputElement( vector<D3D11_INPUT_ELEMENT_DESC>& oElements, size_t stream, const VertexElementType& vertexElementType, RenderLayout::StreamType type, UINT frequency);
	};
}