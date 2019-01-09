#pragma once

#include <string>
#include <Core/AresMath.h>
#include <Engine/RenderSystem/AresMesh.h>
#include <Engine/RenderSystem/AresModel.h>

using namespace std;

namespace Ares
{
	//--------------------------------------
	// ģ��ת��
	//--------------------------------------
	class ModelConverter
	{
	public:
		// YND�ļ�ת��ΪAres
		static void YNDToAres( const string& yndFile, const string& aresLoacation, FileUtils& fileUtils, bool isReplaceExistAres);

	private:
		// ����
		static void Reset();

	private:
		static vector<Mesh::IDCard*>			m_meshIDCards;		// ģ������
		static vector<SuperMaterial::IDCard*>	m_materialIDCards;// ��������
		static Model::IDCard*					m_modelIDcard;		// ģ������
	};
}