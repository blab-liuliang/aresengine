#include <algorithm>
#include <fstream>
#include "ConfigMgr.h"
#include <boost/lexical_cast.hpp>
#include <Core/3rdParty/RapidXml/rapidxml_utils.hpp>

using namespace boost;
using namespace rapidxml;

namespace Ares
{
	template<> ConfigMgr* Singleton<ConfigMgr>::m_singleton = new ConfigMgr;

	// ���캯��
	ConfigMgr::ConfigMgr()
	{
		m_fileName = "config\\scene_edit.xml";
	}

	// ��������
	ConfigMgr::~ConfigMgr()
	{

	}

	// ����
	void ConfigMgr::Load()
	{
		try
		{
			file<> fdoc( m_fileName.c_str());
			xml_document<>  doc;
			doc.parse<0>( fdoc.data());

			LoadRencentlyFiles( doc);

			LoadCameraSettings( doc);
		}
		catch ( ...)
		{

		}
	}

	// ����
	void ConfigMgr::Save()
	{
		list<string>  saveHelper;

		xml_document<>  doc; 
		xml_node<>* xmlNode  = doc.allocate_node(node_pi,doc.allocate_string("xml version='1.0' encoding='utf-8'"));
		xml_node<>* rootNode =  doc.allocate_node(node_element,"config");  

		doc.append_node( xmlNode);
		doc.append_node( rootNode);

		SaveRencentlyFiles( doc, rootNode);

		SaveCameraSettings( doc, rootNode, saveHelper);

		// д�ļ�
		std::ofstream out( m_fileName.c_str());
		//out << doc;
	}

	// ��ӵ��ļ��б�
	void ConfigMgr::AddToRecentlyFile( const char* fileName)
	{
		if( fileName)
		{
			// 1.���Ѵ������б� ����
			FileList::iterator it = std::find( m_recentlyFiles.begin(), m_recentlyFiles.end(), fileName);
			if( it != m_recentlyFiles.end())
			{
				m_recentlyFiles.erase( it);

				// ��֤����ļ���Ŀ������10
				while( m_recentlyFiles.size()>=10)
					m_recentlyFiles.pop_back();
			}

			m_recentlyFiles.push_front( fileName);
		}

		// �����ź�
		Signal_OnRencentFilesChanged( m_recentlyFiles);

		Save();
	}

	// �������������
	void ConfigMgr::SetCameraSettings( const CameraSettings& settings) 
	{ 
		if( std::memcmp( &m_cameraSettings, &settings, sizeof(CameraSettings)) != 0)
		{
			m_cameraSettings = settings;

			Signal_CameraSettingsChanged();

			Save();
		}
	}

	// ����������ļ��б�
	void ConfigMgr::LoadRencentlyFiles( xml_document<>& doc)
	{
		m_recentlyFiles.clear();

		// ���ڵ�, �������
		xml_node<>* pRootNode = doc.first_node("config");
		if( !pRootNode) return;

		xml_node<>* pRencentFilesNode = pRootNode->first_node( "rencent_files");
		if( !pRencentFilesNode) return;

		xml_node<>* pRencentFileNode  = pRencentFilesNode->first_node( "file");
		for ( ; pRencentFileNode ;pRencentFileNode=pRencentFileNode->next_sibling( "file"))
		{
			m_recentlyFiles.push_back( pRencentFileNode->first_attribute("path")->value());
		}

		// �����ź�
		Signal_OnRencentFilesChanged( m_recentlyFiles);
	}

	// ����������ļ��б�
	void ConfigMgr::SaveRencentlyFiles( xml_document<>& doc, xml_node<>* rootNode)
	{
		if( rootNode)
		{
			xml_node<>* rencentFilesNode = doc.allocate_node(node_element,"rencent_files");  
			rootNode->append_node( rencentFilesNode);

			for( FileList::iterator it=m_recentlyFiles.begin(); it!=m_recentlyFiles.end(); it++)
			{
				xml_node<>* tNode = doc.allocate_node(node_element, "file");
				xml_attribute<>* pAttribute = doc.allocate_attribute( "path", it->c_str());

				tNode->append_attribute(pAttribute);
				rencentFilesNode->append_node( tNode);
			}
		}
	}

	// �������������
	void ConfigMgr::LoadCameraSettings( xml_document<>& doc)
	{
		// ���ڵ�, �������
		xml_node<>* pRootNode = doc.first_node("config");
		if( !pRootNode)
			return;

		xml_node<>* pCameraSettingsNode = pRootNode->first_node( "camera_settings");
		if( pCameraSettingsNode)
		{
			m_cameraSettings.m_farPlane	= lexical_cast<float>(pCameraSettingsNode->first_attribute("far_plane")->value());
			m_cameraSettings.m_speed	= lexical_cast<float>(pCameraSettingsNode->first_attribute("speed")->value());

			// �����ź�
			Signal_CameraSettingsChanged();
		}
	}

	// �������������
	void ConfigMgr::SaveCameraSettings( xml_document<>& doc, xml_node<>* rootNode, list<string>& saveHelper)
	{
		if( rootNode)
		{
			xml_node<>* pCameraSettingsNode =  doc.allocate_node(node_element,"camera_settings");  
			rootNode->append_node( pCameraSettingsNode);
			if( pCameraSettingsNode)
			{
				saveHelper.push_back(lexical_cast<string>( m_cameraSettings.m_farPlane));
				xml_attribute<>* pFarPlaneAttribute = doc.allocate_attribute( "far_plane", saveHelper.back().c_str());

				saveHelper.push_back(lexical_cast<string>( m_cameraSettings.m_speed));
				xml_attribute<>* pSpeedAttribute = doc.allocate_attribute( "speed", saveHelper.back().c_str());

				pCameraSettingsNode->append_attribute( pFarPlaneAttribute);
				pCameraSettingsNode->append_attribute( pSpeedAttribute);
			}
		}
	}
}