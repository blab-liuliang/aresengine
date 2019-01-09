#pragma once

#include <vector>
#include <string>
#include "LoadTool.h"
#include "Core/AresPlatform.h"

using namespace std;

namespace Ares
{
	//----------------------------------
	// EffectLoad 2012-4-5 ����
	//----------------------------------
	class CgEffectLoader
	{
	public:
		// ���캯��
		CgEffectLoader( const char* fileName);

		// ���캯��
		CgEffectLoader( const void* effectBuffer, size_t size);

		// ��������
		~CgEffectLoader();

		// ����
		bool Parser();

	private:
		vector<string>		m_errors;			// �����뾯��	

		BYTE*				m_data;				// ����������
		UINT				m_dataSize;			// size of data buffer in bytes

		Cg::Heap*		m_reflection;		// Reflection object

	};
}