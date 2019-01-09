#ifndef ARES_FX_DECAL_H
#define ARES_FX_DECAL_H

#include "AresFxObject.h"
#include "AresFxRenderable.h"
#include <Physics/PhysicsWorld.h>

namespace Ares
{
	//--------------------------------------------------
	// ����  2013-7-3 ����
	// ���������Ӧ������ <<��Ϸ��̾���2>> chapter 4.8
	//--------------------------------------------------
	class FxDecal : public FxObject
	{
	public:
		FxDecal();
		virtual ~FxDecal();

		// ���ò���
		void Set( const Vector3& center, const Vector3& normal, const Vector3& tangent, float width, float height, float depth, const Vector3& upDir);

		// ������������
		void SetPhysicsWorld( PhysicsWorldPtr& physicsWorld) { m_physicsWorld = physicsWorld; }

		// ��ȡRenderable
		FxRenderable& GetRenderable() { return m_renderable; }

		// ����
		virtual void FrameMove( float elpasedTime, FxEntity* fxEntity);

		// �ύ����Ⱦ����
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr);

	private:
		// ����Buffer
		void UpdateBuffer();

	private:
		Vector3					m_center;				// ���ĵ�
		Vector3					m_normal;				// ����
		vector<FxVertexFormat>	m_vertices;				// ��������
		vector<WORD>			m_indices;				// ��������
		FxRenderable			m_renderable;			// ��Ⱦ

		PhysicsWorldPtr			m_physicsWorld;		// ��������
	};
	typedef s_ptr<FxDecal> FxDecalPtr;
}

#endif