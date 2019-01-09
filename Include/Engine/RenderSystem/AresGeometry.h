//--------------------------------------
// http://www.quyougame.com AresRender
//--------------------------------------
#pragma once

#include <d3dx9.h>
#include <stdio.h>
#include <Core/AresCore.h>
#include "../Foundation/Ares3DEngine_h.h"

namespace Ares
{
	//--------------------------------------------------
	// IBaseGeometry (����������) 2010-07-28 ����
	//--------------------------------------------------
	class ARES_EXPORT IBaseGeometry
	{
		struct SHeader;
	public:
		enum EGeometryType
		{
			EM_GT_NULL = 0, // ʲô��û��
			EM_GT_ANY,		// ������״
			EM_GT_LINE,		// �߶� 
			EM_GT_RAY,		// ����,���߶β�಻��
			EM_GT_AABB,		// AABB��Χ��
			EM_GT_OBB,
			EM_GT_CONE,
			EM_GT_CYCLE,	// Բ
		};

		// ���캯��
		IBaseGeometry();

		// ��������
		virtual ~IBaseGeometry();

		// ������ɫ
		const DWORD& GetColor();

		// ���ؼ���������
		EGeometryType GetType();

	public:
		// �����������
		const Matrix44& GetWorldMatrix();

		// �����������
		void SetWorldMatrix( const Matrix44& mat);

		// ����
		virtual void  Draw()=0;

		// ������ɫ
		void  SetColor( DWORD color);

		// ����λ��
		void  SetPosition( float _x, float _y, float _z);

		// ��������
		void  SetScale( float fScale);

		// ���ÿɼ���
		void  SetVisible( bool visible);

		// �Ƿ�ɼ�
		bool  IsVisible();

	protected:
		SHeader*	   m_header;		// ����ͷ
		EGeometryType  m_type;
		DWORD          m_dwColor;		// ��������ɫ
		bool           m_bVisible;		// �Ƿ�ɼ�
		FLOAT          m_fScale;		// ����
	};

	//--------------------------------------------------
	// ���� 2010-08-05   ����
	//--------------------------------------------------
	class IGeometryAny : public IBaseGeometry
	{
	public:
		// ֱ�����ö�����������
		virtual void SetParam(UINT32 vertexCount, void* vertexData, D3DPRIMITIVETYPE type, UINT32 indexNum, void* indexData, D3DFORMAT format=D3DFMT_INDEX16)=0;
	};

	//--------------------------------------------------
	// �߶� 2010-07-28   ����
	//--------------------------------------------------
	class ILine : public IBaseGeometry
	{
	public:
		// �����߶εĲ���
		virtual void SetParam( float _x0, float _y0, float _z0, float _x1, float _y1, float _z1)=0;

		// ���ò���
		virtual void SetParam( Vector3& pointBegin, Vector3& face)=0;
	};

	//-------------------------------------------------
	// ����  2010-07-28   ����
	//-------------------------------------------------
	class IBox : public IBaseGeometry
	{
	public:
		// AABB��Χ��
		virtual void SetParam( float _x0, float _y0, float _z0, float _x1, float _y1, float _z1)=0;
	};

	//--------------------------------------------------
	// Բ׶�� 2010-08-03 13:31  ����
	//--------------------------------------------------
	class ICone : public IBaseGeometry
	{
	public:
		// ���ô���
		virtual void SetRadiusAndHeight( float _radius, float _height)=0;

		// ���ó���
		virtual void SetFace( Vector3& face)=0;
	};

	//--------------------------------------------------
	// ������ʾͼ�� Բ  2010-08-05 17:16 ����
	//-------------------------------------------------
	class IRenderCycle : public IBaseGeometry
	{
	public:
		// ���ð뾶
		virtual void SetRadius( float _radius)=0;

		// ��������
		virtual void SetFace( Vector3& face)=0;
	};

	//--------------------------------------------------
	//  Sky    2010-05-31 13��51  ����
	//--------------------------------------------------
	class ISurfaceMaterial;
	class ISkyModel
	{
	public:
		// ָ��̫��λ��( for sun shaft)
		virtual void SetSunPos( float _x, float _y, float _z)=0;

		// ����
		virtual void FrameMove(float fTime)=0;
	};

	//---------------------------------------------------
	// ��ͷѣ��   2010-06-08   ����
	//---------------------------------------------------
	class ILensFlare
	{
	public:
		// ��ʼ��,ָ��������Դ·��
		virtual void Initialize( char* texturePath, WORD totalNum=9, WORD numPerLine=3)=0;

		// ����
		virtual void Update()=0;

		// ��Ⱦ
		virtual void Render()=0;

		// ����ѣ����ɫ
		virtual void SetLightColor( DWORD color)=0;

		// ���÷��������ڷ���
		virtual void SetLightVector( Vector3& sunLightVector)=0;
	};

	//----------------------------------
	// ���������� 2011-08-15  ����
	//----------------------------------
	class IGeometryMgr
	{
	public:
		// ����Line
		virtual ILine* CreateLine( IBaseGeometry::EGeometryType type = IBaseGeometry::EM_GT_LINE)=0;

		// ����Բ׶��
		virtual ICone* CreateCone()=0;

		// ����Box
		virtual IBox* CreateBox( IBaseGeometry::EGeometryType type = IBaseGeometry::EM_GT_AABB)=0;

		// ����Բ
		virtual IRenderCycle* CreateCycle()=0;

		// �������������
		virtual IGeometryAny* CreateGeometryAny()=0;

		// ��Ⱦ
		virtual void Render()=0;
	};
}
