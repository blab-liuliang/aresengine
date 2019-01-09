#pragma once

#include "Physics/Rect3.h"
#include <vector>
#include <boost/serialization/vector.hpp>

using namespace std;

namespace Ares
{
	// KDTreeNode 2012-11-23 ����
	template<typename T>
	struct KdtNode
	{
		float			m_split;		// split pos
		UINT			m_data;			// leaf flag, axis face, child point, primitive list

		// ���캯��
		KdtNode() : m_split( 0.f), m_data(6) {}

		// ��������
		void SetAxis( int axis) { m_data = (m_data&-4) + axis; }

		// ��ȡ����
		int  GetAxis() const { return m_data & 3; }

		// ��������
		void SetLeft( int leftOffset) { m_data = (leftOffset << 10) | ( m_data & 1023); }

		// ��ȡ���ӽ��
		const KdtNode<T>* GetLeft( const vector<KdtNode<T> >& root) const { return (KdtNode<T>*)( &root[m_data>>10]); }

		// ��ȡ���ӽ��
		const KdtNode<T>* GetRight( const vector<KdtNode<T> >& root) const { return (KdtNode<T>*)( &root[(m_data>>10)+1]); }

		// �Ƿ�ΪҶ���
		BOOL IsLeaf() const { return m_data & 4; }

		// �Ƿ�Ϊ��Ҷ���
		BOOL IsInternal() const { return !IsLeaf(); }

		// ���ý������
		void SetLeaf( bool isLeaf) { m_data = isLeaf ? (m_data|4) : (m_data&-5); }

		// ��ȡ����洢λ��ƫ����
		int GetMemberOffset() const { return m_data>>10; }

		// ��ȡ��������
		int GetMemberCount() const { return (m_data&1016)>>3;}

		// ���÷ָ�λ��
		void SetSplitPos( float pos) { m_split=pos; }

		// ��ȡ�ָ�λ��
		float GetSplitPos() const { return m_split; }

		// ���ó�Ա�б�
		void SetMemberList( int offset, int count) { m_data = (offset<<10) + (count<<3) + (m_data&7);}

		// serialization
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_split;
			ar & m_data;
		}
	};

	//----------------------------------------
	// K-dimensional tree 2012-11-23 ����
	// Implents a fast static bounding volume
	// tree based on axis aligned bounding boxe
	//		<<game programming gems 7>> 2.2
	//----------------------------------------
	template <typename T>
	class Kdt
	{
	public:
		Kdt(){}
		~Kdt() {}

		// ���
		void ShapeIntersectionTest( vector<T>& results, const KdtNode<T>* root, const Shape* shape) const;

		// ��ȡ���ڵ�
		const KdtNode<T>* GetRoot() const { return m_root.data(); }

		// serialization
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_root;
			ar & m_memberList;
		}

	public:
		vector<KdtNode<T> >		m_root;				// �����
		vector<T>				m_memberList;		// ��Ա�б�
	};

	// ���
	template<typename T>
	void Kdt<T>::ShapeIntersectionTest( vector<T>& results, const KdtNode<T>* root, const Shape* shape) const
	{
		results.clear();

		// check
		if( !root) return;

		// ��ʹ��AABB
		Rect3 intrAABB;
		shape->BuildAABB( intrAABB, Transform());

		vector<const KdtNode<T>*> stack;
		stack.reserve( 128);
		stack.push_back( root);
		while ( stack.size())
		{
			const KdtNode<T>* node = stack.back(); stack.pop_back();
			if( node->IsInternal())
			{
				int	  axis	   = node->GetAxis();
				float splitPos = node->GetSplitPos();

				// ��¼����
				if( splitPos>intrAABB.m_min[axis])
					stack.push_back( node->GetLeft( m_root));
			
				// ��¼�ҽ��
				if( splitPos<intrAABB.m_max[axis])
					stack.push_back( node->GetRight( m_root));
			}
			else
			{
				int memOffset = node->GetMemberOffset();
				int memCount = node->GetMemberCount();
				for( int i=0; i<memCount; i++)
				{
					// ��������,���� !!!!!
					results.push_back( m_memberList[memOffset+i]);
				}			
			}
		}
	}
}