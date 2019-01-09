//#pragma once
//
//#include <list>
//#include <string>
//#include <Core/AresSingleton.hpp>
//#include <Core/3rdParty/RapidXml/rapidxml.hpp>
//#include <boost/signals2/signal.hpp>
//
//using namespace std;
//using namespace rapidxml;
//using namespace boost::signals2;
//
//namespace Ares
//{
//	//-------------------------------------------
//	// Lightmass���ù����� 2012-4-11 ����
//	//-------------------------------------------
//	class ConfigMgr : public Singleton<ConfigMgr>
//	{
//	public:
//		typedef list<string> FileList;
//
//	public:
//		// ���캯��
//		ConfigMgr();
//
//		// ��������
//		~ConfigMgr();
//
//		// ����
//		void Load();
//
//		// ����
//		void Save();
//
//		// ��ӵ��ļ��б�
//		void AddToRecentlyFile( const char* fileName);
//
//		// ���ó���״̬
//		void SetProgramState( const char* pbrt, const char* img, int tabIdx);
//
//	private:
//		// ����������ļ��б�
//		void LoadRencentlyFiles( xml_document<>& doc);
//
//		// ����������ļ��б�
//		void SaveRencentlyFiles( xml_document<>& doc, xml_node<>* rootNode);
//
//		// �����ϴιر�ʱ״̬
//		void LoadProgramState( xml_document<>& doc);
//
//		// �������״̬
//		void SaveProgramState( xml_document<>& doc, xml_node<>* rootNode);
//
//	public:
//		// Recent files changed signals
//		signal<void( const FileList&)> Signal_OnRencentFilesChanged;
//
//		// Restore program state
//		signal<void( const char*, const char*, int)> Signal_OnRestoreState;
//
//	private:
//		string			m_fileName;			// �����ļ���
//
//		string			m_lastFileOpen;		// �ϴδ��ļ�
//		int				m_tabIdx;			// ����TabIdx
//		string			m_lastImgOpen;		// �ϴδ�ͼ��
//
//		FileList		m_recentlyFiles;	// ������ļ��б�(˳����)
//	};
//}