#ifndef _Lua_CHotKeyUI_h
#define _Lua_CHotKeyUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CHotKeyUI, HotKeyUI, CHotKeyUI, LabelUI, CLabelUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetNormalImage)
		LUA_METHOD_DECL(SetNormalImage)
		LUA_METHOD_DECL(GetHotImage)
		LUA_METHOD_DECL(SetHotImage)
		LUA_METHOD_DECL(GetFocusedImage)
		LUA_METHOD_DECL(SetFocusedImage)
		LUA_METHOD_DECL(GetDisabledImage)
		LUA_METHOD_DECL(SetDisabledImage)
		LUA_METHOD_DECL(SetNativeBkColor)
		LUA_METHOD_DECL(GetNativeBkColor)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CHotKeyUI_h