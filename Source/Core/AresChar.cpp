#include <stdlib.h>
#include "Core/AresChar.h"
#include <Core/AresPlatform.h>

namespace Ares
{
	#pragma warning( disable : 4996)

	//------------------------------------------
	// fwrites  2010-07-20  ����
	//------------------------------------------
	void fwrites( const char* res, FILE* fileHandle)
	{
		if ( res)
		{
			SIZE_T length = strlen(res) + 1;
			fwrite( &length, 4, 1, fileHandle);
			fwrite( res, length, 1,fileHandle);
		}
		else
		{
			SIZE_T length = 0; 
			fwrite( &length, 4, 1, fileHandle);
		}
	}

	//----------------------------------------------
	// freads  2010-07-20  ����
	//----------------------------------------------
	// Ч��ԭ��ֻ�ܶ�ȡС��1024�ֽ��ַ���
	// Ч��ԭ��ʹ��string ����char* c = new char[]
	bool freads( string& _s, FILE* fileHandle)
	{
		int length = 0;
		fread( &length, 4, 1, fileHandle);

		if ( length)
		{
			char tchar[1024];
			fread( tchar, length, 1, fileHandle);
			_s = tchar;

			return true;
		}

		return false;
	}

	bool freads( char*& _s, FILE* fileHandle)
	{
		int length = 0;
		fread( &length, 4, 1, fileHandle);

		if ( length)
		{
			SAFE_DELETE_ARRAY( _s);
			 _s = new_ char[length];
			fread( _s, length, 1, fileHandle);

			return true;
		}

		return false;
	}

	// ����ַ���
	string splitNameExt( const char* fullPath, const char* aimExt/*=NULL*/)
	{
		// ȥ������·��
		char  fileName[128];
		char  fileExt[20];
		char  fileNameAndExt[148];

		_splitpath( fullPath, NULL, NULL, fileName, fileExt);

		if ( aimExt) std::sprintf( fileNameAndExt, "%s%s", fileName, aimExt);
		else		 std::sprintf( fileNameAndExt, "%s%s", fileName, fileExt);

		return fileNameAndExt;
	}

	// �����ļ���
	void changeNameExt( char* pdst, const char* source, const char* nameExt)
	{
		// ȥ������·��
		char  drv[256];
		char  dir[1024];
	
		_splitpath( source, drv, dir, NULL, NULL);

		sprintf( pdst, "%s%s%s", drv, dir, nameExt);
	}

	// ������׺��
	void changeExt( char* pdst, const char* source, const char* ext)
	{
		// ȥ������·��
		char  drv[256];
		char  dir[1024];
		char  name[1024];

		_splitpath( source, drv, dir, name, NULL);

		sprintf( pdst, "%s%s%s%s", drv, dir, name, ext);
	}
}