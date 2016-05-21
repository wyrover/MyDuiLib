#ifndef _LuaUtilsInclude_h
#define _LuaUtilsInclude_h
#pragma once

#include REQUIRE_H(CLuaWindow)

namespace DuiLib
{
	class RegDuiUtils2Lua
	{
	public:
		static void RegModule(lua_State* l)
		{
			LUA_CLASS_REG(CLuaWindow)
		}
	};
}

#endif//_LuaUtilsInclude_h