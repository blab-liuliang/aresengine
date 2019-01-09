#pragma once

#include <list>
#include <Engine/RenderSystem/AresModelIDCard.h>
#include <Core/AresMath.h>

using namespace std;

namespace Ares
{
	//----------------------------------------
	// M1 Model 2010-09-21    ����
	//----------------------------------------
	class CAresAnimation : public CM1Animation
	{
	public:
		// ���캯��
		CAresAnimation();

		// ��������
		~CAresAnimation();

	public:
		// ������Դ
		//virtual bool LoadResource();

		// ������Դ
		virtual bool Save(char* fileName){ return false;}

	public:
		// ��ȡ�����������ӹ�������
		bool GetChildBoneIdxs( size_t parentIdx, vector<size_t>& childIdxs);

		// ��ȡ�����������Ӽ��ֵܹ�������
		bool GetChildSiblingBoneIdxs( size_t parentIdx, vector<size_t>& childIdxs);

	public:
		// ��ȡ��������
		virtual size_t GetNumBones() { return CM1Animation::m_header.m_iNumBones; }

		// ���ݹ�������ȡ��������
		virtual bool GetBoneIdxByName( const char* name, int& boneIdx);

		// ��ȡ�������������
		virtual Matrix44 GetBoneWorld( int boneIdx);

		// ��ȡ������ʼ����
		virtual bool GetInitBoneTM( Matrix44& out, size_t index);

	public:
		// ��ȡ������
		virtual int GetRootBone();

		// ����������ȡ������
		virtual const char* GetBoneName( size_t index);

		// ��ȡ�ֵܹ���
		virtual int GetBoneSibingIdx( size_t index);

		// ��ȡ��һ���ӹ���
		virtual int GetBoneFirstChildIdx( size_t index);

	public:
		// ��ȡ������
		virtual const size_t GetNumAnimationSet() { return CM1Animation::m_header.m_iNumAnimationSet; }

		// ��ȡ������
		virtual const char*  GetAnimationSetName( size_t index);

		// ��δ�ŵ��ӿ���
	public: 
		// ��ȡSM1AnimationSet�ṹ��
		const SM1AnimationSet* GetAnimationSet(size_t index); 

		// �������ֻ�ȡSM1AnimationSet�ṹ��
		const SM1AnimationSet* GetAnimationSet( const char* name, size_t* pIndex=NULL);
	};
}