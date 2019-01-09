#pragma once

#include <Core/Graphics/AresRenderLayout.h>
#include "OGLRenderMethod.h"

namespace Ares
{
	//----------------------------------------
	// OGLESRenderLayout 2013-02-05 ����
	//----------------------------------------
	class OGLRenderLayout : public RenderLayout
	{
	public:
		// ���ü���
		void Render( OGLRenderLayout* preLayout, OGLRenderMethod* method);

		// ����
		void Active( const OGLRenderMethod& method) const;

		// ����
		void Deactive( const OGLRenderMethod& method) const;
	};
}