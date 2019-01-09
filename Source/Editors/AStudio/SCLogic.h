#pragma once

#include <Engine/FxSystem/AresFxEmitter.h>
#include <EditorKit/AresWaterEk.h>
#include "CameraLogic.h"
#include "AILogic.h"
#include "EntityPutLogic.h"
#include "EntityEditLogic.h"
#include "MoveLogic.h"
#include "MapLogic.h"
#include "GpuLightMapBake.h"
#include "PhysicsLogic.h"
#include "ConfigMgr.h"
#include "InputListener.h"
#include "NetLogic.h"
#include "SettingsLogic.h"
#include "WaterEditLogic.h"
#include <Core/AresCore.h>
#include <Engine/FxSystem/AresFxEntity.h>
#include <Engine/SceneSystem/AresScene.h>
#include <EditorKit/BulletDebugDrawer.h>


namespace Ares
{
	// ���в�������
	enum EHandleType
	{
		EM_HT_NULL,					// Nothing
		EM_HT_EDITORTERRAIN,		// �༭����
		EM_HT_EDITTERRAINTEXTURE,	// �༭��������
		EM_HT_EDITOENTITY,			// �༭���������ʵ��(�ƶ� ��ת ����)
		EM_HT_PUTENTITY,			// �ڷ�ʵ��
		EM_HT_PUT_WATER,			// �ڷ�ˮ
		EM_HT_SELECT_WATER,			// ѡ��ˮ
		EM_HT_BRUSH_WATER,			// ˢˮ,����ˮ�ĸ߶�(������Ȼ�߶�)
		EM_HT_AI,					// AI�༭����
	};

	//---------------------------------------
	// �༭���߼����	2010-07-20 ����	
	//---------------------------------------
	class SCLogic
	{
	public:
		SCLogic( HWND hwnd);
		~SCLogic();

		// �Ƿ���ͣ��
		bool IsPaused();

		// ����
		void FrameMove( float fTime);

		// ��ȡ֡��
		float GetFPS()  { return m_fFPS; }

		// ��ȡ���ھ��
		HWND GetHwnd() { return m_hWnd; }

		// ��ȡ��ѡ�е�ˮƬ
		//vector<IWaterPatch*>& GetSelectedWaterPatch() { return m_selectedWaterPatch; }

		// ��ȡˮƬ�༭����
		SWaterEditorData& GetWaterEditorData() { return m_waterEditorData; }

		// ����Ҽ�����
		void OnMouseRightButtonDown();

		// ���ñ༭����
		void SetHandleType( EHandleType type);

		// ���ش��ھ��
		HWND GetHandle() { return m_hWnd; }

		// ���ر༭����
		EHandleType GetHandleType() { return m_handleType; }
		
		// ����֡��
		bool UpdateFPS( float fTime);

		// ����Alpha����ֵ
		void SetAlphaTestValue( int value);

		// ������ӰSoftNess
		void  SetShadowSampleSize( int size);

		// ���ù���͸���ٲ���
		void SetShadowLBR( float lbr);

		// �����Ƿ����ģ��
		void SetShadowBlur( bool blur);

		// �����Ƿ�����Ӱ
		void SetShadow( bool bShadow);

		// �ϲ�batch
		void  CombinationBatch();

	public:
		// ��ʾĳʵ��������
		void ShowEntityWorldBox( s_ptr<Entity>& entity);

		// ���Ĵ��ڴ�С
		void ResizeWindow( size_t width, size_t height);

	public:
		// ��ȡʵ��༭������
		CEntityEditLogic* GetEntityEditLogic() { return m_pEntityEditLogic; }

		// ��ȡʵ����ù�����
		CEntityPutLogic* GetEntityPutLogic() { return m_pEntityPutLogic; }

		// ��ȡ��ͼ�༭��
		CMapLogic* GetMapLogic() { return m_mapLogic; }

		// ��ȡAI�߼�
		CAILogic* GetAILogic() { return m_pAILogic; }

		// ��ȡ��������߼�
		PhysicsLogic* GetPhysicsLogic() { return m_physicsLogic; }

		// ��ȡ����ͼ�決������
		GpuLightmapBakerMgr* GetLightMapBakeMgr() { return &m_bakerMgr; }

		// ������߼�
		CameraLogic* GetCameraLogic() { return m_cameraLogic; }

		// ���������
		//IImageProcessManager* GetImageProcessMgr() { return m_pImageProcessMgr; }

		// ��ȡ�ƶ��߼�
		CMoveLogic*	GetMoveLogic() { return m_moveLogic; }

		// ��ȡ���������
		InputListener* GetInputListener() { return m_inputListener; }

		// ��ȡ���������
		NetLogic* GetNetLogic() { return m_netLogic; }

		SettingsLogic* GetSettingLogic() { return m_settingLogic; }

		// ��ȡ����ϵͳ
		Scene* GetScene();

	private:
		// �༭ˮ
		void EditWaterMesh();

	private:
		HWND							m_hWnd;					// ���ھ��
		float							m_fFPS;					// frames per second   
		SWaterEditorData				m_waterEditorData;		// ˮ�༭����
		//vector<IWaterPatch*>			m_selectedWaterPatch;	// ��ѡ���ˮƬ 
		InputListener*					m_inputListener;		// �����߼�
		CEntityEditLogic*				m_pEntityEditLogic;		// ʵ��༭�߼�	
		CEntityPutLogic*				m_pEntityPutLogic;		// Ҫ�ڷŵ�ʵ��
		CWaterEditLogic*				m_waterEditLogic;		// ˮ�༭�߼�
		CAILogic*						m_pAILogic;				// AI�߼�
		PhysicsLogic*					m_physicsLogic;			// �����߼�
		CameraLogic*					m_cameraLogic;		    // ���������
		//IImageProcessManager*			m_pImageProcessMgr;		// ͼ�����
		CMoveLogic*						m_moveLogic;			// �ƶ��߼�
		CMapLogic*						m_mapLogic;				// ��ͼ�߼�,���������潻��
		GpuLightmapBakerMgr				m_bakerMgr;				// ����ͼ�決������
		NetLogic*						m_netLogic;				// �����߼�
		SettingsLogic*					m_settingLogic;			// �����߼�
		Scene*							m_scene;				// ��ǰ����

	public:
		EHandleType						m_handleType;			// �������
	};

	extern  SCLogic*				g_SCLogic;
	#define SCLogic_Main			g_SCLogic
	#define SCLogic_WindowHandle	SCLogic_Main->GetHandle()
	#define SCLogic_Map				SCLogic_Main->GetMapLogic()
	#define Logic_AI				SCLogic_Main->GetAILogic()
	#define Logic_Physics			SCLogic_Main->GetPhysicsLogic()
	#define SCLogic_EntityEdit		SCLogic_Main->GetEntityEditLogic()
	#define Logic_EntityPut			SCLogic_Main->GetEntityPutLogic()
	#define Logic_LightmapBake		SCLogic_Main->GetLightMapBakeMgr()
	#define Logic_TextureSetBuild	SCLogic_Main->GetTextureSetBuild()
	#define SCLogic_Camera			SCLogic_Main->GetCameraLogic()
	#define Logic_ImageProcess		SCLogic_Main->GetImageProcessMgr()
	#define SCLogic_Move			SCLogic_Main->GetMoveLogic()
	#define Logic_Cfg				ConfigMgr::GetSingletonPtr()
	#define SCLogic_Input			SCLogic_Main->GetInputListener()
	#define Logic_Net				SCLogic_Main->GetNetLogic()
	#define Logic_Setting			SCLogic_Main->GetSettingLogic()
	#define SCLogic_Scene			SCLogic_Main->GetScene()
	#define SELogic_RenderSystem	SCLogic_Main->GetScene()->GetRenderSystem()
	#define SELogic_VisualShape		SCLogic_Main->GetScene()->GetRenderSystem().GetVisualShapeMgr()
}