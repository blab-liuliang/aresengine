#pragma once

#include "ShaderTreeControl.h"
#include <Engine/RenderSystem/SuperMaterialShaderTree.h>

using namespace ST;

namespace Ares
{
	//-------------------------------
	// ���ӹ����� 2013-3-22 ����
	//-------------------------------
	struct ShaderTreeConnectMgr
	{
		vector<ST::QBezierCurve*>	m_curves;
		ST::QBezierCurve*			m_curveEdit;

	public:
		// ���캯��
		ShaderTreeConnectMgr() : m_curveEdit( NULL) {}

		// �½�����
		void CreateConnect();

		// �������
		void FinishConnect( QExpressionInputOutput* end);

		// ɾ������
		void DeleteEditConnect();

		// ��ȡ�༭������
		QBezierCurve* GetEditConnect() { return m_curveEdit; }

		// ��ȡ����
		QBezierCurve* EditConnect( ST::QExpressionInputOutput* end);

		// ����������ƶ�
		void OnMove( QExpressionInputOutput* ioput);

		// ����
		void Reset();

		// �������
		void AddConnection( ST::QBezierCurve* curve);

		// �Ƴ���������
		void RemoveUselessConnection( MaterialShaderTree* shaderTree);

		// ��ȡ����
		ST::QBezierCurve* GetConnection( const string& expression, const string& input);
	};
}