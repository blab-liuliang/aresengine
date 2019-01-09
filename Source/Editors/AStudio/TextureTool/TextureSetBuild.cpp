#include "TextureSetBuild.h"
#include <Engine/AresRoot.h>

namespace Ares
{
	// �½������
	void TextureSetBuild::SetTextureSize( UINT width, UINT height, ElementFormat format)
	{
		if( !m_result)
		{
			m_result  = ARenderDevice->CreateTexture2D( width, height, 1, 1, format, 1, 0, EAH_CPURead | EAH_CPUWrite, NULL);
			m_texSet = AResSystem.CreateTextureSet( m_result);
		}
	}

	// ��������
	void TextureSetBuild::Insert( TexturePtr& subTex)
	{
		m_texSet->Insert( subTex);
	}

	// ��������
	void TextureSetBuild::Insert( const char* fileName)
	{
		TexturePtr subTex = AResSystem.SyncLoadDDS( fileName, EAH_GPURead | EAH_Immutable);
		if( subTex)
			m_texSet->Insert( subTex);
	}
}