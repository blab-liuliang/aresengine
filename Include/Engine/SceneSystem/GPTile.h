#pragma once

#include "GPIndex.h"

namespace Ares
{
	//---------------------------------------
	// �����ռ��еĿ� 2011-08-18  ����
	//     Tile��Ӧһ�����,��λ�úʹ�С����
	// �����������
	//---------------------------------------
	class CGPWorld;
	class CGPTile
	{
	public:
		// ����״̬
		enum GPtileState
		{
			EM_LOADING,
			EM_UNLOADING,
			EM_LOADED,
			EM_UNLOADED,
		};

	public:
		// ���캯��
		CGPTile();

		// ��������
		virtual ~CGPTile();

	public:
		// ��ȡ״̬
		GPtileState GetState() { return m_state; }

		// ��ȡ����
		const CGPIndex& GetIndex() { return m_index; }

		// ��ȡ����
		CGPWorld* GetWorld(){ return m_world; }

	public:
		// ����״̬
		void SetState( GPtileState state) { m_state = state; }

		// ��������
		void SetIndex( const CGPIndex& index) { m_index = index; }

		// ��������
		void SetWorld( CGPWorld* pWorld) { m_world = pWorld; }

	public:
		// ִ�м���(״̬�л�)
		void DoLoad();

		// ִ��ж��(״̬�л�)
		void DoUnload();

	protected:
		// ��������
		virtual void Load() { /* To Redefine */}

		// ж������
		virtual void Unload() { /* To Redefine */}

	protected:
		CGPWorld*	m_world;			// ����

		CGPIndex	m_index;			// ������
		GPtileState m_state;			// ״̬
	};
}