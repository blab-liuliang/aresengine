//#pragma once
//
//#include "AresEntity.h"
//#include <Physics/CollMap.h>
//#include <Physics/Rect3.h>
//#include <Physics/Frustum3.h>
//#include "Engine/RenderSystem/Terrain/AresTerrain.h"
//
//namespace Ares
//{
//	//
//	// SMapWindow
//	//
//	//struct SNavWindow
//	//{
//	//	float  m_x;			// ���ĵ�x
//	//	float  m_y;			// ���ĵ�y
//	//	float  m_radius;	// �뾶
//	//};
//
//	//---------------------------------
//	// ����ӿ� 2011-08-16 ����
//	//---------------------------------
//	class IArea
//	{
//	public:
//		//
//		// 2D����
//		//
//		struct SSize
//		{
//			size_t  m_posX;
//			size_t  m_posY;
//			size_t  m_width;
//			size_t  m_height;
//		};
//
//	public:
//		// ����������
//		virtual ~IArea() {}
//
//	public:
//		// ���õ�������(���ĵ�x,y; �뾶radius)
//		virtual void SetNavWindow( const SNavWindow& window)=0;
//
//		// ����
//		virtual void FrameMove( float fTime)=0;
//
//		// ��Ѱ
//		virtual Entity* BuildSearchResults(const Rect3& worldRect, const Frustum3* pOptionalFrustum/*=NULL*/)=0;
//
//	public:
//		// ��ȡ��ǰ���ؽ���
//		virtual float GetLoadingProgress()=0;
//
//		// ��ȡ��Χ��
//		virtual bool GetBoundingBoxByLayer( Rect3& box, const char* layer, bool update=false)=0;
//
//	public:
//		// ��ȡ��ͼ��
//		virtual const char* GetName()=0;
//
//		// ��ȡ����
//		virtual const SSize& GetSize()=0;
//
//		// ��ȡ�����Χ��
//		virtual const Rect3& GetWorldBounds()=0;
//
//		// ��ȡ�����
//		virtual SPtr<SceneNode> GetRootNode()=0;
//
//		// ����ʵ������ȡʵ��
//		virtual SPtr<Entity> GetEntity( const char* uniqueName)=0;
//
//		// ��ȡ����
//		virtual Terrain* GetTerrain()=0;
//
//		// ��ȡ��ײͼ
//		virtual CCollMap& GetCollMap()=0;
//
//	public:
//		// ���õ�ͼ��
//		virtual void SetName( const char* name)=0;
//
//		// �������򱣴�λ��
//		virtual void SetLocation( const char* location)=0;
//
//		// ��������
//		virtual void SetSize( const SSize& size)=0;
//
//		// ���õ���
//		virtual void SetTerrain( Terrain* terrain)=0;
//
//		// ���ʵ��
//		virtual bool AddEntity( const char* uniqueName, SPtr<Entity> pEntity)=0;
//
//	public:
//		// ����
//		virtual void Load( const char* fileName)=0;
//
//		// ����
//		virtual void Save( const char* fileName)=0;
//	};
//}