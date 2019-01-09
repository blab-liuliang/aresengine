#pragma once

#include "OGLESPlatform.h"
#include <Core/Graphics/AresFrameBuffer.h>

namespace Ares
{
	//-----------------------------------
	// OGLESFrameBuffer 2013-4-3 ����
	//-----------------------------------
	class OGLESFrameBuffer : public FrameBuffer
	{
	public:
		OGLESFrameBuffer( RenderDevice* device, bool offScreen=true);
		virtual ~OGLESFrameBuffer();

		// Clear
		virtual void Clear( const ColorRGB& color, float depth, UINT stencil, UINT flags=CBM_Depth|CBM_Stencil|CBM_Color);

		// ��
		virtual void Bind();
        
        // ��ȡfbo
        GLuint GetFbo() const { return m_fbo; }

	private:
		GLuint		m_fbo;		// Frame Buffer Object
	};
}