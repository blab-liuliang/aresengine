#ifndef	ARES_DYNLIB_H
#define ARES_DYNLIB_H

#include "AresPlatform.h"

#ifdef ARES_PLATFORM_WINDOWS

#include <Windows.h>
#include <string>

using namespace std;

#define DYNLIB_HANDLE         HMODULE
#define DYNLIB_LOAD( a)       LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH)
#define DYNLIB_GETSYM( a, b)  GetProcAddress( a, b)
#define DYNLIB_UNLOAD( a)     FreeLibrary( a)
#endif

namespace Ares
{
	//-----------------------------------
	// DynLib ��̬�� 2011-08-01 ����
	// �ο� : OGRE
	//-----------------------------------
	class CDynLib
	{
	public:
		// constructor used by CDynLibManager
		CDynLib( const char* name);

		// destructor
		~CDynLib();

		// ����
		void Load();

		// ж��
		void Unload();

		// ��ȡ����
		const char* GetName() { return m_name.c_str();}

		// ��ȡsymbol
		void* GetSymbol( const char* strName);

	private:
		string		  m_name;		// ����(��ʶ)
		DYNLIB_HANDLE m_handle;		// ����
	};
}
#endif