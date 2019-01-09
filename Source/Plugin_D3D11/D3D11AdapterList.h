#pragma once

#include <vector>
#include <d3d11.h>
#include "D3D11Adapter.h"

using namespace std;

namespace Ares
{
	//-----------------------------------------
	// D3D11�������б� 2012-02-10 ����
	//-----------------------------------------
	class D3D11AdapterList
	{
	public:
		// ���캯��
		D3D11AdapterList();

		// ����IDXGIFactory1ö�����е�������
		void Enumerate( IDXGIFactory1* dxgiFactory1);

		// ����������ȡ������
		D3D11Adapter* GetAdapter( UINT idx) const;

		// ��ȡAdapter����
		UINT GetAdapterNum() const { return m_adapters.size(); }

		// ��ȡ��ǰAdapter����
		UINT GetCurrentAdapterIdx() const { return m_curAdapterIdx; }

		// ���õ�ǰ������
		void SetCurrentAdapterIdx( UINT adapterIdx) { m_curAdapterIdx = adapterIdx; }

	private:
		UINT					m_curAdapterIdx;// ��ǰ����������
		vector<D3D11Adapter*>	m_adapters;		// �������б�
	};
}