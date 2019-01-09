#pragma once

#include "AresCore.h"

namespace Ares
{
	//----------------------------------
	//	2010-03-09	17:48   ����    
	//  ��������ʵ��(��ά) 
	//-----------------------------------
	class CPerlinNoise
	{
	public:
		enum
		{
			EM_TABLE_SIZE =  256,
			EM_TABLE_MASK = EM_TABLE_SIZE - 1,
		};

		// ���캯��
		CPerlinNoise();

		// ����
		float Noise(int x, int y, float scale);

		// ����
		float Noise(float x, float y, float scale);

	private:
		// ˽�к���
		void SetUp();

		// ��ȡ�����λ���� ֻҪx y ֵ����,����ֵҲ����!�������ǾͲ���ҪΪÿ������洢һ����������
		const Vector2* GetVec(int x, int y) const;		

	private:
		Vector2		  m_vTable[EM_TABLE_SIZE];
		unsigned char m_lut[EM_TABLE_SIZE];
	};
}