#pragma once

#include <Engine/SceneSystem/AresEntity.h>
#include <Engine/RenderSystem/ZRenderable.h>
#include <Engine/RenderSystem/AresModel.h>
#include <Engine/RenderSystem/AresTerrain.h>

namespace Ares
{
	//-----------------------------------
	// д��ȹ����� 2013-2-21 ����
	//-----------------------------------
	class ZWriteMgr
	{
		typedef map<Entity*, map<size_t, ZRenderable*>> MultimapZR;
	public:
		// д���
		void Write( vector<Entity*>& entitys, const Matrix44& viewProj);

	private:
		// ˢ��Renderable
		void RefreshRenderableZWrite( vector<Entity*>& entitys);

		// ˢ��ģ��Renderable
		void RefreshRenderableZWrite( Model* model);

		// ���µ���ZWriteRenderable
		void RefreshRenderableZWrite( Terrain* terrain);

		// ִ��д���
		void ExecZWrite( vector<Entity*>& entitys, const Matrix44& viewProj);

	private:
		MultimapZR		m_zRenderables;		// ZRenderables
	};
}