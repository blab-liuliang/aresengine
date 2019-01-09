#include <Engine/RenderSystem/AresModelIDCard.h>
#include <Engine/RenderSystem/M1Animation.h>

namespace Ares
{
	// ���캯��
	CAresAnimation::CAresAnimation()
	{
	}

	// ��������
	CAresAnimation::~CAresAnimation()
	{
	}

	// ������Դ
	//bool CAresAnimation::LoadResource()
	//{
		//if ( GetResPath().empty() || IsResourceLoaded())	
		//	return false;

		//if( !this->Load( GetResPath().c_str()))
		//	return false;

		// ����Ѽ��� ����
		//NotifyLoaded();
		//NotifyEnabled();

	//	return true;
	//}

	// ��ȡ�����������Ӽ��ֵܹ�������
	bool CAresAnimation::GetChildSiblingBoneIdxs( size_t parentIdx, vector<size_t>& childIdxs)
	{
		// ��¼�ӽ��,�ֵܽ��
		int childIdx = m_pRootBone[parentIdx].m_iFirstChildIndex;
		int sibIdx	 = m_pRootBone[parentIdx].m_iSiblingIndex;

		if( childIdx != -1)
		{
			childIdxs.push_back( childIdx);
			GetChildSiblingBoneIdxs( childIdx, childIdxs);
		}

		if(  sibIdx != -1)
		{
			childIdxs.push_back( sibIdx);
			GetChildSiblingBoneIdxs( sibIdx, childIdxs);
		}

		return false;
	}

	// ��ȡ�����������ӹ�������
	bool CAresAnimation::GetChildBoneIdxs( size_t parentIdx, vector<size_t>& childIdxs)
	{
		if( m_pRootBone[parentIdx].m_iFirstChildIndex != -1)	
			return GetChildSiblingBoneIdxs( parentIdx, childIdxs);

		return false;
	}

	// ��ȡSM1AnimationSet�ṹ��
	const SM1AnimationSet* CAresAnimation::GetAnimationSet(size_t index)
	{
		if ( index >= CM1Animation::m_header.m_iNumAnimationSet)
			return NULL;

		return  &m_pAnimationSets[index];

		return NULL;
	}

	// �������ֻ�ȡSM1AnimationSet�ṹ��
	const SM1AnimationSet* CAresAnimation::GetAnimationSet(  const char* name,  size_t* pIndex/*=NULL*/)
	{
		for ( int i=CM1Animation::m_header.m_iNumAnimationSet-1; i>=0; i--)
			if ( strcmp( name, m_pAnimationSets[i].m_header.m_cName) == 0)
			{
				if( pIndex)
					*pIndex = i;

				return &m_pAnimationSets[i];
			}

			return NULL;
	}

	// ���ݹ�������ȡ��������
	bool CAresAnimation::GetBoneIdxByName( const char* name, int& boneIdx)
	{
		for ( unsigned int i=0; i<CM1Animation::m_header.m_iNumBones; i++)
		{
			if( strcmp( m_pRootBone[i].m_cName, name) == 0)
			{
				boneIdx = (int)i;

				return true;
			}
		}

		return false;
	}

	// ��ȡ�������������
	Matrix44 CAresAnimation::GetBoneWorld( int boneIdx)
	{
		Matrix44 tReturn;

		//D3DXMatrixTranspose( &tReturn, &(D3DXMATRIX&)m_boneMatrixs[boneIdx]);

		return tReturn;
	}

	// ��ȡ������
	const char* CAresAnimation::GetAnimationSetName( size_t index)
	{
		if( index < GetNumAnimationSet())
		{
			return m_pAnimationSets[index].m_header.m_cName;
		}

		return NULL;
	}

	// ��ȡ������
	int CAresAnimation::GetRootBone()
	{
		return 0;
	}

	// ����������ȡ������
	const char* CAresAnimation::GetBoneName( size_t index)
	{
		return m_pRootBone[index].m_cName;
	}

	// ��ȡ�ֵܹ���
	int CAresAnimation::GetBoneSibingIdx( size_t index)
	{
		return m_pRootBone[index].m_iSiblingIndex;
	}

	// ��ȡ��һ���ӹ���
	int CAresAnimation::GetBoneFirstChildIdx( size_t index)
	{
		return m_pRootBone[index].m_iFirstChildIndex;
	}

	// ��ȡ������ʼ����
	bool CAresAnimation::GetInitBoneTM( Matrix44& out, size_t index)
	{
		if( index < CM1Animation::m_header.m_iNumBones)
		{
			Matrix44Inverse( out, (Matrix44&)m_pRootBone[index].m_boneOffset);

			return true;
		}

		return false;
	}
}