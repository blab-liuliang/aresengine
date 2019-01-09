#ifndef MASS_SPRING_SYSTEM_H
#define MASS_SPRING_SYSTEM_H

#include <vector>
#include "PhysicsWorld.h"
#include <boost/array.hpp>

using namespace std;

namespace Ares
{
	//---------------------------------------
	// MassSpringSystem 2013-7-8 ����
	//---------------------------------------
	class MassSpringSystem
	{
	public:
		static const int MaxSpringPerMassPoint = 12;

		// �ʵ�
		struct MassPoint
		{
			bool		m_archor;		// �Ƿ�Ϊê��
			//float		m_mass;			// ����
			Vector3		m_position;		// λ��
			Vector3		m_normal;		// ����
			Vector2		m_uv;			// �ʵ�uv
			Vector3		m_oldPositon;	// ԭλ��
			int			m_numSpring;	// ������������
			int			m_springs[MaxSpringPerMassPoint];	// ��������

			// ���캯��
			MassPoint()
			{
				m_archor	= false;
				//m_mass		= 0.01f;
				m_position	= Vector3::Zero;
				m_oldPositon= m_position;
				m_numSpring = 0;
			}
		};

		// ��������
		enum SpringType
		{
			ST_Structural=0,		// �ṹ�Ե���
			ST_Shear,				// Ť������
			ST_Flexion,				// ��������
			ST_Total,
		};

		// ����:�����ʵ�֮���������
		struct Spring
		{
			SpringType	m_type;		// ����
			int			m_left;		// ��˵�
			int			m_right;	// �Ҷ˵�
			float		m_rest;		// ����ԭ����

			// ���캯��
			Spring()
			{
				m_type = ST_Structural;
				m_left = INVALID;
				m_right= INVALID;
				m_rest = 1.f;
			}
		};

		// ����
		struct Settings
		{
			float							m_dc;			// Air damping coefficent
			boost::array<float, ST_Total>	m_ec;			// �ṹ�Ե���ϵ��(MassSpringSystemʹ��һ�µĵ���ϵ��)
			Vector3							m_airFlotage;	// ��������
			Rect3							m_localBounds;	// ���ذ�Χ��

			// ���캯��
			Settings()
			{
				m_dc		 = 1.f;
				m_ec[0]		 = 2.f;
				m_ec[1]		 = 0.7f;
				m_ec[2]		 = 0.5f;
				m_airFlotage = Vector3( 0.f, 0.f, 0.f);
			}
		};

	public:
		MassSpringSystem();
		virtual ~MassSpringSystem();

		// ��ʼ��
		void Init( const vector<WORD>& triIndices, const vector<MassPoint>& massPoints, const vector<Spring>& springs);

		// ������������
		void SetPhysicsWorld( PhysicsWorldPtr& world) { m_physicsWorld=world; }

		// ��ȡ�豸
		const Settings& GetSettings() const { return m_settings; }

		// ��ȡ����
		const vector<WORD>& GetTriIndices() const { return m_triIndices; }

		// ��ȡ�ʵ�����
		size_t GetNumMassPoint() const { return m_massPoints.size(); }

		// ��ȡ�ʵ�
		MassPoint& GetMassPoint( size_t index) { return m_massPoints[index]; }

		// ��ȡ����
		const vector<Spring>& GetSprings() { return m_springs; }

		// ����
		void FrameMove( float elapsedTime);

	private:
		// �����ʵ㷨��
		void UpdateMassPointNormals();

		// Ӧ������(����,��,��ק,��ײ)
		void ApplyForces( float timeStep);

		// ����Լ��
		void SatisfyStructuralAndShearSpringConstraints( float timeStep);

		// ��ײԼ��
		void SatisfyCollisionConstraints();

		// ��Ӧ
		float2 Responsiveness( MassPoint& p0, MassPoint& p1);

		// ��������
		void SpringDistanceConstraint( MassPoint& p0, MassPoint& p1, const Spring& spring, float timeStep);

		// ģ�����
		void PrepareForNextSimulation( float timeStep);

	private:
		Settings				m_settings;				// ����
		vector<WORD>			m_triIndices;			// ����������(TriangleList)
		vector<MassPoint>		m_massPoints;			// �ʵ�
		vector<Spring>			m_springs;				// ����
		PhysicsWorldPtr			m_physicsWorld;			// ��������

		float					m_oldTimeStep;			// ģ�ⲽ��
	};
}

#endif