#pragma once

#include <vector>
//#include "MtlKeeper.h"
#include "Function.h"
#include "IGame.h"
#include "IGameModifier.h"
#include <Engine/RenderSystem/M1/M1Loader.h>
#include <Core/AresMath.h>

using namespace std;
using namespace Ares;

namespace M1_IGame
{
	//----------------------------------------------------
	// MaxScene bone���� BoneKeeper ���� 2010-11-08 15:16
	//----------------------------------------------------
	class CBoneKeeper
	{
	public:
		// ���캯��
		CBoneKeeper();

		// ��ʼ��
		void Init( vector<IGameSkin*>& gameSkins);

		// ���������ṹ
		void BuildBoneStruct( CM1Animation& m1Animation);

		// ������������(һ�λᵼ��)
		void BuildAnimationSets( CM1Animation& m1Animation);

		// ���ҹ�������
		int  GetBoneID( IGameNode* pGameNode);

	private:
		// ��ӹ������
		void AddBoneNode( IGameNode* pBoneNode, Matrix44& matInit);

		// ���ҵ�һ�ӽ������
		int  GetFirstChildIndex( IGameNode* pNode);

		// ���ҽ����ֵܹ���
		int  GetSiblingIndex( IGameNode* pNode);

		// �ý���Ƿ�Ϊjoint
		bool  IsBone( IGameNode* pNode);

		// �Ƿ���������
		bool  IsRootBone( IGameNode* pGameNode);

		// ����TransKeys
		//void  BuildKeys( SM1Animation& boneAnimation,IGameNode* pGameNode, Control* pControl, Interval interval);

		// ��������
		//void  SampleKeys( SM1Animation& boneAnimation, IGameNode* pGameNode, Interval interval);

		// ��ȡ�ؼ�֡ʱ��
		//TimeValue GetKeyTime(Control* control, int i);

	private:
		bool					m_bScale;				// �Ƿ�������
		vector<IGameNode*>		m_boneNodes;			// �������( ��ر�֤��һ������������) 
		vector<Matrix44>		m_boneInitTransform;	// ������ʼת��( �Ѷ��������ռ�ת���������ռ���)
	};
}