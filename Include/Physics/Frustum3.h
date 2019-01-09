#pragma once

#include <Core/AresCore.h>
#include "Physics/Rect3.h"

using namespace std;

namespace Ares
{
	//-----------------------------------------------------
	// �Ľ������׶�޳��㷨 <<game programing gems 5>>
	//							    Page 52  
	//		2010-08-24   ����
	//-----------------------------------------------------
	class Frustum3 : public Shape
	{
	public:
		enum Flags
		{
			EM_AABB_UPDATE =0,  // AABB��Χ����Ҫ����
			EM_VERTEX_UPDATE,	// �˸�������Ҫ���� 
		};

		// ���캯��
		Frustum3();

		// ����Near
		void  SetNear( const float fNear);

		// ��ȡNear
		float GetNear() const { return m_fNearZ; }

		// ����Far
		void  SetFar( const float fFar);

		// ��ȡFar
		float GetFar() const { return m_fFarZ; }

		// ����Perspective  ����Щ���ݲ����׸ı䣩
		void  SetPerspective( const float fovH, const float fAspect, const float fNear, const float fFar);

		// ����
		void  Build( const Vector3& vEye, const Vector3& vForward, const Vector3& vUp, bool haveNormalize=false);

		// �����˶��������
		virtual Vector3 CalculateLocalInertia( float mass) { A_ASSERT(false); return Vector3::Zero; }

		// ��ȡAABB��Χ��
		const Rect3& GetAABB();

		// ��ȡ�˸�����
		const Vector3*  GetVertexs();

		// ����AABB��Χ��
		virtual void BuildAABB( Rect3& box, const Transform& trans) const;

		// ��ȡƽ��
		bool BuildPlane( vector<Vector3>& plane, float length);

		// �жϵ��Ƿ���ƽ��ͷ����
		bool  IsPointIn( const Vector3& point);

		// �ж����Ƿ���ƽ��ͷ����
		bool  IsSphereIn( const Vector3& center, const float fRadius);

		// �ж�AABB��Χ��
		bool  IsAABBIn( const Vector3& minPoint, const Vector3& maxPoint) const;

		// ��ȡ������
		const Vector3& GetRight() const { return m_vRight; }

		// ��ȡ�Ϸ���
		const Vector3& GetUp() const { return m_vUp; }

	private:
		Vector3	  m_vEyePosition,		// �ӵ�
				  m_vForward,			// ǰ������
				  m_vRight,				// ��������
				  m_vUp;				// ������

		float     m_fRfactor,			// ���ж�����
				  m_fUfactor;			// ���ж�����

		float     m_fNearZ,				// ������
			      m_fFarZ;				// Զ����	

		Vector3   m_vVertexs[8]; 		
		                                    //     7+------+6
		                                    //     /|     /|         z
		                                    //    / |    / |         |
		                                    //   / 4+---/--+5		 |
		                                    // 3+------+2 /          *-----x
		                                    //  | /    | /          /
		                                    //  |/     |/          /
		                                    // 0+------+1		  y   		 
		Rect3		 m_AABB;				// ��Χ��
		bitset<16>   m_flags;				// ���
	};
}