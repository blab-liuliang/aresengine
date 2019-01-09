#pragma once

#ifdef OPENGL_EXPORTS
#define OGL_API __declspec(dllexport)
#else										// Use dll
#define OGL_API __declspec(dllimport)
#endif

#include "OGLRenderDevice.h"

namespace Ares
{
	extern "C"
	{
		// �������
		OGL_API void  DllStartRenderFactory( RenderDevice*& ptr)
		{
			ptr = new_ OGLRenderDevice();
		}

		// �������
		OGL_API void DllStopRenderFactory()
		{

		}
	}
}