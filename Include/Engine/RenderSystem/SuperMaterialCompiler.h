#pragma once

#include <Core/AresCore.h>
#include "SuperMaterialExpression.h"

namespace Ares
{
	// MaterialCodeType
	enum OutputType
	{
		OPT_Float1		= 1,
		OPT_Float2		= 2,
		OPT_Float3		= 4,
		OPT_Float4		= 8,
		OPT_Float		= 15,
		OPT_Texture2D	= 16,
	};

	//-------------------------------------------
	// SuperMaterialShaderTree 2012-12-20 ����
	//-------------------------------------------
	class MaterialCompiler
	{
	public:
		MaterialCompiler();
		~MaterialCompiler();

		// ����
		bool Compile();

		// ����
		virtual INT Constant( const float4& val, INT numComponents)=0;

		// ������
		virtual INT ComponentMask( INT vector, bool maskR, bool maskG, bool maskB, bool maskA)=0;
	};
	typedef s_ptr<MaterialCompiler> SMShaderTreePtr;

	//-------------------------------------------
	// OGLMaterialCompiler 2013-3-11 ����
	//-------------------------------------------
	class OGLMaterialCompiler : public MaterialCompiler
	{

	};
}