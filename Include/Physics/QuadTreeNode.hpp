#pragma once

#include "quadtreemember.hpp"

namespace Ares
{
	// quadtreenode
	template<typename T>
	class quad_tree_node
	{
	public:
		// ���캯��
		quad_tree_node();

		// ��ӳ�Ա
		void add_member(quad_tree_member<T>* member, quad_tree_byte_rect& rect);

		// �Ƴ���Ա
		void  remove_member(quad_tree_member<T>* member);

		// �����������еĳ�Ա
		void  test_local_members_for_search_results(quad_tree_member<T>** pResultList, quad_tree_member<T>** pResultListTail, const quad_tree_rect& trueRect);

		// ���Ա�����еĳ�Ա��ЩҪ����Ⱦ
		void  test_local_members_for_search_results(quad_tree_member<T>** pResultList, quad_tree_member<T>** pResultListTail);

		// �����Ĳ������  Setup
		void setup(quad_tree_node<T>* pParent, quad_tree_node<T>* pChild1, quad_tree_node<T>* pChild2, quad_tree_node<T>* pChild3, quad_tree_node<T>* pChild4);

	private:
		// �����Ա���
		void descendant_member_added();

		// �Ƴ��������Ա
		void descendant_member_removed();

	private:
		quad_tree_node<T>*		m_pChildNode[4];	// �ĸ��ӽ��
		quad_tree_node<T>*		m_pParentNode;		// �����
		quad_tree_member<T>*	m_pFirstMember;		// ���ĵĳ�Ա
	};	

	// �����ཻ���, �����ཻ����
	static inline bool intersect_rect_2d(const quad_tree_rect& a, const quad_tree_rect& b, quad_tree_rect& result)
	{
		result.x0 = std::max<float>( a.x0, b.x0);
		result.y0 = std::max<float>( a.y0, b.y0);

		result.x1 = std::min<float>( a.x1, b.x1);
		result.y1 = std::min<float>( a.y1, b.y1);

		return (result.x0 <= result.x1) && (result.y0 <= result.y1);
	}

	// ���캯��
	template<typename T>
	quad_tree_node<T>::quad_tree_node()
	{
		m_pParentNode = NULL;
		m_pFirstMember= NULL;

		memset( m_pChildNode, 0, sizeof(m_pChildNode));
	}

	// ��ӳ�Ա
	template<typename T>
	void quad_tree_node<T>::add_member(quad_tree_member<T>* member, quad_tree_byte_rect& rect)
	{
		// acount for the new addition
		if ( !m_pFirstMember)
		{
			m_pFirstMember = member;
		}
		else
		{
			// Prepend this member to our list
			member->set_forward_tree_link(NULL);
			member->set_rear_tree_link(m_pFirstMember);
			m_pFirstMember->set_forward_tree_link(member);
			m_pFirstMember = member;
		}

		// notify our parent of the addition
		if (m_pParentNode)
		{
			m_pParentNode->descendant_member_added();
		}
	}

	// ɾ����Ա
	template<typename T>
	void quad_tree_node<T>::remove_member(quad_tree_member<T>* member)
	{
		quad_tree_member<T>* pCurr = m_pFirstMember;
		while( pCurr)
		{
			if( pCurr == member)
			{
				if (member->m_pForwardTreeLink)
				{
					member->m_pForwardTreeLink->set_rear_tree_link( member->rear_tree_link());
				}

				if (member->rear_tree_link())
				{
					member->rear_tree_link()->set_forward_tree_link(member->m_pForwardTreeLink);
				}

				// if this war our first member, advance our pointer to the next member
				if (m_pFirstMember == member)
				{
					m_pFirstMember = member->m_pForwardTreeLink;
				}

				// Clear the former members links
				member->set_rear_tree_link(NULL);
				member->set_forward_tree_link(NULL);

				// Notify our parent
				if ( m_pParentNode)
				{
					m_pParentNode->descendant_member_removed();
				}
			}

			pCurr = pCurr->rear_tree_link();
		}
	}

	// ��ӳ�Ա
	template<typename T>
	void quad_tree_node<T>::descendant_member_added()
	{
		// ֪ͨ������Ա����
		if (m_pParentNode)
		{
			m_pParentNode->descendant_member_added();
		}
	}

	// ɾ����Ա
	template<typename T>
	void quad_tree_node<T>::descendant_member_removed()
	{
		// notify our parent of the removal
		if (m_pParentNode)
		{
			m_pParentNode->descendant_member_removed();
		}
	}

	// ������еĳ�Ա
	template<typename T>
	void quad_tree_node<T>::test_local_members_for_search_results(quad_tree_member<T> **pResultList, quad_tree_member<T>**pResultListTail, const quad_tree_rect &trueRect)
	{
		// calling this function assumes that the 2D search rectangle intersects this node,
		// so we need to test against in the yMask bit patterns as well as the search area
		// for our local members
		quad_tree_member<T>* object=NULL;
		quad_tree_rect result;

			for (object = m_pFirstMember; object; object = object->m_pRearTreeLink)
			{
				if ( intersect_rect_2d( trueRect, object->key, result))
				{
					if (*pResultListTail)
					{
						object->set_forward_search_link( *pResultListTail);
						object->set_rear_search_link(  NULL);
						(*pResultListTail)->set_rear_search_link( object);
						*pResultListTail = object;
					}

					// ��Ѱ����Ϊ��
					else
					{
						object->set_forward_search_link( NULL);
						object->set_rear_search_link(NULL);
						*pResultListTail = object;
						*pResultList = object;
					}
				}
			}
	}

	// ���������Щ��Ա������ʾ 
	template<typename T>
	void quad_tree_node<T>::test_local_members_for_search_results(quad_tree_member<T> **pResultList, quad_tree_member<T> **pResultListTail)
	{
		// calling this function assumes that the 2D search rectangle contains the node completely, so 
		// all we need to test against is the y range specified and the optional frustum
		quad_tree_member<T>* object;

		for (object = m_pFirstMember; object; object = object->m_pRearTreeLink)
		{
			if (*pResultListTail)
			{
				object->set_forward_search_link( *pResultListTail);
				object->set_rear_search_link(  NULL);
				(*pResultListTail)->set_rear_search_link( object);
				*pResultListTail = object;
			}

			// ��Ѱ����Ϊ��
			else
			{
				object->set_forward_search_link( NULL);
				object->set_rear_search_link(NULL);
				*pResultListTail = object;
				*pResultList = object;
			}
		}
	}

	// ����
	template<typename T>
	void quad_tree_node<T>::setup( quad_tree_node<T> *pParent, quad_tree_node<T> *pChild1, quad_tree_node<T> *pChild2, quad_tree_node<T> *pChild3, quad_tree_node<T> *pChild4)
	{
		m_pParentNode = pParent;

		m_pChildNode[0] = pChild1;
		m_pChildNode[1] = pChild2;
		m_pChildNode[2] = pChild3;
		m_pChildNode[3] = pChild4;
	}
}