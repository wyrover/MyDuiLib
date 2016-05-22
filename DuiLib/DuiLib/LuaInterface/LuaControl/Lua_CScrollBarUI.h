#ifndef _Lua_CScrollBarUI_h
#define _Lua_CScrollBarUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CScrollBarUI, ScrollBarUI, CScrollBarUI, ControlUI, CControlUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetOwner)
		LUA_METHOD_DECL(SetOwner)
		LUA_METHOD_DECL(IsHorizontal)
		LUA_METHOD_DECL(SetHorizontal)
		LUA_METHOD_DECL(GetScrollRange)
		LUA_METHOD_DECL(SetScrollRange)
		LUA_METHOD_DECL(GetScrollPos)
		LUA_METHOD_DECL(SetScrollPos)
		LUA_METHOD_DECL(GetLineSize)
		LUA_METHOD_DECL(SetLineSize)

		LUA_METHOD_DECL(GetShowButton1)
		LUA_METHOD_DECL(SetShowButton1)
		LUA_METHOD_DECL(GetButton1NormalImage)
		LUA_METHOD_DECL(SetButton1NormalImage)
		LUA_METHOD_DECL(GetButton1HotImage)
		LUA_METHOD_DECL(SetButton1HotImage)
		LUA_METHOD_DECL(GetButton1PushedImage)
		LUA_METHOD_DECL(SetButton1PushedImage)
		LUA_METHOD_DECL(GetButton1DisabledImage)
		LUA_METHOD_DECL(SetButton1DisabledImage)

		LUA_METHOD_DECL(GetShowButton2)
		LUA_METHOD_DECL(SetShowButton2)
		LUA_METHOD_DECL(GetButton2NormalImage)
		LUA_METHOD_DECL(SetButton2NormalImage)
		LUA_METHOD_DECL(GetButton2HotImage)
		LUA_METHOD_DECL(SetButton2HotImage)
		LUA_METHOD_DECL(GetButton2PushedImage)
		LUA_METHOD_DECL(SetButton2PushedImage)
		LUA_METHOD_DECL(GetButton2DisabledImage)
		LUA_METHOD_DECL(SetButton2DisabledImage)

		LUA_METHOD_DECL(GetThumbNormalImage)
		LUA_METHOD_DECL(SetThumbNormalImage)
		LUA_METHOD_DECL(GetThumbHotImage)
		LUA_METHOD_DECL(SetThumbHotImage)
		LUA_METHOD_DECL(GetThumbPushedImage)
		LUA_METHOD_DECL(SetThumbPushedImage)
		LUA_METHOD_DECL(GetThumbDisabledImage)
		LUA_METHOD_DECL(SetThumbDisabledImage)

		LUA_METHOD_DECL(GetRailNormalImage)
		LUA_METHOD_DECL(SetRailNormalImage)
		LUA_METHOD_DECL(GetRailHotImage)
		LUA_METHOD_DECL(SetRailHotImage)
		LUA_METHOD_DECL(GetRailPushedImage)
		LUA_METHOD_DECL(SetRailPushedImage)
		LUA_METHOD_DECL(GetRailDisabledImage)
		LUA_METHOD_DECL(SetRailDisabledImage)

		LUA_METHOD_DECL(GetBkNormalImage)
		LUA_METHOD_DECL(SetBkNormalImage)
		LUA_METHOD_DECL(GetBkHotImage)
		LUA_METHOD_DECL(SetBkHotImage)
		LUA_METHOD_DECL(GetBkPushedImage)
		LUA_METHOD_DECL(SetBkPushedImage)
		LUA_METHOD_DECL(GetBkDisabledImage)
		LUA_METHOD_DECL(SetBkDisabledImage)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CScrollBarUI_h