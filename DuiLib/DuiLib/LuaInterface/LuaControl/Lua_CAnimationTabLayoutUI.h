#ifndef _Lua_CAnimationTabLayoutUI_h
#define _Lua_CAnimationTabLayoutUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CAnimationTabLayoutUI, AnimationTabLayoutUI, CAnimationTabLayoutUI, TabLayoutUI, CTabLayoutUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CAnimationTabLayoutUI_h