#pragma once

namespace Ares
{
	//-----------------------------------------
	// ˮƬ�༭�ṹ�� 2010-09-12  ����
	//-----------------------------------------
	struct SWaterEditorData
	{
		enum EditorType
		{
			EM_ET_HEIGHT,		// �Ը߶�Ϊ����
			EM_ET_DEPTH,		// �����Ϊ����
		};

		enum EditorSize
		{
			EM_SIZE1 = 1,
			EM_SIZE2 = 2,
			EM_SIZE3 = 3,
			EM_SIZE4 = 5,
			EM_SIZE5 = 8,
		};

		enum  EditorShape
		{
			EM_TYPE_CIRCULAR,	// Բ��	
			EM_TYPE_SQUARE,		// ������
		};

		EditorType  type;
		EditorSize  size;
		EditorShape shape;
		float       height;		// ˮ��			
		float       depth;		// ˮ��

		SWaterEditorData()
		{
			type = EM_ET_HEIGHT;
			size = EM_SIZE2;
			shape= EM_TYPE_CIRCULAR;
			height = 0.0f;
			depth  = 0.0f;
		}
	};
}