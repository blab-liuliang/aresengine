#pragma once

#include "QPropertyModel.h"
#include "QPropertyDelegate.h"

namespace QT_UI
{
	//----------------------------------
	// QProperty 2013-1-21 ����
	// ��¼Model,Delegate��
	//----------------------------------
	struct QProperty
	{
		QPropertyModel*		m_model;
		QPropertyDelegate*	m_delegate;

		// ���캯��
		QProperty( const char* config)
		{			// ����
			m_model    = new_ QPropertyModel( config);
			m_delegate = new_ QPropertyDelegate( m_model);
		}

		// ��������
		~QProperty()
		{
			SAFE_DELETE( m_model);
			SAFE_DELETE( m_delegate);
		}
	};
}