#ifndef _LuaDebug_H
#define _LuaDebug_H
#pragma once

namespace DuiLib
{
	LUA_CLASS(Debug)
	{
	public:
		LUA_METHOD_DECL(LuaAssert)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_LuaDebug_H