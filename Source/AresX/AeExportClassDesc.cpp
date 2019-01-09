#include <WTypes.h>
#include "AeUtility.h"
#include "AeExportClassDesc.h"

extern HINSTANCE    g_hInstance;
extern Interface*   g_pI;

M1_IGame::CAeUtility*		g_utility = NULL;

namespace M1_IGame
{
	CAeExportClassDesc* CAeExportClassDesc::instance = NULL;

	// show this is create branch
	int	CAeExportClassDesc::IsPublic()
	{
		return 1;
	}

	// ���ص�����ʵ��
	void* CAeExportClassDesc::Create(BOOL loading/*=FALSE*/)
	{
		if( !g_utility)
			g_utility = new CAeUtility;

		return g_utility;
	}

	// ���ص���������
	const char* CAeExportClassDesc::ClassName()
	{
		return "AresX";
	}

	// ����������� dle, dlu �ȵ�
	SClass_ID CAeExportClassDesc::SuperClassID()
	{
		//return SCENE_EXPORT_CLASS_ID;
		return UTILITY_CLASS_ID;
	}

	// �����Ψһ��ʶ��,max�������ֲ��
	Class_ID CAeExportClassDesc::ClassID()
	{
#ifdef _DEBUG
		// �ǵ����»�ȡһ��Ψһֵ
		return Class_ID(0x77ff6121, 0x6b7c31);
#else
		// �ǵ����»�ȡһ��Ψһֵ
		return Class_ID(0x77ff6121, 0x6b7c31);
#endif
	}

	// ���� ���
	const char* CAeExportClassDesc::Category()
	{
		return "AresEngine";
	}

	//// �������ڲ���
	//const char* CAeExportClassDesc::InternalName()
	//{
	//	return "CAeUtility";
	//}

	// dll ʵ�����
	HINSTANCE CAeExportClassDesc::HInstance()
	{
		return g_hInstance;
	}
}