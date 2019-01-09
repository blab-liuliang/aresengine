#pragma once

#include <stdlib.h>
#include <string.h>
#include <vector>
#include "AresNavMap.h"

using namespace std;

namespace Ares
{
	//------------------------------------
	// A* Algorithm 2011-01-19  ����
	//------------------------------------
	typedef UINT PolyRef;
	class CAStar
	{
		// A*�ӵ� 2011-01-19  ����
		struct SANode
		{
			int   m_ID;				// �ӵ��άһ��ʶ
			float m_f, m_g, m_h;	// Fitness, goal, heuristic
			int   m_numChildren;	// ������

			SANode*  m_pParent;		// ���ӵ�
			SANode*  m_pNext;		// ����Open���Closed����(��������)
			SANode*  m_pChild[8];

			// ���캯��
			SANode( int id)
			{
				m_ID = id;
				m_numChildren = 0;
				m_pParent   = NULL;
				m_pNext     = NULL;
				memset( m_pChild, 0, sizeof(m_pChild));
			}
		};

		// Stack for propagation
		struct SAStack
		{
			SANode*  m_pData;
			SAStack* m_pNext;
		};

		enum EFindState
		{
			EM_FAILE,		// �����ڴ���ʼ�㵽Ŀ�ĵص�·��
			EM_CONTINUE,	// ����
			EM_OK,			// ���ҽ���
		};

	public:
		CAStar();
		~CAStar();

		// ���õ���ͼ
		void SetNavMap( INavMap* pNavMap);

		// ����·���Ķ����
		size_t FindPath( int startRef, int endRef, const Vector3& startPos, const Vector3& endPos, vector<PolyRef>& path);

		// ��ȡ·��
		SANode* GetBestNode() { return m_pBest; }

	private:
		// ����
		EFindState  Step();

		// ��ȡf��С���
		SANode*  GetBest();

		// LinkChild
		void  LinkChild( SANode* pParent, SANode* pTemp);

		// ���������ӵ�
		void DealWithChildren( SANode* pNode);

		// ���¸����
		void  UpdateParents(SANode* pNode);

		// ��ӽ�㵽OpenList
		void AddToOpenList( SANode* pNodeAdd);

		// ����б�
		SANode* CheckList( SANode* pNodeList, int id);

		// ����
		bool  StepInitialize( int startRef, int endRef, const Vector3& vStart, const Vector3& vEnd);

		// ������
		void ClearNodes();

		// Statck Fuctions  ( Push)
		void  Push( SANode* pNode);

		// ��ջ
		SANode* Pop();

	private:
		int				m_iSID;
		int				m_iDID;			// Ŀ�ĵ�ID
		Vector3			m_vStart;		// ��ʼ��
		Vector3			m_vEnd;			// Ŀ�ĵ�
		SANode*			m_pOpen;		// open list
		SANode*			m_pClosed;		// closed list
		SANode*			m_pBest;		// ��ǰ���Ž��
		SAStack*		m_pStack;
		INavMap*		m_pNavMap;		// ����ͼ
	};
}