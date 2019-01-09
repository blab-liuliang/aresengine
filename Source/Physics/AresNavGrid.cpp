#include "Physics/AresNavGrid.h"
#include <stdlib.h>
#include <math.h>

namespace Ares
{
	// ���캯��
	CNavGrid::CNavGrid(int iWidth, int iHeight)
	{
		m_iWidth  = iWidth;
		m_iHeight = iHeight;

		m_pPassAble = new_ bool[ m_iWidth * m_iHeight];

		// ��ʼ��Ϊ��ͨ��
		for ( int i=0; i<m_iHeight* m_iWidth; i++)
			m_pPassAble[i] = true;
	}

	// ��������
	CNavGrid::~CNavGrid()
	{
		if( m_pPassAble)
			delete[] m_pPassAble;
	}

	// ����ID���������h
	//float CNavGrid::CalcH( int idFrom, int idTo, ARESVECTOR3& vEnd)
	//{
	//	// ���Ż� 
	//	int row1 = iD1 / m_iWidth;
	//	int row2 = iD2 / m_iWidth;
	//	int col1 = iD1 % m_iWidth;
	//	int col2 = iD2 % m_iWidth;
	//	
	//	return (float)(abs( row2 - row1) + abs( col2 - col1));
	//}

	//// ����ID���������g
	//float CNavGrid::CalcG( ARESVECTOR3& vStart, int idFrom, int idTo, int idFromFrom/*=-1*/)
	//{
	//	// ���Ż� 
	//	int row1 = idFrom  / m_iWidth;
	//	int row2 = idTo    / m_iWidth;
	//	int col1 = idFrom  % m_iWidth;
	//	int col2 = idTo    % m_iWidth;

	//	float g = (float)(( row2 - row1) *( row2 - row1) + ( col2 - col1) * ( col2 - col1));

	//	return sqrtf( g);
	//}

	// ��ȡ��ͨ����Χ�ӵ�
	void CNavGrid::GetPassAbleNeighbor( int* childID, int& numChild,int fatherID)
	{
		numChild = 0;

		int row = fatherID / m_iWidth;
		int col = fatherID % m_iWidth;

		for ( int i=-1; i<2; i++)
			for( int j=-1; j<2; j++)
			{
				if ( i==0 && j==0)
					continue;

				int tRow = row + i;
				int tCol = col + j;

				if ( tRow>=0 && tRow<m_iHeight && tCol>=0 && tCol<m_iWidth)
				{
					int ID = Coord2ID( tRow, tCol);
					if( IsPassAble( ID))
					{
						childID[numChild] = ID;
						numChild++;
					}
				}
			}
	}

	// �Ƿ��ͨ��
	bool CNavGrid::IsPassAble( int ID)
	{
		return m_pPassAble[ID];
	}

	// ���ÿɷ�ͨ��
	bool CNavGrid::SetPassAble( int row, int col, bool bPass)
	{
		return SetPassAble( Coord2ID( row, col), bPass);
	}

	// �����Ƿ�ͨ��
	bool CNavGrid::SetPassAble( int ID, bool bPass)
	{
		if ( ID >=0 && ID < m_iWidth*m_iHeight)
		{
			m_pPassAble[ID] = bPass;

			return true;
		}

		return false;
	}
}