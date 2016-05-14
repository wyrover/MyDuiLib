#ifndef _LuaUtilsInclude_h
#define _LuaUtilsInclude_h
#pragma once

#include "LuaWindowExport.h"

namespace DuiLib
{
	class RegDuiUtils2Lua
	{
	public:
		static void RegModule(lua_State* l)
		{
			REG_MODULE(LuaWindowExport)
		}
	};
}

#endif//_LuaUtilsInclude_h