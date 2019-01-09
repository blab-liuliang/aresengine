#pragma once

#include <vector>
#include <Core/AresCore.h>
#include <Physics/Shapes.h>

using namespace std;

namespace Ares
{
	//--------------------------------------
	// �㼶��Ӱ������ 2013-2-22 ����
	//--------------------------------------
	class Scene;
	class CSMMgr
	{
	public:
		// shader param type
		enum SPType
		{
			SP_SplitPos	  = 0,			// �۲�crop
			SP_ViewCropRemap,			// Remap
			SP_DepthMap,				// ���ͼ
			SP_NumSplits,
			SP_Total,
		};

	public:
		CSMMgr();
		~CSMMgr();

		// ���ù�������
		void SetScene( Scene* scene);

		// ����̫���⳯��
		void SetLightDirection( const Vector3& dir);

		// �����������ֱ���
		void SetShadowMapResolution( size_t resolution=0);

		// ��ʼ��Ӱ��Ⱦͼ�׶�
		void RefreshShadowMaps( const Rect3& rect);

		// ��ʼ��Ӱ��Ⱦͼ�׶�
		void RefreshShadowMaps( Frustum3& frustum, size_t numSplits);

		// ��ȡshader�󶨲���
		ShaderParamPtr GetSPAB( SPType type) const { return m_spab[type]; }

		// ��ȡ�������
		TexturePtr GetDepthTexture() { return m_depthTexture; }

	private:
		// ���·�����Դ
		void ReAllocateRes();

		// ������Ӱ������Ͷ��������
		void SetFocusRegion( const Rect3& rect);

		// ������Ӱ������Ͷ��������(���ڶ�̬ƽ�зָ���Ӱ)
		void SetFocusRegion( const Frustum3& frustum, size_t numSplits);

		// ������Ӱ����������(�㼯)
		void SetFocusRegion( const vector<Vector3>& points, size_t index);

		// ��������Ӧ����
		void CalculateCropMatrix( Matrix44& crop, const vector<Vector3>& points, const Matrix44& view);

		// ������Ѱ�����Χ��
		void CalculateSearchBox3( Box3& searchBox, const vector<Vector3>& points, const Vector3& pos);

		// ����SPAB
		void UpdateSPAB();

	private:
		Scene*					m_scene;			// ��������
		Vector3					m_dir;				// �⳯��
		size_t					m_resolution;		// ����ͼ�ֱ���
		size_t					m_numSplits;		// �ָ���
		Matrix44				m_remap;			// ƫ��
		vector<Matrix44>		m_views;			// �۲����
		vector<Matrix44>		m_crops;			// ����Ӧ����
		TexturePtr				m_depthTexture;		// �������
		vector<FrameBufferPtr>	m_depthBuffers;		// ��Ȼ���
		vector<Box3>			m_searchBox3s;		// ��Ѱ��Χ��
		float					m_splitSchemeWeight;// �ָ�Ȩ��
		vector<float4>			m_splitPos;			// �ָ�λ��

		boost::array<ShaderParamPtr,SP_Total>	m_spab;	// ShaderParamAutoBind
	};
	typedef s_ptr<CSMMgr> CSMMgrPtr;
}