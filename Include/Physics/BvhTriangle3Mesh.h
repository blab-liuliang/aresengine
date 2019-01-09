//#pragma once
//
//#include "Line3.h"
//#include "Capsule3.h"
//#include "Box3.h"
//#include "Sphere3.h"
//#include "Triangle3.h"
//#include <string>
//#include <vector>
//#include <map>
//#include <set>
//
//using namespace std;
//
//namespace Ares
//{
//	// ��
//	struct Face
//	{
//		int m_idx[3];
//	};
//
//	// ��ײ��Ϣ
//	struct SCapsuleCollInfo
//	{
//		Vector3  m_triCollPoint;	// ��ײ��
//		Vector3  m_collNormal;		// ��ײ����,�������������Ϣ
//		Vector3  m_triNormal;		// �����η���
//	};
//	
//	//------------------------------------
//	// collmesh   2011-09-02 ����
//	//------------------------------------
//	class BvhTriangleMesh : public Shape
//	{
//	public:
//		// Header
//		struct SHeader
//		{
//			int				m_version;			// �ļ��汾
//			size_t			m_numVerts;			// ������
//			size_t			m_numTris;			// ��������
//			int				m_numGrids;			// ������
//			float			m_edgeLength;		// �߳���
//
//			int				m_dataSize;			// ���ݴ�С
//			int				m_vertsOffset;		// ��������ƫ��
//			int				m_trisOffset;		// ������ƫ��
//			int				m_triIdxsOffset;	// ����������ƫ��
//			int				m_gridDataOffset;	// ��������ƫ��
//
//			Rect3			m_boundingBox;		// ��Χ��
//		};
//
//		// ��������,��¼��������Ϣ
//		struct SGridInfo
//		{
//			char	m_id[64];			// ����ID
//			size_t  m_baseOffset;		// ��ƫ��
//			size_t  m_numTris;			// ����������
//		};
//
//	public:
//		// ���캯��
//		BvhTriangleMesh();
//
//		// ��������
//		~BvhTriangleMesh();
//
//		// constructor AABB bounding box
//		virtual void BuildAABB( Rect3& box, const RTTransform& trans) const;
//
//	public:
//		// ��������
//		bool Init( size_t numVertexs, Vector3* vertsData, size_t numTris, int* trisData, const Matrix44* matInit=NULL, float edgeLength=2.f);
//
//		// ���߼��( Ĭ�ϼ�����1000��λ)
//		bool Pick( const Line3& line, float& dist, Vector3* _intersectPos=NULL) const;
//
//		// ��Capsule������ײ���
//		int  CheckCapsuleColl( const Capsule3& capsule, vector<SCapsuleCollInfo>& outInfo);
//
//		// Interect with box3
//		bool CheckOBBColl( const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& dir, float& length, bool bCalcMin/*=true*/);
//
//	public:
//		// ��ȡ��Χ��
//		const Rect3& GetBoundingBox() const { return m_header.m_boundingBox; }
//
//	public:
//		// ����
//		bool Load( const char* fileName);
//
//		// ����
//		void Save( const char* fileName);
//
//		// ��������
//		void Reset();
//
//		// ������������֯������
//		Triangle3 GetTriangle( const Face* face) const;
//
//		// ��ȡ����
//		bool GetGridId( int x, int y, int z, string& outId) const;
//
//		// ��ȡ���Ӱ�Χ��
//		void GetGridSphere3( int x, int y, int z, Sphere3& sphere3);
//
//		// ��ȡAABB��Χ����������
//		size_t GetFace( set<const Face*>& out, set<const Face*>& without, const Rect3& boundingBox) const;
//
//		// ��ȡOBB�е�������
//		int GetFace( set<const Face*>& out, set<const Face*>& without, const Box3& box3);
//
//		// ����OBB
//		void BuildOBB( vector<Box3>& obbs, const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& dir, float length, float segmentLength);
//
//	private:
//		typedef map<string, SGridInfo*> GridInfo;
//
//		SHeader			m_header;		// �ļ�ͷ
//		unsigned char*	m_data;			// ����
//
//		Vector3*		m_verts;		// ����
//		Face*			m_tris;			// ������
//		size_t*			m_triIdxs;		// ����������
//		SGridInfo*		m_gridData;		// ��������
//
//		GridInfo        m_gridInfos;	// ��������,���ټ���
//	};
//}