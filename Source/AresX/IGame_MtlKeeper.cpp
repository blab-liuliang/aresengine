#include "IGame_MtlKeeper.h"
#include <string>
#include "AeConfig.h"

using namespace std;

extern Interface*   g_pI;

namespace M1_IGame
{
	extern SExportConfig  g_config;	// ��������

	// ��ȫ��·���в�ֳ�������,�ɸ��ĺ�׺��
	static string SplitNameExt( const char* fullPath, const char* aimExt)
	{
		// ȥ������·��
		char  fileName[128];
		char  fileExt[20];
		char  fileNameAndExt[148];

		_splitpath( fullPath, NULL, NULL, fileName, fileExt);

		if ( aimExt) sprintf( fileNameAndExt, "%s%s", fileName, aimExt);
		else		 sprintf( fileNameAndExt, "%s%s", fileName, fileExt);

		return fileNameAndExt;
	}

	// �����ļ���
	static string ChangeName( const char* source, const char* Name)
	{
		// ȥ������·��
		char  fileDiv[128];
		char  fileDir[2048];
		char  fileNew[2048];

		_splitpath( source, fileDiv, fileDir, NULL, NULL);

		sprintf( fileNew, "%s%s%s", fileDiv, fileDir, Name);

		return fileNew;
	}

	// ��ȡ����ID
	int CMtlKeeper::GetMtlID( IGameMaterial* pMtl)
	{
		if( pMtl)
		{
			size_t numMtls = m_mtlList.size();
			for ( size_t i=0; i<numMtls; i++)
			{
				if( m_mtlList[i] == pMtl) 
					return i;
			}

			m_mtlList.push_back( pMtl);
			return m_mtlList.size()-1;
		}

		return 0;
	}

	// ��������
	void CMtlKeeper::BuildMtls( CM1Material& M1)
	{
		M1.m_header.m_iId        = 20100925;
		M1.m_header.m_iVersion   = 15;
		M1.m_header.m_iNumMtls = m_mtlList.size();

		M1.m_pMtls = new SM1Material[M1.m_header.m_iNumMtls];
		for ( size_t i=0; i<M1.m_header.m_iNumMtls; i++)
		{
			IGameTextureMap* pTexMap = m_mtlList[i]->GetIGameTextureMap(0);
			if( pTexMap)
			{
				char* texName = pTexMap->GetBitmapFileName();
				char* texPath = g_pI->GetCurFilePath();
				string fileNameAndExt;
				string tFileNameExt = SplitNameExt( texName, NULL);

				fileNameAndExt = SplitNameExt( texName, NULL);

				if ( fileNameAndExt.length() < 68)
				{
					M1.m_pMtls[i].m_iTexNum = 1;

					M1.m_pMtls[i].m_pTextures = new SM1TexName[1];
					strcpy( M1.m_pMtls[i].m_pTextures[0].m_cName, fileNameAndExt.c_str());

					// Copy ����Ŀ¼��( ��ת����ʽ)
					if( g_config.m_bCopyTexture)
					{
						string tTexPath = ChangeName( texPath, tFileNameExt.c_str());

						string texConv;
						CopyTextureToTargetRoot( texConv, tTexPath.c_str(), fileNameAndExt.c_str());

						// ��ע���
						//string texConv;
						//HKEY rooKey = HKEY_CURRENT_USER;
						//HKEY tKey	= NULL;
						//if( ERROR_SUCCESS == RegOpenKeyExA( rooKey, "Software\\Ares\\ModelEditor", 0, KEY_READ, &tKey))
						//{
						//	// �ɹ���,��������
						//	char  tValue[1024];
						//	DWORD tLen = 1023;
						//	DWORD tKeyType = REG_SZ;
						//	RegQueryValueEx( tKey, "exePath", NULL, &tKeyType, (LPBYTE)tValue, &tLen);
						//	RegCloseKey( tKey);

						//	texConv = ChangeName( tValue, "texconv.exe");
						//}
						//else
						//{
							//::MessageBoxA( NULL, "��ע���ʧ��,�Ҳ��� texconv.exe, ����ת�������ʽΪdds", "AresX Warn", MB_OK);
						//}
					}
				}		
			}
		}

		// ����ͼƬת��Ŀ���ʽ
		//ConfigTransFormat();
	}

	// ��������Ŀ��·��
	void  CMtlKeeper::CopyTextureToTargetRoot( const string& texConv, const char* fileName, const char* aimName, const char* format/*=" DXT1 "*/)
	{
		// ����һ����ʱ���λ��
		//char tdrive[256];
		//_splitpath( g_config.m_m1Location.c_str(), tdrive, NULL, NULL, NULL);
		//string drive = string( tdrive)+"\\";

		// ��������ʱλ��, �������г����޷�����ո�·��
		//string tempLoc = ChangeName( drive.c_str(), aimName);
		//CopyFile( fileName, tempLoc.c_str(), FALSE);

		// ��ʽת��
		string targetPath = ChangeName( g_config.m_m1Location.c_str(), aimName);
		CopyFile( fileName, targetPath.c_str(), FALSE);
		//string tCmd = texConv + string(" -ft DDS -f ") + format + tempLoc + string(" -o ") + targetPath;
		//WinExec( tCmd.c_str(), SW_HIDE);

		// ɾ����ʱ�ļ�
		//Sleep( 1000);
		//remove( tempLoc.c_str());
	}

	// �����ļ�ת����ʽ
	bool CMtlKeeper::ConfigTransFormat()
	{
		return false;
	}
}