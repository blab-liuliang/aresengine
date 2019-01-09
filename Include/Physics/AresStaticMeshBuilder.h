#pragma once

// ע����ͷ�ļ��ɲ����ⷢ��

#include "AresRecast.h"
#include "AresStaticNavMesh.h"

namespace Ares
{
	//------------------------------------------------------
	// ����������(�ɴ�������ݴ�С����32*32) 2011-02-22 ����
	//	   ������ģʽ
	//------------------------------------------------------
	class AI_API CStaticMeshBuilder
	{
	public:
		// ���캯��
		CStaticMeshBuilder();

		// ��������

		// ����
		bool HandleBuild( const SBuildParam& params);

	private:
		// ����
		void  CleanUp();

	public:
		bool                    m_bKeepInterResults;	// �Ƿ񱣴��ڲ�����
		SRcConfig				m_rcConfig;				// ����
		unsigned char*			m_pTriFlags;			// ���
		SRcHeightField*			m_pSolid;				//
		SRcCompactHeightField*	m_pCHF;					//
		SRcContourSet*          m_pCSet;
		RcPolyMesh*				m_pMesh;				// �����mesh
		SRcPolyMeshDetail*		m_pDMesh;				// ��ϸ�����mesh
	};
}