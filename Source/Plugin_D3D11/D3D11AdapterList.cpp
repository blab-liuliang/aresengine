#include "D3D11AdapterList.h"

namespace Ares
{
	// ���캯��
	D3D11AdapterList::D3D11AdapterList()
		: m_curAdapterIdx( 0)
	{

	}

	// ����IDXGIFactory1ö�����е�������
	void D3D11AdapterList::Enumerate( IDXGIFactory1* dxgiFactory1)
	{
		// ö��ϵͳ�е�������
		IDXGIAdapter1* dxgiAdapter = NULL;
		for ( UINT i=0; dxgiFactory1->EnumAdapters1( i, &dxgiAdapter) != DXGI_ERROR_NOT_FOUND; ++i)
		{
			if( dxgiAdapter)
			{
				DXGI_ADAPTER_DESC1 adapterDesc;
				dxgiAdapter->GetDesc1( &adapterDesc);

				if( 0 == wcscmp( adapterDesc.Description, L"NVIDIA_PerfHUD"))
				{
					m_curAdapterIdx = i;
				}

				D3D11Adapter* adapter = new_ D3D11Adapter( i, dxgiAdapter);
				adapter->Enumerate();

				m_adapters.push_back( adapter);
			}
		}

		// ���û���ҵ����ݵ��豸���׳�����
		if( m_adapters.empty())
		{
			//THR();
		}
	}

	// ����������ȡ������
	D3D11Adapter* D3D11AdapterList::GetAdapter( UINT idx) const
	{
		A_ASSERT( idx < m_adapters.size());

		return m_adapters[idx];
	}
}