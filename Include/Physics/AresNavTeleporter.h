#pragma once

#include <vector>
#include <Core/AresFileIO.hpp>
#include "AresNavMap.h"

using namespace std;

namespace Ares
{
	#define MAX_REGION_TELEPORTERS 30
	//---------------------------------------------------------
	// ������ͨ��, 2012-02-02 ����
	// ʵ�ֿ��ͼѰ·
	// 1.���͵�Ϊ������,���޷�����Ԥ��Ѱ·ʧ�ܵ����
	// 2.������IDΨһ
	// 3.ͬʱʵ��xml������Ƹ�ʽ
	// 4.����������п��ͼ����(Ӧ������ID���ͼID��϶���)
	// 5.��ͬ���򲻽��д�����Ѱ·(��� ħ������),���޷���ЧԤ��
	//---------------------------------------------------------
	class CAStar;
	class CNavTeleporter : public INavMap, public IFileIO
	{
		friend class CAStar;
	public:
		// ���͵�
		struct STeleporter
		{
			UINT		m_ID;			// ���͵�ID
			UINT		m_regionID;		// ���͵���������ID
			Vector3     m_pos;			// ���͵�λ��
			UINT		m_aimRegionID;	// Ŀ������ID
			Vector3		m_aimPos;		// Ŀ�ĵ�λ��	
		};

		// ��������
		struct SRegion
		{
			UINT	m_ID;									// ����ID
			UINT	m_numLeaveTeleporters;					// �뿪������Ĵ��͵�����
			UINT	m_numEnterTeleporters;					// ���������Ĵ��͵�����
			INT		m_teleporterIDs[MAX_REGION_TELEPORTERS];// �����ڵĴ��͵�ID
		};

		// Header definition
		struct SHeader
		{
			UINT				m_version;				// �汾
			UINT				m_numRegions;			// ��������
			UINT				m_numTeleporters;		// ����������
			SRegion*			m_regions;				// ����
			STeleporter*		m_teleporters;			// ������
		};	

		typedef vector<const STeleporter*>	PathResult; 

	public:
		CNavTeleporter();
		~CNavTeleporter();

	public:
		// ����xml��ʽ(��֧���������)
		virtual BOOL LoadXml( const char* fileName);

		// ����·�� 
		size_t FindPath( PathResult& oPath, UINT startRegionID, const Vector3& startPos, UINT endRegionID, const Vector3& endPos);

	public:
		// ���ݴ�����ID��ȡ��������Ϣ
		const STeleporter* GetTeleporter( UINT id);

		// ��������ID��ȡ������Ϣ
		const SRegion* GetRegion( UINT id);

	protected:
		// ��ȡ��ͨ����Χ�ӵ�
		virtual void GetPassAbleNeighbor( int* childID, int& numChild,int fatherID);

		// ����ID����������μ�h
		virtual float CalcH( const Vector3& vStart, const Vector3& vEnd, int idFrom, int idTo=-1);

		// ����ID����������μ�g
		virtual float CalcG( const Vector3& vStart, int idFrom, int idTo, int idFromFrom=-1);

	public:
		CAStar*		m_aStar;		// A*�㷨������
		SHeader*	m_header;		// ���������ݰ�
	};
}