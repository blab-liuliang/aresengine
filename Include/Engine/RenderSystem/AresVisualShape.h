#pragma once

#include <stdio.h>
#include <Core/AresCore.h>
#include <Core/AresSingleton.hpp>
#include <Physics/Shapes.h>
#include "Engine/RenderSystem/AresRenderable.h"
#include "Engine/Foundation/Ares3DEngine_h.h"
#include "Engine/SceneSystem/AresScene.h"

namespace Ares
{
	// ����
	enum VisualShapeType
	{
		VST_Base,			// ����	
		VST_Capsule,		// ����
	};

	//--------------------------------------------------
	// VisualShape (����������) 2010-07-28 ����
	//--------------------------------------------------
	class VisualShape : public Renderable
	{
	public:
		VisualShape( Scene& scene, VisualShapeType type=VST_Base);
		virtual ~VisualShape();

		// ����
		void FrameMove();

		// ��������
		VisualShapeType GetType() { return m_type; }

		// ��ȡת��������
		Transform* GetTransform() { return &m_transform; }

		// ������ɫ
		//const ColorRGB GetColor() { return *m_color; }

		// ���ù̶���С
		void SetSizeFixed( bool isFixed, float sizePixel=100.f);

		// ������ɫ
		void  SetColor( ColorRGB color) { *m_color=color; }

		// �������ƫ��
		void SetDepthBias( float depthBias) { *m_depthBias = depthBias; }

		// ���ÿɼ���
		void  SetVisible( bool visible) { m_visible = visible; }

		// �Ƿ�ɼ�
		bool  IsVisible() { return m_visible; }

		// ����RenderLayout
		void Set(RenderLayout::TopologyType topologyType, Vector3* positions, int vertexSizeInByte, const void* indices, int indicesSizeInByte, ElementFormat indiceFormat=EF_R16UI, Vector3* normals=NULL, DWORD* colors=NULL);

	protected:
		VisualShapeType	m_type;			// ����

		ShaderParamPtr	m_color;		// ��ɫ
		ShaderParamPtr  m_useNormal;	// �Ƿ�ʹ�÷���
		ShaderParamPtr	m_spWorld;		// �������
		ShaderParamPtr	m_worldViewProj;// λ���������
		ShaderParamPtr	m_depthBias;	// ���ƫ��

		bool			m_visible;		// �Ƿ�ɼ�
		bool			m_isFixedSize;	// �Ƿ��С�̶�
		Transform		m_transform;	// ת��
		Scene&			m_scene;	    // ����ϵͳ
	};
	typedef s_ptr<VisualShape> VisualShapePtr;

	//--------------------------------------------------
	// �߶� 2010-07-28   ����
	//--------------------------------------------------
	class ARES_EXPORT VisualSegment3 : public VisualShape
	{
	public:
		// constructor
		VisualSegment3( Scene& scene);

		// �����߶εĲ���
		void Set( const Segment3& segment);

		// �����߶β���( vertex0, vertex1)
		void Set( float x0, float y0, float z0, float x1, float y1, float z1);

	private:
		Segment3	m_segment;
	};
	typedef s_ptr<VisualSegment3> VisualSegmentPtr;

	//-------------------------------------------------
	// ����  2010-07-28   ����
	//-------------------------------------------------
	class ARES_EXPORT VisualRect3 : public VisualShape
	{
	public:
		// constructor
		VisualRect3( Scene& scene);

		// AABB��Χ��
		void Set( const Rect3& rect);

	private:
		Rect3		m_rect;
	};
	typedef s_ptr<VisualRect3> VisualRect3Ptr;

	//--------------------------------------------------
	// �����Χ����Ⱦ 2013-7-3 ����
	//--------------------------------------------------
	class VisualBox3 : public VisualShape
	{
	public:
		VisualBox3( Scene& scene);

		// ���������Χ��
		void Set(const Box3& box);

	private:
		Box3			m_box3;
	};

	//--------------------------------------------------
	// Բ׶�� 2010-08-03 13:31  ����
	//--------------------------------------------------
	class VisualCone3 : public VisualShape
	{
	public:
		// constructor
		VisualCone3( Scene& scene);

		// ���ô���
		virtual void SetRadiusAndHeight( float _radius, float _height);

		// ���ó���
		virtual void SetFace( Vector3& face);
	};
	typedef s_ptr<VisualCone3> VisualCone3Ptr;

	//--------------------------------------------------
	// ������ʾͼ�� Բ  2010-08-05 17:16 ����
	//-------------------------------------------------
	class VisualCycle3 : public VisualShape
	{
	public:
		// constructor
		VisualCycle3( Scene& scene);

		// ���ð뾶
		void SetRadius( float _radius);

		// ��������
		void SetFace( Vector3& face);
	};
	typedef s_ptr<VisualCycle3> VisualCycle3Ptr;

	//--------------------------------------------------
	// ��������ʾ 2012-9-10 ����
	//--------------------------------------------------
	class VisualCapsule : public VisualShape
	{
	public:
		// ���캯��
		VisualCapsule( Scene& scene);

		// ���ò���
		void SetShape( const Capsule3& capsule);

		// ���ò���
		void SetShape( float height, float radius);

		// ��ȡ�뾶
		float GetRadius() { return m_capsuleInternal.m_radius; }

		// ��ȡ��
		float GetHeight() { return m_capsuleInternal.m_segment.Length(); }

		// ��ȡ����
		Capsule3 GetCapsule();

	private:
		Capsule3		m_capsuleInternal;		// ֻ��¼�߶���뾶
	};
	typedef s_ptr<VisualCapsule> VisualCapsulePtr;


	//--------------------------------------
	// ������������Ⱦ������ 2011-08-15  ����
	//--------------------------------------
	class RenderQueue;
	class VisualShapeMgr
	{
		typedef multimap< int, VisualShape*> VisualShapeList;
	public:
		// constructor
		VisualShapeMgr( Scene& scene);

		// deconstructor
		~VisualShapeMgr();

		// �������������
		VisualShape* CreateVisualShape( int layer=0);

		// create line
		VisualSegment3* CreateSegment( int layer=0);

		// create aabb
		VisualRect3* CreateRect3( int layer=0);

		// ���������Χ��
		VisualBox3* CreateBox3( int layer=0);

		// ����Բ׶��
		VisualCone3* CreateCone( int layer=0);

		// ����Բ
		VisualCycle3* CreateCycle( int layer=0);

		// ��������
		VisualCapsule* CreateCapsule( int layer=0);

		// ɾ��
		bool DeleteVisualShape( VisualShape* shape);

	public:
		// ����
		void FrameMove();

		// ��Ⱦ
		void SubmitRenderElements( RenderElementMgr& renderElementMgr);		

	private:
		VisualShapeList  m_shapes;			// visual shapes
		Scene&			 m_scene;
	};
}
