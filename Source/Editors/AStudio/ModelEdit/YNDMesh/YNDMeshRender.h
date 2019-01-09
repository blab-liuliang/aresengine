#pragma once

#include <string>
#include <Engine/RenderSystem/ZRenderable.h>
#include <Engine/RenderSystem/AresRenderable.h>
#include <Physics/Rect3.h>

namespace Ares
{
	// YNDRenderable
	struct YNDRenderable
	{
		RenderLayoutPtr m_layout;			// ����
		SuperMaterial	m_material;			// ����
	};

	//-------------------------------------------
	// ����YNDMesh��Ⱦ 2012-9-26 ����
	//-------------------------------------------
	class YNDMeshRender
	{
	public:
		// �����ʽ
		struct VertexFormat
		{
			float3 m_position;
			float3 m_normal;
			float2 m_uv;
		};

		// ���캯��
		YNDMeshRender( const std::string& filePath);

		// ˢ��
		void FrameMove();

		// ��Ⱦ
		void SubmitRenderElements();

		// ��Ⱦ���
		void RenderDepth( const Matrix44& viewProj);

		// ���ذ�Χ�д�С
		const Rect3& GetWorldBounds() { return m_worldBounds; }

		// ���ΪAresModel
		void SaveAsAresModel( const char* file);

	private:
		// ��ʼ��RenderLayout
		void AddRenderable( const vector<VertexFormat>& vertexs, const vector<WORD>& indices, const string& texturePath);

	private:
		Rect3					m_worldBounds;
		vector<YNDRenderable>	m_renderables;
		vector<ZRenderable>		m_zRenderables;		// �����Ⱦ
		vector<ShaderParamPtr>	m_diffuseParams;
		ShaderParamPtr			m_spWorld;
	};
	typedef s_ptr<YNDMeshRender> YNDMeshRenderPtr;
}