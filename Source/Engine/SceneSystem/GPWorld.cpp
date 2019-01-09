#include <Engine/SceneSystem/GPWorld.h>

namespace Ares
{
	// ���캯��
	CGPWorld::CGPWorld()
		: CThreadLoopObject()
		, m_unloadEnable(true)
	{
		ENTER_CRITICAL_SECTION( tHoder, m_critication);

		m_tilesMap.clear();
		m_loadUnloadTileList.clear();
		m_loadingProgress = 0.f;

		//SetPriority(THREAD_PRIORITY_BELOW_NORMAL);

		Start( 20);
	}

	// ��������
	CGPWorld::~CGPWorld()
	{
		ENTER_CRITICAL_SECTION( tHoder, m_critication);

		Finish();

		Clean();
	}

	// ��ȡTile
	CGPTile* CGPWorld::GetTile( const CGPIndex& index)
	{
		ENTER_CRITICAL_SECTION( tHoder, m_critication);

		CGPTile* pTile = 0;

		if( IsValidIndex( index))
		{
			GPTileMap::const_iterator it = m_tilesMap.find( index);
			if( it == m_tilesMap.end())
			{
				pTile = BuildTile( index);
				if( pTile)
				{
					pTile->SetIndex( index);
					pTile->SetWorld( this);

					m_tilesMap[index] = pTile;
				}
			}
			else
			{
				pTile = it->second;
			}
		}

		return pTile;
	}

	// �������� 
	void CGPWorld::LoadTile( CGPTile* pTile)
	{
		ENTER_CRITICAL_SECTION( tHoder, m_critication);

		if( pTile)
		{
			bool found = false;

			deque<SGPTileListData>::iterator it=m_loadUnloadTileList.begin();
			for( ; it!=m_loadUnloadTileList.end(); it++)
			{
				if( pTile == it->m_tile)
				{
					found = true;
					break;
				}
			}

			// ��Tile���ڼ���ж���б�
			if( found)
			{
				if( it->m_state == EM_FOR_LOAD)
				{
					if( it->m_tile->GetState() == CGPTile::EM_LOADED)
						m_loadUnloadTileList.erase( it);
				}
				else if( it->m_state == EM_FOR_UNLOAD)
				{
					it->m_state = EM_FOR_LOAD;
				}
			}
			else
			{
				SGPTileListData tileListData;
				tileListData.m_state = EM_FOR_LOAD;
				tileListData.m_tile  = pTile;

				//if( !m_loadUnloadTileList.size())
				//	Start( 30);

				m_loadUnloadTileList.push_back( tileListData);
			}
		}
	}

	// ж������
	void CGPWorld::UnloadTile( CGPTile* pTile)
	{
		ENTER_CRITICAL_SECTION( tHoder, m_critication);

		if( pTile)
		{
			bool found = false;

			deque<SGPTileListData>::iterator it=m_loadUnloadTileList.begin();
			for( ; it!=m_loadUnloadTileList.end(); it++)
			{
				if( pTile == it->m_tile)
				{
					found = true;
					break;
				}
			}

			// ��tile����װ��ж���б�
			if( found)
			{
				if( it->m_state == EM_FOR_LOAD)
				{
					it->m_state = EM_FOR_UNLOAD;
				}
				else if( it->m_state == EM_FOR_UNLOAD)
				{
					if( it->m_tile->GetState() == CGPTile::EM_UNLOADED)
						m_loadUnloadTileList.erase( it);
				}
			}
			else
			{
				SGPTileListData tileListData;
				tileListData.m_state = EM_FOR_UNLOAD;
				tileListData.m_tile  = pTile;

				//if( !m_loadUnloadTileList.size())
				//	Start( 30);

				m_loadUnloadTileList.push_back( tileListData);
			}
		}
	}

	// ��ʼ(�����߳�,�ָ��߳�)
	void CGPWorld::Start(  DWORD hz)
	{
		ENTER_CRITICAL_SECTION( tHoder, m_critication);

		if( m_loadUnloadTileList.size())
			CThreadLoopObject::Start( hz);
	}

	// ����
	void CGPWorld::Loop()
	{
		size_t needLoad = m_loadUnloadTileList.size();
		while( m_loadUnloadTileList.size())
		{
			// �Ƴ�
			SGPTileListData tileListData;
			{
				ENTER_CRITICAL_SECTION( tHoder, m_critication);

				tileListData = (*m_loadUnloadTileList.begin());
				m_loadUnloadTileList.erase( m_loadUnloadTileList.begin());
			}

			if( tileListData.m_state == EM_FOR_LOAD)
			{
				tileListData.m_tile->DoLoad();
			}
			else if( tileListData.m_state == EM_FOR_UNLOAD && m_unloadEnable)
			{
				tileListData.m_tile->DoUnload();

				DestroyTile( tileListData.m_tile->GetIndex());
			}

			float process = 1.f - (float)m_loadUnloadTileList.size() / (float)needLoad;
			SetLoadingProgress( process);
		}

		// �������
		SetLoadingProgress( 1.f);

		Pause();
	}

	// ��ȡ��ǰ���ؽ���
	float CGPWorld::GetLoadingProgress()
	{
		ENTER_CRITICAL_SECTION( tHoder, m_critication);

		return m_loadingProgress;
	}

	// ���õ�ǰ���ؽ���
	void CGPWorld::SetLoadingProgress( float progress)
	{
		ENTER_CRITICAL_SECTION( tHoder, m_critication);

		m_loadingProgress = progress;
	}

	// ����Tile
	void  CGPWorld::DestroyTile( const CGPIndex& index)
	{
		CGPTile* pTile = NULL;
		{
			ENTER_CRITICAL_SECTION( tHoder, m_critication);

			GPTileMap::iterator it = m_tilesMap.find( index);
			if( it != m_tilesMap.end())
			{
				pTile = it->second;
				pTile->SetWorld( 0);

				for ( deque<SGPTileListData>::iterator itd=m_loadUnloadTileList.begin(); itd!=m_loadUnloadTileList.end(); itd++)
				{
					if( pTile == itd->m_tile)
					{
						m_loadUnloadTileList.erase( itd);
						break;
					}
				}

				m_tilesMap.erase( it);
			}
		}

		SAFE_DELETE( pTile);
	}

	// ��Ӧ�����������Ƿ����
	bool CGPWorld::IsValidIndex( const CGPIndex& index)
	{
		// to redefine if it is needed
		return true;
	}

	// ����Tile
	CGPTile* CGPWorld::BuildTile( const CGPIndex& index)
	{
		CGPTile* pTile = new_ CGPTile;
		
		return pTile;
	}

	// �����Դ
	void CGPWorld::Clean()
	{
		ENTER_CRITICAL_SECTION( tHolder, m_critication);

		m_loadUnloadTileList.clear();

		GPTileMap::iterator itEnd = m_tilesMap.end();
		for ( GPTileMap::iterator it = m_tilesMap.begin(); it!=itEnd; it++)
		{
			CGPTile* pTile = it->second;
			pTile->DoUnload();
			pTile->SetWorld( NULL);
			delete pTile;
			pTile = NULL;
		}

		m_tilesMap.clear();
	}
}