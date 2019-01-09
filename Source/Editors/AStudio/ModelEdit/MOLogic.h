#pragma once

#include "MOLogicHelper.h"
#include "MOCameraLogic.h"
#include "MOConfigMgr.h"
#include "MOModelEdit.h"
#include "MOLightmapUVBuild.h"
#include "MOLightmapUVRender.h"
#include "MOInputListener.h"
#include "MOCollisionBuildLogic.h"
#include "MOTransformLogic.h"
#include "MOLightEditLogic.h"
#include <Engine/SceneSystem/AresScene.h>
#include <EditorKit/Ares3DAxis.h>
#include <Core/AresCore.h>

namespace Ares
{
	//---------------------------------------
	// �༭���߼����	2010-07-20 ����	
	//---------------------------------------
	class MOLogic
	{
	public:
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
		};

		MOLogic( HWND hwnd);
		~MOLogic();

	public:
		// �Ƿ���ͣ��
		bool IsPaused();

		// ���ʵ��
		void AddEntity( char* namePath);

		// ���Ŷ���
		void PlayAnimation(int index);

		// ����
		void FrameMove( float fTime);

		// ��ȡ��ģ������
		size_t  GetMeshNum(); 

		// ��ȡ֡��
		float GetFPS()  { return m_fFPS; }

		// ���ñ༭����
		void SetHandleType( EHandleType type);
		
		// ����֡��
		bool UpdateFPS( float fTime);

		// ������䷽ʽ
		void SetFillMode(WORD index);

	public:
		// ת������
		void ChangeTextureToDDS( vector<string>& textures);

	public:
		// ��ʾ��������ϵ
		void ShowBoneCoord( const Matrix44& coord);

	public:
		// ��ȡ�����ļ��в�����
		int GetMaterialNumInFile( const char* matFile);

		// ��ȡЧ���༭�߼�
		ModelEdit* GetModelEdit() { return m_modelEdit; }

		// ��ȡ���������
		MOInputListener* GetInputListener() { return m_inputListener; }

		// ��ȡUVBuild
		LightmapUVBuild* GetLightmapUVBuild() { return m_lightmapUVBuild; }

		// ��ȡUVRender
		LightmapUVRender* GetLightmapUVRender() { return m_lightmapUVRender; }

		// ��ȡ��ײ�༭�߼�
		CollisionBuildLogic* GetCollisionBuild() { return m_collisionBuildLogic; }

		// ת���߼�
		TransformLogic* GetTransformLogic() { return m_transformLogic; }

		// ��ȡ������߼�
		MOCameraLogic* GetCameraLogic() { return m_cameraLogic; }

		// ��ȡ����
		Scene*	GetScene() { return m_scene; }

	public:
		// �½���ɫ
		void NewCharacter( const char* resPath);

		// ���Ĵ��ڴ�С
		void ResizeWindow( int width, int height);

	private:
		EHandleType				m_flags;				// �������
		float                   m_fFPS;					// frames per second

		// ���λ�õ�
		POINT                   m_lastPoint;

	private:
		ModelEdit*				m_modelEdit;			// ����ģ���߼�
		IImageProcessManager*	m_pImageProcessMgr;
		MOCameraLogic*			m_cameraLogic;		    // ���������
		MOInputListener*		m_inputListener;		// �����߼�
		LightmapUVBuild*		m_lightmapUVBuild;		// ����ͼUV���ɹ�����
		LightmapUVRender*		m_lightmapUVRender;		// ����ͼUV��ʾRenderable
		CollisionBuildLogic*	m_collisionBuildLogic;	// ��ײ�༭�߼�
		TransformLogic*			m_transformLogic;		// ת���߼�
		LightEditLogic*			m_lightLogic;			// ��Դ����
		Scene*					m_scene;				// ����
	};

	extern  MOLogic*					g_MOLogic;
	#define MOLogic_Main				g_MOLogic
	#define MOLogic_Input				MOLogic_Main->GetInputListener()
	#define MOLogic_ModelEdit			MOLogic_Main->GetModelEdit()
	#define MOLogic_LightmapUVBuild		MOLogic_Main->GetLightmapUVBuild()
	#define MOLogic_LightmapUVRender	MOLogic_Main->GetLightmapUVRender()
	#define MOLogic_CollisionBuild		MOLogic_Main->GetCollisionBuild()
	#define MOLogic_Transform			MOLogic_Main->GetTransformLogic()
	#define MOLogic_Camera				MOLogic_Main->GetCameraLogic()
	#define MOLogic_Cfg					MOConfigMgr::GetSingletonPtr()
	#define EntityEdit_Scene			MOLogic_Main->GetScene()
	#define MOLogic_RenderSystem		MOLogic_Main->GetScene()->GetRenderSystem()
	#define MOLogic_VisualShpae			MOLogic_Main->GetScene()->GetRenderSystem().GetVisualShapeMgr()
	#define MOLogic_CameraSystem		MOLogic_Main->GetScene()->GetCameraSystem()
	#define MOLogic_RenderWindow		EntityEdit_Scene->GetRenderSystem().GetRenderWindow()
}