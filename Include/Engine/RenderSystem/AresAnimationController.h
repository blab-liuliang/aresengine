#pragma once

#include <map>
#include <queue>
#include "M1Animation.h"
#include "Attachment.h"
#include <Core/AresMath.h>
#include "Engine/Foundation/Ares3DEngine_h.h"

using namespace std;
using namespace boost;

namespace Ares
{
	//-----------------------------------
	// ���������� 2011-08-10  ����
	//-----------------------------------
	class CORE_EXPORT AnimationController
	{
		typedef map<string, SAttachment> Attachments; 

	public:
		// playmode
		enum EPlayMode
		{
			STOP_SAMELAYER_DA,	// stop animation that were started in the samelayer and different animation
			STOP_SAMELAYER,		// stop all animations that were started in the samelayer
			STOP_ALL,			// stop all animations that were started with this component before playing
		};

		// queuemode
		enum EQueueMode
		{
			COMPLETE_OTHERS,// this animation will only start once all other animations have stopped playing	
			PLAY_NOW,		// this animation will start playing immediately on a duplicated animation state
		};

		// ��������
		struct SAnimationDesc
		{
			bool		m_loop;			// �Ƿ�ѭ������
			float		m_speed;		// ��������
			float		m_weight;		// Ȩ��( 0 - 1)
			int			m_layer;		// �㼶,���ȼ�

			SAnimationDesc()
			{
				m_loop	  = false;
				m_speed	  = 1.f;
				m_weight  = 1.f;
				m_layer	  = 0;
			}
		};

		// ����״̬
		struct SAnimationInfo
		{
			int						m_index;		// ����
			const SM1AnimationSet*	m_animation;	// ��ǰ���Ŷ���
			const SAnimationDesc*	m_desc;			// ��������
			float					m_elapseTime;	// �Ѳ���ʱ��
			float					m_totalTime;	// �ö�����ʱ��
			float					m_weight;		// �ں�Ȩ��
			//vector<bool>			m_boneIdxs;		// ʹ�õĹ���(Ϊ��ʹ��ȫ��)

			// ���캯��
			SAnimationInfo();
		};

		// ������Ϣ
		struct SFadeInfo
		{
			size_t		m_index;		// ��������	
			float		m_duration;		// ����ʱ��
			EPlayMode	m_playmodel;	// ����ģʽ
		};

		enum BlendState
		{
			BLENDING,		// �ں���
			BLENDED,		// �ںϽ���
		};

		enum BlendMode
		{
			FADE,			// ���ϵ���һ֡
			CROSS_FADE,		// �����ں�
		};

		// �ںϿ�����
		struct SBlendController
		{
			float				m_elapseTime;		// ����ʱ��
			float				m_duration;			// ����ʱ��
			BlendMode			m_blendModel;		// ���뷽ʽ
			vector<Transform>	m_sourceTransforms;	// Դ����
			vector<Transform>	m_currTransforms;			// ��ǰ����
			SAnimationInfo		m_currAnimInfo;		// ���붯����Ϣ
			queue<SFadeInfo>	m_crossFadeQueued;	// �����������

			BlendState			m_state;		// ״̬

			// ����
			void Update( float elapsedTime, AnimationController& owner);

		private:
			// �ں�
			void Blend( vector<Transform>& out, const vector<Transform>& source, const vector<Transform>& target, float elapseTime, float totalTime);
		};

		typedef map<int, SBlendController, std::greater<int> >  LayerController;

	public:
		// ���캯��
		AnimationController();

		// ��������
		~AnimationController();

		// ÿ֡����
		void FrameMove( float fTime, const Matrix44& matWorld);

	public:
		// ���ö���
		virtual void SetAnimation( const char* aniPath);

		// ���ö���
		virtual void SetAnimation( s_ptr<CAresAnimation> animation);

		// ��ȡ����
		virtual s_ptr<CAresAnimation> GetAnimation() { return m_animation; }

	public:
		// ��ȡ��������
		virtual SAnimationDesc* GetAnimationDesc( size_t index);

		// �������ƻ�ȡ��������
		virtual SAnimationDesc* GetAnimationDesc( const char* name);

	public:
		// ��Ӹ���
		void AddAttachment( const char* attachName);

		// ���ø���
		void SetAttachment( const char* attachName, const char* boneName);

		// ɾ������
		void DelAttachment( const char* attachName);

	public:
		// ��϶���


	public:
		// ������ �Ƿ�ѭ�� �����ٶ�(�����ٶȵİٷֱ�) 
		void PlayAnimation( const char* name, bool loop = false, float speed = 1.0f, float blend = 1.0f);

		// �������� �Ƿ�ѭ�� �����ٶ�(�����ٶȵİٷֱ�) 
		void PlayAnimationByIndex( size_t index, bool loop = false, float speed = 1.0f, float blend = 1.0f);

		// ���Ŷ���
		void PlayAnimation( size_t setIndex, float fSetTotalTime);

	public:
		// �ں�
		void Fade( size_t index, float duration=0.3f, EPlayMode playModel=STOP_SAMELAYER_DA);

		// �����ں�
		void CrossFade( size_t index, float duration=0.3f, EPlayMode playmodel=STOP_SAMELAYER_DA);

		// �����ں�
		void CrossFade( const char* name, float duration=0.3f, EPlayMode playmodel=STOP_SAMELAYER_DA);

		// ��������ں�
		void CrossFadeQueued( size_t index, float duration=0.3f, EQueueMode queueModel=COMPLETE_OTHERS, EPlayMode playmodel=STOP_SAMELAYER_DA);

	private:
		// �ں�
		void Fade( size_t index, float duration=0.3f, EPlayMode playmodel=STOP_SAMELAYER_DA, BlendMode blendMode=CROSS_FADE);

	public:
		// �����Զ���
		void SetCustomBone( size_t index, const Matrix44& mat);

		// ��ȡ�Զ���
		bool GetCustomBone( Matrix44& bone, size_t index);

	public:
		// ��ȡ�������� 
		size_t GetCurrBone( Matrix44* meshBone, const vector<int>& boneIdxs);

		// ��ȡ�������������
		const Matrix44& GetCurrBone( int boneIdx);

	private:
		// ����boneOffset
		void AttachBoneOffset();

		// ���¼ܹ�
		void UpdateHierarchy( vector<Transform>& out, const vector<Transform>& source, Transform* fartherData, int index);

		// �㼶�ں�
		void LayerBlend( float elapseTime);

		// �����ں�Ȩ�ػ�ȡ���ս��
		void CalcResultByBlendWeight( size_t boneIdx);

		// ����ָ��index������ָ��ʱ��t�ľ���
		bool ComputeAnimationTransforms( vector<Transform>& oTransforms, const SM1AnimationSet& animSet, float time, const vector<bool>& boneIdxs=vector<bool>(0));

		// ����ָ��index��ָ��������t�ľ���
		bool ComputeAnimationTransform( vector<Transform>& oTransforms, const SM1AnimationSet& animSet, float time, size_t boneIdx);

		// ���ӹ����Զ�������
		void AttachCustomBoneData( Transform& oTransform, size_t boneIdx);

	public:
		// ����������ɻص�
		void OnAnimationLoaded();

	private:
		Attachments							m_attachments;			// ����
		s_ptr<CAresAnimation>				m_animation;			// ��������
		vector<SAnimationDesc>				m_animationDesc;		// ��������	
		LayerController						m_layerController;		// �ںϷֲ����

		vector<bool>						m_customBone;			// �����Ƿ��Զ���	
		vector<Matrix44>					m_customMatrixs;		// �Զ������
		vector<Matrix44>					m_resultMatrixs;		// ������
		vector<Transform>					m_resultTransforms;		// ת��

		ShaderParamPtr						m_spabBone;				// ��������
	};
}