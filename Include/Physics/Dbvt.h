#pragma once

#include <vector>
#include <Physics/Rect3.h>
#include <Physics/Collide.h>

using namespace std;

namespace Ares
{
	typedef Rect3 DbvtVolume;

	// DbvtNode 2012-11-19 ����
	template<typename T>
	struct DbvtNode
	{
		DbvtVolume		m_volume;		// ��Χ��
		DbvtNode<T>*	m_parent;		// �����
		DbvtNode<T>*	m_childs[2];	// �ӽ��
		T				m_data;			// �û�����

		// �Ƿ�ΪҶ�ӽ��
		bool IsLeaf() const { return !m_childs[1]; }

		// �Ƿ�Ϊ��Ҷ���
		bool IsInternal() const { return !IsLeaf(); }
	};

	//------------------------------------------
	// Dynamics bounding volume tree 2012-11-19
	// Implents a fast dynamic bounding volume
	// tree based on axis aligned bounding boxes,
	// It has a fast insert, remove and update of
	// nodes.
	//------------------------------------------
	template <typename T>
	class Dbvt
	{
	public:
		// Stack element
		struct StkNN
		{
			const DbvtNode<T>*	m_a;
			const DbvtNode<T>*	m_b;

			StkNN() {}
			StkNN( const DbvtNode<T>* na, const DbvtNode<T>* nb) : m_a(na), m_b(nb) {}
		};

	public:
		Dbvt();
		~Dbvt() {}

		// ����
		DbvtNode<T>* Insert( const DbvtVolume& volume, T& data);

		// ����
		void Update( DbvtNode<T>* leaf, const DbvtVolume& volume);

		// ���
		void ShapeIntersectionTest( const DbvtNode<T>* root, const Shape* shape, vector<T>& results);

		// ��ȡ���ڵ�
		const DbvtNode<T>* GetRoot() const { return m_root; }

		// �Ƿ�Ϊ��
		bool IsEmpty() const { return !m_root; }

		// �Ƴ����
		void Remove( DbvtNode<T>* leaf);

		// ���
		void Clear();

	private:
		// �ݹ�ɾ�����
		void RecursiveDeleteNode( DbvtNode<T>* node);

		// �������
		DbvtNode<T>* CreateNode( DbvtNode<T>* parent, T& data);

		// �������
		DbvtNode<T>* CreateNode( DbvtNode<T>* parent, const DbvtVolume& volume, T& data);

		// �������
		DbvtNode<T>* CreateNode( DbvtNode<T>* parent, const DbvtVolume& volume0, const DbvtVolume& volume1, T& data);

		// ɾ�����
		void DeleteNode( DbvtNode<T>* node);

		// ����ڵ�
		void InsertLeaf( DbvtNode<T>* root, DbvtNode<T>* leaf);

		// �Ƴ�Ҷ���
		DbvtNode<T>* RemoveLeaf( DbvtNode<T>* leaf);

		// ��ȡ����
		int Indexof( const DbvtNode<T>* node);

		// Proximity
		float Proximity( const DbvtVolume& a, const DbvtVolume& b);

		// Select
		int Select( const DbvtVolume& o, const DbvtVolume& a, const DbvtVolume& b);

	private:
		DbvtNode<T>*	m_root;		// ���ڵ�
		DbvtNode<T>*	m_free;		// ���нڵ�
		int				m_lkhd;
		int				m_leaves;	// Ҷ�ڵ���
		UINT			m_opath;

		vector<StkNN>				m_stkStack;
		vector<const DbvtNode<T>*>	m_shapeTestStack;
	};

	// ���캯��
	template <typename T>
	Dbvt<T>::Dbvt()
	 : m_root( NULL)
	 , m_free( NULL)
	 , m_lkhd( -1)
	 , m_leaves( 0)
	 , m_opath( 0)
	{}

	// ���
	template <typename T>
	FORCEINLINE void Dbvt<T>::Clear()
	{
		if( m_root)
			RecursiveDeleteNode( m_root);

		m_lkhd = -1;
		m_opath = 0;
		m_stkStack.clear();
	}

	// ����
	template <typename T>
	FORCEINLINE DbvtNode<T>* Dbvt<T>::Insert( const DbvtVolume& volume, T& data)
	{
		DbvtNode<T>* leaf = CreateNode( NULL, volume, data);

		InsertLeaf( m_root, leaf);

		m_leaves++;

		return leaf;
	}

	// ����
	template <typename T>
	void Dbvt<T>::Update( DbvtNode<T>* leaf, const DbvtVolume& volume)
	{
		DbvtNode<T>* root = RemoveLeaf( leaf);
		if( root)
		{
			if( m_lkhd>=0)
			{
				for( int i=0; (i<m_lkhd)&&root->m_parent; ++i)
					root = root->m_parent;
			}
			else
				root = m_root;
		}

		leaf->m_volume = volume;
		InsertLeaf( root, leaf);
	}

	// �������
	template <typename T>
	FORCEINLINE DbvtNode<T>* Dbvt<T>::CreateNode( DbvtNode<T>* parent, T& data)
	{
		DbvtNode<T>* node;
		if( m_free)
		{
			node   = m_free;
			m_free = NULL;
		}
		else
		{
			// ���·���
			node = new_ DbvtNode<T>;
		}
		
		node->m_parent	  = parent;
		node->m_data	  = data;
		node->m_childs[1] = NULL;

		return node;
	}

	// �������
	template <typename T>
	FORCEINLINE DbvtNode<T>* Dbvt<T>::CreateNode( DbvtNode<T>* parent, const DbvtVolume& volume, T& data)
	{
		DbvtNode<T>* node = CreateNode( parent, data);
		node->m_volume = volume;

		return node;
	}

	// �������
	template <typename T>
	DbvtNode<T>* Dbvt<T>::CreateNode( DbvtNode<T>* parent, const DbvtVolume& volume0, const DbvtVolume& volume1, T& data)
	{
		DbvtNode<T>* node = CreateNode( parent, data);
		Rect3::Merge( node->m_volume, volume0, volume1);

		return node;
	}

	// ��ȡ����
	template <typename T>
	FORCEINLINE int Dbvt<T>::Indexof( const DbvtNode<T>* node)
	{
		return static_cast<int>( node->m_parent->m_childs[1]==node);
	}

	// ����ڵ�
	template <typename T>
	FORCEINLINE void Dbvt<T>::InsertLeaf( DbvtNode<T>* root, DbvtNode<T>* leaf)
	{
		if( !m_root)
		{
			m_root		   = leaf;
			leaf->m_parent = NULL;
		}
		else
		{
			if( !root->IsLeaf())
			{
				do 
				{
					root = root->m_childs[ Select( leaf->m_volume, root->m_childs[0]->m_volume, root->m_childs[1]->m_volume)];
				} while ( !root->IsLeaf());
			}

			T			 nullT;
			DbvtNode<T>* prev = root->m_parent;
			DbvtNode<T>* node = CreateNode( prev, leaf->m_volume, root->m_volume, nullT);
			if( prev)
			{
				prev->m_childs[Indexof( root)] = node;
				node->m_childs[0]			   = root; root->m_parent = node;
				node->m_childs[1]			   = leaf; leaf->m_parent = node;
				do 
				{
					if( !prev->m_volume.IsContain( node->m_volume))
						Rect3::Merge( prev->m_volume, prev->m_childs[0]->m_volume, prev->m_childs[1]->m_volume);
					else
						break;

					node = prev;
				} while ( prev=node->m_parent);
			}
			else
			{
				node->m_childs[0] = root; root->m_parent = node;
				node->m_childs[1] = leaf; leaf->m_parent = node;
				m_root			  = node;
			}
		}
	}

	// �ݹ�ɾ�����
	template <typename T>
	void Dbvt<T>::RecursiveDeleteNode( DbvtNode<T>* node)
	{
		if( !node->IsLeaf())
		{
			RecursiveDeleteNode( node->m_childs[0]);
			RecursiveDeleteNode( node->m_childs[1]);
		}

		if( node==m_root)
			m_root = NULL;

		DeleteNode( node);
	}

	// ɾ�����
	template <typename T>
	void Dbvt<T>::DeleteNode( DbvtNode<T>* node)
	{
		SAFE_DELETE( m_free);

		m_free = node;
	}

	// �Ƴ�Ҷ���
	template <typename T>
	DbvtNode<T>* Dbvt<T>::RemoveLeaf( DbvtNode<T>* leaf)
	{
		if( leaf==m_root)
		{
			m_root = NULL;
			return NULL;
		}
		else
		{
			DbvtNode<T>* parent = leaf->m_parent;
			DbvtNode<T>* prev	= parent->m_parent;
			DbvtNode<T>* sibling= parent->m_childs[1-Indexof(leaf)];
			if( prev)
			{
				prev->m_childs[Indexof(parent)] = sibling;
				sibling->m_parent = prev;
				DeleteNode( parent);
				while( prev)
				{
					const DbvtVolume pd = prev->m_volume;
					Rect3::Merge( prev->m_volume, prev->m_childs[0]->m_volume, prev->m_childs[1]->m_volume);
					if( pd!=prev->m_volume)
						prev = prev->m_parent;
					else
						break;
				}
				return prev ? prev : m_root;
			}
			else
			{
				m_root = sibling;
				sibling->m_parent = NULL;
				DeleteNode( parent);
				
				return m_root;
			}
		}
	}

	// ���
	template<typename T>
	void Dbvt<T>::ShapeIntersectionTest( const DbvtNode<T>* root, const Shape* shape, vector<T>& results)
	{
		results.clear();

		// check
		if( !root) return;

		vector<const DbvtNode<T>*>& stack = m_shapeTestStack;
		stack.reserve( 128);
		stack.push_back( root);
		while ( stack.size()) 
		{
			const DbvtNode<T>* node = stack.back(); stack.pop_back();
			if( Collide::IntersectionTest( shape, &node->m_volume))
			{
				if( node->IsInternal())
				{
					stack.push_back( node->m_childs[0]);
					stack.push_back( node->m_childs[1]);
				}
				else
				{
					// �Ƿ����ظ���� !!!!!
					results.push_back( node->m_data);
				}
			}
		}
	}

	// �Ƴ����
	template <typename T>
	void Dbvt<T>::Remove( DbvtNode<T>* leaf)
	{
		RemoveLeaf( leaf);
		DeleteNode( leaf);
		m_leaves--;
	}

	// Select
	template <typename T>
	int Dbvt<T>::Select( const DbvtVolume& o, const DbvtVolume& a, const DbvtVolume& b)
	{
		return Proximity( o, a) < Proximity( o, b) ? 0 : 1;
	}

	// Proximity
	template <typename T>
	float Dbvt<T>::Proximity( const DbvtVolume& a, const DbvtVolume& b)
	{
		const Vector3 d = (a.m_min+a.m_max) - (b.m_min+b.m_max);

		return std::abs( d.x) + std::abs( d.y) + std::abs( d.z);
	}
}