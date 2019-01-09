//#include "Physics/Shapes/Algorithm/Intersect.h"
//#include "Physics/Shapes/Algorithm/IntrCapsule3Triangle3.h"
//#include "Physics/Shapes/Algorithm/IntrBox3Triangle3.h"
//#include <vector>
//#include <map>
//#include <set>
//#include <Core/AresMacros.h>
//#include <Core/AresThread.h>
//#include <Core/AresCriticalSection.h>
//#include <algorithm>
//#include <boost/timer.hpp>
//#include <Physics/Shapes/CollMap.h>
//
//using namespace std;
//
//namespace Ares
//{
//	// ���캯��
//	CCollMap::CCollMap()
//	{
//		m_numVerts = 0;	
//		m_numTris  = 0;
//		m_verts    = NULL;
//		m_tris     = NULL;
//
//		m_triIdxs  = NULL;
//		m_gridInfos= NULL;
//
//		m_heightField = NULL;
//		m_quadTree	  = NULL;
//	}
//
//	// ��������
//	CCollMap::~CCollMap()
//	{
//		SAFE_DELETE_ARRAY( m_verts);
//		SAFE_DELETE_ARRAY( m_tris);
//
//		SAFE_DELETE_ARRAY( m_triIdxs);
//		SAFE_DELETE_ARRAY( m_gridInfos);
//
//		SAFE_DELETE( m_quadTree);
//
//		for ( TreeMemberMap::iterator it = m_memberMap.begin(); it != m_memberMap.end(); it++)
//		{
//			BvhTriangleMesh* mesh = it->second.value;
//			SAFE_DELETE( mesh);
//		}
//
//		m_memberMap.clear();
//	}
//
//	// ���ó�����С
//	void CCollMap::SetBoundingBox( const Rect3& boundingBox)
//	{
//		m_boundingBox = boundingBox;
//
//		m_width  = (int)(m_boundingBox.GetXSize() + 0.999999f);
//		m_height = (int)(m_boundingBox.GetYSize() + 0.999999f);
//
//		SAFE_DELETE( m_quadTree);
//		m_quadTree = new_ QuadTree<BvhTriangleMesh*>;
//		m_quadTree->create( quad_tree_rect( m_boundingBox.x0, m_boundingBox.x1, m_boundingBox.y0, m_boundingBox.y1), 7);
//	}
//
//	// ��Ӽ�ģ
//	bool CCollMap::AddCollMesh(  const char* uniqueName, BvhTriangleMesh* triMesh)
//	{
//		quad_tree_member<BvhTriangleMesh*>& member = m_memberMap[uniqueName];
//
//		const Rect3& boundingBox = triMesh->GetBoundingBox();
//		quad_tree_rect rect;
//		rect.union_point( boundingBox.x0, boundingBox.y0);
//		rect.union_point( boundingBox.x1, boundingBox.y1);
//
//		member.value = triMesh;
//		member.key   = rect;
//
//		m_quadTree->add_member( &member);
//
//		return true;
//	}
//
//	// ɾ����ģ
//	bool CCollMap::DeleteCollMesh(  const char* uniqueName)
//	{
//		// ����
//		TreeMemberMap::iterator it = m_memberMap.find( uniqueName);
//		if( it != m_memberMap.end())
//		{
//			// ���Ĳ������޳�
//
//			// ɾ����Դ
//		}
//
//		return false;
//	}
//
//	// ��ײͼ����
//	void CCollMap::Init( Vector3* pVerts, int numVerts, int* pTris, int numTris)
//	{
//		timer tTimer;
//
//		if( !numVerts || !numTris)
//			return;
//
//		// ��������
//		SAFE_DELETE( m_verts);
//		SAFE_DELETE( m_tris);
//
//		m_numVerts = numVerts;
//		m_numTris  = numTris;
//
//		m_verts = new_ Vector3[numVerts];
//		m_tris  = new_ Face[numTris];
//
//		// ��������
//		std::memcpy( m_verts, pVerts, sizeof( Vector3) * numVerts);
//		std::memcpy( m_tris,  pTris,  sizeof( Face) * numTris);
//
//		size_t tGridNum = m_width * m_height;
//
//		// ����ÿһ��������
//		multimap<int, int> tGridTriIdxs;
//		#pragma omp parallel for
//		for ( int i=0; i<m_numTris; i++)
//		{
//			const Face& face = m_tris[i];
//			Rect2		tRect2;
//
//			// ��ȡ��Χ��
//			for ( int j=0; j<3; j++)
//			{
//				const Vector3& v = m_verts[face.m_idx[j]];
//
//				tRect2.UnionPoint( v[0], v[1]);
//			}
//
//			// �õ�Ӧ��¼����������
//			int minx = (int)(tRect2.x0 + 1e-5f);
//			int maxx = (int)(tRect2.x1 - 1e-5f);
//
//			int miny = (int)(tRect2.y0 + 1e-5f);
//			int maxy = (int)(tRect2.y1 - 1e-5f);
//
//			for ( int y=miny; y<=maxy; y++)
//			{
//				for ( int x=minx; x<=maxx; x++)
//				{
//					size_t index; 
//					if( GetGridId( x, y, index))
//					{
//						#pragma omp critical
//						tGridTriIdxs.insert( make_pair( index, i));
//					}
//				}
//			}
//		}
//
//		// ����
//		m_triIdxs   = new_ size_t[tGridTriIdxs.size()];
//		m_gridInfos	= new_ SGridInfo[tGridNum];
//		int	curIdx = 0, preGridIdx = -1;
//		for ( multimap<int, int>::iterator it=tGridTriIdxs.begin(); it!=tGridTriIdxs.end(); it++, curIdx++)
//		{
//			int curGridIdx = it->first;
//			if( curGridIdx != preGridIdx)
//				m_gridInfos[curGridIdx].m_baseOffset = curIdx;
//				
//			// ��������
//			m_triIdxs[curIdx] = it->second;
//			m_gridInfos[curGridIdx].m_numTris++;
//
//			preGridIdx = curGridIdx;
//		}
//
//		double elapsedTime = tTimer.elapsed();
//	}
//
//	// ���ø߶�ͼ
//	void CCollMap::SetHeightField( const HeightField* heightField) 
//	{ 
//		m_heightField = heightField;
//	}
//
//	// ��ȡ����
//	bool CCollMap::GetGridId( size_t x, size_t y, size_t& outId) const
//	{
//		if( x < m_width && y < m_height)
//		{
//			outId = x + y * m_width;
//
//			return true;
//		}
//
//		return false;
//	}
//
//	// capsule ���
//	int CCollMap::CheckCapsuleColl( const Capsule3& capsule, vector<SCapsuleCollInfo>& collInfo) const
//	{
//		collInfo.clear();
//		
//		WORD radius = (WORD)((capsule.m_radius+1.f) * (capsule.m_radius > 1.f ? capsule.m_radius : 1.f));
//
//		Rect3 boundingBox;
//		capsule.BuildAABB( boundingBox);
//
//		// ��ʱ����
//		SCapsuleCollInfo tCollInfo;
//
//		// �߶�ͼ
//		if( m_heightField)
//		{
//			// ����������
//			vector<Triangle3> terTriangles;
//
//			m_heightField->GetTriangle( terTriangles, boundingBox);
//
//			vector<Triangle3>::iterator end = terTriangles.end();
//			for( vector<Triangle3>::const_iterator it=terTriangles.begin(); it!=end; it++)
//			{
//				IntrCapsule3Triangle3 intrCT( capsule, *it);
//				if( intrCT.Test())
//				{
//					tCollInfo.m_triCollPoint = intrCT.m_intrPointTriangle;
//					tCollInfo.m_collNormal   = intrCT.m_intrPointTriangle - intrCT.m_intrPointCapsule;
//					tCollInfo.m_triNormal	 = it->GetNormal();
//
//					collInfo.push_back( tCollInfo);
//				}
//			}
//		}
//
//		// ��ײ��ģ
//		quad_tree_rect			 rect;
//		rect.union_point( boundingBox.x0, boundingBox.y0);
//		rect.union_point( boundingBox.x1, boundingBox.y1);
//		static vector<BvhTriangleMesh*> meshList;
//		meshList.clear();
//		if( m_quadTree->search( rect , meshList))
//		{
//			for ( size_t i=0; i<meshList.size(); i++)
//			{
//				meshList[i]->CheckCapsuleColl( capsule, collInfo);
//			}
//		}
//
//		return collInfo.size();
//	}
//
//	// ��ѡ
//	bool CCollMap::Pick(  const Line3& line, float& dist, Vector3& _intersectPos) const
//	{/*
//		// �����Ƿ񾭹�����
//		float tmin, tmax;
//		if( !Intersect( line, m_boundingBox, 0.f, dist, &tmin, &tmax))
//			return false;
//
//		Vector3 orig = line.m_orig + line.m_dir * (std::max)( 0.f, tmin);
//		Vector3 end  = line.m_orig + line.m_dir * (std::min)( dist,tmax);
//
//		// �߶ε���� �е�
//		orig = orig - m_boundingBox.GetMinPoint();
//		end  = end  - m_boundingBox.GetMinPoint();;
//
//		// ��ȡ
//		float x_y = line.m_dir.y / line.m_dir.x;
//		float y_x = line.m_dir.x / line.m_dir.y;
//
//		// �洢����ID
//		static set<size_t> tTriIds;
//		static vector<Triangle3> tHeightFieldTris;
//
//		if( abs( line.m_dir.x) > abs( line.m_dir.y))
//		{
//			// ��Y�ָ�
//			float by = max( orig.y, 0.f);
//				  by = min( by, m_height);
//			float ey = max( end.y, 0.f);
//				  ey = min( ey, m_height);
//
//			// ����
//			if( by > ey)
//			{
//				float ty = by; by = ey; ey = ty;
//			}
//
//			int iby = (int)( by + 1e-5f);
//			int iey = (int)( ey - 1e-5f);
//			for ( int y = iby; y<= iey; y++)
//			{
//				// x ���
//				float fby = clamp( (float)y, by, ey),
//					  fey = clamp( y + 1.f,  by ,ey);
//
//				float fbx = orig.x + y_x * ( fby - orig.y);
//				float fex = orig.x + y_x * ( fey - orig.y);
//
//				int ibx = (int)(std::min)( fbx, fex);
//				int iex = (int)(std::max)( fbx, fex);
//
//				for( int x=ibx; x<=iex; x++)
//				{
//					size_t id;
//					if( !GetGridId( x, y, id))
//						continue;
//
//					if( m_gridInfos)
//					{
//						// ���ģ��������
//						for( size_t g = 0; g<m_gridInfos[id].m_numTris; g++)
//						{
//							size_t triId = m_triIdxs[m_gridInfos[id].m_baseOffset+g];
//							if( tTriIds.find( triId) == tTriIds.end())
//								tTriIds.insert( triId);
//						}
//					}
//
//					// ��ӵ���������
//					if( m_heightField)
//						m_heightField->AddTri( tHeightFieldTris, x, y);
//				}
//			}
//		}
//		else
//		{
//			// ��X�ָ�
//			float bx = max( orig.x, 0.f);
//				  bx = min( bx, m_width);
//			float ex = max( end.x, 0.f);
//				  ex = min( ex, m_width);
//
//			// ����
//			if( bx > ex)
//			{
//				float tx = bx; bx = ex; ex = tx;
//			}
//
//
//			int ibx = (int)( bx + 1e-5f);
//			int iex = (int)( ex - 1e-5f);
//			for ( int x = ibx; x<= iex; x++)
//			{
//				// x ���
//				float fbx = clamp( (float)x, bx, ex),
//					  fex = clamp( x + 1.f,  bx ,ex);
//
//				float fby = orig.y + x_y * ( fbx - orig.x);
//				float fey = orig.y + x_y * ( fex - orig.x);
//
//				int iby = (int)(std::min)( fby, fey);
//				int iey = (int)(std::max)( fby, fey);
//
//				for( int y=iby; y<=iey; y++)
//				{
//					size_t id;
//					if( !GetGridId( x, y, id))
//						continue;
//
//					if( m_gridInfos)
//					{
//						// ģ��������
//						for( size_t g = 0; g<m_gridInfos[id].m_numTris; g++)
//						{
//							size_t triId = m_triIdxs[m_gridInfos[id].m_baseOffset+g];
//
//							if( tTriIds.find( triId) == tTriIds.end())
//								tTriIds.insert( triId);
//						}
//					}
//
//					// ��ӵ���������
//					if( m_heightField)
//						m_heightField->AddTri( tHeightFieldTris, x, y);
//				}
//			}
//		}
//
//		// �����е������ν����ж�
//		float distance = 1e30f;
//		for ( set<size_t>::const_iterator it = tTriIds.begin(); it!=tTriIds.end(); ++it)
//		{
//			// ��������������ײ
//			const Vector3& v0 = m_verts[m_tris[*it].m_idx[0]];
//			const Vector3& v1 = m_verts[m_tris[*it].m_idx[1]];
//			const Vector3& v2 = m_verts[m_tris[*it].m_idx[2]];
//		
//			Triangle3 tri( v0, v1, v2);
//			float tDist;
//			if( Intersect( line, tri, tDist))
//			{
//				if( tDist >= 0.f)
//					distance = (std::min)( distance, tDist);
//			}
//		}
//
//		// ����������
//		for ( vector<Triangle3>::const_iterator it=tHeightFieldTris.begin(); it!=tHeightFieldTris.end();++it)
//		{
//			float tDist;
//			if( Intersect( line, *it, tDist))
//			{
//				if( tDist >= 0.f)
//					distance = (std::min)( distance, tDist);
//			}
//		}
//
//		tTriIds.clear();
//		tHeightFieldTris.clear();
//
//		if( distance < 1e30f)
//		{
//			dist = distance;
//
//			_intersectPos = line.m_orig + line.m_dir * dist;
//
//			return true;
//		}
//		*/
//		return false;
//	}
//
//	// obb���, ��ͼΪ����˳��// 0  1 // 3  2
//	int CCollMap::CheckOBBColl( const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& dir, float& length, bool bCalcMin/*=true*/) const
//	{
//		int collNum = 0;
//
//		// ���������Χ��
//		Vector3  center = (v1 + v3 + dir * length) / 2.f,
//				 axis0  = (v0 - v3) / 2.f,
//				 axis1  = (v2 - v3) / 2.f,
//				 axis2  = dir;
//
//		axis2.Normalize();
//
//		float  extent0 = axis0.Length();
//		float  extent1 = axis1.Length();
//
//		axis0 /= extent0;
//		axis1 /= extent1;
//
//		Box3 tBox( center, axis0, axis1, axis2, extent0, extent1, length / 2.f);
//
//		Rect3 boundBox;
//		tBox.BuildAABB( boundBox);
//
//		// ����ǰ��ʼ��
//		if( !bCalcMin)
//			length = 0.f;
//
//		// ������ײ
//		if( m_heightField)
//		{
//			// ����������
//			vector<Triangle3> terTriangles;
//
//			m_heightField->GetTriangle( terTriangles, boundBox);
//
//			vector<Triangle3>::iterator end = terTriangles.end();
//			for( vector<Triangle3>::const_iterator it=terTriangles.begin(); it!=end; it++)
//			{
//				IntrBox3Triangle3 intrBT( tBox, *it);
//				if( intrBT.Test())
//				{
//					collNum++;
//					intrBT.Find();
//
//					for ( int i=0; i<intrBT.m_quantity; i++)
//					{
//						Vector3 proj = ( intrBT.m_akPoint[i] - v0);
//						float tLength = Vector3Dot( proj, axis2);
//
//						if( bCalcMin)
//							length = std::min<float>( length, tLength);
//						else
//							length = std::max<float>( length, tLength);
//					}
//				}
//			}
//		}
//
//		return collNum;
//	}
//
//	// ����
//	void CCollMap::Load( const char* fileName)
//	{
//
//	}
//
//	// ����
//	void CCollMap::Save( const char* fileName)
//	{
//
//	}
//}