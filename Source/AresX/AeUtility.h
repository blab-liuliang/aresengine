#pragma once

#include <max.h>
#include <utilapi.h>

namespace M1_IGame
{
	//---------------------------------------
	// ������� 2011-07-20     ����
	//---------------------------------------
	class CAeUtility : public UtilityObj
	{
	public:
		// ���캯��
		CAeUtility();

		// ��������
		~CAeUtility();

		// δ֪
		void BeginEditParams(Interface *ip, IUtil *iu);

		// δ֪
		void EndEditParams(Interface *ip,IUtil *iu);

		// ɾ��
		void DeleteThis() {}
	
	private:
		IUtil		*m_iu;
		Interface	*m_ip;
		HWND		 m_panelAbout;		// About����
		HWND		 m_panelGeneral;	// �������
		HWND		 m_panelModel;		// ģ�����
		HWND		 m_panelMaterial;	// �������
		HWND		 m_panelAnimation;	// �������
	};
}