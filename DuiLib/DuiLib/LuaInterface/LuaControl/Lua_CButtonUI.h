#ifndef _Lua_CButtonUI_h
#define _Lua_CButtonUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CButtonUI, ButtonUI, CButtonUI, ControlUI, CControlUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetNormalImage)
		LUA_METHOD_DECL(GetNormalImage)
		LUA_METHOD_DECL(GetHotImage)
		LUA_METHOD_DECL(SetHotImage)
		LUA_METHOD_DECL(GetPushedImage)
		LUA_METHOD_DECL(SetPushedImage)
		LUA_METHOD_DECL(GetFocusedImage)
		LUA_METHOD_DECL(SetFocusedImage)
		LUA_METHOD_DECL(GetDisabledImage)
		LUA_METHOD_DECL(SetDisabledImage)
		LUA_METHOD_DECL(GetForeImage)
		LUA_METHOD_DECL(SetForeImage)
		LUA_METHOD_DECL(GetHotForeImage)
		LUA_METHOD_DECL(SetHotForeImage)
		LUA_METHOD_DECL(SetHotBkColor)
		LUA_METHOD_DECL(GetHotBkColor)
		LUA_METHOD_DECL(SetHotTextColor)
		LUA_METHOD_DECL(GetHotTextColor)
		LUA_METHOD_DECL(SetPushedTextColor)
		LUA_METHOD_DECL(GetPushedTextColor)
		LUA_METHOD_DECL(SetFocusedTextColor)
		LUA_METHOD_DECL(GetFocusedTextColor)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CButtonUI_h