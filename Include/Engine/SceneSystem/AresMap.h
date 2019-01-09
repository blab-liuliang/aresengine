//#pragma once
//
//#include "AresArea.h"
//
//namespace Ares
//{
//	//---------------------------------
//	// ����������ӿ� 2011-08-16 ����
//	//---------------------------------
//	class IMap
//	{
//	public:
//		// ����������
//		virtual ~IMap() {}
//
//	public:
//		// ����Window(���ĵ�x,y; �뾶radius)
//		virtual void SetNavWindow( float x, float y, float radius)=0;
//
//		// ����
//		virtual void FrameMove( float fTime)=0;
//
//		// ��Ⱦ
//		virtual void Render()=0;
//
//	public:
//		// ��ȡ��ǰ���ؽ���
//		virtual float GetLoadingProgress()=0;
//
//		// ��ȡ��Χ��
//		virtual const Rect3& GetBoundingBox()=0;
//
//		// ��ȡ��Χ��
//		virtual bool GetBoundingBoxByLayer( Rect3& box, const char* layer, bool update=false)=0;
//
//	public:
//		// ��ȡ��ͼ��
//		virtual const char* GetName()=0;
//
//		// ��ȡ��������
//		virtual size_t GetAreaNum()=0;
//
//		// ��ȡ����
//		virtual IArea* GetArea( size_t idx)=0;
//
//		// ��ȡ����
//		virtual IArea*	GetArea( const char* areaName)=0;
//
//	public:
//		// ���õ�ͼ��
//		virtual void SetName( const char* name)=0;
//
//		// �������
//		virtual bool AddArea( IArea* pArea)=0;
//
//	public:
//		// ����
//		virtual void Load( const char* fileName)=0;
//
//		// ����
//		virtual void Save( const char* fileName=0)=0;
//	};
//}