#pragma once

#include "Core/AresMath.h"

namespace Ares
{
	namespace Cg
	{
		//-----------------------------------------
		// Heap 2012-4-6   ����
		// Assist adding data to a block of memory
		//-----------------------------------------
		class Heap
		{
		public:
			// ���캯��
			Heap();

			// ��������
			~Heap();

		protected:
			UINT		m_size;
			UINT		m_bufferSize;
			BYTE*		m_data;
		};
	}
}