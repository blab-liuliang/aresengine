#pragma once

namespace Ares
{
	//-----------------------------------------
	// ���α༭�ṹ�� 2010-07-24  ����
	//-----------------------------------------
	struct STerrainMeshEditorData
	{
		enum EditorType
		{
			EM_UP_HEAVAL,		// ¡��ر�
			EM_DEBASE,			// ���͵ر�
			EM_CALM1,           // �⻬��ƽ
			EM_CALM2,           // ǿ����ƽ
			EM_CRAGGEDNESS,		// ���͵ر�
		};

		enum TextureNum
		{
			EM_TEXTURE0 = 0,	// ����0	
			EM_TEXTURE1,		// ����1	
			EM_TEXTURE2,		// ����2	
			EM_TEXTURE3,		// ����3	
			EM_TEXTURE4,		// ����4	
			EM_TEXTURE5,		// ����5	
			EM_TEXTURE6,		// ����6	
			EM_TEXTURE7,		// ����7	
			EM_TEXTURETOTAL,	// ���������
		};

		enum  EditorShape
		{
			EM_TYPE_CIRCULAR,	// Բ��	
			EM_TYPE_SQUARE,		// ������
		};

		EditorType  type;
		TextureNum  activeTexture;
		int         size;
		EditorShape shape;
		float       height;			// ��ƽ�ر�ʱʹ��	

		STerrainMeshEditorData()
		{
			type = EM_UP_HEAVAL;
			activeTexture = EM_TEXTURE0;
			size = 1;
			shape= EM_TYPE_CIRCULAR;
			height = 0.0f;
		}
	};
}