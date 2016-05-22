#ifndef _Lua_CFadeButtonUI_h
#define _Lua_CFadeButtonUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CFadeButtonUI, FadeButtonUI, CFadeButtonUI, ButtonUI, CButtonUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CFadeButtonUI_h