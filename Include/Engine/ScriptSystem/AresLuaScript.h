#pragma once

#include <string>
#include <Core/AresCore.h>
#include "Engine/Foundation/Ares3DEngine_h.h"
#include "AresLuaArg.h"

using namespace std;

namespace Ares
{
	//-----------------------------------------
	// Lua�ű� 2012-8-3  ����
	//-----------------------------------------
	class ARES_EXPORT LuaScript
	{
		typedef int(*ExportFun)(lua_State*);
	public:
		// ���캯��
		LuaScript( const char* filePath);

		// ��������
		~LuaScript();

		// ִ�к���(0��)
		void ExecFunc( const char* functionName);

		// ͨ��ִ��
		void ExecFunc( const char* functionName, const char*sig, ...);

		// ͨ��ִ��
		void ExecFunc( const char* functionName, LuaArgList* args, LuaRVList* rv);

		// �жϺ����Ƿ����
		bool IsFuncExist( const char* functionName) const;

		// ���ñ���ֵ
		void SetGlobal( const char* name, void* value, const char* type);

		// ��ȡLuaState
		lua_State* GetLuaState() { return m_luaState; }

		// ע�ᵼ������
		static void RegisterExportFun(ExportFun fun) { m_exportFun.push_back( fun); }

	private:
		string					 m_filePath;	// �ű���Դ
		lua_State*				 m_luaState;	// �ű�������ָ��
		static vector<ExportFun> m_exportFun;	// ��������
	};

	typedef s_ptr<LuaScript> LuaScriptPtr;
}