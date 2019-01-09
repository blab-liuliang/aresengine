#pragma once

#include "AresPlatform.h"

namespace Ares
{
	//----------------------------------------------------
	// Singleton 2011-11-18		����
	//	ժ�� ogre, Ե��boost singleton�Ĳ�����
	// template class for creating  single-instance
	// global classes.
	//---------------------------------------------------
	template<typename T>
	class Singleton
	{
	private:
		// ���ÿ�������
		Singleton(const Singleton<T>&);

		// ���� "="
		Singleton& operator=(const Singleton<T>&);

	public:
		// ���캯��
		Singleton()
		{
			// ����ʵ����,���Ա���
			assert( !m_singleton);

			m_singleton = static_cast<T*>(this);
		}

		// ��������
		virtual ~Singleton()
		{
			assert( m_singleton);

			m_singleton = 0;
		}

		// �Ƿ����
		static bool IsEnabled()
		{
			return m_singleton ? true : false;
		}

		// ��ȡ����
		static T& GetSingleton()
		{
			assert( m_singleton);

			return *m_singleton;
		}

		// ��ȡ����ָ��
		static T* GetSingletonPtr()
		{
			assert( m_singleton);

			return m_singleton;
		}

		// ����������
		static const char* getClassTypeName()
		{
			return "Singleton";
		}

		// ����
		static void Destory()
		{
			SAFE_DELETE( m_singleton);
		}

	protected:
		static T*		m_singleton;			// ����ʵ��
	};
}