#pragma once

#include <Engine/RenderSystem/RenderAPI/AresRenderEffect.h>
#include "D3D11Typedefs.h"
#include <Cg/cgD3D11.h>

namespace Ares
{
	//--------------------------------------
	// D3D11RenderEffect 2012-4-6 ����
	// CGeffect Encapsulation
	//--------------------------------------
	class D3D11CgEffect : public RenderEffect
	{
	public:
		// ��ʼ��
		static bool InitCg( ID3D11DevicePtr& d3d11Device);

		// ��ȡCGcontext
		static CGcontext GetContext() { return m_cgContext; } 

	public:
		// ���캯��
		D3D11CgEffect();

		// ��������
		~D3D11CgEffect();

		// ���غ��� *.cgfx
		virtual bool Load( const char* fileName);

		// ���ڴ����
		virtual bool LoadFromMemory( void* code, size_t length);

	private:
		// ����Effect
		void ParseCgEffect();

		// ��������
		void ParseCgEffectParameters();

		// ����Techniques
		void ParseCgEffectTechniques();

		// ����CgTechnique
		void ParseCgTechnique( CGtechnique cgTechnique, RenderTechniquePtr& renderTechnique);

		// ����CgPass
		void ParseCgPass( CGpass cgPass, RenderPassPtr& renderPass);

	private:
		static CGcontext	m_cgContext;			// ȫ��Ψһ

		CGeffect			m_cgEffect;				// CgEffect
	};
}