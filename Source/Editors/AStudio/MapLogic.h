#pragma once

#include <Engine/AresRoot.h>
#include <Engine/SceneSystem/AresScene.h>
#include <Engine/RenderSystem/AresVisualShape.h>
#include <EditorKit/AresWorldEK.h>
#include <Physics/MassSpringSystem.h>
#include <Engine/RenderSystem/AresClothFabricBuilder.h>
#include <Physics/Bullet/btBulletDynamicsCommon.h>
#include <EditorKit/BulletDebugDrawer.h>

namespace Ares
{
	//-------------------------------------
	// �����ͼ�߼�  2011-08-16  ����
	//-------------------------------------
	class CMapLogic
	{
	public:
		// ��ͼ����
		void FrameMove( float fTime);

		// ����ѡ
		Entity* SelectEntity();

	public:
		// ���캯��
		CMapLogic();
		~CMapLogic();

		// �ָ��ϴιر�ʱ״̬
		void Restore();

		// ������ͼ
		void CreateScene( const char* name, const char* location);

		// �򿪵�ͼ
		void OpenScene( const char* filename);

		// �����ͼ
		void SaveMap( const char* filename);

		// ���Ϊ
		void SaveMapAs();

	private:
		// �½�����
		void SetSceneSize( size_t posX, size_t posY, int width, int height);

	public:
		// ����Window(���ĵ�x,y; �뾶radius)
		void SetNavWindow( float x, float y, float radius);

		// ��������
		void CreateWhiteGrid();

		// ������ɫ����
		void CreateRedCross();

		// �������
	public:
		// ���õ���UV����
		void SetUVScale(int index, float value);

		// ��ȡUV����ֵ
		float GetUVScale(int index);

		// ���õ���������
		void SetTerrainTexture( int index, const char* resPath);

		// ���õ���������
		const char* GetTerrainTexture( int index);

		// ��ǰ���ε���߶�ͼ
		void ImportTerrainHeight( const char* heightPath);

		// ��ǰ���ε��������϶�
		void ImportTerrainTexBlend( int idx, const char* texPath);

		// �༭���λ�����
		void EditTerrainMeshOrTexture( float fTime);

		// ��ȡ���α༭����(��Ȼ��ϲ�����ַ�ʽ, �༭������ν��)
		STerrainMeshEditorData& GetTerrainMeshEditorData() { return m_meshEditorData; }

		// ������
	public:
		// ��ʼ������
		void InitPhysics();

	public:
		// Recent files changed signals
		signal<void()> Signal_OnSceneChanged;

	private:
		STerrainMeshEditorData	m_meshEditorData;	// ���α༭��
		VisualShape*			m_whiteGrid;		// ��������
		VisualShape*			m_redCross;			// ���ĺ�ʮ��

		MassSpringSystem*		m_massSpringSystem;	// �ʵ㵯��ϵͳ
		VisualShape*			m_cloth;			// ������Ⱦ
		VisualShape*			m_springRender;		// ���ɵ���

		ClothFabricPtr			m_clothFabric;


		PhysicsWorldPtr			m_physicsWorld;		// ��������

		btBroadphaseInterface*					m_broadphase;				// �ֽ׶�
		btCollisionDispatcher*					m_dispatcher;				// ��ײ
		btConstraintSolver*						m_solver;					// ��Լ��
		btDefaultCollisionConfiguration*		m_collisionConfiguration;	// ��ײ����
		btDynamicsWorld*						m_dynamicsWorld;			// ��̬����
		btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;			// ��ײ��
		BulletDebugDrawer*						m_bulletDebugDrawer;		// ��Ⱦ
	};
}