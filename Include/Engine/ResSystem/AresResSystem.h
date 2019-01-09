#pragma once

#include <map>
#include <string>
#include <Core/AresFileUtils.h>
#include "Engine/RenderSystem/AresModel.h"
#include "Engine/RenderSystem/AresModelIDCard.h"
#include "Engine/RenderSystem/M1Animation.h"
#include "Engine/RenderSystem/AresTerrain.h"
#include "Engine/RenderSystem/AresTextureSet.h"
#include "Engine/RenderSystem/AresPointLight.h"
#include "Engine/RenderSystem/AresDirectionalLight.h"
#include <Core/Graphics/AresElementFormat.h>
#include "Engine/ScriptSystem/AresLuaScript.h"

using namespace std;

namespace Ares
{
	// ��Դ·���б�
	typedef vector<string> ResPaths;

	//-----------------------------------------
	// ��Դ������ 2012-05-21     ����
	//	   ֻ��֤��ͬ�ļ���ԴΨһ���������߳�
	//	���ش���
	//-----------------------------------------
	class ResSystem
	{
	public:
		ResSystem( const ResPaths& paths);
		~ResSystem();

		// ���·��
		void AddPath( const string& path);

		// �Ƴ�·��
		void RemovePath( const string& path);

		// ��ȫ·��
		string FullPath( const string& name);

		// ����ʵ����
		void LoadEntityGroup( const char* filePath) {}

		// ����ģ���ļ� *.mod
		MeshPtr  LoadMesh( const char* filePath, int index);

		// ������Ⱦ����
		RenderMethodPtr LoadMethod( string fileName, const ShaderMacros& macros=ShaderMacros(), QWORD guid=0);

		// ���ز���
		SuperMaterialPtr LoadMaterialParameter( SuperMaterialPtr& material, const char* filePath, int index, QWORD usage);

		// ����ģ��ʵ���ļ� *.m1
		ModelPtr LoadModel( const char* filePath);

		// ���ض����ļ�
		s_ptr<CAresAnimation> LoadAnimation( const char* filePath);

		// ���ؽű�
		LuaScriptPtr	LoadLuaScript( const char* filePath);

		// ��ȡ�Զ���shader����
		void AutoBindParam( RenderMaterialPtr& material, const RenderEntity* renderEntity);

		// ͬ����������
		TexturePtr SyncLoadDDS( const char* texPath, UINT accessHint);

		// �½�����
		TextureSet* CreateTextureSet( TexturePtr& texture);

		// �½���
		LightPtr MakeLight( LightType type);

	public:
		// �ļ��ı�
		void FileChanged( const char* path) {}

	public:
		// ͬ����������
		void SyncSaveTexture( const TexturePtr& texture, const char* filePath, ElementFormat destFmt=EF_UnKnown);

	public:
		// ����
		void Step( float elapsedTime) {}

		// ����(Garbage clear)
		UINT Clear();

	private:
		map<string, MeshPtr>					m_meshPool;				// Mesh��
		map<string, SuperMaterial::IDCardPtr>	m_materialPool;			// Դ����
		map<string, s_ptr<CAresAnimation> >		m_m1Animations;			// ������Դ
		map<size_t, RenderMethodPtr>			m_methodPool;			// Ч����
		map<string, LuaScriptPtr>				m_luaScriptPool;		// �ű���Դ��
		map<string, TexturePtr>					m_texturePool;			// �����
		string									m_exePath;				// ִ���ļ�·��
		//vector<string>							m_pathes;				// ��ͼ�б�
        FileUtils*                              m_fileUtils;            // �ļ�����
	};
}