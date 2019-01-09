#pragma once

#include <vector>
#include "IGame.h"
#include "IGame_Mesh.h"
#include "IGame_MtlKeeper.h"
#include "IGame_BoneKeeper.h"
#include "AeConfig.h"
#include "M1Export.h"

using namespace std;
using namespace Ares;

namespace M1_IGame
{
	//----------------------------------------------------
	// MaxScene Mesh���� MeshKeeper ���� 2010-11-01 11:53
	//----------------------------------------------------
	class CMeshKeeper
	{
	public:
		// ���캯��
		CMeshKeeper();

		// ��ʼ��
		void  Init();

		// ����M1
		void  BuildMeshs( SExportM1& M1);

	private:
		// ��ʼ��BoneKeeper
		void InitBoneKeeper();

		// ������ײ��ģ
		void BuildCollisionTriMesh( CM1CollMesh& colliedMesh);

	private:
		vector<CMesh*>    m_pMeshs;				// ��ʱģ��
		vector<CMesh*>	  m_collMeshs;			// ��ײ��ģ
		CMtlKeeper*		  m_pMtlKeeper;			// ����
		CBoneKeeper*      m_pBoneKeeper;		// ����

		vector<SM1Face>	  m_colFaces;			// ��ײ����Ϣ
		vector<SM1Vertex> m_colVertexs;			// ��ײλ����Ϣ
	};
}