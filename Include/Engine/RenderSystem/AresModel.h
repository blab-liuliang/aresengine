#pragma once

#include <map>
#include <list>
#include "Engine/RenderSystem/M1Animation.h"
#include "Engine/RenderSystem/AresAnimationController.h"
#include "Engine/RenderSystem/AresRenderEntity.h"
#include "Engine/RenderSystem/SuperMaterial.h"
#include "Engine/RenderSystem/AresMesh.h"

using namespace std;

#define BONE_MAX 64

namespace Ares
{
	//-------------------------------------
	// MeshRenderable 2013-4-27 ����
	//-------------------------------------
	class MeshRenderable : public Renderable
	{
	public:
		// ���캯��
		MeshRenderable();

		// ��ȡ����������
		int GetPrimitiveCount() const;

	public:
		string				m_materialPath;		// ����·��	
		int					m_materialIdx;		// ��������
		string				m_meshFilePath;		// ����·��
		int					m_meshIdx;			// ��������
		MeshPtr				m_mesh;				// ��Ⱦ����
		SuperMaterialPtr	m_superMaterial;	// ��ǰ����
	};

	//---------------------------------------
	// M1Entity  2010-09-25   ����
	//---------------------------------------
	class Model : public RenderEntity
	{
	public:
		//------------------------------
		// IDCardModel 2013-4-26 ����
		//------------------------------
		struct IDCard
		{
		public:
			// ��ȾԪ��
			struct RenderInfo
			{
				string	m_materialPath;			// ����·��	
				int		m_materialIdx;			// ��������
				string	m_meshFilePath;			// ����·��
				int		m_meshIdx;				// ��������

				// ���л�
				template <typename Archive> void serialize( Archive& ar, const unsigned int version)
				{
					ar & m_materialPath & m_materialIdx & m_meshFilePath & m_meshIdx;
				}
			};

			// �ؽ�ģ������
			void RebuildModel( Model& model);

			// ���л�
			template <typename Archive> void serialize( Archive& ar, const unsigned int version)
			{
				ar & m_aniPath;
				ar & m_renderInfos;
			}

		public:
			string				m_aniPath;		// ����·��(Ψһ)
			vector<RenderInfo>	m_renderInfos;	// ��Ⱦ��Ϣ
		};
		typedef s_ptr<IDCard> IDCardPtr;
		friend struct IDCard;

	public:
		Model();
		~Model();

		// ������Դ·��
		void SetFilePath( const char* filePath) { m_filePath = filePath; }

		// ��ȡ��Դ·��
		const char* GetFilePath() const { return m_filePath.c_str(); }

		// ��ȡM1Renderable����
		size_t GetMeshRenderableNum() { return m_renderables.size(); }

		// ��ȡM1Renderable
		MeshRenderable& GetMeshRenderable( size_t idx);

		// ʹ�ù���ͼ
		bool ApplyLightmap( TexturePtr lightmapTex, const Vector4& lightmapViewport, int meshIdx);

		// ��ȡ����������
		AnimationController* GetAnimationController() { return &m_animationController; }

		// ����
		virtual void FrameMove( float fTime);

		// �ύ����Ⱦ����( ʹ����Ч ��������)
		virtual void SubmitRenderElements( RenderElementMgr& renderElementMgr);

	private:
		// �󶨲��ʲ���
		void AutoBindMaterialParameter( MeshRenderable& mr);

		// ��RenderLayout
		void AutoBindRenderLayout( MeshRenderable& mr);

		// ��ӵ�������Ϣ
		virtual void OnAddToScene( Scene* scene);

	protected:
		IDCardPtr				m_idcard;				// �����Ϣ
		string					m_filePath;				// ģ��·��
		AnimationController		m_animationController;	// ����������
		vector<MeshRenderable>	m_renderables;			// ����Ⱦ�Ｏ
		ShaderParamPtr			m_boneTransform;		// ����ת��
		ShaderParamPtr			m_lightViewCrop;		// ��Դ�ռ�
	};
	typedef s_ptr<Model>  ModelPtr;
}