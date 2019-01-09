#pragma once

#include <Physics/Rect3.h>
#include <Physics/Frustum3.h>

namespace Ares
{
	//----------------------------------------------
	// ��Դ�ռ���Ӱ 2010-12-08 ����
	//----------------------------------------------
	class ILiSPSM
	{
	public:
		// ��ʼ��
		virtual void Init()=0;

		// ׼����Ⱦshadowmap
		virtual void Begin()=0;

		// ������Ⱦ
		virtual void End()=0;

		// ������ӰͶ���߰�Χ��
		virtual void SetShadowCastBoundingBox( const Rect3& boundingBox)=0;

		// ��ȡ��ԴsearchRect
		virtual const Rect3& GetLightSearchRect()=0;

		// ��ȡ��Դ����
		virtual const Vector3& GetLightDir()=0;

	public:
		typedef void( *RenderCallBack)( const Rect3&, const Frustum3*);

		// ����ShadowMap
		virtual void  UpdateShadowMap()=0;

		// ��ȡ����͸ֵ
		virtual float GetLBRAmount()=0;

		// �����Ƿ����ģ��
		virtual void SetBlur(bool blur)=0;

		// ���ò������
		virtual void  SetSampleSize( int iSize)=0;

		// ����Light bleeding reduction
		virtual void  SetLBR( float fLBR)=0;

		// ��ȡ��ȾshadowMap����Ч�ļ�
		virtual const Matrix44& GetLightMatrix()=0;

		// ��ȡShadwMapRefMap
		virtual const Matrix44& GetLightReMapMatrix()=0;

		// ��ȡshadowMap
		//virtual SPtr<ITexture>& GetShadowTexture()=0;

		// ������Ⱦ�ص�����
		virtual void SetRenderShadowMapFun( void( *pFun)( const Rect3&, const Frustum3* ))=0;
	};
}