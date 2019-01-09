#include <Core/AresPerlinNoise.h>

namespace Ares
{
	// ���캯��
	CPerlinNoise::CPerlinNoise()
	{
		SetUp();
	}

	// ����
	void CPerlinNoise::SetUp()
	{
		float stepDegree = 2 * PI / EM_TABLE_SIZE;
		float degree = 0.0f;

		srand(GetTickCount());

		for (int i=0; i<EM_TABLE_SIZE; i++)
		{
			// sinA��ƽ�� + cosA��ƽ�� = 1; ��ȷ��Ϊ��λ����
			m_vTable[i].x = (float)sin(degree);
			m_vTable[i].y = (float)cos(degree);	

			degree += stepDegree;

			// ȡ�������ǰ8λ
			m_lut[i] = rand() & EM_TABLE_MASK;	
		}

	}

	// ��������
	float CPerlinNoise::Noise(int x, int y, float scale)
	{
		return Noise( (float)x, (float)y, scale);
	}

	float CPerlinNoise::Noise(float x, float y, float scale)
	{
		Vector2 pos( x*scale, y*scale);

		// ����������ڸ��ӵ����Ͻ����½�����
		float x0 = (float)floor( pos.x);
		float x1 = x0 + 1.0f;
		float y0 = (float)floor( pos.y);
		float y1 = y0 + 1.0f;

		// Ϊ������ĸ����������������λ����
		Vector2 vectorLU = *GetVec( (int)x0, (int)y0);
		Vector2 vectorLD = *GetVec( (int)x0, (int)y1);
		Vector2 vectorRU = *GetVec( (int)x1, (int)y0);
		Vector2 vectorRD = *GetVec( (int)x1, (int)y1);

		// ������ĸ����㵽���ص�����
		Vector2 d0( pos.x-x0, pos.y-y0);
		Vector2 d1( pos.x-x0, pos.y-y1);
		Vector2 d2( pos.x-x1, pos.y-y0);
		Vector2 d3( pos.x-x1, pos.y-y1);

		// ������������������ĵ��
		float h0 = (d0.x * vectorLU.x) + (d0.y * vectorLU.y);
		float h1 = (d1.x * vectorLD.x) + (d1.y * vectorLD.y);
		float h2 = (d2.x * vectorRU.x) + (d2.y * vectorRU.y);
		float h3 = (d3.x * vectorRD.x) + (d3.y * vectorRD.y);

		float Sx, Sy;
		//
		// ���ֹ�ʽ
		// w = 3t*t - 2t*t*t; ���ٵ������϶��͵���
		// w = 6t5 �C 15t4 + 10t3; �˴�ʹ�����

		Sx = 6 * powf( d0.x, 5.0f) - 15 * powf( d0.x, 4.0f) + 10 * powf( d0.x, 3.0f);
		Sy = 6 * powf( d0.y, 5.0f) - 15 * powf( d0.y, 4.0f) + 10 * powf( d0.y, 3.0f);

		float avgX0 = h0 + ( Sx * (h2 - h0));
		float avgX1 = h1 + ( Sx * (h3 - h1));

		float result = avgX0 + ( Sy * (avgX1 - avgX0));

		return result;
	}

	inline const Vector2* CPerlinNoise::GetVec(int x, int y) const
	{
		unsigned char xr = m_lut[x & EM_TABLE_MASK];			// ����x��ȡ�������
		unsigned char yr = m_lut[y & EM_TABLE_MASK];			// ����y��ȡ�������
		unsigned char xyr = m_lut[(xr + yr) & EM_TABLE_MASK];	// �в���x y ��ͬ�����������(�������λ��0-255֮��)

		return &m_vTable[xyr];
	}
}