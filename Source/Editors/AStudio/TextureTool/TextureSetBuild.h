#pragma once

#include <Engine/RenderSystem/AresTextureSet.h>

namespace Ares
{
	//-----------------------------------------------
	// TexturePackageBuild 2012-7-23 ����
	//-----------------------------------------------
	class TextureSetBuild
	{
	public:
		// �½������
		void SetTextureSize( UINT width, UINT height, ElementFormat format);

		// ��������
		void Insert( TexturePtr& subTex);

		// ��������
		void Insert( const char* fileName);

		// ��ȡ�������
		TexturePtr GetResultTexture() { return m_result; }

	private:
		TexturePtr	   m_result;
		TextureSet*	   m_texSet;
	};
}