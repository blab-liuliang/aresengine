#pragma once

#include <max.h>

namespace M1_IGame
{
	//----------------------------------------
	// ��������� 2010-08-26   ����
	//----------------------------------------
	class CAeExportClassDesc : public ClassDesc
	{
	public:
		// show this is create branch
		virtual int	IsPublic();

		// ���ص�����ʵ��
		virtual void* Create(BOOL loading=FALSE);

		// ���ص���������
		virtual const char* ClassName();

		// ����������� dle, dlu �ȵ�
		virtual SClass_ID SuperClassID();

		// �����Ψһ��ʶ��,max�������ֲ��
		virtual Class_ID ClassID();

		// ���� ���
		virtual const char* Category();  

		//// �������ڲ���
		//virtual const char* InternalName();

		// dll ʵ�����
		HINSTANCE HInstance();

	public:
		// ����ģʽ
		static CAeExportClassDesc* GetInstance();

	private:
		// ˽�й��캯��
		CAeExportClassDesc(){}

	private:
		static CAeExportClassDesc*  instance;
	};


	// ����������ʵ�� (����ģʽ)
	inline CAeExportClassDesc* CAeExportClassDesc::GetInstance()
	{
		if ( instance == NULL)
		{
			instance = new CAeExportClassDesc();
		}

		return instance;
	}
}