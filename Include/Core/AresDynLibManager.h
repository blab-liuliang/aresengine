#pragma once

#include "AresDynLib.h"
#include "Core/AresPlatform.h"

using namespace std;

namespace Ares
{
	//---------------------------------------
	// AresDynLibManager 2011-08-01  ����
	//---------------------------------------
	class CDynLibManager
	{
		typedef map<string, CDynLib*> DynLibList;
	public:
		// ���캯��
		CDynLibManager();

		// ��������
		~CDynLibManager();

		// ���ؿ�
		CDynLib* Load( const char* fileName);

		// ж�ؿ�
		void Unload( CDynLib* lib);

		// ��ȡ��
		CDynLib* GetDynLib( const char* fileName);

	private:
		DynLibList		m_libList;			// ���б�
	};
}