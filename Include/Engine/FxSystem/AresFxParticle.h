#pragma once

#include <Core/AresMath.h>
#include <Engine/FxSystem/AresFxModel.h>

namespace Ares
{
	//----------------------------------------------
	// Particle 2011-9-14  ����
	//     A Particle is the primitive on which all 
	// the SPARK engine relies. Particles are design-
	// ed to be handled in large amounts( called group)
	// This is why the user cannot update or render
	// directly a single particle
	//	   Note that the particle class is only a class
	// that presents an interface to the user, particles
	// data are stored in the groups. This is why copying
	// a particle will not copy its data.
	//----------------------------------------------
    class FxParticleSystem;
	class FxParticle
	{
		friend class FxParticleSystem;
		friend void SwapParticles( FxParticle& a, FxParticle& b);
	public:
		// ��������
		struct SParticleData
		{
			Vector3 m_oldPosition;
			Vector3 m_position;
			Vector3 m_velocity;
			float	m_age;
			float	m_life;
			float	m_sqrDist;

			// constructor
			SParticleData()
			{	
				m_oldPosition = Vector3::Zero;
				m_position    = Vector3::Zero;
				m_velocity    = Vector3::Zero;
			}
		};

	public:
		// ��ʼ��
		virtual void Init();

		// ����
		virtual bool Update( float deltaTime);

	public:
		// ��ȡ��Ӧ�������͵ĵ�ǰֵ
		virtual float GetParamCurrentValue( FxModel::EModelParam type) const;

	public:
		// ��ȡλ��
		virtual const Vector3& GetPosition()const { return m_data->m_position; }

		// ����λ��
		virtual void SetPosition( const Vector3& position) { m_data->m_position = position; } 

		// ��ȡԭλ��
		virtual const Vector3& GetOldPosition()const { return m_data->m_oldPosition; }

		// ����ԭλ��
		virtual void SetOldPosition( const Vector3& position) { m_data->m_oldPosition = position; }

		// ��ȡ�ٶ�
		virtual const Vector3& GetVelocity()const { return m_data->m_velocity; }

		// �����ٶ�
		virtual void SetVelocity( const Vector3& velocity) { m_data->m_velocity = velocity; }

	public:
		// �ڲ����
		void InterpolateParameters();

		// ��������ƽ��
		void ComputeSqrDist();

		// ��ȡ���ӵĴ��ʱ�� 
		float GetAge() const { return m_data->m_age; }

		// ��ȡʡ����ʱ�� 
		float GetLifeLeft() const { return m_data->m_life; }

		// ��ȡ��ɫ
		ColorRGB GetColor(); 

		// ������ɫ
		void SetColor( const ColorRGB& color);

	private:
		// ���캯��
		FxParticle( FxParticleSystem* group, size_t index);

		// ��ȡģ��
		FxModel* GetModel() const;

	private:
		FxParticleSystem*	m_group;			// ��
		size_t				m_index;			// ����

		SParticleData*		m_data;				// ����
		float*				m_currentParams;	// ��ǰ����
		float*				m_extendedParams;	// ��չ����
	};

	// swaps particle data. Used internally. Do not use with particles that are not from the same group
	extern void SwapParticles( FxParticle& a, FxParticle& b);
}