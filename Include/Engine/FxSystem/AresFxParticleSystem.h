#pragma once

#include <vector>
#include <deque>
#include <map>
#include "AresFxObject.h"
#include "AresFxEmitter.h"
#include "AresFxModifier.h"
#include "Pool.h"
#include "AresFxModel.h"
#include "AresFxParticle.h"
#include "AresFxRenderable.h"
#include "AresFxInterpolater.h"
#include <Physics/Shapes.h>

using namespace std;

namespace Ares
{
	//------------------------------------------------------
	// Ч���� 2011-9-14   ����
	//------------------------------------------------------
	class FxParticleSystem : public FxObject
	{
		friend class FxParticle;
		friend void SwapParticles( FxParticle& a, FxParticle& b);
	private:
		// ������
		enum EGroupType
		{
			PARTICLE,		// ������
			STRIPE,			// ����
			MODEL,			// ģ��
		};

		// ����������
		struct SEmitterData
		{
			FxEmitter*		m_emitter;
			size_t			m_numParticles;
		};

		// ��������
		struct SCreationData
		{
			size_t			m_num;
			Vector3			m_position;
			Vector3			m_velocity;
			const FxZone*  m_zone;
			FxEmitter*		m_emitter;
			bool			m_full;
		};

		typedef vector<SEmitterData> EmitterDataList;
		typedef vector<FxModifier*>  ModifiersList;

	public:
		FxParticleSystem();
		FxParticleSystem( FxModel* model, size_t capacity=CPool<FxParticle>::DEFAULT_CAPACITY);

		// ��ȡ������
		virtual size_t GetNumParticles() { return m_particlePool.GetNumActive(); }

		// ��ȡ��Ⱦ����
		FxRenderablePtr GetRenderable() { return m_renderable; }

	public:
		// ��������
		void SetCapacity( size_t capacity);

		// ǿ���趨��Χ��
		virtual void SetBoundingBox( const Rect3& boundingBox) { m_boundingBox = boundingBox; }

		// ��ȡ��Χ��
		virtual const Rect3& GetBoundingBox() { return m_boundingBox; }

		// updates this group by a step time
		virtual void FrameMove( float elapsedTime,  FxEntity* fxEntity);

		// ��Ⱦ
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr);

	public:
		// ��ȡ����ģ�� 
		virtual FxModel* GetModel() { return m_model; }

		// Gets the friction coefficient of this group
		virtual float GetFriction() const { return m_friction; }

		// ��ȡ����
		FxParticle& GetParticle( size_t index) { return m_particlePool[index]; }

	public:
		// ��ȡ����
		const Vector3& GetGravity() const { return m_gravity; }

		// ��������
		void SetGravity( const Vector3& gravity) { m_gravity = gravity; }

		// Adds an emitter in this group, if emitter is already in the group, it will no be inserted again.
		virtual void AddEmitter( FxEmitter* emitter);

		// Removes an emitter from this group
		virtual void RemoveEmitter( FxEmitter* emitter);

		// Adds an modifier in this group
		virtual void AddModifier( FxModifier* modifier);

		// Removes an modifier from this group
		virtual void RemoveModifier( FxModifier* modifier);

		// Serialize
		BOOST_SERIALIZATION_SPLIT_MEMBER()
		template<typename Archive> void save( Archive & ar, const unsigned int version) const
		{
			ar & boost::serialization::base_object<FxObject>(*this);
			ar & m_model;
			ar & m_emitters;
			//ar & m_modifiers;
			ar & m_friction;
			ar & m_gravity;
			ar & m_capacity;
			ar & m_numBufferedParticles;
			//ar & m_render;
		}
		template<typename Archive> void load( Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<FxObject>(*this);
			ar & m_model;
			ar & m_emitters;
			//ar & m_modifiers;
			ar & m_friction;
			ar & m_gravity;
			ar & m_capacity;
			ar & m_numBufferedParticles;
			//ar & m_render;

			SetCapacity( m_capacity);
		}

	private:
		// ��������
		void SortParticles();

		// ��������
		void SortParticles( int start, int end);

		// �������
		void ComputeDistance();

		// �������
		void PushParticle( EmitterDataList::iterator& emitterIt, size_t& numManualBorn);

		// ��������
		void LaunchParticle( FxParticle& particle, EmitterDataList::iterator& emitterIt, size_t& numManualBorn);

		// �ֹ�ɾ��
		void PopNextManualAdding( size_t& numManualBorn);

		// ����AABB��Χ��
		void UpdateAABB( const FxParticle& particle);

		// �ؼ�֡��ֵ
		void KeyFrameInterpolate();

		// ����Buffer
		void UpdateBuffer();

	private:
		float				m_life;					// ����
		EGroupType			m_type;					// ������
		FxModel*			m_model;				// model
		vector<FxEmitter*>  m_emitters;				// ���ӷ�����
		vector<FxModifier*> m_modifiers;			// �޸���

		EmitterDataList		m_activeEmitters;		// ��Ծ�ķ�����
		ModifiersList		m_activeModifiers;		// �޸���

		FxInterpolater		m_interpolater;			// ��ֵ��

		float				m_friction;				// Ħ����
		Vector3				m_gravity;				// ����

		size_t						m_capacity;		// ����
		CPool<FxParticle>			m_particlePool;	// ���ӳ�
		FxParticle::SParticleData*	m_particleData;	// ��������	

		float*			m_particleCurrentParams;	// Sotres the current parameters values of the particles
		float*			m_particleExtendedParams;	// Stores the extended parameters values of the particles

		deque<SCreationData>m_creationBuffer;		// createion Buffer
		size_t				m_numBufferedParticles;	// ������

		bool (*m_fUpdate)(FxParticle&, float);		// ���Ӹ��º���
		void (*m_fBirth) (FxParticle&);				// ���ӳ�������
		void (*m_fDeath) (FxParticle&);				// ������������

		bool				m_boundingBoxEnabled;	// �Ƿ�ʹ�ð�Χ��
		bool				m_sortingEnabled;		// �Ƿ�����
		bool				m_disComputeEnabled;	// �Ƿ���о������
		Rect3				m_boundingBox;			// ��Χ��

		FxRenderablePtr		m_renderable;				// ��Ⱦ��
	};
}