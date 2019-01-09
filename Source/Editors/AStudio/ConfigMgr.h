#pragma once

#include <list>
#include <string>
#include <Core/AresSingleton.hpp>
#include <Core/3rdParty/RapidXml/rapidxml.hpp>
#include <boost/signals2/signal.hpp>
#include "ConfigSettings.h"

using namespace std;
using namespace rapidxml;
using namespace boost::signals2;

namespace Ares
{
	//-------------------------------------------
	// Lightmass���ù����� 2012-4-11 ����
	//-------------------------------------------
	class ConfigMgr : public Singleton<ConfigMgr>
	{
	public:
		typedef list<string> FileList;

		ConfigMgr();
		~ConfigMgr();

	public:
		// ����
		void Load();

		// ����
		void Save();

		// ��ӵ��ļ��б�
		void AddToRecentlyFile( const char* fileName);

		// ��ȡ���������
		const CameraSettings& GetCameraSettings() const { return m_cameraSettings; }

		// �������������
		void SetCameraSettings( const CameraSettings& settings);

	private:
		// ����������ļ��б�
		void LoadRencentlyFiles( xml_document<>& doc);

		// ����������ļ��б�
		void SaveRencentlyFiles( xml_document<>& doc, xml_node<>* rootNode);

		// �������������
		void LoadCameraSettings( xml_document<>& doc);

		// �������������
		void SaveCameraSettings( xml_document<>& doc, xml_node<>* rootNode, list<string>& saveHelper);

	public:
		// Recent files changed signals
		signal<void( const FileList&)> Signal_OnRencentFilesChanged;

		// CameraSettings changed signals
		signal<void()> Signal_CameraSettingsChanged;

	private:
		string			m_fileName;			// �����ļ���

		FileList		m_recentlyFiles;	// ������ļ��б�(˳����)
		CameraSettings	m_cameraSettings;	// ���������
	};
}