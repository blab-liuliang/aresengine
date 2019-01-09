#pragma once

#include "AresMath.h"

namespace Ares
{
	//------------------------------------
	// ��Ԫ�� 2011-11-1 <ժ��ogre> ����
	//------------------------------------
	class Quaternion
	{
	public:
		// ���캯��
		Quaternion( const D3DXMATRIX& rot);

		// ת���ɾ���
		void  ToRotationMatrix( D3DXMATRIX& rot);

	public:
		  float		x, y, z, w;		// ��ֵ
	};
}