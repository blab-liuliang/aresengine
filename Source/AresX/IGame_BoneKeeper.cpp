#include "IGame_BoneKeeper.h"
#include "AeConfig.h"
#include <algorithm>

namespace M1_IGame
{
	extern IGameScene *     g_pIGame;
	extern SExportConfig	g_config;	// ��������

	// ���캯��
	CBoneKeeper::CBoneKeeper()
	{

	}

	// ��ȡ������offset matrix
	static GMatrix GetBoneOffset( IGameNode* boneNode)
	{
		GMatrix bT = boneNode->GetWorldTM( 0);

		IGameNode* parent = boneNode->GetNodeParent();

		if( parent)
		{
			GMatrix pT = parent->GetWorldTM( 0);

			return bT * pT.Inverse();
		}
	
		return bT;
	}

	// ��ʼ��
	void CBoneKeeper::Init(  vector<IGameSkin*>& gameSkins)
	{
		// skin����ʹ�õĹ���
		for ( size_t i=0; i<gameSkins.size(); i++)
		{
			for( int j=0; j<gameSkins[i]->GetTotalSkinBoneCount(); j++)
			{
				IGameNode* pNode = gameSkins[i]->GetIGameBone( j);
				if( pNode)
				{
					GMatrix matInit;

					// ע����skinδʹ�ô˹���,�򷵻�false. matInit������Ϊ��λ����
					bool result = gameSkins[i]->GetInitBoneTM( pNode, matInit);

					// ������ʼֻ����ת��λ��
					Ares::Transform initTransform		 = GMatrixToAresTransform( matInit);
					Ares::Matrix44	inintMat			 = initTransform.GetMatrix();
					Matrix44Inverse( inintMat, inintMat);

					AddBoneNode( pNode, inintMat);
				}
			}
		}

		// �޹��� �˳�
		if( !m_boneNodes.size())
			return;

		// ��֤��0����������ڵ�
		if( !IsRootBone( m_boneNodes[0]))
		{
			for ( size_t i=1; i<m_boneNodes.size(); i++)
				if( IsRootBone( m_boneNodes[i]))
				{
					IGameNode* tN = m_boneNodes[0];
					m_boneNodes[0] = m_boneNodes[i];
					m_boneNodes[i] = tN;

					std::swap( m_boneInitTransform[0], m_boneInitTransform[i]);

					break;
				}
		}
	}

	// ���ҹ�������
	int  CBoneKeeper::GetBoneID( IGameNode* pGameNode)
	{
		for ( size_t i=0; i<m_boneNodes.size(); i++)
		{
			if ( pGameNode == m_boneNodes[i])
				return i;
		}
		
		// ���ܳ��ֵ����( Bug)
		return 0;
	}

	// ��ӹ������
	void CBoneKeeper::AddBoneNode( IGameNode* pBoneNode, Ares::Matrix44& matTransform)
	{
		for ( size_t i=0; i<m_boneNodes.size(); i++)
			if ( pBoneNode == m_boneNodes[i])
			{
				// ��֤��ȷ�ĳ�ʼ������
				if( m_boneInitTransform[i].IsIdentity())
					m_boneInitTransform[i] = matTransform;

				return;
			}

		m_boneNodes.push_back( pBoneNode);
		m_boneInitTransform.push_back( matTransform);
	}

	// ���������ṹ
	void CBoneKeeper::BuildBoneStruct( CM1Animation& m1Animation)
	{
		m1Animation.m_header.m_iNumBones = m_boneNodes.size();

		if ( !m_boneNodes.size())
			return;

		m1Animation.m_pRootBone = new SM1Bone[ m_boneNodes.size()];

		vector<size_t> rootBones;

		// ��������
		for ( size_t i=0; i<m_boneNodes.size(); i++)
		{
			strcpy( m1Animation.m_pRootBone[i].m_cName, m_boneNodes[i]->GetName());

			// ���õ�һchild
			m1Animation.m_pRootBone[i].m_iFirstChildIndex = GetFirstChildIndex( m_boneNodes[i]);

			// �����ֵܽ��
			m1Animation.m_pRootBone[i].m_iSiblingIndex = GetSiblingIndex( m_boneNodes[i]);

			// InitMatrix
			//Transform tfT = m_boneInitTransform[i];
			//if( IsRootBone( m_boneNodes[i]))
				//tfT.m_rotation.y = -tfT.m_rotation.y;
			//tfT.m_origin.x *= g_config.m_scale.x;
			//tfT.m_origin.y *= g_config.m_scale.y;
			//tfT.m_origin.z *= g_config.m_scale.z;
			std::memcpy( m1Animation.m_pRootBone[i].m_boneOffset, &m_boneInitTransform[i], sizeof(Ares::Matrix44));

			// ��¼������
			if ( IsRootBone( m_boneNodes[i]))
			{
				rootBones.push_back(i);
			}
		}

		// �������������
		for ( size_t i=0; i<rootBones.size()-1; i++)
		{
			m1Animation.m_pRootBone[rootBones[i]].m_iSiblingIndex = rootBones[i+1];
		}

		// ��֤�������ȷ��
		vector<SM1Bone> boneStructs;
		for ( size_t i=0; i<m_boneNodes.size(); i++)
		{
			boneStructs.push_back( m1Animation.m_pRootBone[i]);
		}
		int a = 10;
	}

	// �Ƿ���������
	bool  CBoneKeeper::IsRootBone( IGameNode* pGameNode)
	{
		IGameNode* pGameParent = pGameNode->GetNodeParent();
		if( !pGameParent)
			return true;

		if( !IsBone( pGameParent))
			return true;

		return false;
	}

	// ������������(һ�λᵼ��)
	void CBoneKeeper::BuildAnimationSets( CM1Animation& m1Animation)
	{
		if ( !m_boneNodes.size())
			return;

		Interval interval;
		interval.SetStart( g_pIGame->GetSceneStartTime());
		interval.SetEnd( g_pIGame->GetSceneEndTime());
		float    fTime = TicksToSec( interval.End() - interval.Start());

		// �޸�header
		m1Animation.m_header.m_iNumAnimationSet = 1;

		m1Animation.m_pAnimationSets = new SM1AnimationSet[ m1Animation.m_header.m_iNumAnimationSet];

		strcpy( m1Animation.m_pAnimationSets[0].m_header.m_cName, "default");
		m1Animation.m_pAnimationSets[0].m_header.m_fLenght = fTime;						// ����ʱ��
		m1Animation.m_pAnimationSets[0].m_header.m_iNumBoneUses = m_boneNodes.size();
		m1Animation.m_pAnimationSets[0].m_pAnimations  = new SM1Animation[m_boneNodes.size()];

		// cycle through every bone( Ӧ�ÿ����Ż�,ĳЩ����������������δ�����仯,���豣��)
		for ( size_t i=0; i<m_boneNodes.size(); i++)
		{
			SM1Animation& boneAnimation = m1Animation.m_pAnimationSets[0].m_pAnimations[i];

			// ��������
			boneAnimation.m_header.m_iBoneIndex = i;

			Control* pControl = m_boneNodes[i]->GetMaxNode()->GetTMController();
			IGameControl* pGameControl = m_boneNodes[i]->GetIGameControl();
			if ( pControl)
			{
			}
			else
			{
				int a = 10;
			}
		}
	}

	// ���ҵ�һ�ӽ������
	int  CBoneKeeper::GetFirstChildIndex( IGameNode* pNode)
	{
		for ( int i=0; i<pNode->GetChildCount(); i++)
		{
			if ( IsBone( pNode->GetNodeChild(i)))
			{
				return GetBoneID( pNode->GetNodeChild(i));
			}
		}

		return -1;
	}

	// ���ҽ����ֵܹ���
	int  CBoneKeeper::GetSiblingIndex( IGameNode* pNode)
	{
		IGameNode* pParentNode = pNode->GetNodeParent();
		if ( pParentNode)
			for ( int i=0; i<pParentNode->GetChildCount(); i++)
				if ( pNode == pParentNode->GetNodeChild(i))
				{
					int tIndex = i+1;
					while( tIndex < pParentNode->GetChildCount())
					{
						if ( IsBone( pParentNode->GetNodeChild( tIndex)))
						{
							return GetBoneID( pParentNode->GetNodeChild( tIndex));
						}

						tIndex++;
					}
				}

		return -1;
	}

	// �ý���Ƿ�Ϊjoint
	bool  CBoneKeeper::IsBone( IGameNode* pNode)
	{
		vector<IGameNode*>::iterator pos = find( m_boneNodes.begin(), m_boneNodes.end(), pNode);
		if( pos == m_boneNodes.end())
			return false;

		return true;
	}
}