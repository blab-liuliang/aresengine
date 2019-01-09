//--------------------------------------
// http://www.quyougame.com AresRender
//--------------------------------------
#pragma once

#include <stdio.h>
#include <Physics/Frustum3.h>
#include <Core/Graphics/AresRenderMethod.h>

namespace Ares
{
	enum CameraType
	{
		CT_Normal = 0,	// ���������
		CT_Sky,			// ��պ������
		CT_Total,
	};

	//-------------------------------------------------------
	// ������ӿ�  2010-10-11         ����
	//-------------------------------------------------------
	class CameraSystem
	{
	public:
		struct Params
		{
			Matrix44	m_skyViewProj;
		};

	public:
		// shader param type
		enum SPType
		{
			SP_View		= 0,			// �۲����
			SP_ViewProj,				// ������۲�ͶӰ����
			SP_SkyViewProj,				// ��պй۲�ͶӰ����
			SP_Pos,						// �����λ��
			SP_NearFar,					// �������Զ����
			SP_Right,
			SP_Up,
			SP_Front,
			SP_Direction,				// ���������
			SP_Total,
		};

		CameraSystem();
		~CameraSystem();

		// ��ȡ������
		virtual float GetNear()=0;

		// ��ȡԶ����
		virtual float GetFar()=0;

		// ��ȡ����
		virtual Vector3& GetFacing()=0;

		// ��ȡ�۲����
		virtual Matrix44& GetView()=0;

		// ��ȡ�۲������ת����
		Matrix44 GetViewRotationInverse();

		// ��ȡͶӰ����
		virtual Matrix44& GetProj()=0;

		// ��ȡ�۲�ͶӰ����
		virtual Matrix44& GetViewProj()=0;

		// ��������
		virtual const Matrix44& GetOrtho()=0;

		// �۲���������
		virtual const Matrix44& GetViewOrtho()=0;

		// ��ȡ�����λ��
		virtual Vector3& GetPosition()=0;

		// ��ȡ��������Ѱ��Χ��
		virtual const Rect3& GetSearchRect()=0;

		// ��ȡ������ƽ��ͷ��
		virtual Frustum3* GetFrustum()=0;

		// ���û�Ծ�����
		void SetActive( CameraType type);

		// ��ȡ����
		const Params& GetParams() { return m_params; }

	public:
		// ��ȡ����ͶӰ
		virtual ShaderParamPtr& GetVpOrthoProj()=0;

		// ����Shader����
		virtual void UpdateSPAB()=0;
        
        // ÿ֡����
		virtual void FrameMove(float fTime)=0;

		// ��ȡshader�󶨲���
		ShaderParamPtr GetSPAB( SPType type) const;

	protected:
		Params									m_params;	// ����
		CameraType								m_active;	// ��ǰ������
		boost::array<ShaderParamPtr, SP_Total>	m_spab;		// ShaderParamAutoBind
	};
}
