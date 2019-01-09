#include "Core/Graphics/LoadTool.h"

namespace Ares
{
	namespace Cg
	{
		// ���캯��
		Heap::Heap()
		{
			m_data		 = NULL;
			m_size		 = 0;
			m_bufferSize = 0;
		}

		// ��������
		Heap::~Heap()
		{
			SAFE_DELETE_ARRAY( m_data);
		}
	}
}