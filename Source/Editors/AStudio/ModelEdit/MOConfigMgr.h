#pragma once

#include <list>
#include <string>
#include <Core/AresSingleton.hpp>
#include <Core/3rdParty/RapidXml/rapidxml.hpp>
#include <boost/signals2/signal.hpp>

using namespace std;
using namespace rapidxml;
using namespace boost::signals2;

namespace Ares
{
	//-------------------------------------------
	// Lightmass���ù����� 2012-4-11 ����
	//-------------------------------------------
	class MOConfigMgr : public Singleton<MOConfigMgr>
	{
	public:
		typedef list<string> FileList;

		MOConfigMgr();
		~MOConfigMgr();

	public:
		// ����
		void Load();

		// ����
		void Save();

		// ��ӵ��ļ��б�
		void AddToRecentlyFile( const char* fileName);

		// �������������
		void AddToResDirectorys( const char* resDir);

	private:
		// ����������ļ��б�
		void LoadRencentlyFiles( xml_document<>& doc);

		// ����������ļ��б�
		void SaveRencentlyFiles( xml_document<>& doc, xml_node<>* rootNode);

		// �������������
		void LoadResDirectory(  xml_document<>& doc);

	public:
		// Recent files changed signals
		signal<void( const FileList&)> Signal_OnRencentFilesChanged;

		// CameraSettings changed signals
		signal<void( const FileList&)> Signal_ResDirectorysChanged;

	private:
		string			m_fileName;			// �����ļ���

		FileList		m_recentlyFiles;	// ������ļ��б�(˳����)
		FileList		m_resDirectorys;	// ��ԴĿ¼
	};
}