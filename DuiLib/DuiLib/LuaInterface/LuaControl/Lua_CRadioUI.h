#ifndef _Lua_CRadioUI_h
#define _Lua_CRadioUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CRadioUI, RadioUI, CRadioUI, OptionUI, COptionUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		
		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CRadioUI_h