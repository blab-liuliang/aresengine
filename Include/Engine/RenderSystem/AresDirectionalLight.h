#pragma once

#include <Core/AresCore.h>
#include "AresLight.h"
#include <Engine/FxSystem/AresFxEntity.h>
#include "Engine/RenderSystem/CSMMgr.h"

using namespace boost;
using namespace boost::signals2;

namespace Ares
{
	//------------------------------------------
	// ����� 2012-6-20 ����
	//	   �༭����֤�����һֱλ�ڳ�������ߴ�
	//------------------------------------------
	class DirectionalLight : public Light
	{
	public:
		// shader param type
		enum SPType
		{
			//SP_ViewCrop	  = 0,			// �۲�crop
			//SP_ViewCropRemap,			// Remap
			SP_Direction=0,				// ����
			SP_Color,					// ��ɫ
			//SP_DepthMap,				// ���ͼ
		};

	public:
		// ���캯��
		DirectionalLight();

		// ��ȡ����
		virtual const Vector3& GetDirection() const { return m_direction; }

		// ���ó���
		virtual void SetDirection( const Vector3& dir);

		// ��ȡshader�󶨲���
		ShaderParamPtr GetSPAB( SPType type) const { return m_spab[type]; }

		// ����ʹ��LightShaft
		virtual void SetLightShaft( const char* fxPath);

		// ��������Դ
		void SetDomaintLight( bool isDomaint) { m_domaint = isDomaint; }

		// ��ȡShaft��������
		virtual float2 GetShaftCenterCoord();

		// ����
		virtual void  FrameMove( float fTime);

		// �Ƿ�ʹ��Shaft
		virtual bool IsUseLightShaft();

		// ��ȡShaft
		virtual FxEntityPtr GetLightShaft() { return m_shaft; }	

		// ��ȡShaft·��
		const string& GetShaftPath() const { return m_shaftPath; }

		// ��ȡ�㼶��Ӱ������
		CSMMgrPtr& GetCSMMgr() { return m_csmMgr; }

		// �ύ��ȾԪ��
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr);

	private:
		// ����SPAB
		void UpdateSPAB();

		// ����Shaftλ�� 
		void UpdateShaftPos();

	private:
		bool			m_domaint;					// �Ƿ�Ϊ����Դ
		float			m_distance;					// �����������
		Vector3			m_pos;						// ��ʱλ��
		Box3			m_searchBox3;				// ��Ѱ�����Χ��
		Vector3			m_direction;				// ����	
		size_t			m_resolution;				// �ֱ���
		TexturePtr		m_depthTextureRT;
		TexturePtr		m_depthTexture;				// ���ͼ
		FrameBufferPtr	m_depthBuffer;				// ���buffer
		Matrix44		m_view;						// �۲����
		Matrix44		m_crop;						// ����Ӧ
		Matrix44		m_remap;					// Remap

		boost::array<ShaderParamPtr,5>	m_spab;				// ShaderParamAutoBind

		string			m_shaftPath;				// ��Դ·��
		FxEntityPtr		m_shaft;					// LightShaft
		CSMMgrPtr		m_csmMgr;					// �㼶��Ӱ������
	};
	typedef s_ptr<DirectionalLight> DirectionalLightPtr;
}