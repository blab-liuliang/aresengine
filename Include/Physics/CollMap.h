//#pragma once
//
//#include "BvhTriangle3Mesh.h"
//#include "Physics/Accelerators/QuadTree.hpp"
//#include <map>
//
//using namespace std;
//using namespace boost;
//
//namespace Ares
//{
//	//------------------------------------------
//	// ��ײͼ 2011-06-29  ����
//	// ʹ���������
//	// �ص㣺
//	// 1. ��̬��
//	// 2. �޷�ȷ��֪����ײ������
//	//------------------------------------------
//	class CCollMap
//	{
//		typedef map< string, quad_tree_member<BvhTriangleMesh*>> TreeMemberMap;
//
//		// ��������,��¼��������Ϣ
//		struct SGridInfo
//		{
//			size_t  m_baseOffset;		// ��ƫ��
//			size_t  m_numTris;			// ����������
//
//			// ���캯��
//			SGridInfo()
//				: m_baseOffset(0), m_numTris(0)
//			{}
//		};
//
//	public:
//		// ����
//		void Load( const char* fileName);
//
//		// ��ѡ( Ĭ�ϼ�����1000��λ)
//		bool Pick( const Line3& line, float& dist, Vector3& _intersectPos) const;
//
//		// capsule ���
//		int  CheckCapsuleColl( const Capsule3& capsule, vector<SCapsuleCollInfo>& collInfo) const;
//
//		// obb���, ��ͼΪ����˳��// 0  1// 3  2
//		int CheckOBBColl( const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& dir, float& length, bool bCalcMin=true) const;
//
//	public:
//		// ��Ӽ�ģ
//		bool AddCollMesh( const char* uniqueName, BvhTriangleMesh* triMesh);
//
//		// ɾ����ģ
//		bool DeleteCollMesh( const char* uniqueName);
//
//	public:
//		// ���캯��
//		CCollMap();
//
//		// ��������
//		~CCollMap();
//
//		// ��ײͼ����( note:z������)
//		void Init( Vector3* pVerts, int numVerts, int* pTris, int numTris);
//
//		// ���ó�����С
//		void SetBoundingBox( const Rect3& boundingBox);
//
//		// ���ø߶�ͼ
//		void SetHeightField( const HeightField* heightField);
//
//		// ��ȡ����
//		bool  GetGridId( size_t x, size_t y, size_t& outId) const;
//
//		// ����
//		void Save( const char* fileName);
//
//	private:
//		size_t				m_numVerts;			// ������
//		int					m_numTris;			// ��������
//		Vector3*			m_verts;			// ����
//		Face*				m_tris;				// ������
//
//		size_t				m_width;			// ��
//		size_t				m_height;			// ��
//		Rect3				m_boundingBox;		// ��Χ��
//
//		size_t*				m_triIdxs;			// ����������			
//
//		SGridInfo*			m_gridInfos;		// ������Ϣ
//
//		const HeightField*   m_heightField;		// �߶�ͼ
//		QuadTree<BvhTriangleMesh*>*  m_quadTree;		// �Ĳ��� 
//		TreeMemberMap		  m_memberMap;		// ��Ա
//	};
//}