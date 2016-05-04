#include "StdAfx.h"


namespace DuiLib
{
	lua_State* LuaState::m_Lua = NULL;
	luaCallFunc LuaState::luaPanic = NULL;
	luaCallFunc LuaState::luaPrint = NULL;

	lua_State* LuaState::newLua()
	{
		lua_State  *ls;

		ls = luaL_newstate();
		if (ls == NULL) {
			return NULL;
		}

		lua_atpanic(ls, lua_panic);
		luaL_openlibs(ls);

		lua_createtable(ls, 0, 32);

		return ls;
	}

	void LuaState::closeLua()
	{
		if (NULL != m_Lua)
		{
			::lua_close(m_Lua);
			m_Lua = NULL;
		}
	}
	int LuaState::lua_panic(lua_State* ls)
	{
		if (NULL != luaPanic)
		{
			return luaPanic(ls);
		}
		else
		{
			char  *errstr;

			errstr = (char *)lua_tostring(ls, -1);

			MessageBox(NULL, errstr, "", MB_OK);
		}
		return 0;
	}
	int LuaState::lua_print(lua_State* ls)
	{
		string str;
		int nargs = lua_gettop(ls);
		for (int i = 1; i <= nargs; i++) {
			if (lua_isstring(ls, i))
			{
				char *name = (char *)luaL_checkstring(ls, i);

				name = Utf8Char::ngx_utf8_to_gb(name);
				str.append(name);
				free(name);
			}
			else if (lua_isboolean(ls, i))
				str += (lua_toboolean(ls, i) ? _T("true") : _T("false"));
			else if (lua_istable(ls, i))
				str += _T("table");
			else if (lua_isuserdata(ls, i))
				str += _T("userdata");
			else if (lua_isnil(ls, i))
				str += _T("nil");
		}
		str += _T("\n");
		Console::Write(str.c_str());
		return 0;

	}


	void LuaState::AddPackagePath(const char* path)
	{
		if (NULL != m_Lua)
		{
			string new_path = "package.path = package.path .. \"";
			if (!path || strlen(path) == 0)
			{
				return;
			}

			if (path[0] != ';')
			{
				new_path += ";";
			}

			new_path.append(path);

			if (path[strlen(path) - 1] != '/')
			{
				new_path.append("/");
			}

			new_path.append("?.lua\" ");

			if (luaL_dostring(m_Lua, new_path.c_str()))
			{
				char* err = (char*)lua_tostring(m_Lua, -1);
				::lua_pop(m_Lua, 1);
			}
		}
	}
	bool LuaState::LoadFile(const char* file)
	{
		if (NULL != m_Lua)
		{
			return 0 == luaL_dofile(m_Lua, file);
		}
		return false;
	}

	bool LuaState::RunString(const char* str)
	{
		if (NULL != m_Lua)
		{
			return 0 == luaL_dostring(m_Lua, str);
		}
		return false;
	}

	const struct luaL_reg LuaState::printlib[] = {
			{ "print", lua_print },
			{ NULL, NULL } /* end of array */
	};


	bool LuaState::CoInitialize()
	{
		if (NULL == m_Lua)
		{
			m_Lua = newLua();

			lua_getglobal(m_Lua, "_G");
			luaL_register(m_Lua, NULL, printlib);
			lua_pop(m_Lua, 1);

			Register(m_Lua);
			lua_setglobal(m_Lua, "DuiLib");

			return true;
		}
		return false;
	}

	void LuaState::CoUninitialize()
	{
		closeLua();
	}

	void LuaState::Register(lua_State* ls)
	{
		LuaUIControl::Register(ls);
	}
}

