#pragma once

namespace Ares
{
	// �����
	enum SegmentDetectFlag
	{
		SDF_NearestHitPoint   = 1<<0,	// �����
	};

	// ������� 
	struct SegmentDetectConfig
	{
		int		m_detectFlag;

		// ���캯��
		SegmentDetectConfig()
			: m_detectFlag( SDF_NearestHitPoint)
		{}
	};

	// �����
	struct SegmentDetectResult
	{
		Vector3		m_closetHitPoint;		// �ཻλ��
		Vector3		m_closetHitNormal;		// �ཻ�㷨��
	};
}