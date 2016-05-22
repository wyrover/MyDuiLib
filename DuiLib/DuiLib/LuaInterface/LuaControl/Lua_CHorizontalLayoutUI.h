#ifndef _Lua_CHorizontalLayoutUI_h
#define _Lua_CHorizontalLayoutUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CHorizontalLayoutUI, HorizontalLayoutUI, CHorizontalLayoutUI, ContainerUI, CContainerUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetSepWidth)
		LUA_METHOD_DECL(GetSepWidth)
		LUA_METHOD_DECL(SetSepImmMode)
		LUA_METHOD_DECL(IsSepImmMode)
		LUA_METHOD_DECL(GetThumbRect)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CHorizontalLayoutUI_h