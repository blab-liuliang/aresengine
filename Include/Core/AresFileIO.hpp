#pragma once

#include "AresPlatform.h"

namespace Ares
{
	//--------------------------------------------
	// �����ļ����� 2012/2/4  ����
	//--------------------------------------------
	class IFileIO
	{
	public:
		// ���캯��
		IFileIO();

		// ��������
		virtual ~IFileIO();

	public:
		// ����xml��ʽ
		virtual BOOL LoadXml( const char* fileName)=0;

		// ����xml��ʽ
		virtual BOOL SaveXml( const char* fileName) { return FALSE; }

		// ���ض����Ƹ�ʽ
		virtual BOOL LoadBinary( const char* fileName);

		// ����Ϊ�����Ƹ�ʽ
		virtual BOOL SaveBinary( const char* fileName);

	public:
		// �������
		virtual void Clear();

	protected:
		UINT	m_dataSize;	// ���ݴ�С
		BYTE*	m_data;		// ����
	};

	//
	// INLINE
	//

	// ���캯��
	INLINE IFileIO::IFileIO()
		: m_data(NULL),
		  m_dataSize( 0)
	{}

	// ��������
	INLINE IFileIO::~IFileIO()
	{
		m_dataSize = 0;
		SAFE_DELETE_ARRAY( m_data);
	}

	// �������
	INLINE void IFileIO::Clear()
	{
		m_dataSize = 0;
		SAFE_DELETE_ARRAY( m_data);
	}

	// ���ض����Ƹ�ʽ
	INLINE BOOL IFileIO::LoadBinary( const char* fileName)
	{
		if( !fileName)
			return false;

		FILE* fileHandle = fopen( fileName, "rb");
		if( fileHandle)
		{
			// �������ݴ�С
			fread( &m_dataSize, sizeof( UINT), 1, fileHandle);

			// ��������ʵ��
			m_data = new_ BYTE[m_dataSize];
			fread( m_data, m_dataSize, 1, fileHandle);

			fflush( fileHandle);
			fclose( fileHandle);

			return TRUE;
		}

		return FALSE;
	}

	// ����Ϊ�����Ƹ�ʽ
	INLINE BOOL IFileIO::SaveBinary( const char* fileName)
	{
		if( !fileName)
			return false;

		FILE* fileHandle = fopen( fileName, "wb");
		if( fileHandle)
		{
			// �������ݴ�С
			fwrite( &m_dataSize, sizeof( UINT), 1, fileHandle);

			// ��������ʵ��
			fwrite( m_data, m_dataSize, 1, fileHandle);

			fflush( fileHandle);
			fclose( fileHandle);

			return TRUE;
		}

		return FALSE;
	}
}