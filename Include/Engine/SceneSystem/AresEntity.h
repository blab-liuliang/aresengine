#pragma once

#include <stdio.h>
#include <string>
#include <Core/AresCore.h>
#include <Physics/Shapes.h>
#include <Physics/CollisionObject.h>
#include "Engine/RenderSystem/AresRenderable.h"
#include <Engine/CameraSystem/AresCameraSystem.h>

using namespace std;

namespace Ares
{
	//---------------------------------
	// ʵ������ 2012-6-21 ����
	//---------------------------------
	enum EntityType
	{
		ET_Entity,
		ET_Render	= 0,
		ET_Light,
		ET_Sound,
		ET_Physics,
	};

	//----------------------------------
	// ʵ����ϸ���� 2012-6-21 ����
	//----------------------------------
	enum EntityTypeDetail
	{
		ED_Entity,
		ED_Model			= 0,
		ED_Terrain,
		ED_Ocean,
		ED_FxGroup,					// ������
		ED_LightAmbient,
		ED_LightDirection,
		ED_LightPoint,
		ED_LightSpot,
		ED_Physics,
		ED_ClothFabric,				// ����
		ED_VisualShpae,
	};

	//----------------------------------
	//  ��Ⱦʵ�壺2010-07-05   ����
	//----------------------------------
	class Scene;
	class Entity
	{
	public:
		Entity( EntityType type, EntityTypeDetail typeDetail);
		virtual ~Entity();
	
		// ��ȡʵ����
		const char* GetName();

		// ��ȡ����
		EntityType GetType() { return m_type; }

		// ��ȡ��������
		EntityTypeDetail GetTypeDetail() { return m_typeDetail; }

		// ��ȡת������
		const Transform& GetTransform();

		// ����ת��
		void SetTransform( const Transform& transform);

		// ��ȡ��ײ����
		CollisionObject& GetCollSift() { return m_collSift; }

		// ����ʵ����(��֤����������Ψһ)
		void SetName( const char* name);

		// ��ȡ��Χ��
		Rect3 GetLocalBounds();

		// ��ȡ�����Χ��
		Rect3 GetWorldBounds();

		// ��ȡ��������
		Scene* GetScene() { return m_scene; }

		// ��ȡ��Ӧ�����ϵͳ
		CameraSystem& GetCameraSystem();

		// �Ƿ�Ϊ��̬��Ⱦʵ��(unity3d)
		bool IsStatic() const { return m_static; }

		// �����Ƿ�Ϊ��̬
		void SetStatic( bool _static) { m_static = _static; }

		// ����ʵ���Χ��
		void  SetLocalBounds( const Rect3& rect);

	public:
		// ����
		virtual void FrameMove( float fTime);

		// ��ӵ�������Ϣ
		virtual void OnAddToScene( Scene* scene);

		// �ύ��ȾԪ��
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr)=0;

	protected:
		bool				m_bEnabled;				// �Ƿ����
		string				m_name;					// ʵ����(��������ʵ��)	
		bool				m_static;				// ��̬��Ⱦʵ��ɽ��й���ͼ�決, ��̬��ײʵ������һ�����Ż�
		EntityType			m_type;					// ����
		EntityTypeDetail	m_typeDetail;			// ��������
		CollisionObject		m_collSift;				// �������(���ڿɼ���ɸѡ��)
		Scene*				m_scene;				// �������� 
	};

	typedef s_ptr<Entity>  EntityPtr;
}