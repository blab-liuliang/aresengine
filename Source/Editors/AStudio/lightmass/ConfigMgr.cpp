//#include <algorithm>
//#include "ConfigMgr.h"
//#include <boost/lexical_cast.hpp>
//#include <Core/3rdParty/RapidXml/rapidxml_utils.hpp>
//#include <Core/3rdParty/RapidXml/rapidxml_print.hpp>
//
//using namespace boost;
//
//namespace Ares
//{
//	template<> ConfigMgr* Singleton<ConfigMgr>::m_singleton = new ConfigMgr;
//
//	// ���캯��
//	ConfigMgr::ConfigMgr()
//		: m_tabIdx( 0)
//	{
//		m_fileName = "config\\lightmass.xml";
//	}
//
//	// ��������
//	ConfigMgr::~ConfigMgr()
//	{
//
//	}
//
//	// ����
//	void ConfigMgr::Load()
//	{
//		try
//		{
//			file<> fdoc( m_fileName.c_str());
//			xml_document<>  doc;
//			doc.parse<0>( fdoc.data());
//
//			LoadRencentlyFiles( doc);
//
//			LoadProgramState( doc);
//		}
//		catch ( ...)
//		{
//
//		}
//	}
//
//	// ����
//	void ConfigMgr::Save()
//	{
//		xml_document<>  doc;
//		xml_node<>* xmlNode  = doc.allocate_node(rapidxml::node_pi,doc.allocate_string("xml version='1.0' encoding='utf-8'"));
//		xml_node<>* rootNode =  doc.allocate_node(node_element,"config");  
//				
//		doc.append_node( xmlNode);
//		doc.append_node( rootNode);
//
//		SaveRencentlyFiles( doc, rootNode);
//
//		SaveProgramState( doc, rootNode);
//
//		// д�ļ�
//		std::ofstream out( m_fileName.c_str());
//		out << doc;
//	}
//
//	// ��ӵ��ļ��б�
//	void ConfigMgr::AddToRecentlyFile( const char* fileName)
//	{
//		if( fileName)
//		{
//			// 1.���Ѵ������б� ����
//			FileList::iterator it = std::find( m_recentlyFiles.begin(), m_recentlyFiles.end(), fileName);
//			if( it != m_recentlyFiles.end())
//			{
//				m_recentlyFiles.erase( it);
//
//				// ��֤����ļ���Ŀ������10
//				while( m_recentlyFiles.size()>=10)
//					m_recentlyFiles.pop_back();
//			}
//
//			m_recentlyFiles.push_front( fileName);
//		}
//
//		// �����ź�
//		Signal_OnRencentFilesChanged( m_recentlyFiles);
//
//		Save();
//	}
//
//	// ����������ļ��б�
//	void ConfigMgr::LoadRencentlyFiles( xml_document<>& doc)
//	{
//		m_recentlyFiles.clear();
//
//		// ���ڵ�, �������
//		xml_node<>* pRootNode		  = doc.first_node("config");
//		xml_node<>* pRencentFilesNode = pRootNode->first_node( "rencent_files");
//		xml_node<>* pRencentFileNode  = pRencentFilesNode->first_node( "file");
//		for ( ; pRencentFileNode ;pRencentFileNode=pRencentFileNode->next_sibling( "file"))
//		{
//			m_recentlyFiles.push_back( pRencentFileNode->first_attribute("path")->value());
//		}
//
//		// �����ź�
//		Signal_OnRencentFilesChanged( m_recentlyFiles);
//	}
//
//	// ����������ļ��б�
//	void ConfigMgr::SaveRencentlyFiles( xml_document<>& doc, xml_node<>* rootNode)
//	{
//		if( rootNode)
//		{
//			xml_node<>* rencentFilesNode =  doc.allocate_node(node_element,"rencent_files");  
//			rootNode->append_node( rencentFilesNode);
//
//			for( FileList::iterator it=m_recentlyFiles.begin(); it!=m_recentlyFiles.end(); it++)
//			{
//				xml_node<>* tNode = doc.allocate_node(node_element, "file");
//				xml_attribute<>* pAttribute = doc.allocate_attribute( "path", it->c_str());
//
//				tNode->append_attribute(pAttribute);
//				rencentFilesNode->append_node( tNode);
//			}
//		}
//	}
//
//	// ���ó���״̬
//	void ConfigMgr::SetProgramState( const char* pbrt, const char* img, int tabIdx)
//	{
//		m_lastFileOpen = pbrt;
//		m_lastImgOpen  = img;
//		m_tabIdx	   = tabIdx;
//	}
//
//	// �����ϴιر�ʱ״̬
//	void ConfigMgr::LoadProgramState( xml_document<>& doc)
//	{
//		m_recentlyFiles.clear();
//
//		// ���ڵ�, �������
//		xml_node<>* pRootNode		  = doc.first_node("config");
//		xml_node<>* stateNode = pRootNode->first_node( "program_states");
//
//		try
//		{
//			if( stateNode)
//			{
//				m_lastFileOpen = stateNode->first_attribute("pbrt_open")->value();
//				m_lastImgOpen  = stateNode->first_attribute("img_open")->value();
//				m_tabIdx       = lexical_cast<int>(stateNode->first_attribute("tab_index")->value());
//			}
//		}
//		catch(...)
//		{
//			int a = 10;
//		}
//
//		// �����ź�
//		Signal_OnRestoreState( m_lastFileOpen.c_str(), m_lastImgOpen.c_str(), m_tabIdx);
//	}
//
//	// �������״̬
//	void ConfigMgr::SaveProgramState( xml_document<>& doc, xml_node<>* rootNode)
//	{
//		if( rootNode)
//		{
//			xml_node<>* stateNode =  doc.allocate_node(node_element,"program_states");  
//			rootNode->append_node( stateNode);
//
//			try
//			{
//				// ����
//				xml_attribute<>* pAttributeFileOpen = doc.allocate_attribute( "pbrt_open", m_lastFileOpen.c_str());
//				xml_attribute<>* pAttributeImgOpen  = doc.allocate_attribute( "img_open",  m_lastImgOpen.c_str());
//				xml_attribute<>* pAttributeTabIdx   = doc.allocate_attribute( "tab_index", lexical_cast<string>(m_tabIdx).c_str());
//				stateNode->append_attribute(pAttributeFileOpen);
//				stateNode->append_attribute(pAttributeImgOpen);
//				stateNode->append_attribute(pAttributeTabIdx);
//			}
//			catch(...)
//			{
//				int a= 10;
//			}
//		}
//	}
//}