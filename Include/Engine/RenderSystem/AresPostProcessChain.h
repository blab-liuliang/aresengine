#pragma once

#include <Core/AresPlatform.h>
#include "AresGodRay.h"
#include "AresDepthOfField.h"
#include "AresFloodColor.h"

namespace Ares
{
	//-----------------------------
	// ��������� 2013-1-29 ����
	//-----------------------------
	class PostProcessChain
	{
	public:
		PostProcessChain( size_t width, size_t height, Scene& scene);

		// ���Ĵ��ڴ�С
		void Resize( size_t width, size_t height);

		// ��ȡGodRay����
		GodRayPtr GetGodRayPostProcess(){ return m_godRay; }

		// ��ȡ�������
		DepthOfFieldPtr GetDepthOfField() { return m_depthOfField; }

		// ��ȡ����ɫ
		FloodColorPtr GetFloodColor() { return m_floodColor; }

	private:
		GodRayPtr		m_godRay;		// �ϵ�����
		DepthOfFieldPtr m_depthOfField; // ����
		FloodColorPtr	m_floodColor;	// ����ɫ
	};
	typedef s_ptr<PostProcessChain> PostProcessChainPtr;
}