#include "resource.h"
#include "AeUtilityUI.h"
#include <Windows.h>
#include <string>
#include "AeConfig.h"
#include "IGame_M1ExportManager.h"
#include "IGame_AnimationManager.h"

using namespace std;
using namespace Ares;

extern Interface*   g_pI;

namespace M1_IGame
{
	extern SExportConfig	  g_config;				// ��������

	// Dummy function for progress bar
	DWORD WINAPI DProcessBar(LPVOID arg)
	{
		return(0);
	}

	// �����ļ���
	static string ChangeExt( const char* source, const char* ext)
	{
		// ȥ������·��
		char  fileDrive[20];
		char  fileDir[2048];
		char  fileName[256];
		char  fileNew[2048];

		_splitpath( source, fileDrive, fileDir, fileName, NULL);

		sprintf( fileNew, "%s%s%s%s", fileDrive, fileDir, fileName, ext);

		return fileNew;
	}

	// ���캯��
	CAeUtilityUI::CAeUtilityUI()
	{
	}

	// ��ʼ��
	void CAeUtilityUI::InitGeneralPanel( HWND hwnd)
	{
		m_panelGeneral = hwnd;

		CheckDlgButton( hwnd, IDC_CHECK1, g_config.m_exportM1);
		CheckDlgButton( hwnd, IDC_CHECK2, g_config.m_exportMod);
		CheckDlgButton( hwnd, IDC_CHECK3, g_config.m_exportMat);
		CheckDlgButton( hwnd, IDC_CHECK4, g_config.m_exportAni);
		CheckDlgButton( hwnd, IDC_CHECK5, g_config.m_exportTri);

		// m1
		SetWindowText( GetDlgItem( hwnd, IDC_EDIT2), g_config.m_m1Location.c_str());

		// model
		SetWindowText( GetDlgItem( hwnd, IDC_EDIT5), g_config.m_modLocation.c_str());

		// material
		SetWindowText( GetDlgItem( hwnd, IDC_EDIT3), g_config.m_matLocation.c_str());

		// animation
		SetWindowText( GetDlgItem( hwnd, IDC_EDIT4), g_config.m_aniLocation.c_str());

		// collided triangle
		SetWindowText( GetDlgItem( hwnd, IDC_EDIT8), g_config.m_triLocation.c_str());
	}

	// ѡ�񵼳�·��
	void CAeUtilityUI::SetExportDir(HWND hwnd)
	{
		OPENFILENAME ofn;
		memset(&ofn, 0, sizeof(OPENFILENAME));

		char filename[MAX_PATH] = "";
		ofn.lpstrFile		= filename;
		ofn.nMaxFile		= MAX_PATH;

		ofn.lpstrFilter		= "�����ļ�(*.m1)\0*.m1;";
		ofn.lpstrTitle		= ("����m1");
		ofn.Flags			= OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
		ofn.lStructSize		= sizeof(OPENFILENAME);

		if( GetSaveFileName( &ofn))
		{	
			g_config.m_m1Location  = ChangeExt( filename, ".m1");
			g_config.m_modLocation = ChangeExt( filename, ".mod");
			g_config.m_matLocation = ChangeExt( filename, ".mat");
			g_config.m_aniLocation = ChangeExt( filename, ".ani");
			g_config.m_triLocation = ChangeExt( filename, ".tri");

			// m1
			SetWindowText( GetDlgItem( hwnd, IDC_EDIT2), g_config.m_m1Location.c_str());

			// model
			SetWindowText( GetDlgItem( hwnd, IDC_EDIT5), g_config.m_modLocation.c_str());

			// material
			SetWindowText( GetDlgItem( hwnd, IDC_EDIT3), g_config.m_matLocation.c_str());

			// animation
			SetWindowText( GetDlgItem( hwnd, IDC_EDIT4), g_config.m_aniLocation.c_str());

			// collided triangle
			SetWindowText( GetDlgItem( hwnd, IDC_EDIT8), g_config.m_triLocation.c_str());

			// ���¶�����ʾ
			UpdateAnimationPanelShow();
		}
	}

	// ִ�г��浼��
	void CAeUtilityUI::DoExport()
	{
		// start the progress bar
		g_pI->ProgressStart( "AresEngine", TRUE, DProcessBar, NULL);

		// update config
		UpdateConfig();

		SExportM1	      m1Export;
		CM1ExportManager  m1ExportManager;	

		m1ExportManager.Build( m1Export);
		m1Export.Save();

		UpdateAnimationPanelShow();

		g_pI->ProgressEnd();
	}

	// Ԥ��ģ��
	void CAeUtilityUI::PreViewModel()
	{
		if( !g_config.m_m1Location.empty())
		{
			// ��ע���
			HKEY rooKey = HKEY_CURRENT_USER;
			HKEY tKey	= NULL;
			if( ERROR_SUCCESS == RegOpenKeyExA( rooKey, "Software\\Ares\\ModelEditor", 0, KEY_READ, &tKey))
			{
				// �ɹ���,��������
				char  tValue[1024];
				DWORD tLen = 1023;
				DWORD tKeyType = REG_SZ;
				RegQueryValueEx( tKey, "exePath", NULL, &tKeyType, (LPBYTE)tValue, &tLen);
				RegCloseKey( tKey);

				string tCmd = tValue + string(" ") + g_config.m_m1Location;
				WinExec( tCmd.c_str(), SW_NORMAL);
			}
		}
	}

	// ��ʼ��
	void CAeUtilityUI::InitModelPanel( HWND hwnd)
	{
		m_panelModel = hwnd;

		// ����
		SetWindowText( GetDlgItem( hwnd, IDC_EDIT1), g_config.m_colTriFilter.c_str());
	}

	// ��ʼ��
	void CAeUtilityUI::InitMaterialPanel( HWND hwnd)
	{
		CheckDlgButton( hwnd, IDC_CHECK1, g_config.m_bCopyTexture);
	}

	// ��ʼ��
	void CAeUtilityUI::InitAnimationPanel( HWND hwnd)
	{
		m_panelAnimation = hwnd;

		UpdateAnimationPanelShow();
	}

	// ��������
	void CAeUtilityUI::UpdateConfig()
	{
		// ��������
		g_config.m_exportM1  = GetCheckBox( m_panelGeneral, IDC_CHECK1);
		g_config.m_exportMod = GetCheckBox( m_panelGeneral, IDC_CHECK2);
		g_config.m_exportMat = GetCheckBox( m_panelGeneral, IDC_CHECK3);
		g_config.m_exportAni = GetCheckBox( m_panelGeneral, IDC_CHECK4);
		g_config.m_exportTri = GetCheckBox( m_panelGeneral, IDC_CHECK5);

		g_config.m_keyFrame  = GetCheckBox( m_panelAnimation, IDC_CHECK3);

		char tTriFilter[512];
		GetWindowText( GetDlgItem( m_panelModel, IDC_EDIT1), tTriFilter, 512);
		g_config.m_colTriFilter = tTriFilter;
	}

	// ���½�����ʾ
	void CAeUtilityUI::UpdateAnimationPanelShow()
	{
		// ��ʾ����or�����ؼ�֡
		CheckDlgButton( m_panelAnimation, IDC_CHECK3, g_config.m_keyFrame);

		// ����Ƶ��
		char tSampleDensity[256];
		itoa( g_config.m_sampledensity, tSampleDensity, 255);
		SetWindowText( GetDlgItem( m_panelAnimation, IDC_EDIT3), tSampleDensity);

		if( g_config.m_aniLocation.empty())
			return;

		// Empty animations list.
		HWND aniList = GetDlgItem( m_panelAnimation, IDC_LISTANI);
		SendMessage( aniList, LB_RESETCONTENT, 0, 0 );

		CM1Animation m1Animation;

		// Fill the animations list.
		if( m1Animation.Load( g_config.m_aniLocation.c_str()))
		{
			// ��ʾ���ж��������б�
			for ( size_t i=0; i<m1Animation.m_header.m_iNumAnimationSet; i++)
			{
				const SM1AnimationSet& tAniSet = m1Animation.m_pAnimationSets[i];

				SendMessage( aniList, LB_INSERTSTRING, i, (LPARAM)tAniSet.m_header.m_cName );
			}
		}
	}

	// ��Ӷ���
	void CAeUtilityUI::AddAnimation( HWND hwnd)
	{
		if( g_config.m_aniLocation.empty())
			return;

		UpdateConfig();

		CM1Animation m1Animation;

		if( m1Animation.Load( g_config.m_aniLocation.c_str()))
		{
			// name, begin end
			char name[1024];
			char begin[256];
			char end[256];

			GetWindowText( GetDlgItem( hwnd, IDC_EDIT1), name, 1024);
			GetWindowText( GetDlgItem( hwnd, IDC_EDIT6), begin,256);
			GetWindowText( GetDlgItem( hwnd, IDC_EDIT7), end,  256);

			// �Ƿ񰴹ؼ�֡����
			g_config.m_keyFrame = GetCheckBox( m_panelAnimation, IDC_CHECK3);

			// �����ܶ�
			char tSampleDensity[256];
			GetWindowText( GetDlgItem( m_panelAnimation, IDC_EDIT2), tSampleDensity, 255);
		    int tSD = atoi(tSampleDensity);
			if( tSD >=1 && tSD<=6000)
				g_config.m_sampledensity = tSD;

			// �Ϸ��Լ�� 
			if( strlen( name) <= 0)
				return;

			int iStart = atoi( begin);
			int iEnd   = atoi( end);

			CAnimationManager tAniMgr;
			if( tAniMgr.AddAnimation( name, iStart, iEnd, m1Animation))
			{
				m1Animation.Save( g_config.m_aniLocation.c_str());

				UpdateAnimationPanelShow();
			}
		}
	}

	// ɾ������
	void CAeUtilityUI::DelAnimation( HWND hwnd)
	{
		if( g_config.m_aniLocation.empty())
			return;

		CM1Animation m1Animation;

		if( m1Animation.Load( g_config.m_aniLocation.c_str()))
		{
			// ��ȡ��ǰѡ��
			int curSel;
			HWND aniList = GetDlgItem( m_panelAnimation, IDC_LISTANI);
			curSel = SendMessage( aniList, LB_GETCURSEL, 0, 0);

			if( curSel == -1)
				return;

			CAnimationManager tAniMgr;
			if( tAniMgr.DelAnimation( curSel, m1Animation))
			{
				m1Animation.Save( g_config.m_aniLocation.c_str());

				UpdateAnimationPanelShow();
			}
		}
	}

	// ���ö���ʱ�䷶Χ
	void CAeUtilityUI::SetAnimationRange( const char* begin, const char* end)
	{
		SetWindowText( GetDlgItem( m_panelAnimation, IDC_EDIT6), begin);
		SetWindowText( GetDlgItem( m_panelAnimation, IDC_EDIT7), end);
	}
}