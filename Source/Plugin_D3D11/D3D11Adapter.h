#pragma once

#include <vector>
#include <d3d11.h>
#include <Core/AresPtr.h>
#include "D3D11VideoMode.h"
#include <boost/shared_ptr.hpp>

using namespace std;

namespace Ares
{
	//-------------------------------------------
	// D3D11������ 2012-02-10 ����
	// 1.���ڲ�ѯ�豸����
	//-------------------------------------------
	class D3D11Adapter
	{
	public:
		// ���캯��
		D3D11Adapter();

		// ���캯��
		D3D11Adapter( UINT idx, IDXGIAdapter1* adapter);

	public:
		// ö����ʾģʽ
		void Enumerate();

		// ��ȡ������Ϣ
		const wstring GetDescription() const;

		// ��ȡd3d11������
		IDXGIAdapter1* GetAdapter() { return m_adapter; }

	private:
		UINT					m_idx;			// ���ǵڼ���������
		IDXGIAdapter1*			m_adapter;		// ������
		DXGI_ADAPTER_DESC1		m_adapterDesc;	// ����������
		vector<D3D11VideoMode>	m_modes;		// �ֱ��ʵ�
	};
}