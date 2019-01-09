#pragma once

#include <Engine/RenderSystem/SuperMaterial.h>
#include <Engine/RenderSystem/SuperMaterialShaderTree.h>

namespace Ares
{
	//-----------------------------------------
	// �������ʱ༭�� 2012-12-20 ����
	//-----------------------------------------
	class ShaderTreeEdit
	{
	public:
		ShaderTreeEdit();
		~ShaderTreeEdit();

		// �½�
		void New();

		// ��ӱ��ʽ
		void AddExpression( ExpressionType type, const Vector2& pos);

		// �������
		void AddConnection( const string& expression, const string& input);

		// ɾ������
		void DelConnection( const string& input);

		// ��ȡ��ǰ�༭ShaderTree
		MaterialShaderTree* GetShaderTree() { return m_shaderTree; }

		// �Ƿ��д洢·��
		bool IsHaveSavePath() { return !m_path.empty(); }

		// ���ô洢·��
		void SetSavePath( const string& savepath) { m_path=savepath; }

		// ����
		void Save();

		// ����
		void Load( const string& path);

	private:
		string					m_path;				// ·��
		MaterialShaderTree*		m_shaderTree;		// shader tree
	};
}