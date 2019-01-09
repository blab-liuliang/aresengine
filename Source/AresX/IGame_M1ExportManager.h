#pragma once

#include "IGame_MeshKeeper.h"

using namespace Ares;

namespace M1_IGame
{
	//--------------------------------------
	// M1��ʽ����������   ����  2010-11-01
	//--------------------------------------
	class CM1ExportManager
	{
	public:
		// ���캯��
		CM1ExportManager();

		// ����
		void  Build( SExportM1& M1);

	private:
		// ����M1�ļ�
		void BuildExportM1( SExportM1& M1);

		// ����M1
		void BuildM1( SExportM1& m1Export);

		// ����M1Header
		void BuildM1ModelHeader( CM1Model& M1);

	private:
		CMeshKeeper*  m_pMeshKeeper;		// ģ���б�
	};
}