#pragma once

#include "Kdt.h"
#include <deque>

using namespace std;

namespace Ares
{
	// ��Ա�����б�,����Kdt����
	class MemberList
	{
	public:
		// ���캯��
		MemberList() : m_next(NULL) {}

		// ��������
		~MemberList() { SAFE_DELETE(m_next); }

		// ���ö�������
		void SetMemIdx( size_t member) { m_memIdx = member; }

		// ��ȡ����
		const size_t GetMemIdx() { return m_memIdx; }

		// ������һ��
		void SetNext( MemberList* next) { m_next=next; }

		// ��ȡ��һ��
		MemberList* GetNext() { return m_next; }

		// ��ȡ�ߴ�
		int GetSize() { if(m_next) return 1+m_next->GetSize(); else return 1; }

	private:
		size_t		m_memIdx;
		MemberList*	m_next;
	};

	// MemberData
	struct MemberData
	{
		Rect3		m_aabb;
		size_t		m_idx;

		// ��ʼ��
		void Init( const vector<Rect3>& keys, size_t idx);

		// �ؽ����ü�
		void Clip( Rect3& abox);

		// �Ƿ��пռ�
		bool IsHaveSpace() { return m_aabb.GetXSize()>0.f && m_aabb.GetYSize()>0.f && m_aabb.GetZSize()>0.f;}
	};

	// ����, Surface Area Heuristic
	struct kdtbox
	{
		UINT	m_n[3];		// ��¼��һ���ӵ��볯��
		float   m_pos[3];	// 12

		// ��һ��
		kdtbox* GetNext( int a) { return (kdtbox*)( m_n[a]&(0xffffffff - 3));}

		// ��һ��
		void SetNext( int a, kdtbox* p) { m_n[a] = ( m_n[a] & 3) + (UINT)p; }

		// Side
		int GetSide( int a) { return m_n[a] & 3; }

		// Side
		void SetSide( int a, int s) { m_n[a] = ( m_n[a] & (0xffffffff - 3)) + s; }
	};

	// ����
	struct KdtBox 
	{ 
		enum 
		{ 
			END, 
			PLANAR, 
			DISABLE, 
			START 
		};

		// ���
		enum 
		{ 
			LEFTLIST, 
			RIGHTLIST, 
			PROCESSED, 
			STRADDLING 
		}; 

		kdtbox			m_side[2];		// 48 
		size_t			m_memIdx;		// 4 
		unsigned int	m_flags;		// 4 
		KdtBox*			m_clone;		// 4 
		int				m_dummy;		// 4, total = 64 

		// ���캯��
		KdtBox()
		{
			std::memset( this, 0, sizeof(*this));
		}
	}; 

	// �����б�
	struct KdtBoxList 
	{ 
		kdtbox* m_head[3];
		kdtbox* m_tail[3];

		// ���캯��
		KdtBoxList();

		// ��ʼ��
		void Init();

		// ����
		void Sort( int a ); 

		// ����
		void Insert( int a, kdtbox* n ); 

		// �Ƴ�
		void Remove( int a, kdtbox* n ); 
	}; 

	// KdtMManager
	class KdtMManager
	{
	public:
		KdtMManager();
		~KdtMManager();

		// �½���Ա�б�
		MemberList* NewMemberList();

		// �½�KdtBox
		KdtBox* NewKdtBox();

		// �½�KdtBoxList
		KdtBoxList* NewKdtBoxList();

	public:
		UINT		m_eFree;
		UINT		m_eReq;
		KdtBox*		m_ePtr;

		UINT		m_elFree;
		UINT		m_elReq;
		KdtBoxList* m_elPtr;

		UINT		m_mReq;
		MemberList*	m_mList;
		MemberList*	m_mPtr;

	};

	// �����ṹ��,ȥ���ݹ�
	template <typename T>
	struct SAHParam
	{
		KdtNode<T>*	 m_node;		// ���
		Rect3		 m_box;			// ��Χ��
		int			 m_depth;		// ���
		int			 m_numMembers;	// ��Ա��
		KdtBoxList*	 m_kdtBoxList;	// BoxList, ������;����
	};
	
	//------------------------------------
	// KDTreeBuilder 2012-11-23 ����
	// ����KDTree����
	//------------------------------------
	template <typename T>
	class KdtBuilder  
	{
	public:
		KdtBuilder( const vector<Rect3>& keys, const vector<T>& members, Kdt<T>& kdt);
		~KdtBuilder();

	private:
		// ����
		void InitBuild();

		// ��ȡҶ�ӽ������¼�ĳ�Ա����(Recursive)
		int CountNumLeafMembers( const KdtNode<T>* node);

		// ���������б�
		void BuildMemberList( KdtNode<T>* node, int depth);

		// ������
		void BuildTree( MemberList* memberList, KdtNode<T>* node, Rect3& rbox, int depth);

		// �ָ��㷨 Surface Area Heuristic
		void SubdivNewONlogN( KdtNode<T>* anode, Rect3& rbox, int depth, int numMembers, deque<SAHParam<T> >& remaining);

		// ��ȡ��Ա�б�
		MemberList* GetMemberList( const KdtNode<T>* node);

		// ��������ӳ�Ա
		void NodeAddMember( const KdtNode<T>* node, size_t memIdx);

		// ���KdTree���
		size_t NewKdTreeNodePair();

		typedef map<const KdtNode<T>*, MemberList*> NMLMap;
	private:
		vector<KdtNode<T> >	m_root;			// �����
		vector<T>			m_memberList;	// ��Ա�б�

		const vector<Rect3>&m_keys;			// ��������
		const vector<T>&	m_members;		// ���ݳ�Ա
		int					m_curMember;	// ��ǰ����
		int					m_intrCost;		// �ཻ����,�ָ�����
		int					m_travCost;		// ��������
		int					m_maxDepth;		// ������,���ض�����ֹͣ�ָ�,�Կ����ڴ��ʹ�ú͹���ʱ��
		int					m_pPerLeaf;		// Ҷ���
		KdtBoxList*			m_eList;		// �б�
		NMLMap				m_nodeMLists;	// ����Ա�б�
		MemberData			m_memData;		// ��Ա����
		KdtMManager			m_memMgr;		// �ڴ������
	};

	// ���캯��
	template <typename T>
	KdtBuilder<T>::KdtBuilder( const vector<Rect3>& keys, const vector<T>& members, Kdt<T>& kdt)
		: m_keys( keys)
		, m_members( members)
		, m_eList( NULL)
	{
		A_ASSERT( m_keys.size()==m_members.size());

		m_root.reserve( members.size()*4);
		m_memberList.reserve( members.size() * 4);
		m_travCost = 1;
		m_intrCost = 3;
		m_maxDepth = 20;
		m_pPerLeaf = 8;

		// Ĭ�������
		m_root.push_back(KdtNode<T>());

		m_curMember = 0;
		InitBuild();
		if( !m_memberList.size())
		{
			int tReq = CountNumLeafMembers( m_root.data());
			//tReq += (tReq>>2) | 256;
			m_memberList.resize( tReq);
		}

		BuildMemberList( m_root.data(), 0);

		kdt.m_memberList = m_memberList;
		kdt.m_root		 = m_root;
	}

	// ��������
	template <typename T>
	KdtBuilder<T>::~KdtBuilder()
	{}

	// ��ȡ��Ա�б�
	template <typename T>
	MemberList* KdtBuilder<T>::GetMemberList( const KdtNode<T>* node)
	{
		typename NMLMap::iterator it=m_nodeMLists.find( node);
		if( it!=m_nodeMLists.end())
			return it->second;

		return NULL;
	}

	// ��������ӳ�Ա
	template <typename T>
	void KdtBuilder<T>::NodeAddMember( const KdtNode<T>* node, size_t memIdx)
	{
		MemberList* memList = m_memMgr.NewMemberList();
		memList->SetMemIdx( memIdx);
		memList->SetNext( GetMemberList( node));
		m_nodeMLists[node] = memList;
	}

	// ���KdTree���
	template <typename T>
	size_t KdtBuilder<T>::NewKdTreeNodePair()
	{
		A_ASSERT( m_root.size()+2 < m_root.capacity());

		m_root.push_back( KdtNode<T>());
		m_root.push_back( KdtNode<T>());

		return m_root.size() - 2;
	}

	// ��ȡҶ�ӽ������¼�ĳ�Ա����(Recursive)
	template <typename T>
	int KdtBuilder<T>::CountNumLeafMembers( const KdtNode<T>* node)
	{
		int numMembers = 0;
		if( node->IsLeaf())
		{
			// ��ǰ����Ա��
			MemberList* memberList = GetMemberList( node);
			while( memberList)
			{
				numMembers++;
				memberList = memberList->GetNext();
			}
		}
		else
		{
			// ���ҽӵ��Ա��
			const KdtNode<T>* left = node->GetLeft( m_root);
			const KdtNode<T>* right= node->GetRight( m_root);
			if( left)
				numMembers += CountNumLeafMembers( left);
			if( right)
				numMembers += CountNumLeafMembers( right);
		}

		return numMembers;
	}

	// ���������б�
	template <typename T>
	void KdtBuilder<T>::BuildMemberList( KdtNode<T>* node, int depth)
	{
		if( node->IsLeaf())
		{
			// Convert primitives in leaves to triAccels
			int first = m_curMember;
			int count = 0;
			MemberList* memberList = GetMemberList( node);
			while( memberList)
			{
				m_memberList[m_curMember++] = m_members[memberList->GetMemIdx()];
				memberList = memberList->GetNext();

				count++;
			}

			if( count>127)
			{
				count = 127;
				//A_ASSERT( FALSE);
			}

			// ��¼��ʼλ��������
			node->SetMemberList( first, count);
		}
		else
		{
			KdtNode<T>* left = (KdtNode<T>*)node->GetLeft( m_root);
			KdtNode<T>* right= (KdtNode<T>*)node->GetRight( m_root);
			if( left) BuildMemberList( left, depth+1);
			if( right)BuildMemberList( right,depth+1);
		}
	}

	// ����
	template<typename T>
	void KdtBuilder<T>::InitBuild()
	{
		MemberList* mlist=NULL, *tail=NULL;
		for ( size_t i=0; i<m_members.size(); i++)
		{
			MemberList* newNode = m_memMgr.NewMemberList();
			newNode->SetMemIdx( i);
			newNode->SetNext( 0);
			if( !tail)
			{
				tail = newNode;
				mlist= newNode;
			}
			else
			{
				tail->SetNext( newNode);
				tail = newNode;
			}
		}

		Rect3 sceneBox;
		for ( size_t i=0; i<m_keys.size(); i++)
		{
			sceneBox.UnionPoint( m_keys[i].GetMinPoint());
			sceneBox.UnionPoint( m_keys[i].GetMaxPoint());
		}

		BuildTree( mlist, m_root.data(), sceneBox, 0);
	}

	// ������
	template <typename T>
	void KdtBuilder<T>::BuildTree( MemberList* memberList, KdtNode<T>* node, Rect3& rbox, int depth)
	{
		m_eList = m_memMgr.NewKdtBoxList();
		m_eList->Init();

		MemberList* ml  = memberList;
		int		    events = 0;
		float		pos[2];
		KdtBox*		box;
		KdtBox*		next  = m_memMgr.NewKdtBox();
		KdtBox*		first = next;
		// ���ݳ�Ա�б�����KdtBox
		while( ml)
		{
			m_memData.Init( m_keys, ml->GetMemIdx());
			box			 = next;
			next		 = m_memMgr.NewKdtBox();
			box->m_memIdx= ml->GetMemIdx();
			box->m_flags = KdtBox::STRADDLING;
			for ( int a=0; a<3; a++)
			{
				pos[0] = m_memData.m_aabb.GetMinPoint()[a];
				pos[1] = m_memData.m_aabb.GetMaxPoint()[a];
				box->m_side[0].m_pos[a] = pos[0];
				box->m_side[0].SetNext( a, &box->m_side[1]);
				box->m_side[0].SetSide( a, KdtBox::START);
				box->m_side[1].m_pos[a] = pos[1];
				box->m_side[1].SetNext( a, &next->m_side[0]);
				box->m_side[1].SetSide( a, KdtBox::END);
				if ( pos[0] == pos[1]) 
				{
					box->m_side[0].SetSide( a, KdtBox::PLANAR);
					box->m_side[1].SetSide( a, KdtBox::PLANAR);
					box->m_side[0].SetNext( a, box->m_side[1].GetNext( a));
				}
			}

			ml = ml->GetNext();
		}

		for ( int a=0; a<3; a++)
		{
			m_eList->m_head[a] = &first->m_side[0];
			box->m_side[1].SetNext( a, 0);
			if (box->m_side[1].GetSide(a) == KdtBox::PLANAR) 
				box->m_side[0].SetNext( a, 0);

			m_eList->Sort( a);
		}

		// ִ�зָ�����
		SAHParam<T>		rootParam;
		deque<SAHParam<T> > remaining;
		rootParam.m_node	   = node;
		rootParam.m_box		   = rbox;
		rootParam.m_depth	   = 0;
		rootParam.m_numMembers = m_members.size();
		rootParam.m_kdtBoxList = m_eList;
		remaining.push_back( rootParam);
		while( remaining.size())
		{
			SAHParam<T> sahParam = remaining.front(); 
			remaining.pop_front();
			m_eList = sahParam.m_kdtBoxList;

			SubdivNewONlogN( sahParam.m_node, sahParam.m_box, sahParam.m_depth, sahParam.m_numMembers, remaining);
		}
	}

	// Surface Area Heuristic
	template <typename T>
	void KdtBuilder<T>::SubdivNewONlogN(  KdtNode<T>* anode, Rect3& rbox, int depth, int numMembers, deque<SAHParam<T> >& remaining)
	{
		// best cost calculation
		const float NA = rbox.GetXSize() * rbox.GetZSize() + rbox.GetXSize() * rbox.GetYSize() + rbox.GetZSize() * rbox.GetYSize();
		const float iNA = m_intrCost / NA, minf = 0.1f + 0.01f * depth;
		float bestcost = m_intrCost * (float)numMembers, bestpos = -1.0f;
		int bestaxis = -1, bestside = -1;
		int bestTL, bestTR, bestTP;
		for ( int a = 0; a < 3; a++ )
		{
			if ((rbox.GetMaxPoint()[a] - rbox.GetMinPoint()[a]) > ZERO_TOLERANCE)
			{
				const float w = 1.0f / ( rbox.GetMaxPoint()[a] - rbox.GetMinPoint()[a]);
				int TL = 0, TR = numMembers, TP = 0;
				Vector3 lsize = rbox.GetSize();
				Vector3 rsize = lsize;
				kdtbox* el = m_eList->m_head[a];
				while (el)
				{
					const float pos = el->m_pos[a];
					int pl = 0, pr = 0;
					while ((el) && (el->m_pos[a] == pos) && (el->GetSide(a) == KdtBox::END)) { pl++; el = el->GetNext(a); }
					while ((el) && (el->m_pos[a] == pos) && (el->GetSide(a) == KdtBox::PLANAR)) { TP++; el = el->GetNext(a); }
					while ((el) && (el->m_pos[a] == pos) && (el->GetSide(a) == KdtBox::START)) { pr++; el = el->GetNext(a); }
					TR -= (TP + pl);
					lsize[a] = pos - rbox.GetMinPoint()[a];
					rsize[a] = rbox.GetMaxPoint()[a] - pos;
					const float LA = lsize.x * lsize.y + lsize.x * lsize.z + lsize.y * lsize.z;
					const float RA = rsize.x * rsize.y + rsize.x * rsize.z + rsize.y * rsize.z;
					const float f1 = (pos - rbox.GetMinPoint()[a]) * w;
					const float f2 = (rbox.GetMaxPoint()[a] - pos) * w;
					float bonus1 = 1.0f, bonus2 = 1.0f, bound = 0.1f;
					const float cost1 = bonus1 * ( m_travCost + iNA * (LA * (TL + TP) + RA * TR));
					const float cost2 = bonus2 * ( m_travCost + iNA * (LA * TL + RA * (TR + TP)));
					if (cost1 < bestcost)
					{
						bestcost = cost1, bestpos = pos;
						bestside = 0, bestaxis = a;
						bestTL = TL, bestTR = TR, bestTP = TP;
					}
					if (cost2 < bestcost)
					{
						bestcost = cost2, bestpos = pos;
						bestside = 1, bestaxis = a;
						bestTL = TL, bestTR = TR, bestTP = TP;
					}
					TL += (pr + TP);
					TP = 0;
				}
			}
		}
		
		if (bestside == -1)
		{
			// store primitives in leaf
			kdtbox* el = m_eList->m_head[0];
			while (el)
			{
				KdtBox* eb = (KdtBox*)(((UINT)el) & (0xffffffff - 63));
				if (eb->m_flags != KdtBox::PROCESSED)
				{
					NodeAddMember( anode, eb->m_memIdx);
					eb->m_flags = KdtBox::PROCESSED;
				}
				el = el->GetNext( 0);
			}
			return;
		}
		// best cost calculated; build child nodes
		int count[2] = { bestTL + ((bestside == 0)?bestTP:0), bestTR + ((bestside == 1)?bestTP:0) };
		Rect3 box[2] = { rbox, rbox};
		box[0].GetMaxPoint()[bestaxis] = bestpos;
		box[1].GetMinPoint()[bestaxis] = bestpos;
		size_t nodeIdxs[2];
		nodeIdxs[0] = NewKdTreeNodePair();
		nodeIdxs[1] = nodeIdxs[0] + 1;
		// classify EBoxes (all set to straddling by final pass)
		kdtbox* el = m_eList->m_head[bestaxis];
		while (el)
		{
			const int side = el->GetSide(bestaxis);
			KdtBox* eb = (KdtBox*)(((UINT)el) & (0xffffffff - 63));
			if ((side == KdtBox::END) && (el->m_pos[bestaxis] <= bestpos))
				eb->m_flags = KdtBox::LEFTLIST;
			else if ((side == KdtBox::START) && (el->m_pos[bestaxis] >= bestpos))
				eb->m_flags = KdtBox::RIGHTLIST;
			else if (side == KdtBox::PLANAR)
			{
				if (bestside == 0)
					eb->m_flags = (el->m_pos[bestaxis] <= bestpos)? KdtBox::LEFTLIST : KdtBox::RIGHTLIST;
				else
					eb->m_flags = (el->m_pos[bestaxis] >= bestpos)? KdtBox::RIGHTLIST : KdtBox::LEFTLIST;
			}
			el = el->GetNext( bestaxis );
		}
		el = m_eList->m_head[bestaxis];

		// Split elist to cl[0] and cl[1]
		KdtBoxList* cl[2];
		cl[0] = m_memMgr.NewKdtBoxList();
		cl[1] = m_memMgr.NewKdtBoxList();
		for ( int a = 0; a < 3; a++)
		{
			kdtbox* el = m_eList->m_head[a], *llp = 0, *rlp = 0;
			while (el)
			{
				kdtbox* next = el->GetNext( a);
				KdtBox* eb = (KdtBox*)((( UINT)el) & (0xffffffff - 63));
				if (eb->m_flags == KdtBox::LEFTLIST)
				{
					if (llp) 
						llp->SetNext( a, el ); 
					else 
					{ 
						llp = el; 
						cl[0]->m_head[a] = el; 
					}

					el->SetNext( a, 0);
					llp = el;
				}
				else if (eb->m_flags == KdtBox::RIGHTLIST)
				{
					if (rlp) 
						rlp->SetNext( a, el ); 
					else 
					{ 
						rlp = el; 
						cl[1]->m_head[a] = el; 
					}

					el->SetNext( a, 0);
					rlp = el;
				}
				else
				{
					eb->m_flags = KdtBox::PROCESSED;
					if (!eb->m_clone)
					{
						eb->m_clone = m_memMgr.NewKdtBox();
						std::memcpy( eb->m_clone, eb, 64);
					}
					const int oside = (el->GetSide( a) == KdtBox::END)?1:0;
					kdtbox* clel = &eb->m_clone->m_side[oside];
					if (llp) 
						llp->SetNext( a, el ); 
					else 
					{ 
						llp = el; cl[0]->m_head[a] = el; 
					}

					el->SetNext( a, 0 );
					llp = el;

					if (rlp) 
						rlp->SetNext( a, clel); 
					else 
					{ 
						rlp = clel; cl[1]->m_head[a] = clel; 
					}

					clel->SetNext( a, 0 );
					rlp = clel;
				}

				el = next;
			}
		}
		// remove invalid primitives from ll and rl
		for ( int i = 0; i < 2; i++ )
		{
			el = cl[i]->m_head[0];
			bool needsort = false, needclean = false;
			// clip
			while (el)
			{
				KdtBox* eb = (KdtBox*)(((unsigned long)el) & (0xffffffff - 63));
				if (eb->m_flags == KdtBox::PROCESSED)
				{
					eb->m_flags = KdtBox::LEFTLIST + i;
					eb->m_clone = 0;
					m_memData.Init( m_keys, eb->m_memIdx);
					m_memData.Clip( box[i]);
					if ( !m_memData.IsHaveSpace())
					{
						for ( int a = 0; a < 3; a++)
						{
							eb->m_side[0].SetSide( a, KdtBox::DISABLE);
							eb->m_side[1].SetSide( a, KdtBox::DISABLE);
						}
						count[i]--;
						needclean = true;
					}
					else 
					{
						for ( int a = 0; a < 3; a++ )
						{
							eb->m_side[0].m_pos[a] = m_memData.m_aabb.GetMinPoint()[a];
							eb->m_side[1].m_pos[a] = m_memData.m_aabb.GetMaxPoint()[a];
						}
						needsort = true;
					}
				}

				eb->m_flags = KdtBox::STRADDLING;
				el = el->GetNext( 0 );
			}
			// clean and resort
			for ( int a = 0; a < 3; a++ )
			{
				if (needclean)
				{
					el = cl[i]->m_head[a];
					kdtbox* prev = 0;
					while (el)
					{
						if (el->GetSide( a) == KdtBox::DISABLE)
						{
							if (!prev) 
								cl[i]->m_head[a] = el->GetNext( a);
							else 
								prev->SetNext( a, el->GetNext( a));
						}
						else 
							prev = el;

						el = el->GetNext( a);
					}
				}

				if ((needsort) && (cl[i]->m_head[a])) 
					cl[i]->Sort( a);
			}
		}
		// recursive
		if ( depth < m_maxDepth)
		{
			anode->SetSplitPos( bestpos );
			anode->SetAxis( bestaxis );
			anode->SetLeft( nodeIdxs[0] );
			anode->SetLeaf( false );
			for ( int i=0; i<2; i++)
			{
				if ( count[i]>m_pPerLeaf) 
				{
					SAHParam<T>	sahParam;
					sahParam.m_node		  = &m_root[nodeIdxs[i]];
					sahParam.m_box		  = box[i];
					sahParam.m_depth	  = depth + 1;
					sahParam.m_numMembers = count[i];
					sahParam.m_kdtBoxList = cl[i];
					remaining.push_back( sahParam);
				}
				else
				{
					// store primitives in leaf
					kdtbox* el = cl[i]->m_head[0];
					while (el)
					{
						KdtBox* eb = (KdtBox*)(((UINT)el) & (0xffffffff - 63));
						if (eb->m_flags != KdtBox::PROCESSED)
						{
							NodeAddMember( &m_root[nodeIdxs[i]], eb->m_memIdx);
							eb->m_flags = KdtBox::PROCESSED;
						}

						el = el->GetNext( 0);
					}
				}
			}
		}
	}
}