#pragma once

#include <string>
#include <IGame.h>
#include <vector>
#include <Engine/RenderSystem/M1/M1Loader.h>

using namespace std;
using namespace Ares;

namespace M1_IGame
{
	//---------------------------------------
	// AnimationManager ���� 2011-07-26
	//---------------------------------------
	class CAnimationManager
	{
	public:
		// ���캯��
		CAnimationManager();

		// ��Ӷ���
		bool AddAnimation( const string& aniName, int start, int end, CM1Animation& m1Animation);

		// ɾ������
		bool DelAnimation( int aniIndex, CM1Animation& m1Animation);

		// �޸Ķ�������
		bool EditAnimation( const string& newName, int index,CM1Animation& m1Animation);

		// ��������˳��
		bool ExchangeAnimation( int index0, int index1, CM1Animation& m1Animation);

	private:
		// ��������
		void SampleKeys( SM1Animation& boneAnimation, IGameNode* pGameNode, Interval interval);

		// �ؼ�֡����
		void BuildKeys(  SM1Animation& boneAnimation, IGameNode* pGameNode, vector<TimeValue>& keyTimes,Interval interval);

	private:
		// �����ӽ��
		void FindChildNodes( IGameNode* parent, vector<IGameNode*>& out);

		// ��ȡ���нӵ�
		void FindAllNodes( vector<IGameNode*>& out);

		// ��ȡ���
		IGameNode* GetIGameNodeByName( const char* name, vector<IGameNode*>& nodes);

		// ��ȡ�ؼ�֡ʱ���
		void GetBoneAnimationSetTime( vector<TimeValue>& keyTimes, Interval interval, IGameNode* gameNode);

		// ��ӿ������ؼ�ʱ���
		void AddKeyTime( vector<TimeValue>& keyTimes, Control* contrl, Interval interval);

		// ��ӹؼ�ʱ���
		void AddKeyTime( vector<TimeValue>& keyTimes, TimeValue keyTime);

	private:
		// �ж�ĳ����Ƿ��ǹ���
		bool IsBone( IGameNode* gameNode);

		// �жϹ����Ƿ񵼳�
		bool IsNeedExport( IGameNode* gameNode);

	private:
		// ��ȡҪ�����Ĺ��������
		void GetExportBones();

	private:
		vector<IGameNode*>			m_nodes;			// ���н��
		vector<IGameNode*>			m_boneNodes;		// ���й������
		vector<IGameNode*>			m_exportNodes;		// ��ǰѡ�еĽ��
	};
}