//#pragma once
//
//#include "GPWorld.h"
//#include "AresScene.h"
//#include "SceneNode.h"
//#include "LightmapMgr.h"
//
//namespace Ares
//{
//	//------------------------------------
//	// QtWorld 2011-08-18 ����
//	//------------------------------------
//	class CQtGPWorld : public CGPWorld
//	{
//		//typedef map<string, s_ptr<Entity>> EntityList;
//	public:
//		// ���캯��
//		CQtGPWorld();
//
//		// ������������
//		//void SetScene( Scene* scene) { m_scene = scene; }
//
//		// �������ڵ�
//		//void SetRootNode( const s_ptr<SceneNode>& rootNode);
//
//		// ����Tile�ļ�����·��
//		//void  SetWorldLocation( const char* location) { m_location = location; } 
//
//		// ���÷�Χ
//		//void  SetWorldLimits( const Scene::SSize& size, const CGPIndex& gpIdx);
//
//		// ���ʵ��
//		//bool AddEntity( const char* uniqueName, s_ptr<Entity> pEntity);
//
//		// ���ʵ��
//		//bool AddEntityToWorldOnly( const char* uniqueName, s_ptr<Entity> pEntity);
//
//		// �����ײ����ײͼ��
//		//void AddCollMesh( const char* uniqueName, BvhTriangleMesh* mesh);
//
//		// ����ʵ��
//		//void FrameMove( float elapsedTime);
//
//	public:
//		// ����ʵ������ȡʵ��
//		//s_ptr<Entity>GetEntity( const char* uniqueName);
//
//		// ��ȡ����
//		//Scene* GetScene() { return m_scene; }
//
//		// ��ȡ��Χ��
//		//bool GetBoundingBoxByLayer( Rect3& box, const char* layer, bool update=false);
//
//	public:
//		// ��Ӧ�����������Ƿ����
//		//virtual bool IsValidIndex( const CGPIndex& index);
//
//	public:
//		// ���õ���
//		//void SetTerrain( Terrain* terrain);
//
//		//// �����������
//		//void  SaveTerrain( const char* terLocation);
//
//		//// ���ص�������
//		//void  LoadTerrain( const char* terLocation);
//
//		// ��ȡ����
//		//Terrain* GetTerrain() { return m_terrain; }
//
//		// ��ȡ��ײͼ
//		//CCollMap& GetCollMap() { return m_collMap; }
//
//		// ��ȡ����ͼ������
//		//LightmapMgr& GetLightmapMgr() { return m_lightmapMgr; }
//
//	public:
//		// ����
//		//void Save();
//
//	protected:
//		// ����Tile
//		virtual CGPTile* BuildTile( const CGPIndex& index);
//
//		// ����Tile
//		virtual void  DestroyTile( const CGPIndex& index);
//
//	protected:
//		string				m_location;			// world�ļ����·��
//		//int					m_xTiles;			// x���������
//		//int					m_yTiles;			// y���������
//		CGPIndex			m_mainGPIdx;		// ��GP����,����tile��С��
//		Scene::SSize		m_size;				// �������з�Χ
//		//Scene*				m_scene;			// ��������
//		//EntityList			m_entiys;			// ʵ���б�
//		//s_ptr<SceneNode>		m_rootNode;			// ���������	
//
//		//Terrain*			m_terrain;			// ����			��������Դ��
//		//CCollMap			m_collMap;			// ��ײͼ		����ײ���ݡ�
//		//LightmapMgr			m_lightmapMgr;		// ����ͼ������ ��������ݡ�
//
//		//CriticalSection		m_qtCritication;	// ����ʵ���б�
//		//CriticalSection		m_rtCritication;
//	};
//}