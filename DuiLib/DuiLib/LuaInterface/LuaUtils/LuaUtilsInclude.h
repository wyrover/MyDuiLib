#ifndef _LuaUtilsInclude_h
#define _LuaUtilsInclude_h
#pragma once

#include REQUIRE_H(CLuaWindow)
#include REQUIRE_H(DuiEngine)

namespace DuiLib
{
	class RegDuiUtils2Lua
	{
	public:
		static void RegModule(lua_State* l)
		{
			LUA_CLASS_REG(CLuaWindow)
			LUA_CLASS_REG(DuiEngine)
		}
	};
}

#endif//_LuaUtilsInclude_h