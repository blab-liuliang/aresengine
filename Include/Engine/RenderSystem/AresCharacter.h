#pragma once

#include "Engine/RenderSystem/AresRenderEntity.h"

namespace Ares
{
	//------------------------------------
	// ���岿�� 2011-08-12 ����
	//------------------------------------
	class IBodyPart
	{

	};

	//------------------------------------
	// ��ɫʵ�� 2011-08-09 ����
	//------------------------------------
	class ICharacterEntity : public RenderEntity
	{
	public:
		// ������岿��
		virtual bool AddBodyPart( const char* partName)=0;

		// �������岿��mesh
		virtual void SetBodyPartModel( const char* partName, const char* modPath, int meshIdx, int subsetIdx=0)=0;

		// �������岿��
		virtual void SetBodyPartModel( const char* partName, SPtr<IAresModel> modPath, int meshIdx, int subsetIdx=0)=0;

		// �������岿������
		virtual void SetBodyPartMaterial( const char* partName, const char* matPath, int matIdx)=0;

		// �������岿������
		virtual void SetBodyPartMaterial( const char* partName, SPtr<ISurfaceMaterial> pMaterial, int matIdx)=0;

		// ɾ�����岿��
		virtual void DelBodyPart( const char* partName)=0;

	public:
		// ��ȡ����������,����ֵ
		//virtual IAnimationController* GetAnimationController()=0;

	public:
		// ��ʼ��(.cha��ʽ)
		virtual void Load( const char *resPath)=0;

		// ����
		virtual void Save( const char* resPath)=0;
	};
}