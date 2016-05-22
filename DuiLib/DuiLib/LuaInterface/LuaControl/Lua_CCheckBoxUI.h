#ifndef _Lua_CCheckBoxUI_h
#define _Lua_CCheckBoxUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CCheckBoxUI, CheckBoxUI, CCheckBoxUI, OptionUI, COptionUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetCheck)
		LUA_METHOD_DECL(GetCheck)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CCheckBoxUI_h