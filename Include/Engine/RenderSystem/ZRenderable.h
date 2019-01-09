#pragma once

#include <Core/AresCore.h>
#include <Engine/RenderSystem/SuperMaterial.h>
#include <Engine/RenderSystem/AresTerrain.h>

namespace Ares
{
	//----------------------------------------
	// ZWriteRenderable 2013-2-21 ����
	//----------------------------------------
	class ZRenderable
	{
	public:
		ZRenderable( bool isZTest=false);
		~ZRenderable();

		// ��Ⱦ
		void Render( const Matrix44& worldViewProj);

		// ����Renderlayout
		void SetRenderlayout( const RenderLayoutPtr& renderLayout) { m_layout = renderLayout;}

		// ��������
		void SetMaskTexture( ShaderParamPtr mask);

	private:
		RenderLayoutPtr	m_layout;			// RenderGeometry
		SuperMaterial	m_material;			// RenderMaterial

		ShaderParamPtr	m_worldViewProj;	// ����
		ShaderParamPtr	m_maskTexture;		// ZTest����
	};

	//--------------------------------------
	// ZWriteObject 2013-8-10 ����
	//--------------------------------------
	class ZWriteObject
	{
	public:
		// ��Ⱦ
		virtual void Render( const Matrix44& worldViewProj)=0;

		// ִ��д���
		virtual void ExecZWrite()=0;
	};

	//--------------------------------------
	// ZWriteTerrain 2013-8-10 ����
	//--------------------------------------
	class ZWriteTerrain
	{
	public:
		ZWriteTerrain( Terrain* terrain);
		~ZWriteTerrain();

		// ��Ⱦ
		virtual void Render( const Matrix44& worldViewProj);

		// ִ��д���
		virtual void ExecZWrite();

	private:
		vector<ZRenderable*>		m_zRenderables;		// �����Ⱦ
	};
}