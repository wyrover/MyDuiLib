#ifndef _LuaDebug_H
#define _LuaDebug_H
#pragma once

namespace DuiLib
{
	class UILIB_API LuaDebug
	{
	public:
		DECL_LUA_FUNC(LuaAssert)

		static void Register(lua_State* l);
	};
}


#endif//_LuaDebug_H