#include "IGame.h"
#include "Init.h"
#include "AeConfig.h"
#include "Function.h"
#include "IGame_M1ExportManager.h"

namespace M1_IGame
{
	extern SExportConfig	  g_config;				// ��������

	// ���캯��
	CM1ExportManager::CM1ExportManager()
	{
		InitScene();

		m_pMeshKeeper = new CMeshKeeper();
	}

	// ����
	void CM1ExportManager::Build( SExportM1& M1)
	{
		// ��ʼ����ʱ����
		m_pMeshKeeper->Init();

		BuildExportM1( M1);
	}

	// ����M1�ļ�
	void CM1ExportManager::BuildExportM1( SExportM1& M1)
	{
		// ͷ
		BuildM1ModelHeader( M1.m_model);

		// ģ��
		m_pMeshKeeper->BuildMeshs( M1);

		// M1��ϸ����
		BuildM1( M1);
	}

	// ����M1
	void CM1ExportManager::BuildM1( SExportM1& m1Export)
	{
		SM1Header& m1Header = m1Export.m_m1.m_header;

		// ����m1
		char modelNameExt[1024];
		char materialNameExt[1024];
		char animationNameExt[1024];

		NameExt( modelNameExt,    g_config.m_modLocation.c_str());
		NameExt( materialNameExt, g_config.m_matLocation.c_str());
		NameExt( animationNameExt,g_config.m_aniLocation.c_str());

		// tomorrow here!!!
		if( m1Export.m_animation.m_header.m_iNumBones)
			strcpy( m1Header.m_animationPath, animationNameExt);

		// ����subset����

		m1Header.m_sqrNum = m1Export.m_model.GetTotalSubsets();
		m1Header.m_sqr = new SSQRenderable[m1Header.m_sqrNum];

		assert( m1Header.m_sqr);

		int renderIdx = 0;
		for ( size_t i=0; i<m1Export.m_model.m_header.m_iNumMeshes; i++)
		{
			const IDCardMesh& tM1Mesh = m1Export.m_model.m_pMeshes[i];
			for( int j=0; j< tM1Mesh.m_Header.m_iSubsetNum; j++)
			{
				SSQRenderable& tRenderable = m1Header.m_sqr[renderIdx];
				strcpy( tRenderable.m_searchName, "main");
				strcpy( tRenderable.m_queueName,  "opacity");
				strcpy( tRenderable.m_materialPath, materialNameExt);
				tRenderable.m_materialIdx = tM1Mesh.m_pSubsets[j].m_iMtlIndex;
				strcpy( tRenderable.m_modelPath, modelNameExt);
				tRenderable.m_meshIdx     = i;
				tRenderable.m_subsetIdx	  = j;

				renderIdx++;
			}
		}
	}

	// ����M1Header
	void CM1ExportManager::BuildM1ModelHeader( CM1Model& M1)
	{
		SM1ModelHeader&  M1Header = M1.m_header;

		// ��ʼ��ID 2010��9��25��
		M1Header.m_iId        = 20100925;
		M1Header.m_iVersion   = 15;

		M1Header.m_iNumTags   = 0;
		M1Header.m_iTagStart  = 0;
		M1Header.m_iTagEnd    = 0;
		M1Header.m_iFileSize  = 0;							// Fuck 

		M1Header.m_formats	  = SM1ModelFormat();
	}
}