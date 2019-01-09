#pragma once

#include <vector>
#include <Core/AresMath.h>

using namespace std;

namespace Ares
{
	//--------------------------------------
	// ����ͼ 2011-03-08		����
	//--------------------------------------
	class INavMap
	{
		friend class CAStar;
	protected:
		// ��ȡ��ͨ����Χ�ӵ�
		virtual void GetPassAbleNeighbor( int* childID, int& numChild,int fatherID)=0;

		// ����ID����������μ�h
		virtual float CalcH( const Vector3& vStart, const Vector3& vEnd, int idFrom, int idTo=-1)=0;

		// ����ID����������μ�g
		virtual float CalcG( const Vector3& vStart, int idFrom, int idTo, int idFromFrom=-1)=0;
	};
}