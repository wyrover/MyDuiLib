#ifndef _Lua_CTabLayoutUI_h
#define _Lua_CTabLayoutUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CTabLayoutUI, TabLayoutUI, CTabLayoutUI, ProgressUI, CProgressUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetCurSel)
		LUA_METHOD_DECL(SelectItem)
		LUA_METHOD_DECL(SelectItem2)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CTabLayoutUI_h