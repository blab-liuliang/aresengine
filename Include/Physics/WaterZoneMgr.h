/********************************************************************
	created:	2011/06/15
	created:	15:6:2011   10:11
	filename: 	f:\work\MoveManager\WaterZoneMgr.h
	file path:	f:\work\MoveManager
	file base:	WaterZoneMgr
	file ext:	h
	author:		����
	
	purpose:	��ǰ�����ͼ��ˮ��������࣬�����жϴ�����Ӿ������
				���������л�
*********************************************************************/
#pragma once

#include <Core/AresMath.h>
#include <Physics/Rect3.h>

namespace Ares
{
	/******************************************************************************
	 SWaterInfoFlag
	 һ�������Ϣ
	******************************************************************************/
	struct SWaterInfoFlag
	{
		float m_fFlag;
		SWaterInfoFlag(void)
		{
			m_fFlag = FLT_MAX;
		}
	};

	class WaterZoneMgr : public Shape
	{
	public:
		WaterZoneMgr(void);
		~WaterZoneMgr(void);

		bool LoadWaterFlags(const char* pszFileName);
		bool PtInWater(int nX, int nZ, float& fDeep) const;

		// �ж��Ƿ���ˮ��
		virtual bool IsPointIn( const Vector3& point) const;

		// ����AABB��Χ��
		virtual void BuildAABB( Rect3& box, const Transform& trans) const;

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass) { A_ASSERT(false); return Vector3::Zero; }

	private:
		int				m_nXGrids;	//��ͼx�����ϵĸ�������(�������Ҫ��1)
		int				m_nZGrids;  //��ͼz�����ϵĸ�������(�������Ҫ��1)
		int				m_nGridSize;//���ӱ߳�
		SWaterInfoFlag* m_pWaterInfoFlag;	//��ͼ�����еĵ��ˮ��Ϣ
	};
}

