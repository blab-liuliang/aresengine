#pragma once

#include "AresMap.h"
#include "../RenderSystem/AresCameraCallback.h"
#include "../Foundation/AresErrorCallback.h"

namespace Ares
{
	//-----------------------------------
	// IMainSystem 2011-08-16 ����
	//-----------------------------------
	class IMainSystem
	{
	public:
		// ��ʼ��
		virtual void Init( ICameraCallback* mainCamera, IErrorCallback* errorCallback)=0;

	public:
		// �������������, ��ͼ��,���λ��
		virtual IMap* CreateMap( const char* mapName=0, const char* location=0)=0;

		// �½�����
		virtual IArea* CreateArea( const char* areaName=0)=0;
	};
}