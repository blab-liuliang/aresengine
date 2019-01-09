#pragma once

#include <set>

using namespace std;

namespace Ares
{
	//----------------------------------
	// InterpolatorEntry 2011-9-21 ����
	//----------------------------------
	struct SInterpolatorEntry
	{
		float	m_x;		// x value of this entry
		float	m_y0;		// y first value of this entry
		float   m_y1;		// y second value of this entry

		// constructor
		SInterpolatorEntry() : m_x( 0.f), m_y0( 0.f), m_y1( 0.f) {}

		// constructor with y0 and y1 having the same value
		SInterpolatorEntry( float x, float y) : m_x( x), m_y0( y), m_y1( y) {}

		// constructor and interpolate entry
		SInterpolatorEntry( float x, float y0, float y1) : m_x( x), m_y0( y0), m_y1( y1) {}

		// used internally
		SInterpolatorEntry( float x) : m_x( x) {}

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_x;
			ar & m_y0;
			ar & m_y1;
		}
	};

	// forward declaration to allow the set of entries in interpolator to be constructed
	bool operator < (const SInterpolatorEntry& entry0, const SInterpolatorEntry& entry1);

	//---------------------------------
	// Interpolate 2011-9-21 ����
	//---------------------------------
	class FxParticle;
	class FxModelInterpolator
	{
		friend class FxParticle;
		friend class FxModel;

		typedef float( FxModelInterpolator::*ComputeXFun)( const FxParticle&) const;
	public:
		// ����������
		enum EInterpolationType
		{
			INTERPOLATOR_LIFETIME,		// life time as the value used to be interpolate
			INTERPOLATOR_AGE,			// the age as the value used to be interpolate
			INTERPOLATOR_PARAM,			// a parameter as the value used to interpolate
			INTERPOLATOR_VELOCITY,		// the square norm of the velocity as the value used to interpolate
		};

	public:
		FxModelInterpolator();
		~FxModelInterpolator() {}

		// ��ȡX���ű仯��
		float GetScaleXVariation() const { return m_scaleXVariation; }

		// ��ȡXƫ�����ı仯��
		float GetOffsetXVariation() const { return m_offsetXVariation; }

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_graph;
			ar & m_type;
			ar & m_param;
			ar & m_loopingEnabled;
			ar & m_scaleXVariation;
			ar & m_offsetXVariation;
		}

	private:
		// ��ֵ
		float Interpolate( const FxParticle& particle, int interpolateParam, float ratioY, float offsetX, float scaleX);
	
		// ��ֵY 
		float InterpolateY( const SInterpolatorEntry& entry, float ratio);

		// ��������ʱ��
		float ComputeXLifeTime( const FxParticle& particle) const;

		// ����Age
		float ComputeXAge( const FxParticle& particle) const;

		// ����X����
		float ComputeXParam( const FxParticle& particle) const;

		// ����X velocity
		float ComputeXVelocity( const FxParticle& particle) const;

	private:
		set<SInterpolatorEntry> m_graph;				// ��ֵ�ؼ�֡

		EInterpolationType		m_type;					// �����ֵ������
		int						m_param;				// ��������
		bool					m_loopingEnabled;		// ��ѭ��

		float					m_scaleXVariation;		// X����ֵ�仯��
		float					m_offsetXVariation;		// Xƫ��ֵ�仯��

		static ComputeXFun		m_computeXFun[4];		// ����X����
	};

	// ����
	// ��ֵY
	inline float InterpolateY( const SInterpolatorEntry& entry, float ratio)
	{
		return entry.m_y0 + ( entry.m_y1 - entry.m_y0) * ratio;
	}

	//
	// Functions to sort the entries on the interpolator graph
	// forward declaration to allow the set of entries in interpolator to be constructed
	inline bool operator < (const SInterpolatorEntry& entry0, const SInterpolatorEntry& entry1)
	{
		return entry0.m_x < entry1.m_x;
	}
}