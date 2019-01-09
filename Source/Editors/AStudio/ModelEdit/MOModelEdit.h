#pragma once

#include "YNDMesh/YNDMeshRender.h"
#include <Engine/RenderSystem/AresVisualShape.h>
#include <Engine/RenderSystem/ZWriteMgr.h>
#include <boost/filesystem.hpp>

using namespace boost;
using namespace boost::filesystem;

namespace Ares
{
	// ģ������
	enum ModelType
	{
		MT_NULL,		// �ޱ༭ģ��
		MT_ARES,		// Ares����ģ��
		MT_YND,			// YND����ģ��
		FX_ARES,		// Ares��Ч
	};

	//--------------------------------------
	// Ч���༭�߼� 2012-8-20 ����
	//--------------------------------------
	class ModelEdit
	{
	public:
		ModelEdit();

		// ��������
		void CreateWhiteGrid();

		// ������ɫ����
		void CreateRedCross();

		// ����ʵ��
		void SetResEntity( const char* resPath);

		// ��ȡģ������
		ModelType GetModelType();

		// ��ȡģ�Ͱ�Χ�а뾶
		float GetModelRadius();

		// ��ȡģ�������Χ��
		Rect3 GetModelWorldBounds();

		// ��ȡ��ǰ��Դ·��
		const char* GetResPath() { return m_currResPath.c_str(); }

		// ��ȡ��ǰʵ��
		ModelPtr&  GetCurrEntity() { return m_currEntity; }

		// ����
		void FrameMove( float elapsedTime);

		// ���¼���
		void Reload();

	private:
		// Zoom
		void Zoom();

	private:
		VisualShape*			m_whiteGrid;		// ��������
		VisualShape*			m_redCross;			// ���ĺ�ʮ��

		string					m_currResPath;		// ��ǰģ��·��
		ModelPtr				m_currEntity;		// ��ǰ�༭ʵ��

		string					m_modelPath;		// ģ�ʹ洢·��
	};
}