#include "AresLuaScript.h"
#include "lua_AresScriptSystem.h"

namespace Ares
{
	// ���캯��
	LuaScript::LuaScript( const char* filePath)
		: m_filePath( filePath)
	{
		// �½�״̬
		m_luaState = luaL_newstate();

		// ����
		luaL_openlibs( m_luaState);
		//tolua_AresScriptSystem_open( m_luaState);

		// �����ļ� 
		luaL_loadfile( m_luaState, filePath);
	}

	// ��������
	LuaScript::~LuaScript()
	{
		lua_close( m_luaState);
	}

	// ���ú���(�޲�)
	void LuaScript::ExecFunc( const char* functionName)
	{
		lua_getglobal( m_luaState, functionName);

		lua_pcall( m_luaState, 0, 0, 0);
	}
}