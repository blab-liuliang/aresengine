#pragma once

#include <max.h>
#include <utilapi.h>
#include "M1Export.h"

namespace M1_IGame
{
	//---------------------------------------
	// ������� 2011-07-22     ����
	//---------------------------------------
	class CAeUtilityUI
	{
	public:
		// ���캯��
		CAeUtilityUI();

		// �������
	public:
		// ��ʼ��
		void InitGeneralPanel( HWND hwnd);

		// ѡ�񵼳�·��
		void SetExportDir( HWND hwnd);

		// ִ�г��浼��
		void DoExport();

		// Ԥ��ģ��
		void PreViewModel();

		// ��������
		void UpdateConfig();

		// ģ�����
	public:
		// ��ʼ��
		void InitModelPanel( HWND hwnd);

		// �������
	public:
		// ��ʼ��
		void InitMaterialPanel( HWND hwnd);
		
		// �������
	public:
		// ��ʼ��
		void InitAnimationPanel( HWND hwnd);

		// ���½�����ʾ
		void UpdateAnimationPanelShow();

		// ��Ӷ���
		void AddAnimation( HWND hwnd);

		// ɾ������
		void DelAnimation( HWND hwnd);

	public:
		// ���ö���ʱ�䷶Χ
		void SetAnimationRange( const char* begin, const char* end);

	private:
		HWND		 m_panelAbout;		// About����
		HWND		 m_panelGeneral;	// �������
		HWND		 m_panelModel;		// ģ�����
		HWND		 m_panelMaterial;	// �������
		HWND		 m_panelAnimation;	// �������
	};
}