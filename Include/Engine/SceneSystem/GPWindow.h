#pragma once

#include "GPIndex.h"
#include "GPWorld.h"

namespace Ares
{
	//-----------------------------------------
	// GPWindow 2011-08-18  ����
	// Description:
	//	   This class is the navigator of 
	// the GP, It uses the GPIndex to navigate
	// through the GPWorld, this class also 
	// tells to the gpworld which GPTiles must
	// be loaded and which of them must be
	// unloaded
	//------------------------------------------
	class CGPWindow
	{
		typedef map<CGPIndex, CGPTile*> GPTileMap;
	public:
		// ���캯��
		CGPWindow();

		// ��������
		virtual ~CGPWindow();

	public:
		// ��ʼ��
		virtual void Init( const CGPIndex& index);

		// ����GPWorld
		void SetWorld( CGPWorld* pWorld) { m_world = pWorld; }

		// ����λ��
		virtual void UpdatePosition( float x, float y, bool checkMovement=true);

		// ���°뾶
		virtual void UpdateRadius( float radius);

	public:
		// ��ȡGPWorld
		CGPWorld* GetWorld() { return m_world; }

		// ��ȡX
		float GetX() { return m_x; }

		// ��ȡY
		float GetY() { return m_y; }

		// ��ȡ�뾶
		float GetRadius() { return m_radius; }

	protected:
		// ����tilesmap
		void UpdateTilesMap();

	protected:
		CGPWorld*   m_world;		// GP����
		GPTileMap   m_tilesMap;		// ������tile

		float		m_x, m_y;		// ���ĵ�
		float		m_radius;		// �뾶

		CGPIndex	m_centerIdx;	// ���Ŀ�
	};
}