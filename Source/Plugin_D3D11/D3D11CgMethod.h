//#pragma once
//
//#include <Core/Graphics/AresRenderMethod.h>
//#include "D3D11Typedefs.h"
//#include <Cg/cgD3D11.h>
//
//namespace Ares
//{
//	//--------------------------------------
//	// D3D11RenderEffect 2012-4-6 ����
//	// CGeffect Encapsulation
//	//--------------------------------------
//	struct D3D11CgMethod : public RenderMethod
//	{
//	public:
//		// ��ʼ��
//		static bool InitCg( ID3D11DevicePtr& d3d11Device);
//
//		// ��ȡCGcontext
//		static CGcontext GetContext() { return m_cgContext; } 
//
//	public:
//		// ���캯��
//		D3D11CgMethod();
//
//		// ��������
//		~D3D11CgMethod();
//
//		// ���غ��� *.cgfx
//		virtual bool Load(  const char* fileName);
//
//		// ���ڴ����
//		virtual bool LoadFromMemory( void* code, size_t length);
//
//		// ��ȡIASignature
//		ID3D10Blob* GetIASignature() { return cgD3D11GetIASignatureByPass( m_cgPass); }
//
//		// Ӧ�ò���
//		virtual void SetParams(const RenderMaterial& mat);
//
//	private:
//		// ��������
//		void ParseParameters();
//
//		// ����״̬
//		void ParseStates();
//
//		// ������
//		void CheckForCgError( string* error=NULL);
//
//	private:
//		static CGcontext	m_cgContext;			// ȫ��Ψһ
//
//		CGeffect			m_cgEffect;				// CgEffect
//		CGtechnique			m_cgTechnique;
//		CGpass				m_cgPass;
//		vector<CGparameter> m_cgParameters;			// CgParameters
//	};
//}