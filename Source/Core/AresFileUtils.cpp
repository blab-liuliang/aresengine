#include <boost/filesystem.hpp>
#include <Core/AresFileUtils.h>

namespace Ares
{
	// �滻��׺��
	void FileUtils::ReplaceExt( string& out, const string& source, const string& ext)
	{
		boost::filesystem::path filePath( source);

		out = filePath.replace_extension( ext).string();
	}

	// �����ļ���
	void FileUtils::ReplaceNameExt( string& out, const string& source, const string& nameExt)
	{
		boost::filesystem::path filePath(source);

		boost::filesystem::rename( filePath, nameExt);

		out = filePath.string();
	}

	// ��ȡ��׺��
	string FileUtils::GetExt( const string& source)
	{
		return boost::filesystem::path( source).extension().string();
	}

	// ��ȡ����
	string FileUtils::GetNameExt( const string& source)
	{
		return boost::filesystem::path( source).filename().string();
	}

	// ���캯��
	FileUtils::FileUtils()
		: m_rootPath( "")
	{
	}

	// ��������
	FileUtils::~FileUtils()
	{

	}

	// �����Ѱ·��
	void FileUtils::AddSearchPath( const char* path_)
	{
		string strPrefix;
		string path( path_);
		if( !IsAbsolutePath( path))
			strPrefix = m_rootPath;

		path = strPrefix + path;
		if( path.length()>0 && path[path.length()-1]!='/')
			path += "/";

		m_searchPaths.push_back( path);
	}

	// �ݹ������Ѱ·��
	void FileUtils::AddSearchPathRecursive( const char* path)
	{
		using namespace boost::filesystem;

		AddSearchPath( path);

		for( directory_iterator pos(path); pos!=directory_iterator(); pos++)
		{
			if( is_directory( *pos))
			{
				AddSearchPathRecursive( pos->path().string().c_str());
			}
		}
	}

	// ����ָ��Ŀ¼���ļ�
	void FileUtils::SearchFilesByExt( vector<string>& oFiles, const char* path, const char* ext)
	{
		using namespace boost::filesystem;
		for( directory_iterator pos(path); pos!=directory_iterator(); pos++)
		{
			string posPath = pos->path().string();

			if( is_directory( *pos))
			{
				SearchFilesByExt( oFiles, posPath.c_str(), ext);
			}
			else if( GetExt( posPath) == ext)
			{
				oFiles.push_back( posPath);
			}
		}
	}

	// ��ȡ����·��
	string FileUtils::FullPath( const char* fileName)
	{
		string strFileName = fileName;
		if( IsFileExist( strFileName))
			return strFileName;
		else
		{
			for ( size_t i=0; i<m_searchPaths.size(); i++)
			{
				string resPath = m_searchPaths[i] + strFileName;
				if( IsFileExist( resPath))
					return resPath;
			}
		}

		return "";
	}
    
    // ������·��
    void FileUtils::SetRootPath( const char* rootPath)
    {
        m_rootPath = rootPath;
        
        m_searchPaths.push_back( m_rootPath);
    }
    
	// ��ȡ��Դ����
	void FileUtils::ExtractFileData( vector<BYTE>& oData, const char* fileName)
	{

	}
}