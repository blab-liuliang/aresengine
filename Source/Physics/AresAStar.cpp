#include "Physics/AresAStar.h"

namespace Ares
{
	// ���캯��
	CAStar::CAStar()
		: m_pNavMap( NULL)
		, m_pOpen( NULL)
		, m_pClosed( NULL)
		, m_pStack( NULL)
		, m_pBest( NULL)
	{
	}

	// ��������
	CAStar::~CAStar()
	{
		ClearNodes();
	}

	// ���õ���ͼ
	void CAStar::SetNavMap( INavMap* pNavMap)
	{
		m_pNavMap = pNavMap;
	}

	// ����·���Ķ����
	size_t CAStar::FindPath( int startRef, int endRef, const Vector3& startPos, const Vector3& endPos, vector<PolyRef>& path)
	{
		// ���
		path.clear();

		// ��ʼ��
		if( !StepInitialize( startRef, endRef, startPos, endPos))
			return 0;

		EFindState state = EM_CONTINUE;
		while ( EM_CONTINUE == state)
		{
			state = Step();
		}

		if ( state == EM_FAILE || !m_pBest)
		{
			m_pBest = NULL;
			return 0;
		}

		static vector<PolyRef> tPath;
		SANode* pPath = m_pBest;
		while( pPath)
		{
			tPath.push_back( pPath->m_ID);	

			pPath = pPath->m_pParent;
		}

		// ����·��˳��
		while( tPath.size())
		{
			path.push_back( tPath.back());

			tPath.pop_back();
		}

		return path.size();
	}

	// ����
	bool CAStar::StepInitialize( int startRef, int endRef,const Vector3& vStart, const Vector3& vEnd)
	{
		ClearNodes();

		m_vStart = vStart;
		m_vEnd	 = vEnd;
	
		if( startRef == -1 || endRef == -1)
			return false;

		m_iSID = startRef;
		m_iDID = endRef;

		SANode* pT = new_ SANode( m_iSID);
		pT->m_g = 0;
		pT->m_h = m_pNavMap->CalcH( m_vStart, m_vEnd, m_iSID, -1);// abs( dx-sx) + abs(dy-sy);
		pT->m_f = pT->m_g + pT->m_h;

		m_pOpen = pT;
		
		return true;
	}

	// ����
	CAStar::EFindState CAStar::Step()
	{
		// open�б�Ϊ��,����ʧ��
		if ( !(m_pBest = GetBest()))
			return EM_FAILE;

		// ����Ŀ�ĵ�ID(�ɹ�)
		if ( m_pBest->m_ID == m_iDID)
			return EM_OK;

		// �����Χ�����ӵ�
		DealWithChildren( m_pBest);

		return EM_CONTINUE;
	}

	// ��ȡf��С���
	CAStar::SANode* CAStar::GetBest()
	{
		if ( !m_pOpen) 
			return NULL;
		
		SANode*  pO = m_pOpen;
		SANode*  pC = m_pClosed;

		// ɾ��
		m_pOpen = m_pOpen->m_pNext;

		// ��ӵ�close�б�
		m_pClosed = pO;
		m_pClosed->m_pNext = pC;

		return pO;
	}

	// ���������ӵ�
	void CAStar::DealWithChildren( SANode* pNode)
	{
		int childID[8];
		int numChild;
		m_pNavMap->GetPassAbleNeighbor( childID, numChild, pNode->m_ID);

		for ( int i=0; i<numChild; i++)
		{
			SANode pChild(childID[i]);
			LinkChild( pNode, &pChild);
		}
	}

	// LinkChild
	void CAStar::LinkChild( SANode* pParent, SANode* pTemp)
	{
		int idFromFrom = pParent->m_pParent ? pParent->m_pParent->m_ID : -1;

		float g = pParent->m_g + m_pNavMap->CalcG( m_vStart, pParent->m_ID, pTemp->m_ID, idFromFrom);//UDFunc( m_pUDCost, pParent, pTemp, 0, m_pCBData);

		SANode* pCheck = NULL;

		// �Ƿ���open�б���
		if( pCheck = CheckList( m_pOpen, pTemp->m_ID))
		{
			pParent->m_pChild[ pParent->m_numChildren++] = pCheck;
			if ( g < pCheck->m_g)
			{
				pCheck->m_pParent = pParent;
				pCheck->m_g = g;
				pCheck->m_f = g + pCheck->m_h;
			}
		}
		// ��Cloased����
		else if ( pCheck = CheckList( m_pClosed, pTemp->m_ID))
		{
			pParent->m_pChild[ pParent->m_numChildren++] = pCheck;
			if ( g < pCheck->m_g)
			{
				pCheck->m_pParent = pParent;
				pCheck->m_g = g;
				pCheck->m_f = g + pCheck->m_h;

				UpdateParents( pCheck);
			}
		}
		// δ����Ľ��
		else
		{
			SANode* pNew = new_ SANode( pTemp->m_ID);
			pNew->m_pParent = pParent;
			pNew->m_g = g;
			pNew->m_h = m_pNavMap->CalcH( m_vStart, m_vEnd,pParent->m_ID, pNew->m_ID);
			pNew->m_f = pNew->m_g + pNew->m_h;

			AddToOpenList( pNew);

			pParent->m_pChild[ pParent->m_numChildren++] =  pNew;
		}
	}

	// ���¸����
	void  CAStar::UpdateParents(SANode* pNode)
	{
		float g = pNode->m_g;
		int c = pNode->m_numChildren;

		SANode* pKid = NULL;
		for ( int i=0; i<c; i++)
		{
			pKid = pNode->m_pChild[i];
			int idFromFrom = pNode->m_pParent ? pNode->m_pParent->m_ID : -1;
			float fNKg = m_pNavMap->CalcG( m_vStart, pNode->m_ID, pKid->m_ID, idFromFrom);
			if ( g+fNKg < pKid->m_g)
			{
				pKid->m_g = g + fNKg;
				pKid->m_f = pKid->m_g + pKid->m_h;
				pKid->m_pParent = pNode;

				Push( pKid);
			}
		}

		SANode* pParent;
		while( m_pStack)
		{
			pParent = Pop();
			c = pParent->m_numChildren;
			for( int i=0; i<c;i++)
			{
				pKid = pParent->m_pChild[i];
				int idFromFrom = pParent->m_pParent ? pParent->m_pParent->m_ID : -1;
				float fPKg = m_pNavMap->CalcG( m_vStart, pParent->m_ID, pKid->m_ID, idFromFrom);
				if ( pParent->m_g + fPKg< pKid->m_g)
				{
					pKid->m_g = pParent->m_g + fPKg;//UDFunc( m_pUDCost, pParent, pKid, 0, m_pCBData);
					pKid->m_f = pKid->m_g + pKid->m_h;
					pKid->m_pParent = pParent;

					Push( pKid);
				}
			}
		}
	}

	// ��ӽ�㵽OpenList
	void CAStar::AddToOpenList( SANode* pNodeAdd)
	{
		SANode*  pNode = m_pOpen;
		SANode*  pPrev = NULL;

		// ��һ��
		if( !m_pOpen)
		{
			m_pOpen = pNodeAdd;
			m_pOpen->m_pNext = NULL;

			return;
		}

		// ����f ��ӵ��ʵ�λ��
		while( pNode)
		{
			if ( pNodeAdd->m_f > pNode->m_f)
			{
				pPrev = pNode;
				pNode = pNode->m_pNext;
			}
			else
			{
				if( pPrev)
				{
					pPrev->m_pNext = pNodeAdd;
					pNodeAdd->m_pNext = pNode;
				}
				else
				{
					pNodeAdd->m_pNext = m_pOpen;
					m_pOpen = pNodeAdd;
				}

				return;
			}
		}

		pPrev->m_pNext = pNodeAdd;
	}

	// Statck Fuctions  ( Push)
	void CAStar::Push( SANode* pNode)
	{
		if( !m_pStack)
		{
			m_pStack = new_ SAStack;
			m_pStack->m_pData = pNode;
			m_pStack->m_pNext = NULL;
		}
		else
		{
			SAStack* pT = new_ SAStack;
			pT->m_pData = pNode;
			pT->m_pNext = m_pStack;
			m_pStack = pT;
		}
	}

	// ��ջ
	CAStar::SANode* CAStar::Pop()
	{
		SANode* pData = m_pStack->m_pData;
		SAStack* pT = m_pStack;

		m_pStack = m_pStack->m_pNext;

		if (pT) 
			delete pT;

		return pData;
	}

	// ����б�
	CAStar::SANode* CAStar::CheckList( SANode* pNodeList, int id)
	{
		while( pNodeList)
		{
			if( pNodeList->m_ID == id)
				return pNodeList;

			pNodeList = pNodeList->m_pNext;
		}

		return NULL;
	}

	// ������
	void CAStar::ClearNodes()
	{
		SANode* pT = NULL;
		while( m_pOpen)
		{
			pT = m_pOpen->m_pNext;

			delete m_pOpen;

			m_pOpen = pT;
		}

		while( m_pClosed)
		{
			pT = m_pClosed->m_pNext;

			delete m_pClosed;

			m_pClosed = pT;
		}
	}
}