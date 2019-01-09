#pragma once

#include <Engine/RenderSystem/AresVisualShape.h>

#define YND_Engine

namespace Ares
{
	//--------------------------------------------
	// ��ײ�༭�߼� 2012-9-12 ����
	//--------------------------------------------
	class CollisionBuildLogic
	{
	public:
		CollisionBuildLogic();

		// ���shape
		void AddShape( VisualShapeType type);

		// ��ȡ��ǰ������״
		const vector<VisualShape*>& GetShapes() { return m_visualShapes; }

		// ���õ�ǰѡ����״
		void SetSelected( size_t idx);

		// ��ȡ��ǰѡ����״
		VisualShape* GetSelected();

		// ɾ����ǰѡ��
		void DeleteSelected();

		// �������ģʽ
		void SwitchToWireFrameFillMode();

		// �������ģʽ
		void SwitchToNormalFillMode();

		// ����������ײģ��
		void SavePhysicsShapes( const std::string& filePath);

		// ����������ײģ��
		void LoadPhysicsShapes( const std::string& filePath);

		// ����������ײģ��
		void YNDSavePhysicsShapes( const std::string& filePath);

		// ����������ײģ��
		void YNDLoadPhysicsShapes( const std::string& filePath);

	private:
		// ��ȡ��������
		Shape* ExtractShape( VisualShape* vs);

		// ��ԭVisualShape
		void RestoreVisualShape( Shape* shape);

	private:
		size_t					m_selectedIdx;
		vector<VisualShape*>	m_visualShapes;
		//VisualShape*			m_visualShape;		// ֻ��һ������
	};
}