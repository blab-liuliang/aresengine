#pragma once

#include <Engine/RenderSystem/AresRenderable.h>

namespace Ares
{
	//------------------------------------
	// RenderLightmapUV 2012-7-10 ����
	//------------------------------------
	class LightmapUVRender : public Renderable
	{
	public:
		// ���캯��
		LightmapUVRender();

		// ��������
		~LightmapUVRender();

		// ������ʾ����
		void Set( RenderLayout::TopologyType topologyType, const void* positions, int vertexSizeInByte, const void* indices, int indicesSizeInByte, ElementFormat indiceFormat=EF_R16UI);
	};
}