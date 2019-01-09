#pragma once

#include <map>
#include <deque>
#include "GPTile.h"
#include <Core/AresCriticalSection.h>
#include <Core/AresThreadLoopObject.h>
#include <boost/signals2/signal.hpp>

using namespace std;
using namespace boost;
using namespace boost::signals2;

namespace Ares
{
	//---------------------------------------------------------
	// "World" of GP 2011-08-18 ����
	//  Description:
	//      The GPWorld  loads and unloads the GPTiles that the
	//  GPWindows needs. when a GPTile is unloaded and no other
	//  GPWindow needs it, the GPWorld automatically destroys it 
	//  int order to get a better performance and an optimal use
	//  of the system memory( and other resources)
	//---------------------------------------------------------
	class CGPWorld : public CThreadLoopObject
	{
	public:
		// ״̬
		enum SGRPTileAction
		{
			EM_FOR_LOAD,
			EM_FOR_UNLOAD
		};

		// GPTileListData
		struct SGPTileListData
		{
			SGRPTileAction	m_state;
			CGPTile*		m_tile;
		};

		typedef map<CGPIndex, CGPTile*> GPTileMap;

	public:
		// ���캯��
		CGPWorld();

		// ��������
		virtual ~CGPWorld();

	public:
		// ��ȡ��ǰ���ؽ���
		float GetLoadingProgress();

		// ���õ�ǰ���ؽ���
		void SetLoadingProgress( float progress);

		// ��ʼ(�����߳�,�ָ��߳�)
		virtual void Start( DWORD hz=0);

		// �����ź�
		signal<void(float)> Signal_LoadingProgress;

	protected:
		// ����
		virtual void Loop();

	public:
		// ��ȡTile
		CGPTile* GetTile( const CGPIndex& index);

	public:
		// �������� 
		void LoadTile( CGPTile* pTile);

		// ж������
		void UnloadTile( CGPTile* pTile);

	public:
		// ��Ӧ�����������Ƿ����
		virtual bool IsValidIndex( const CGPIndex& index);

		// ����ж�ر��
		void SetAutoUnload( bool unload) { m_unloadEnable=unload; }

	protected:
		// ����Tile
		virtual CGPTile* BuildTile( const CGPIndex& index);

		// ����Tile
		virtual void  DestroyTile( const CGPIndex& index);

	public:
		// �����Դ
		void Clean();

	protected:
		GPTileMap				m_tilesMap;				// �����е�ǰ����
		deque<SGPTileListData>	m_loadUnloadTileList;	// ����ж�ض���
		boost::recursive_mutex	m_critication;			// �ٽ���
		float					m_loadingProgress;		// ��Դ���ؽ���
		bool					m_unloadEnable;			// �Ƿ��ж��
	};
}