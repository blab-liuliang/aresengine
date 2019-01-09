#include <Core/AresFileUtils.h>
#include <Windows.h>

namespace Ares
{
	//-------------------------------------
	// Win32FileUtils 2013-7-29 ����
	//-------------------------------------
	class FileUtilsWin32 : public FileUtils
	{
	public:
	};

	// �½�ʵ��
	FileUtils* FileUtils::Create( const char* rootPath/*=""*/)
	{
		char pszResourcePath[MAX_PATH] = { 0};
		if( !pszResourcePath[0])
		{
			WCHAR wszPath[MAX_PATH] = {0};
			int nNum = WideCharToMultiByte(CP_ACP, 0, wszPath, GetCurrentDirectoryW(sizeof(wszPath), wszPath), pszResourcePath, MAX_PATH, NULL, NULL);
			pszResourcePath[nNum] = '/';
		}

		string _rootPath = rootPath;
		if( !IsAbsolutePath( _rootPath))
		{
			_rootPath = pszResourcePath + _rootPath;
		}

		FileUtilsWin32* fileUtils = new FileUtilsWin32;
		fileUtils->SetRootPath( _rootPath.c_str());

		return fileUtils;
	}

	// ����ļ��Ƿ����
	bool FileUtils::IsFileExist( const string& strFilePath)
	{
		if( strFilePath.length()==0)
			return false;

		string strPath = strFilePath;
		//if( !IsAbsolutePath( strPath))
		//	strPath.insert( 0, m_);

		return GetFileAttributesA( strPath.c_str()) != -1 ? true : false;
	}

	// ����Ƿ�Ϊ����·��
	bool FileUtils::IsAbsolutePath( const string& strPath)
	{
		if( strPath.length()>2 && ( ( strPath[0]>='a'&& strPath[0]<='z') || ( strPath[0]>='A' && strPath[0]<='Z')) && strPath[1]==':')
			return true;

		return false;
	}
}