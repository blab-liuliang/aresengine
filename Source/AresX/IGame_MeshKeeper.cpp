#include "AeConfig.h"
#include "IGame_MeshKeeper.h"

namespace M1_IGame
{
	extern SExportConfig g_config;				// ��������
	extern IGameScene *  g_pIGame;

	// ���캯��
	CMeshKeeper::CMeshKeeper()
	{
		m_pMtlKeeper  = new CMtlKeeper();
		m_pBoneKeeper = new CBoneKeeper();
	}

	// ��ʼ��
	void CMeshKeeper::Init()
	{
		Tab<IGameNode*> pMeshNodes = g_pIGame->GetIGameNodeByType( IGameObject::IGAME_MESH);

		for ( int i=0; i<pMeshNodes.Count(); i++)
		{
			// ���ؽ�㲻����
			if( pMeshNodes[i]->IsNodeHidden())
				continue;

			string tName = pMeshNodes[i]->GetName();
			if( tName.find( g_config.m_colTriFilter.c_str()) != string::npos)
			{
				// ����ײ��ģ;Ӧ���������ײ��ģ
				CMesh* pMesh = new CMesh( pMeshNodes[i], m_pMtlKeeper, m_pBoneKeeper);

				m_collMeshs.push_back( pMesh);
			}
			else if( pMeshNodes[i]->GetNodeMaterial())
			{
				CMesh* pMesh = new CMesh( pMeshNodes[i], m_pMtlKeeper, m_pBoneKeeper);

				m_pMeshs.push_back( pMesh);
			}
		}

		// ��ʼ��BoneKeeper
		InitBoneKeeper();

		// ��Ⱦ��ģ��
		for ( size_t i=0; i<m_pMeshs.size(); i++)
			m_pMeshs[i]->BuildData();

		// ��ײģ��
		m_colFaces.clear();
		m_colVertexs.clear();
		for ( size_t i=0; i<m_collMeshs.size(); i++)
			m_collMeshs[i]->BuildCollisionData( m_colVertexs, m_colFaces);

		// ������õ�ģ��
		for ( vector<CMesh*>::iterator it=m_pMeshs.begin(); it!=m_pMeshs.end(); )
		{
			if ((*it)->IsBadMesh())
				it = m_pMeshs.erase( it);
			else
				++it;
		}
	}

	// ��ʼ��BoneKeeper
	void CMeshKeeper::InitBoneKeeper()
	{
		vector<IGameSkin*> gameSkins;
		for ( size_t i=0; i<m_pMeshs.size(); i++)
		{
			IGameSkin* pGameSkin = m_pMeshs[i]->GetMeshInf()->m_pGameSkin;
			if ( pGameSkin)
			{
				gameSkins.push_back( pGameSkin);
			}
		}

		m_pBoneKeeper->Init( gameSkins);
	}

	// ������Χ��
	static void BuildBoundingBox( CM1Model& m1)
	{
		m1.m_header.m_boundingBox[0] = 1e30f;
		m1.m_header.m_boundingBox[1] = 1e30f;
		m1.m_header.m_boundingBox[2] = 1e30f;
		m1.m_header.m_boundingBox[3] = -1e30f;
		m1.m_header.m_boundingBox[4] = -1e30f;
		m1.m_header.m_boundingBox[5] = -1e30f;

		for ( size_t i=0; i<m1.m_header.m_iNumMeshes; i++)
		{
			m1.m_header.m_boundingBox[0] = min( m1.m_header.m_boundingBox[0], m1.m_pMeshes[i].m_Header.m_boundingBox[0]);
			m1.m_header.m_boundingBox[1] = min( m1.m_header.m_boundingBox[1], m1.m_pMeshes[i].m_Header.m_boundingBox[1]);
			m1.m_header.m_boundingBox[2] = min( m1.m_header.m_boundingBox[2], m1.m_pMeshes[i].m_Header.m_boundingBox[2]);

			m1.m_header.m_boundingBox[3] = max( m1.m_header.m_boundingBox[3], m1.m_pMeshes[i].m_Header.m_boundingBox[3]);
			m1.m_header.m_boundingBox[4] = max( m1.m_header.m_boundingBox[4], m1.m_pMeshes[i].m_Header.m_boundingBox[4]);
			m1.m_header.m_boundingBox[5] = max( m1.m_header.m_boundingBox[5], m1.m_pMeshes[i].m_Header.m_boundingBox[5]);
		}
	}

	// ����M1
	void  CMeshKeeper::BuildMeshs( SExportM1& M1)
	{
		M1.m_model.m_header.m_iNumMeshes = m_pMeshs.size();

		Box3 box;
		box.Init();

		M1.m_model.m_pMeshes = new IDCardMesh[m_pMeshs.size()];
		for ( size_t i=0; i<m_pMeshs.size(); i++)
		{
			m_pMeshs[i]->BuildM1Mesh( M1.m_model.m_pMeshes[i]);
		}

		// ����
		m_pBoneKeeper->BuildBoneStruct( M1.m_animation);

		// ����
		m_pMtlKeeper->BuildMtls( M1.m_material);

		// ��Χ��
		BuildBoundingBox( M1.m_model);

		// ��ײ��ģ
		if( g_config.m_exportTri)
			BuildCollisionTriMesh( M1.m_collidedTri);
	}

	// ������ײ��ģ
	void CMeshKeeper::BuildCollisionTriMesh(  CM1CollMesh& colliedMesh)
	{
		if( !m_collMeshs.size())
			return;

		if( !m_colFaces.size() || !m_colVertexs.size())
			return;

		colliedMesh.Reset();
		colliedMesh.m_numVerts = m_colVertexs.size();
		colliedMesh.m_numTris  = m_colFaces.size();
		colliedMesh.m_verts	   = new SM1Vertex[colliedMesh.m_numVerts];
		colliedMesh.m_faces	   = new SM1Face[colliedMesh.m_numTris];

		memcpy( colliedMesh.m_verts,  &m_colVertexs[0], sizeof( SM1Vertex) * colliedMesh.m_numVerts);
		memcpy( colliedMesh.m_faces,  &m_colFaces[0],   sizeof( SM1Face) * colliedMesh.m_numTris);
	}
}