#pragma once

#include <map>
#include <vector>
#include "D3D11Typedefs.h"
#include "D3D11CgMethod.h"
#include "D3D11RenderMethod.h"
#include <Core/Graphics/AresRenderLayout.h>

using namespace std;

namespace Ares
{
	//--------------------------------------
	// D3D11RenderLayout 2012-4-12 ����
	//--------------------------------------
	class D3D11RenderLayout : public RenderLayout
	{
		typedef map<ID3D10Blob*, ID3D11InputLayoutPtr> InputLayoutMaps;

	public:
		// ���캯��
		D3D11RenderLayout();

		// ��������
		~D3D11RenderLayout();

		// ���ü���
		void Render( D3D11RenderLayout* preLayout, D3D11RenderMethod* method);

		// ��ȡ��������
		D3D11_PRIMITIVE_TOPOLOGY GetD3D11TopologyType() { return m_d3d11TopologyType; }

	private:
		// ������������
		virtual void SetTopologyType( TopologyType type);

		// ��ȡInputLayout
		const ID3D11InputLayoutPtr& GetInputLayout( ID3D10Blob* signature) const;

	private:
		D3D11_PRIMITIVE_TOPOLOGY			m_d3d11TopologyType;// D3D11��������

		vector<D3D11_INPUT_ELEMENT_DESC>	m_vertexElems;		// �����ʽ
		mutable InputLayoutMaps				m_inputLayouts;		// input layouts	
	};
}