//#pragma once
//
//namespace Ares
//{
//	//---------------------------------------
//	// �㾫�� 2011-04-02  ����
//	//---------------------------------------
//	struct SSPrite
//	{
//		Vector3		 m_vPos;	  // ���ӵ�ǰλ��
//		float        m_fLifeTime; // ��������
//		float        m_fAge;	  // �Ѵ���ʱ��
//		float        m_fSpeed;	  // �ƶ��ٶ�
//		Vector3		 m_vMoveDir;  // �ƶ�����	
//		float		 m_fSize;	  // ���ӳߴ� 
//		DWORD		 m_color;     // ������ɫ
//		bool         m_bIdle;	  // ������(��ռé��)
//
//		// ���캯��
//		SSPrite() 
//			: m_fSize(1.f),
//			  m_fLifeTime(1.f),
//			  m_fAge(0.f),
//			  m_fSpeed(1.f),
//			  m_bIdle(true)
//		{ 
//		}
//
//		// ����
//		bool FrameMove(float fTime)
//		{
//			// Age the Particle
//			m_fAge += fTime;
//
//			// If this particle's age is greater than it's lifetime, it dies
//			if(m_fAge > m_fLifeTime) 
//			{
//				m_bIdle = true;
//				return false;
//			}
//
//			m_vPos += m_vMoveDir * fTime;
//
//			return true;
//		}
//	};
//}