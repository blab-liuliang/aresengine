#include <Engine/AresRoot.h>
#include <Engine/RenderSystem/AresAnimationController.h>
#include <Physics/QuadTreeMember.hpp>

#define BONE_NOTUSE -1		// �����޶���

namespace Ares
{
	// ״̬���ƹ��캯��
	AnimationController::SAnimationInfo::SAnimationInfo()
	{		
		m_index			  = -1;
		m_weight		  = 1.f;
		m_elapseTime = 0.f;
		m_totalTime    = 0.f;

		m_desc		   = NULL;
		m_animation = NULL;
	}

	// ���캯��
	AnimationController::AnimationController()
	{
	}

	// ��������
	AnimationController::~AnimationController()
	{
		m_attachments.clear();
		m_layerController.clear();
	}

	// ���ö���
	void AnimationController::SetAnimation( const char* aniPath)
	{
		//IResource::LoadListener listener( OnResourceLoaded, this);

		m_animation = AResSystem.LoadAnimation( aniPath);
		//m_animation->AddLoadListener( listener);

		OnAnimationLoaded();
	}

	// ���ö���
	void AnimationController::SetAnimation( s_ptr<CAresAnimation> animation)
	{
		//IResource::LoadListener listener( OnResourceLoaded, this);

		m_animation = animation;
		//if( m_animation)
		//{
		//	m_animation->AddLoadListener( listener);
		//}
	}

	// ����������ɻص�
	void AnimationController::OnAnimationLoaded()
	{
		size_t numAniSet = m_animation->GetNumAnimationSet();
		size_t numBones  = m_animation->GetNumBones();

		// �������� 
		if( numAniSet)
			m_animationDesc.resize( numAniSet);

		if( numBones)
		{
			// Ϊ������������ڴ�, ����ʼ��Ϊ��λ����
			m_resultMatrixs.resize( numBones);
			m_customMatrixs.resize( numBones);
			m_resultTransforms.resize( numBones);
			m_customBone.resize( numBones, false);

			for ( size_t i=0; i<numBones; i++)
			{
				m_resultMatrixs[i].SetIdentity();
				m_customMatrixs[i].SetIdentity();
			}
		}

		// ���״̬
		m_layerController.clear();
	}

	// ���Ŷ���
	void AnimationController::PlayAnimation( size_t setIndex, float fSetTotalTime)
	{
		if( setIndex >= m_animationDesc.size())
			return;

		SBlendController& blendController = m_layerController[ m_animationDesc[setIndex].m_layer];

		blendController.m_elapseTime = 0.f;
		blendController.m_state	= BLENDED;

		blendController.m_currAnimInfo.m_index      = setIndex;
		blendController.m_currAnimInfo.m_animation  = &m_animation->m_pAnimationSets[setIndex];
		blendController.m_currAnimInfo.m_desc	    = &m_animationDesc[setIndex];
		blendController.m_currAnimInfo.m_totalTime  = fSetTotalTime;
	}

	// �ں�
	void AnimationController::Fade( size_t index, float duration, EPlayMode playModel)
	{
		Fade( index, duration, playModel, FADE);
	}

	// �����ں�
	void AnimationController::CrossFade( size_t index, float duration/*=0.3f*/, EPlayMode playmodel/*=STOP_SAMELAYER_DA*/)
	{
		Fade( index, duration, playmodel, CROSS_FADE);
	}

	// �����ں�
	void AnimationController::CrossFade( const char* name, float duration/*=0.3f*/, EPlayMode playmodel/*=STOP_SAMELAYER_DA*/)
	{
		if( !m_animation)
			return;

		// ��Ӧ��������
		size_t index;
		if( m_animation->GetAnimationSet( name, &index))
		{
			Fade( index, duration, playmodel, CROSS_FADE);
		}
	}

	// �ں�
	void AnimationController::Fade( size_t index, float duration, EPlayMode playmodel, BlendMode blendMode)
	{
		if( index >= m_animationDesc.size())
			return;

		SBlendController& blendController = m_layerController[ m_animationDesc[index].m_layer];
		SAnimationInfo& animInfo = blendController.m_currAnimInfo;
		if( playmodel == STOP_SAMELAYER_DA)
		{
			if( animInfo.m_index == index)
				return;
		}

		size_t tNumBones = m_animation->GetNumBones();

		blendController.m_sourceTransforms.resize( tNumBones);
		blendController.m_currTransforms.resize( tNumBones);

		blendController.m_blendModel = blendMode;
		blendController.m_duration	 = duration;
		blendController.m_elapseTime = 0.f;
		blendController.m_state	= BLENDING;

		// ����ȫ����
		if( !animInfo.m_animation)
			memset( blendController.m_sourceTransforms.data(), 0, sizeof( Transform) * blendController.m_sourceTransforms.size());
		else
			ComputeAnimationTransforms( blendController.m_sourceTransforms, *animInfo.m_animation, animInfo.m_elapseTime/*, animInfo.m_boneIdxs*/);

		animInfo.m_index     = index;
		animInfo.m_animation = &m_animation->m_pAnimationSets[index];
		animInfo.m_desc	     = &m_animationDesc[index];
		animInfo.m_totalTime = blendController.m_currAnimInfo.m_animation->m_header.m_fLenght;
	}

	// ��������ں�
	void AnimationController::CrossFadeQueued( size_t index, float duration, EQueueMode queueModel, EPlayMode playmodel)
	{
		if( index >= m_animationDesc.size())
			return;

		// �������Ŷ�,ֱ���ں�
		if( m_layerController.find(  m_animationDesc[index].m_layer) == m_layerController.end())
		{
			CrossFade( index, duration, playmodel);
		}
		else
		{
			SFadeInfo tFadeInfo;
			tFadeInfo.m_index    = index;
			tFadeInfo.m_duration = duration;
			tFadeInfo.m_playmodel= playmodel;

			SBlendController& blendController = m_layerController[ m_animationDesc[index].m_layer];
			blendController.m_crossFadeQueued.push( tFadeInfo);
		}
	}

	// ÿ֡����
	void AnimationController::FrameMove( float fTime, const Matrix44& matWorld)
	{
		if( !m_animation)
			return;

		if( !m_layerController.empty())
		{
			LayerBlend( fTime);

			if( !m_layerController.empty())
			{
				// ���¿������
				UpdateHierarchy( m_resultTransforms, m_resultTransforms, NULL, 0);

				// ���ӹ�����ʼ����( ת���������ռ�)
				AttachBoneOffset();
			}
		}

		// ���¹����󶨵�����
		for ( Attachments::iterator it = m_attachments.begin(); it != m_attachments.end(); it++)
		{
			Matrix44 tBoneWorld = GetCurrBone( it->second.m_boneIdx);
			Matrix44 tResult	  = matWorld * tBoneWorld;

			//it->second.m_sceneNode->SetWorldMatrix( tResult);
		}
	}

	// ���¼ܹ�
	void AnimationController::UpdateHierarchy( vector<Transform>& out, const vector<Transform>& source, Transform* fartherData, int index)
	{
		if ( !fartherData)
		{
			Transform tfIdentity;

			fartherData = &tfIdentity;		// Ĭ��ʹ�õ�λ����
		}

		out[index] = (*fartherData) * source[index];

		if( m_animation->m_pRootBone[index].m_iFirstChildIndex != -1)	 
			UpdateHierarchy( out , source, &out[index], m_animation->m_pRootBone[index].m_iFirstChildIndex);

		if(  m_animation->m_pRootBone[index].m_iSiblingIndex != -1)
			UpdateHierarchy( out, source, fartherData, m_animation->m_pRootBone[index].m_iSiblingIndex);
	}

	// ����boneOffset
	void AnimationController::AttachBoneOffset()
	{
		for( size_t i=0; i<m_resultTransforms.size(); i++)
			m_resultMatrixs[i] = m_resultTransforms[i].GetMatrix();

		for( size_t i=0; i<m_resultMatrixs.size(); i++)
		{
			Matrix44 inverseOffset = (Matrix44&)m_animation->m_pRootBone[i].m_boneOffset;

			m_resultMatrixs[i] = inverseOffset * m_resultMatrixs[i];
		}
	}

	// �������� �Ƿ�ѭ�� �����ٶ�(�����ٶȵİٷֱ�) 
	void AnimationController::PlayAnimationByIndex( size_t index, bool loop /*= false*/, float speed /*= 1.0f*/, float blend /*= 1.0f*/)
	{
		if( !m_animation)
			return;

		const SM1AnimationSet* pAnimSet = m_animation->GetAnimationSet( index);	

		if( !pAnimSet) 
			return;

		// ɾ������״̬�б���Ԫ�� 
		PlayAnimation( index, pAnimSet->m_header.m_fLenght);
	}

	// ���ò��Ŷ���״̬
	void AnimationController::PlayAnimation( const char *name, bool loop, float speed, float blend)
	{
		if(!name)	return;

		// ����AnimationSet
		size_t index;
		const SM1AnimationSet* pAnimSet = m_animation->GetAnimationSet( name, &index);	

		if( !pAnimSet) 
			return;

		PlayAnimation( index, pAnimSet->m_header.m_fLenght);
	}

	// ��ȡ�������� 
	size_t AnimationController::GetCurrBone( Matrix44* meshBone, const vector<int>& boneIdxs)
	{
		if( !m_resultMatrixs.size())
			return false;

		for ( size_t i=0; i<boneIdxs.size(); i++)
		{
			meshBone[i] = m_resultMatrixs[boneIdxs[i]];
		}

		return boneIdxs.size();
	}

	// ��ȡ�������������
	const Matrix44& AnimationController::GetCurrBone( int boneIdx)
	{
		return m_resultMatrixs[boneIdx];
	}

	// ��ȡ��������
	AnimationController::SAnimationDesc* AnimationController::GetAnimationDesc( size_t index)
	{
		if( index < m_animationDesc.size())
		{
			return &m_animationDesc[index];
		}

		return NULL;
	}

	// �������ƻ�ȡ��������
	AnimationController::SAnimationDesc* AnimationController::GetAnimationDesc( const char* name)
	{
		// ��Ӧ��������
		size_t index;
		if( m_animation->GetAnimationSet( name, &index))
		{
			if( index < m_animationDesc.size())
			{
				return &m_animationDesc[index];
			}
		}

		return NULL;
	}

	// ��Ӹ���
	void AnimationController::AddAttachment( const char* attachName)
	{

	}

	// ���ø���
	void AnimationController::SetAttachment( const char* attachName, const char* boneName)
	{

	}

	// ɾ������
	void AnimationController::DelAttachment( const char* attachName)
	{

	}

	// �����Զ���
	void AnimationController::SetCustomBone( size_t index, const Matrix44& mat)
	{
		if( mat.IsIdentity())
		{
			m_customBone[index]    = false;
			m_customMatrixs[index] = mat;
		}
		else
		{
			m_customBone[index]	   = true;
			m_customMatrixs[index] = mat;
		}
	}

	// ��ȡ�Զ���
	bool AnimationController::GetCustomBone( Matrix44& bone, size_t index)
	{
		if( index < m_customMatrixs.size())
		{
			bone = m_customMatrixs[index];

			return true;
		}

		return false;
	}


	struct SMatFactor 
	{
		const Transform*	m_mat;		// ��������
		float				m_factor;	// ����

		// ���캯��
		SMatFactor( const Transform& mat, float factor)
		{
			m_mat	 = &mat;
			m_factor = factor;
		}
	};

	void AnimationController::SBlendController::Update( float fTime,  AnimationController& owner)
	{
		// ���½���
		if( m_state == BLENDING)
		{
			m_elapseTime += fTime * m_currAnimInfo.m_desc->m_speed;
			m_currAnimInfo.m_weight = clamp(m_elapseTime / m_duration * m_currAnimInfo.m_desc->m_weight, 0.f, 1.f);

			if( m_elapseTime > m_duration)
			{
				m_state = BLENDED;

				//if( m_blendModel == CROSS_FADE)
				//	m_currAnim.m_fElapseTime = m_elapseTime;
				//else
				//	m_currAnim.m_fElapseTime = m_elapseTime - m_duration;
			}
		}
		else if( m_state == BLENDED)
		{
			m_currAnimInfo.m_elapseTime += fTime * m_currAnimInfo.m_desc->m_speed;

			// ���Ž���,�ںϻ�ȥ
			if( !m_currAnimInfo.m_desc->m_loop /*&& m_crossFadeQueued.empty()*/)
			{
				if( m_currAnimInfo.m_elapseTime > m_currAnimInfo.m_totalTime-m_duration)
				{
					m_currAnimInfo.m_weight = clamp((m_currAnimInfo.m_totalTime - m_currAnimInfo.m_elapseTime) / m_duration  * m_currAnimInfo.m_desc->m_weight, 0.f, 1.f);
				}
			}

			if( m_currAnimInfo.m_elapseTime > m_currAnimInfo.m_totalTime)
			{
				if( m_currAnimInfo.m_desc->m_loop)
					m_currAnimInfo.m_elapseTime = fmodf( m_currAnimInfo.m_elapseTime, m_currAnimInfo.m_totalTime);
				else
				{
					if( m_crossFadeQueued.empty())
						m_currAnimInfo.m_animation = NULL;
					else
					{
						SFadeInfo& fadeInfo = m_crossFadeQueued.front();

						owner.CrossFade( fadeInfo.m_index, fadeInfo.m_duration, fadeInfo.m_playmodel);
						m_crossFadeQueued.pop();
					}
				}
			}
		}

		// ��ʼ�ں�
		if( m_state == BLENDING)
		{
			// ����Ŀ���������
			if( m_blendModel == CROSS_FADE)
				m_currAnimInfo.m_elapseTime = m_elapseTime;

			// ��ʼ����ǰ����
			owner.ComputeAnimationTransforms( m_currTransforms, *m_currAnimInfo.m_animation, m_currAnimInfo.m_elapseTime/*, m_currAnimInfo.m_boneIdxs*/);

			// �ں�
			Blend( m_currTransforms, m_sourceTransforms, m_currTransforms, m_elapseTime, m_duration);
		}
		else if( m_state == BLENDED && m_currAnimInfo.m_animation)
		{
			owner.ComputeAnimationTransforms( m_currTransforms, *m_currAnimInfo.m_animation, m_currAnimInfo.m_elapseTime/*, m_currAnimInfo.m_boneIdxs*/);
		}
	}

	// �ں�
	void AnimationController::SBlendController::Blend( vector<Transform>& out, const vector<Transform>& source, const vector<Transform>& target, float elapseTime, float totalTime)
	{
		float factor = clamp( elapseTime / totalTime, 0.f, 1.f);

		for ( size_t i=0; i<out.size(); i++)
			out[i] = source[i] + ( target[i]-source[i]) * factor;
	}

	// �㼶�ں�
	void AnimationController::LayerBlend( float elapseTime)
	{
		// ÿ�����
		for ( LayerController::iterator it=m_layerController.begin(); it!=m_layerController.end(); it++)
		{
			it->second.Update( elapseTime, *this);
		}

		// ������ò�
		for ( LayerController::iterator it=m_layerController.begin(); it!=m_layerController.end();)
		{
			if( !it->second.m_currAnimInfo.m_animation)
            {
#ifdef ARES_PLATFORM_WINDOWS
				it = m_layerController.erase( it);
#endif
                A_ASSERT(false);
            }
			else
				it++;
		}

		// ����֮�����ں�,��ȡ���ս��
		if( m_layerController.empty())
			return;

		if( m_layerController.size() == 2)
			int a = 10;

		// ����������
		for ( size_t i=0; i<m_resultMatrixs.size(); i++)
		{
			CalcResultByBlendWeight( i);
		}
	}

	// �����ں�Ȩ�ػ�ȡ���ս��
	void AnimationController::CalcResultByBlendWeight(  size_t boneIdx)
	{
		// ������Ȩ��
		float tFactor   = 1.f;
		float curFactor = 0.f;
		vector<SMatFactor> factors;
		LayerController::iterator itNext;
		for ( LayerController::iterator it=m_layerController.begin(); it!=m_layerController.end(); it++)
		{
			if( tFactor > 0.f)
			{
				itNext = it; 
				if( ++itNext !=m_layerController.end())
				{		
					if( it->second.m_currAnimInfo.m_animation->m_boneUsed[boneIdx])
					{
						curFactor =  tFactor * it->second.m_currAnimInfo.m_weight;
						tFactor   -= curFactor;
						factors.push_back( SMatFactor(it->second.m_currTransforms[boneIdx], curFactor));
					}
				}
				else
				{
					// ���һ�����л������
					factors.push_back( SMatFactor(it->second.m_currTransforms[boneIdx], tFactor));
				}			
			}
		}

		// ������
		Transform result = (*factors[0].m_mat) * factors[0].m_factor;
		for ( size_t i=1; i<factors.size(); ++i)
		{
			result += (*factors[i].m_mat) * factors[i].m_factor;
		}

		m_resultTransforms[boneIdx] = result;
	}

	// ����ָ��index������ָ��ʱ��t�ľ���
	bool AnimationController::ComputeAnimationTransforms( vector<Transform>& oTransforms, const SM1AnimationSet& animSet, float time, const vector<bool>& boneIdxs)
	{
		size_t tAnimBoneUses = animSet.m_header.m_iNumBoneUses;

		if( !boneIdxs.empty())
		{
			// ���ֹ���
			for ( size_t i=0; i<tAnimBoneUses; i++)
			{
				if( boneIdxs[i])
					ComputeAnimationTransform( oTransforms, animSet, time, boneIdxs[i]);
			}
		}
		else
		{
			// ʹ�����й���
			for ( size_t i=0; i<tAnimBoneUses; i++)
			{
				ComputeAnimationTransform( oTransforms, animSet, time, i);
			}
		}

		return true;
	}

	// ����ָ��index��ָ��������t�ľ���
	bool AnimationController::ComputeAnimationTransform( vector<Transform>& oTransforms, const SM1AnimationSet& animSet, float time, size_t boneIdx)
	{
		const SM1Animation&       currAnim       = animSet.m_pAnimations[boneIdx];
		const SM1AnimationHeader& currAnimHeader = currAnim.m_header;

		// ��ǰ����δʹ�ô˹���
		if( currAnimHeader.m_iBoneIndex == BONE_NOTUSE)
			return false;

		// ��λ��
		Transform& transform = oTransforms[currAnimHeader.m_iBoneIndex];

		//// Ӧ������֡
		//if ( currAnimHeader.m_iNumScaleKeys)
		//{
		//	size_t key1 = 0, key2 = 0;

		//	// ���Ż� ���ٲ�ֵ
		//	for ( size_t i=0; i<currAnimHeader.m_iNumScaleKeys; i++)
		//	{
		//		if( time >= currAnim.m_pScaleKeys[i].m_fTime)
		//			key1 = i;
		//		else
		//			break;
		//	}

		//	key2 = key1 > ( currAnimHeader.m_iNumScaleKeys - 1)? key1 : key1 + 1;

		//	float timeDiff = currAnim.m_pScaleKeys[key2].m_fTime - currAnim.m_pScaleKeys[key1].m_fTime;

		//	if( timeDiff == 0.f)
		//		timeDiff = 1.f;

		//	float scalar = ( time - currAnim.m_pScaleKeys[key1].m_fTime) / timeDiff;

		//	Vector3 vScale = ( (Vector3&)currAnim.m_pScaleKeys[key2].m_vecKey - (Vector3&)currAnim.m_pScaleKeys[key1].m_vecKey) * scalar;
		//	vScale += (Vector3&)currAnim.m_pScaleKeys[key1].m_vecKey;

		//	Matrix44 matScale;
		//	Matrix44Scaling( matScale, vScale.x, vScale.y, vScale.z);
		//}

		// Ӧ����ת֡
		if ( currAnimHeader.m_iNumRotationKeys)
		{
			size_t key1 = 0, key2 = 0;

			// ���Ż� ���ٲ�ֵ
			for ( size_t i=0; i<currAnimHeader.m_iNumRotationKeys; i++)
			{
				if( time >= currAnim.m_pRotationKeys[i].m_fTime)
					key1 = i;
				else
					break;
			}

			key2 = key1 > ( currAnimHeader.m_iNumRotationKeys - 1)? key1 : key1 + 1;

			float timeDiff = currAnim.m_pRotationKeys[key2].m_fTime - currAnim.m_pRotationKeys[key1].m_fTime;
			float scalar = ( time - currAnim.m_pRotationKeys[key1].m_fTime) / timeDiff;

			// ��Ԫ����ֵ
			Quat quatSD[2];
			quatSD[0] = (Quat&)currAnim.m_pRotationKeys[key1].m_quatKey;
			quatSD[1] = (Quat&)currAnim.m_pRotationKeys[key2].m_quatKey;

			transform.m_rotation = QuatSlerp( quatSD[0], quatSD[1], scalar);
		}

		// Ӧ��ƽ��֡
		if ( currAnimHeader.m_iNumTransKeys)
		{
			size_t key1 = 0, key2 = 0;

			// ���Ż� ���ٲ�ֵ
			for ( size_t i=0; i<currAnimHeader.m_iNumTransKeys; i++)
			{
				if( time >= currAnim.m_pTransKeys[i].m_fTime)
					key1 = i;
				else
					break;
			}

			key2 = key1 > ( currAnimHeader.m_iNumTransKeys - 1)? key1 : key1 + 1;

			float timeDiff = currAnim.m_pTransKeys[key2].m_fTime - currAnim.m_pTransKeys[key1].m_fTime;

			if( timeDiff == 0.f)
				timeDiff = 1.f;

			float scalar = ( time - currAnim.m_pTransKeys[key1].m_fTime) / timeDiff;

			Vector3 tTrans = ( (Vector3&)currAnim.m_pTransKeys[key2].m_vecKey - (Vector3&)currAnim.m_pTransKeys[key1].m_vecKey) * scalar;
			tTrans += (Vector3&)currAnim.m_pTransKeys[key1].m_vecKey;

			transform.m_origin = tTrans;
		}

		//// ������
		//if ( currAnimHeader.m_iNumMatKeys)
		//{
		//	size_t key1 = 0, key2 = 0;

		//	// ���Ż� ���ٲ�ֵ
		//	for ( size_t i=0; i<currAnimHeader.m_iNumMatKeys; i++)
		//	{
		//		if( time >= currAnim.m_pMatKeys[i].m_fTime)
		//			key1 = i;
		//		else
		//			break;
		//	}

		//	key2 = key1 > ( currAnimHeader.m_iNumMatKeys - 1)? key1 : key1 + 1;

		//	// ��֡��ʱ�����
		//	float timeDiff = currAnim.m_pMatKeys[key2].m_fTime - currAnim.m_pMatKeys[key1].m_fTime;
		//	if( timeDiff == 0.f)
		//		timeDiff = 1.f;

		//	float scalar = ( time - currAnim.m_pMatKeys[key1].m_fTime) / timeDiff;

		//	Matrix44 matResult; 
		//	matResult  = ((Matrix44&)currAnim.m_pMatKeys[key2].m_matKey - (Matrix44&)currAnim.m_pMatKeys[key1].m_matKey) * scalar;
		//	matResult += ( Matrix44&)currAnim.m_pMatKeys[key1].m_matKey;

		//	currBone *= matResult;
		//}

		// �����Զ�������

		AttachCustomBoneData( transform, boneIdx);

		return true;
	}

	// ���ӹ����Զ�������
	void AnimationController::AttachCustomBoneData( Transform& oTransform, size_t boneIdx)
	{
		if( !m_customBone[boneIdx])
			return;

		// �ֽ���ת����ƽ��
		//Vector3    tScale;
		//D3DXQUATERNION tRotate;
		//Vector3	   tTrans;
		//D3DXMatrixDecompose( &tScale, &tRotate, &tTrans, &out);

		//// �ֽ���ת����ƽ��
		//Vector3    tScale1;
		//D3DXQUATERNION tRotate1;
		//Vector3	   tTrans1;
		//D3DXMatrixDecompose( &tScale1, &tRotate1, &tTrans1, &m_customMatrixs[boneIdx]);

		//tScale.x = tScale.x * tScale1.x;
		//tScale.y = tScale.y * tScale1.y;
		//tScale.z = tScale.z * tScale1.z;

		//tTrans = tTrans + tTrans1;

		//D3DXMatrixTransformation( &out, NULL, NULL, &tScale, NULL, &tRotate, &tTrans);
	}
}