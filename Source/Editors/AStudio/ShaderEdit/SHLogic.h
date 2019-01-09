#pragma once

#include <vector>
#include <string>
#include <map>
#include "ShaderTreeEdit.h"

using namespace std;

namespace Ares
{
	//---------------------------------------
	// �༭���߼����	2010-07-20 ����	
	//---------------------------------------
	class SHLogic
	{
	public:
		// ���캯��
		SHLogic();

		// ����
		void FrameMove( float fTime);

		// ��ȡ֡��
		float GetFPS()  { return m_fFPS; }

		// ��Ⱦ
		void Render();
		
		// ����֡��
		bool UpdateFPS( float fTime);

		// ������䷽ʽ
		void SetFillMode(WORD index);

		// ����ʵ��
		void SetModelEntity( const char* resPath);

		// Ϊ��ǰ���ʸ���ģ��
		void SetModel( const char* resPath);

		// Ӧ�õ�ǰ����shader
		void ApplyShader();

		// ��ȡ�������
		//RenderMaterial& GetActiveMaterial();

		// ����shader
		void SetActiveShader( const char* shaderName, const char* modelName);

		// ���浱ǰ����shader����ʾ����
		void SaveActiveShader();

	public:
		// ��ȡ���ʱ༭��
		ShaderTreeEdit* GetShaderTreeEdit() { return m_shaderTreeEdit; }

	private:
		HWND					m_hWnd;
		float					m_fFPS;					// frames per second

		// ���λ�õ�
		POINT					m_lastPoint;
		bool					m_mouseLeftButtonDown;	// ����Ƿ���
		//RenderMaterial			m_material;

		string					m_shaderName;			// shader��(��ǰ����)
		ShaderTreeEdit*			m_shaderTreeEdit;	// �������ʱ༭
	};

	extern  SHLogic*				g_pSHLogic;
	#define SHLogic_Main			g_pSHLogic
	#define SHLogic_Input			SHLogic_Main->GetInputListener()
	#define SHLogic_ShaderTreeEdit	SHLogic_Main->GetShaderTreeEdit()
}