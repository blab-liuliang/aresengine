#pragma once

#include <string>

using namespace std;

namespace Ares
{
	//------------------------------------------
	// fwrites  2010-07-20  ����
	//------------------------------------------
	void fwrites( const char* res, FILE* fileHandle);

	//----------------------------------------------
	// freads  2010-07-20  ����
	//----------------------------------------------
	// Ч��ԭ��ֻ�ܶ�ȡС��1024�ֽ��ַ���
	// Ч��ԭ��ʹ��string ����char* c = new char[]
	bool freads( string& _s, FILE* fileHandle);
	bool freads( char*& _s, FILE* fileHandle);

	// ��ȫ��·���в�ֳ�������,�ɸ��ĺ�׺��
	string splitNameExt( const char* fullPath, const char* aimExt=NULL);

	// �����ļ���
	void changeNameExt( char* pdst, const char* source, const char* nameExt);

	// ������׺��
	void changeExt( char* pdst, const char* source, const char* ext);
}