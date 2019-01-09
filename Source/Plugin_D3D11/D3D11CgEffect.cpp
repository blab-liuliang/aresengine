#include "D3D11CgEffect.h"

namespace Ares
{
	CGcontext D3D11CgEffect::m_cgContext = NULL;		// Cg����(ȫ��Ψһ)

	// ��ʼ��
	bool D3D11CgEffect::InitCg( ID3D11DevicePtr& d3d11Device)
	{
		if( !m_cgContext)
		{
			m_cgContext = cgCreateContext();

			HRESULT hr = cgD3D11SetDevice( m_cgContext, d3d11Device.get());

			cgD3D11RegisterStates( m_cgContext );
			cgD3D11SetManageTextureParameters( m_cgContext, CG_TRUE );
		}

		return true;
	}

	// ���캯��
	D3D11CgEffect::D3D11CgEffect()
		: RenderEffect()
	{

	}

	// ��������
	D3D11CgEffect::~D3D11CgEffect()
	{

	}

	// ���غ��� *.cgfx
	bool D3D11CgEffect::Load( const char* fileName)
	{
		RenderEffect::Load( fileName);

		m_cgEffect = cgCreateEffectFromFile( m_cgContext, fileName, NULL);
		if( !m_cgEffect)
			return false;

		ParseCgEffect();

		return true;
	}

	// ���ڴ����
	bool D3D11CgEffect::LoadFromMemory( void* code, size_t length)
	{
		m_cgEffect = cgCreateEffect( m_cgContext, (const char*)code, NULL);

		return false;
	}

	// ����Effect
	void D3D11CgEffect::ParseCgEffect()
	{
		ParseCgEffectParameters();

		ParseCgEffectTechniques();
	}

	// ��������
	void D3D11CgEffect::ParseCgEffectParameters()
	{
		CGparameter cgParameter = cgGetFirstEffectParameter( m_cgEffect);
		while( cgParameter)
		{
			ShaderParamDesc paramDesc;

			paramDesc.m_name	 = cgGetParameterName( cgParameter);
			paramDesc.m_semantic = cgGetParameterSemantic( cgParameter);

			m_paramesDesc.push_back( paramDesc);
		}
	}

	// ����Techniques
	void D3D11CgEffect::ParseCgEffectTechniques()
	{
		CGtechnique cgTechnique = cgGetFirstTechnique( m_cgEffect);
		while (cgTechnique)
		{
			RenderTechniquePtr technique = RenderTechniquePtr( new RenderTechnique(RenderEffectPtr(this)));

			const char * cgTechniqueName = cgGetTechniqueName(cgTechnique);
			if (cgTechniqueName)
				technique->SetName(cgTechniqueName);

			ParseCgTechnique(cgTechnique, technique);

			m_techniques.push_back( technique);

			cgTechnique = cgGetNextTechnique(cgTechnique);
		}
	}

	// ����CgTechnique
	void D3D11CgEffect::ParseCgTechnique( CGtechnique cgTechnique, RenderTechniquePtr& renderTechnique)
	{
		CGpass cgPass = cgGetFirstPass( cgTechnique);
		while( cgPass)
		{
			RenderPassPtr renderPass = RenderPassPtr( new RenderPass( RenderEffectPtr(this)));

			const char* cgPassName = cgGetPassName( cgPass);
			if( cgPassName)
				renderPass->SetName( cgPassName);

			ParseCgPass( cgPass, renderPass);

			renderTechnique->Insert( renderPass);

			cgPass = cgGetNextPass( cgPass);
		}
	}

	// ����CgPass
	void D3D11CgEffect::ParseCgPass( CGpass cgPass, RenderPassPtr& renderPass)
	{
		// ��¼PassState
		//cgGetState
	}
}