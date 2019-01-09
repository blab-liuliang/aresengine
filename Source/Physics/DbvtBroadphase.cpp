#include "Physics/DbvtBroadphase.h"

namespace Ares
{
	// ���캯��
	DbvtBroadphase::DbvtBroadphase()
		: m_paircache( NULL)
	{

	}

	// ��������
	DbvtBroadphase::~DbvtBroadphase()
	{

	}

	// ��������
	BroadphaseProxy* DbvtBroadphase::CreateProxy( const Rect3& aabb, int shapeType, void* userPtr, UINT collisionFilterGroup, UINT collisionFilterMask, void* multiSapProxy)
	{ 
		DbvtBroadphaseProxy* broadphaseProxy = new_ DbvtBroadphaseProxy( aabb, userPtr, collisionFilterGroup, collisionFilterMask);
		
		broadphaseProxy->m_leaf = m_dbvt.Insert( aabb, broadphaseProxy);

		return broadphaseProxy;
	}

	// ɾ������
	void DbvtBroadphase::DestroyProxy( BroadphaseProxy* proxy)
	{
		DbvtBroadphaseProxy* dbvtPorxy = (DbvtBroadphaseProxy*)( proxy);

		m_dbvt.Remove( dbvtPorxy->m_leaf);

		SAFE_DELETE( proxy);
	}

	// ���ø��������Χ��
	void DbvtBroadphase::SetAABB( BroadphaseProxy* proxy, const Rect3& aabb)
	{
		DbvtBroadphaseProxy* dbvtProxy = (DbvtBroadphaseProxy*)proxy;
		//dbvtProxy->m_aabb = aabb;

		m_dbvt.Update( dbvtProxy->m_leaf, aabb);
	}

	// ��������
	bool DbvtBroadphase::ShapeIntersectionTest( const Shape* shape, vector<BroadphaseProxy*>& result)
	{
		vector<DbvtBroadphaseProxy*> dbvtProxys;
		m_dbvt.ShapeIntersectionTest( m_dbvt.GetRoot(), shape, dbvtProxys);

		result.resize( dbvtProxys.size());
		for( size_t i=0; i<dbvtProxys.size(); i++)
			result[i] = dbvtProxys[i];

		return result.size()>0;
	}
}