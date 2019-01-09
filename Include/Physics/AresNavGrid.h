#pragma once

#include "AresNavMap.h"

namespace Ares
{
	//--------------------------------------
	// �������� 2011-01-20  ����
	//--------------------------------------
	class CNavGrid : public INavMap
	{
	protected:
		// ���캯��
		CNavGrid(int iWidth, int iHeight);

		// ��������
		~CNavGrid();

		// ��ȡ��ͨ����Χ�ӵ�
		void GetPassAbleNeighbor( int* childID, int& numChild,int fatherID);

		//// ����ID���������h
		//virtual float CalcH( int idFrom, int idTo, ARESVECTOR3& vEnd);

		//// ����ID���������g
		//virtual float CalcG( ARESVECTOR3& vStart, int idFrom, int idTo, int idFromFrom=-1);

	public:
		// ���������ȡID
		int  Coord2ID( int row, int col) { return row*m_iWidth + col; }

		// ���ÿɷ�ͨ��
		bool SetPassAble( int row, int col, bool bPass);

		// �����Ƿ�ͨ��
		bool SetPassAble( int ID, bool bPass);

		// �Ƿ��ͨ��
		bool IsPassAble( int ID);

		// ����
		void  Save();

		// ����
		void  Load();

	private:
		int    m_iWidth;		// ��ͼ
		int    m_iHeight;		// �߶�
		bool*  m_pPassAble;  	// ͨ���б�
	};
}