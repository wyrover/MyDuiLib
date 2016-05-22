#ifndef _Lua_CVerticalLayoutUI_h
#define _Lua_CVerticalLayoutUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CVerticalLayoutUI, VerticalLayoutUI, CVerticalLayoutUI, ContainerUI, CContainerUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetSepHeight)
		LUA_METHOD_DECL(GetSepHeight)
		LUA_METHOD_DECL(SetSepImmMode)
		LUA_METHOD_DECL(IsSepImmMode)
		LUA_METHOD_DECL(GetThumbRect)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CVerticalLayoutUI_h