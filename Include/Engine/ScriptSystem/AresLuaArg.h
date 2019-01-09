#pragma once

#include <vector>
#include <tolua++/tolua++.h>

extern "C"
{
#include <tolua++/lua/lualib.h>
};

using namespace std;

namespace Ares
{
	//--------------------------------------
	// �������� 2012-8-4 ����
	//--------------------------------------
	struct LuaArg
	{
		// ����ֵ
		virtual void PushValue( lua_State* luaState)const=0;
	};

	//--------------------------------------
	// ���β��� 2012-8-4 ����
	//--------------------------------------
	struct LuaIntArg : public LuaArg
	{
		int		m_value;

		// ���캯��
		explicit LuaIntArg( int v)
			: m_value( v)
		{}

		// ����ֵ
		virtual void PushValue(lua_State* luaState) const
		{
			lua_pushinteger( luaState, m_value);
		}
	};

	//-----------------------------------
	// �����б� 2012-8-4 ����
	//-----------------------------------
	class LuaArgList
	{
	public:
		// ���Int����
		void AddArg( int value)
		{
			LuaIntArg* arg = new_ LuaIntArg( value);
			m_args.push_back( arg);
		}

		// PushValue
		void PushValue( lua_State* luaState)
		{
			for ( size_t i=0; i<m_args.size(); i++)
				m_args[i]->PushValue( luaState);
		}

		// ��������
		int GetSize() { return (int)m_args.size(); }

	private:
		vector<LuaArg*>		m_args;
	};

	//--------------------------------------
	// ����ֵ���� 2012-8-4 ����
	//--------------------------------------
	struct LuaRV
	{
		// ����ֵ
		virtual void ToValue( lua_State* luaState, int idx)const=0;
	};

	//-----------------------------------
	// ����ֵ�б� 2012-8-4 ����
	//-----------------------------------
	class LuaRVList
	{
	public:
		// PushValue
		void ToValue( lua_State* luaState)
		{
			for ( int i=1; i<=(int)m_rvs.size(); i++)
				m_rvs[i]->ToValue( luaState, -i);
		}

		// ��������
		int GetSize() { return (int)m_rvs.size(); }

	private:
		vector<LuaRV*>	m_rvs;
	};
}