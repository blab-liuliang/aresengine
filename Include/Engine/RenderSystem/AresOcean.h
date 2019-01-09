#pragma once

#include "Engine/RenderSystem/AresRenderEntity.h"

namespace Ares
{
	//--------------------------------------
	// Infinity Big Ocean 2013-8-21 ����
	//--------------------------------------
	class Ocean : public RenderEntity
	{
	public:
		Ocean();
		~Ocean();

		// ������Ļ�ռ��ʽ��С
		void SetScreenSpaceGridSize( int gridNum);

		// ����
		virtual void FrameMove( float fTime);

		// �ύ��ȾԪ��
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr);

	public:
		// ��ӵ�������Ϣ
		virtual void OnAddToScene( Scene* scene);

	private:
		int						m_scrGridNum;			// �ָ�����
		ShaderParamPtr			m_lodFactor;			// Lod factor
		ShaderParamPtr			m_oceanParams0;			// WindDirection WindSpeed, waveSpeed, wavesAmount
		ShaderParamPtr			m_oceanParams1;			// WavesSize WindDirection.x WinDirection.y WaterHeight
		ShaderParamPtr			m_waterShallowColor;	// ˮ��ɫ
		ShaderParamPtr			m_waterDeepColor;		// ��ˮ����ɫ
		ShaderParamPtr			m_fracStrength;			// ˮ��Ե,������ĭ�������� 
		ShaderParamPtr			m_texWaveBump;			// ������ͼ
		ShaderParamPtr			m_texFoam;				// ��ĭ��ͼ
		ShaderParamPtr			m_texReflect;			// ������ͼ
		Renderable				m_renderable;			// ��Ⱦ���
	};
	typedef s_ptr<Ocean> OceanPtr;
}