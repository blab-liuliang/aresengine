#pragma once

#include <Core/Graphics/AresRenderLayout.h>
#include "OGLESRenderMethod.h"

namespace Ares
{
	//----------------------------------------
	// OGLESRenderLayout 2013-02-05 ����
	//----------------------------------------
	class OGLESRenderLayout : public RenderLayout
	{
	public:
		// ���ü���
		void Render( OGLESRenderLayout* preLayout, OGLESRenderMethod* method);

		// ����
		void Active( const OGLESRenderMethod& method) const;

		// ����
		void Deactive( const OGLESRenderMethod& method) const;
	};
}