#pragma once

#include "Engine/SceneSystem/AresEntity.h"
#include <Engine/FxSystem/AresFxEntity.h>

namespace Ares
{
	// ��Դ����
	enum LightType
	{
		LT_Ambient   = 0,
		LT_Direction,
		LT_Point,
		LT_Spot,
	};

	//------------------------------------------
	//  ��Դ��2010-08-02 14:37 	    ����
	//------------------------------------------
	class Light : public Entity
	{
	public:
		// ��ȡ��Դ����
		LightType GetLightType() const { return m_lightType; }

		// ��ȡ��ɫ
		const ColorRGB& GetColor() const { return m_color; }

		// ������ɫ
		void  SetColor( const ColorRGB& color);

		// �ж�ĳ���Ƿ��ڹ�Դ��Ӱ��
		bool IsPointIn( const Vector3& pos);

		// ����ʹ��LightShaft
		virtual void SetLightShaft( const char* fxPath) {}

		// ��ȡShaft
		virtual FxEntityPtr GetLightShaft() { return FxEntityPtr(); }	

		// ��ȡShaft��������
		virtual float2 GetShaftCenterCoord() { return float2( 0.5f, 0.5f);}

		// �Ƿ�ʹ��Shaft
		virtual bool IsUseLightShaft() { return false; }

	public:
		// ��ȡ���� LT_Direction
		virtual const Vector3& GetDirection() const;

		// ���ó��� LT_Direction
		virtual void SetDirection( const Vector3& dir);

		// ��ȡ��ɫֵ
		const ShaderParamPtr& GetSPABColor() const { return m_spabColor; }

		// ��������ֱ���
		//virtual void SetShadowMapResolution( size_t resolution=0);

	protected:
		Light( EntityTypeDetail typeDetail);
		~Light();

	protected:
		LightType		m_lightType;	// ��Դ����
		ColorRGB		m_color;		// ��������ɫ
		ShaderParamPtr  m_spabColor;	// ��ɫֵ
	};
	typedef s_ptr<Light>  LightPtr;

	//---------------------------------------------------
	// ������ 2010-08-25  11:31  ����
	//---------------------------------------------------
	class AmbientLight : public Light
	{
	public:
		// ���캯��
		AmbientLight() : Light( ED_LightAmbient) {}

		// �ύ��ȾԪ��
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr){}
	};
	typedef s_ptr<AmbientLight> AmbientLightPtr;

	//---------------------------------------------------
	// �۹��  2010-08-25    ����
	//---------------------------------------------------
	class ILightSpot : public Light
	{
	public:
		// ���캯��
		ILightSpot() : Light( ED_LightSpot) {}

		// ��ȡ˥����ʽ( a, b*d, c*d*d)ϵ��a, b ,c������ dΪ��Դλ�õ�����ľ���
		virtual const Vector3& GetAttenuate()=0;

		// ��ȡ�Ƕȵ�cosֵ
		virtual const float& GetCosine()=0;

		// ��ȡ��Դ����
		virtual const Vector3& GetDirection()=0;

		// ��ȡλ��
		virtual const Vector3& GetPosition()=0;

		// ��ȡ�۹�ƵĿ���
		virtual float& GetRadian()=0;

		// ����˥����
		virtual void SetAttenuate( float a, float b, float c)=0;

		// ���ù�Դ����
		virtual void SetDirection( const Vector3& dir)=0;

		// ����λ��
		virtual void SetPosition( float x, float y, float z)=0;

		// ���þ۹�ƵĿ���
		virtual void SetRadian( float radian)=0;
	};

	//---------------------------------------------------
	// ��Դ����ӿ� ILightManager 2010-08-13  ����
	//---------------------------------------------------
	class ILightManager
	{
	public:
		// ������Դ
		virtual ILightSpot* CreateSpotLight()=0;

	public:
		// ��ȡ�ƹ�����
		virtual UINT GetActiveLightNum()=0;

		// ����������ȡ�ƹ�
		virtual Light* GetActiveLight( size_t index)=0;

		// ��ȡ��Դ
		virtual Light*  GetLight( size_t index)=0;

		// ��ȡ��Դ����
		virtual UINT GetLightNum()=0;

	public:
		// ��ӹ�Դ
		virtual void  AddActiveLight( Light* pLight ,int len = 0)=0;

		// ���
		virtual void  ClearActiveLightList()=0;
	};
}