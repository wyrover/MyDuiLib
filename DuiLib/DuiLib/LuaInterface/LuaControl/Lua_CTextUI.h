#ifndef _Lua_CTextUI_h
#define _Lua_CTextUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CTextUI, TextUI, CTextUI, LabelUI, CLabelUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetLinkContent)
		
		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CTextUI_h