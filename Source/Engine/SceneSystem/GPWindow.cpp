#include <Engine/SceneSystem/GPWindow.h>

namespace Ares
{
	// ���캯��
	CGPWindow::CGPWindow()
		: m_world( NULL),
		  m_x( 0.f),
		  m_y( 0.f),
		  m_radius( 0.f)
	{
	}

	// ��������
	CGPWindow::~CGPWindow()
	{

	}

	// ��ʼ��
	void CGPWindow::Init( const CGPIndex& index)
	{
		m_centerIdx = index;

		m_x = (float)index.GetX();
		m_y = (float)index.GetY();

		UpdateRadius( m_radius);
	}

	// ����λ��
	void CGPWindow::UpdatePosition( float x, float y, bool checkMovement/*=true*/)
	{
		if( m_world)
		{
			m_x = x;
			m_y = y;

			// ��ȡ��ǰ����index
			CGPIndex newIdx = m_centerIdx.GetIndex( (int)m_x, (int)m_y);
			if( checkMovement && newIdx == m_centerIdx)
				return;

			m_centerIdx = newIdx;

			// ����TilesMap
			GPTileMap tPre = m_tilesMap;
			UpdateTilesMap();

			// unload unneeded tiles
			for ( GPTileMap::iterator it=tPre.begin(); it!=tPre.end(); it++)
			{
				CGPTile* pTile = it->second;
				if( pTile)
				{
					// ����ʹ�õ�tiles
					if( m_tilesMap.find( pTile->GetIndex()) == m_tilesMap.end())
						m_world->UnloadTile( pTile);
				}
			}

			// ���Ҫ���صĿ�
			for( GPTileMap::iterator it=m_tilesMap.begin(); it!=m_tilesMap.end(); it++)
			{
				CGPTile* pTile = it->second;
				if( pTile)
				{
					m_world->LoadTile( pTile);
				}
			}

			m_world->Start( 10);
		}
	}

	// ���°뾶
	void CGPWindow::UpdateRadius( float radius)
	{
		if( radius == m_radius)
			return;

		if( radius < 0)
			m_radius = 0;

		m_radius = radius;

		// ����
		UpdatePosition( m_x, m_y, false);
	}

	// ����tilesmap
	void CGPWindow::UpdateTilesMap()
	{
		if( m_world)
		{
			m_tilesMap.clear();

			float tmaxx = m_x + m_radius;
			float tmaxy = m_y + m_radius;

			if( tmaxx < 0.f || tmaxy < 0.f)
				return;

			// 0Ϊ�½�
			float tminx = max( 0.f, m_x - m_radius);
			float tminy = max( 0.f, m_y - m_radius);

			int minx = (int)( tminx / m_centerIdx.GetWidth());
			int miny = (int)( tminy / m_centerIdx.GetHeight());

			int maxx = (int)( tmaxx / m_centerIdx.GetWidth());
			int maxy = (int)( tmaxy / m_centerIdx.GetHeight());

			// �����
			for ( int i=minx; i<=maxx; i++)
			{
				for( int j=miny; j<=maxy; j++)
				{
					CGPIndex tIndex( m_centerIdx);
					tIndex.SetX( i);
					tIndex.SetY( j);

					CGPTile* pTile = m_world->GetTile( tIndex);
					if( pTile)
					{
						//pTile->AddWindow( this);
						m_tilesMap[tIndex] = pTile;
					}
				}
			}

			// ȫ�ֿ�
			{
				CGPTile* globalTile = m_world->GetTile( CGPIndex::Global);
				if( globalTile)
					m_tilesMap[CGPIndex::Global] = globalTile;
			}
		}
	}
}