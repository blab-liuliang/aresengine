#pragma once

#include <vector>
#include "IGame.h"
#include "IGameModifier.h"
#include "IGame_MtlKeeper.h"
#include "IGame_BoneKeeper.h"
#include <Core/AresMath.h>
#include <Physics/Shapes/Triangle3.h>
#include "M1Export.h"

using namespace std;
using namespace Ares;

namespace M1_IGame
{	
	// ��Ƥ��Ϣ
	struct SMeshInf
	{
		IGameNode*		m_pGameNode;
		IGameMesh*		m_pGameMesh;
		IGameSkin*      m_pGameSkin;

		// ���캯��
		SMeshInf()
		{
			memset( this, 0, sizeof( SMeshInf));
		}
	};

	// �������㸴�Ƽ���
	struct STexIndex
	{
		Point2        m_texCoord;	// UV ����ֵ
		int           m_iIndex;		// ��Ӧ����λ��

		STexIndex*    m_pNext;

		// ���캯��
		STexIndex( Point2& texCoord, int iIndex)
		{
			m_texCoord = texCoord;
			m_iIndex   = iIndex;

			m_pNext = NULL;
		}

		// ���New
		void  AddNew( Point2& texCoord, int iIndex)
		{
			STexIndex* pTexIndex = new STexIndex( texCoord, iIndex);

			// ��ӵ��б���
			pTexIndex->m_pNext = this->m_pNext;
			this->m_pNext = pTexIndex;
		}

		// ��ȡ����
		bool GetIndex( int& index, const Point2& texCoord)
		{
			STexIndex* pTexIndex = this;
			while ( pTexIndex)
			{
				if( pTexIndex->m_texCoord == texCoord)
				{
					index = pTexIndex->m_iIndex;
					return true;
				}

				pTexIndex = pTexIndex->m_pNext;
			}

			return false;
		}
	};

	//---------------------------------------
	// CMesh �������� ���� 2010-11-01 
	//---------------------------------------
	class CMesh
	{
	public:
		// ���캯��
		CMesh( IGameNode* pGameNode, CMtlKeeper* pMtlKeeper, CBoneKeeper* pBoneKeeper);

		// ��������
		void BuildData();

		// ������ײ����
		void BuildCollisionData( vector<SM1Vertex>& colVertexs, vector<SM1Face>& colFaces);

		// ����Mesh
		void BuildM1Mesh( IDCardMesh& mesh);

		// ��ȡMesh��Ϣ
		const SMeshInf* GetMeshInf() { return m_pMeshInf; }

		// �Ƿ����赼����ģ��
		bool IsBadMesh();

	private:
		// ������������
		void BuildM1MeshHeader(SM1MeshHeader& meshHeader);

		// ����mesh��������
		void BuildM1MeshMatter( IDCardMesh& mesh);

		// ����SubSet
		void BuildSubset();

		// ����λ������
		void BuildPos();

		// ����Ȩ������
		void BuildBoneInfluence();

		// ����UV����( ���ƶ���.�Բе�����)
		void BuildUV();

		// ��������
		void BuildNormal();

		// ���°�Χ��
		void BuildBoundingBox();

		// ������
		void AddFace(  FaceEx* pFace);

		// ��ȡ����ID
		int  GetBoneID( IGameNode* pGameNode);

	private:
		SMeshInf*					m_pMeshInf;
		vector<SM1Subset>			m_m1Subsets;		// �Ӽ� 
		vector<SM1Face>				m_m1Faces;			// ��ʱ����Ϣ
		vector<SM1Vertex>			m_m1Vertexs;		// ��ʱ����λ��
		vector<SM1BoneInfluence>    m_m1BoneInfluence;	// Ȩ����Ϣ
		vector<SM1TexCoord>			m_m1Texcoords;		// ��ʱ��������

		vector<SM1Normal>			m_m1Normals;		// ����
		vector<SM1Normal>			m_m1Tangent;		// ����
		vector<SM1Normal>			m_m1Binormal;		// ����

		vector<FaceEx*>             m_maxFaces;			// ������
		vector<int>					m_boneIdxs;			// ��������

		CMtlKeeper*					m_pMtlKeeper;		// ���ʹ�����
		CBoneKeeper*                m_pBoneKeeper;		// ����������
		float                       m_boundingBox[6];	// ��Χ��                    

	private:
		vector<STexIndex*>			m_pTexIndexs;		// ��������
		vector<int>					m_vertexIndexs;		// ��������(�ظ�����)
	};
}