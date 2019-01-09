#pragma once

#include "iskincodes.h"
#include "Phyexp.h"
#include "iparamb2.h"
#include "iskin.h"
#include <d3dx9math.h>
#include <string>
#include <IGame.h>
#include <Core/AresMath.h>
#include <Engine/RenderSystem/M1/M1Loader.h>

using namespace std;

namespace M1_IGame
{
	// �Ӳ��ʵ�Diffuse slot�л�ȡ����
	void  GetIndicesFromTexMap( int& i1, int& i2, Mtl* _mtl);

	// ��ȫ��·���в�ֳ�������,�ɸ��ĺ�׺��
	string SplitNameExt( const char* fullPath, const char* aimExt);

	// ����PhysiqueModifier
	Modifier*  FindPhysiqueModifier( INode* pNode);

	// ����MaxSkinModifier
	Modifier* FindMaxSkinModifier( INode* nodePtr);

	// ��������ϵ
	D3DXMATRIX MAXtoARES( Matrix3& mat);

	//// �ļ�����
	//bool CopyFile(char* source, char* target);

	// ��������
	void ChangeExt( char* dst, const char* source, const char* ext);

	// ��������
	void NameExt( char* dst, const char* source);

	// ת����Ares�ռ�
	Ares::Transform GMatrixToAresTransform( const GMatrix& mat);

	// ת��
	void Point3ToSM1Vertex( Ares::SM1Vertex& oV, const Point3& iV);
}