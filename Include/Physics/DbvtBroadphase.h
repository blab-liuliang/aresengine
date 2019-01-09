#pragma once

#include "Dbvt.h"
#include "Broadphase.h"

namespace Ares
{
	// DbvtProxy
	struct DbvtBroadphaseProxy : BroadphaseProxy
	{
		DbvtNode<DbvtBroadphaseProxy*>*	m_leaf;

		// ���캯��
		DbvtBroadphaseProxy( const Rect3& aabb, void* userPtr, UINT collisionFilterGroup, UINT collisionFilterMask)
			: BroadphaseProxy( aabb, userPtr, collisionFilterGroup, collisionFilterMask)
		{}
	};

	//--------------------------------------
	// DefaultBroadphase 2012-11-19 ����
	//--------------------------------------
	class DbvtBroadphase : public Broadphase
	{
	public:
		// ����
		enum
		{
			Dynamic_Set = 0,	// Dynamic set index
			Fixed_Set,			// Fixed set index
		};

	public:
		DbvtBroadphase();
		virtual ~DbvtBroadphase();

		// ��������
		virtual BroadphaseProxy* CreateProxy( const Rect3& aabb, int shapeType, void* userPtr, UINT collisionFilterGroup, UINT collisionFilterMask, void* multiSapProxy);

		// ɾ������
		virtual void DestroyProxy( BroadphaseProxy* proxy);

		// ���ø��������Χ��
		virtual void SetAABB( BroadphaseProxy* proxy, const Rect3& aabb);

		// ��������
		virtual bool ShapeIntersectionTest( const Shape* shape, vector<BroadphaseProxy*>& result);

		// ��ȡ�ص����ζ�
		virtual OverlappingPairCache* GetOverlappingPairCache(){ return m_paircache; }

	private:
		Dbvt<DbvtBroadphaseProxy*>		m_dbvt;			// Dynamics bounding volume tree
		OverlappingPairCache*			m_paircache;	// Pair cache
	};
}