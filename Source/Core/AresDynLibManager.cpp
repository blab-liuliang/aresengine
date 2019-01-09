#include "Core/AresDynLibManager.h"

namespace Ares
{
	// ���캯��
	CDynLibManager::CDynLibManager()
	{

	}

	// ��������
	CDynLibManager::~CDynLibManager()
	{
		for ( DynLibList::iterator it = m_libList.begin(); it != m_libList.end(); it++)
		{
			it->second->Unload();
			delete it->second;
		}

		m_libList.clear();
	}

	// ���ؿ�
	CDynLib* CDynLibManager::Load( const char* fileName)
	{
		DynLibList::iterator it = m_libList.find( fileName);

		if( it != m_libList.end())
		{
			return it->second;
		}
		else
		{
			CDynLib* pLib = new_ CDynLib( fileName);

			pLib->Load();
			m_libList[fileName] = pLib;

			return pLib;
		}
	}

	// ж�ؿ�
	void CDynLibManager::Unload( CDynLib* lib)
	{
		DynLibList::iterator it = m_libList.find( lib->GetName());

		if( it != m_libList.end())
		{
			m_libList.erase( it);
		}

		lib->Unload();
		delete lib;
	}

	// ��ȡ��
	CDynLib* CDynLibManager::GetDynLib( const char* fileName)
	{
		DynLibList::iterator it = m_libList.find( fileName);

		if( it != m_libList.end())
		{
			return it->second;
		}

		return NULL;
	}
}