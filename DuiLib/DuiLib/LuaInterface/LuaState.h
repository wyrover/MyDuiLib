#ifndef _LUA_STATE_H
#define _LUA_STATE_H
#pragma once


typedef int(*luaCallFunc)(lua_State* ls);


namespace DuiLib
{
	class UILIB_API LuaState
	{
	protected:
		static const struct luaL_reg printlib[];
		static luaCallFunc luaPanic;
		static luaCallFunc luaPrint;
		static lua_State* newLua();
		static void closeLua();
		static int lua_panic(lua_State* ls);
		static int lua_print(lua_State* ls);
		static void Register(lua_State* ls);

		static lua_State* m_Lua;
	public:
		
		static bool CoInitialize();
		static void CoUninitialize();
				
		static void AddPackagePath(const char* path);
		static bool LoadFile(const char* file);
		static bool RunString(const char* str);
	};
}

#endif//_LUA_STATE_H