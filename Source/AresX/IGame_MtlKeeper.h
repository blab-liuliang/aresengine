#pragma once

#include <vector>
#include "IGame.h"
#include <Engine/RenderSystem/M1/M1Loader.h>

using namespace std;
using namespace Ares;

namespace M1_IGame
{
	//---------------------------------------------------
	// MaxScene ���ʹ��� MtlKeeper ���� 2010-10-29 16:08
	//---------------------------------------------------
	class CMtlKeeper
	{
	public:
		// ���캯��
		CMtlKeeper() {}

		// ��������
		void BuildMtls( CM1Material& M1);

		// ���
		void Clear();

		// ��ȡ����ID
		int GetMtlID( IGameMaterial* pMtl);

		// ����ID��ȡ����
		IGameMaterial*  GetMtl( size_t id);

		// ��ȡ��������
		size_t GetCount();

		// ��������Ŀ��·��
		void  CopyTextureToTargetRoot( const string& texConv, const char* fileName, const char* aimName, const char* format=" DXT1 ");

	private:
		// ��Ӳ���
		bool  AddMtl( IGameMaterial* pMtl);

		// �����ļ�ת����ʽ
		bool ConfigTransFormat();

	private:
		vector<IGameMaterial*>  m_mtlList;		// �����б�
	};
}