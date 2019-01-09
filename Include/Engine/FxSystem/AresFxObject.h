#pragma once

#include <string>
#include <Core/AresTransform.h>
#include <Physics/Rect3.h>

using namespace std;

namespace Ares
{
	//------------------------------------------
	// Ч���������� 2012-8-25 ����
	//------------------------------------------
	enum FxObjectType
	{
		FOT_2DPatch=0,		// 2D��Ƭ
		FOT_3DPatch,		// 3D��Ƭ
		FOT_2DGridPatch,	// 2D����Ƭ
		FOT_3DGridPatch,	// 3D����Ƭ
		FOT_ParticleSystem,	// ����ϵͳ
		FOT_Decal,			// ����
		FOT_Cloth,			// ����
		FOT_Sound,			// ��Ч
		FOT_Max,
	};

	//-----------------------------------------
	// Ч������ 2012-8-25 ����
	//-----------------------------------------
	class FxEntity;
	class RenderElementMgr;
	class FxObject
	{
	public:
		// ���캯��
		FxObject( FxObjectType type)
			: m_type( type)
			, m_entity( NULL)
		{}

		// ����������
		virtual ~FxObject() 
		{}

		// ��������
		FxObjectType GetType() { return m_type; }

		// ��ȡ����
		const char* GetName() const { return m_name.c_str(); }

		// ��ȡʵ��
		FxEntity* GetEntity() { return m_entity; }

		// ��ȡת��
		Transform* GetTransform() { return &m_transform; }

		// ��ȡ����ת��
		Transform GetWorldTransform();

		// ��ȡ���ذ�Χ��
		const Rect3& GetLocalBounds() const { return m_localBounds; }

		// ��������
		void SetName( const char* name) { m_name = name; } 

		// ����ʵ��
		void SetEntity( FxEntity* enity) { m_entity=enity; }

		// ����
		virtual void FrameMove( float elpasedTime, FxEntity* fxEntity)=0;

		// ִ��
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr)=0;

		// ���л�
		template <typename Archive> void serialize( Archive& ar, const unsigned int version)
		{
			ar & m_type;
			ar & m_name;
			ar & m_transform;
		}

	protected:
		FxObjectType	m_type;			// ����
		string			m_name;			// ����
		Transform		m_transform;	// ת������
		Rect3			m_localBounds;	// ���ذ�Χ��
		FxEntity*		m_entity;		// ʵ��
	};
}