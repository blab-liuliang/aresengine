#pragma once

#include "Core/AresPlatform.h"

namespace Ares
{
	//-----------------------------------
	// TessellationMethod 2012-3-20 ����
	//-----------------------------------
	enum TessellationMethod
	{
		TM_Hardware,
		TM_Instanced,
		TM_No
	};

	//-----------------------------------
	// �豸���� 2011-12-28 ����
	//				ժ�� KlayGe ������
	//-----------------------------------
	struct RenderDeviceCaps
	{
		UINT8		m_maxShaderModel;

		UINT		m_maxTextureWidth;				// ��������
		UINT		m_maxTextureHeight;				// ��������
		UINT		m_maxTextureDepth;
		UINT		m_maxTextureCubeSize;
		UINT		m_maxTextureArrayLength;
		UINT8		m_maxVertexTextureUnits;
		UINT8		m_maxPixelTextureUnits;
		UINT8		m_maxGeometryTextureUnits;

		UINT8		m_maxSimulataneousRts;			// ���ͬʱ��ȾĿ������

		UINT		m_maxVertices;					// ��󶥵���
		UINT		m_maxIndices;					// ���������
		UINT		m_maxVertexStreams;				// ��󶥵���

		UINT8		m_maxTextureAnisotropy;	

		bool		m_hwInstancingSupport;			// �Ƿ�֧��Ӳ��ʵ����
		bool		m_instanceIdSupport;			
		bool		m_streamOutputSupport;
		bool		m_alphaToCoverageSupport;
		bool		m_primitiveRestartSupport;
		bool		m_multithreadRenderingSupport;
		bool		m_multithreadResCreatingSupport;
		bool		m_mrtIndependentBitDepthsSupport;

		bool		m_gsSupport;
		bool		m_csSupport;
		bool		m_hsSupport;
		bool		m_dsSupport;

		TessellationMethod	m_tessllationMethod;

		boost::function<bool(ElementFormat)> IsVertexFormatSupport;
		boost::function<bool(ElementFormat)> IsTextureFormatSupport;
		boost::function<bool(ElementFormat, UINT32, UINT32)> IsRenderTargetFormatSupport;
	};
}