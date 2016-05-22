#ifndef _Lua_CContainerUI_h
#define _Lua_CContainerUI_h
#pragma once
#include "LuaDefine.h"
namespace DuiLib
{
	LUA_CLASS(CContainerUI, ContainerUI, CContainerUI, ControlUI, CControlUI)
	{
	public:
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(New)
		//
		LUA_METHOD_DECL(GetItemAt)
		LUA_METHOD_DECL(GetItemIndex)
		LUA_METHOD_DECL(SetItemIndex)
		LUA_METHOD_DECL(GetCount)
		LUA_METHOD_DECL(Add)
		LUA_METHOD_DECL(AddAt)
		LUA_METHOD_DECL(Remove)
		LUA_METHOD_DECL(RemoveAt)
		LUA_METHOD_DECL(RemoveAll)

		LUA_METHOD_DECL(GetInset)
		LUA_METHOD_DECL(SetInset)
		LUA_METHOD_DECL(GetChildPadding)
		LUA_METHOD_DECL(SetChildPadding)
		LUA_METHOD_DECL(IsAutoDestroy)
		LUA_METHOD_DECL(SetAutoDestroy)
		LUA_METHOD_DECL(IsDelayedDestroy)
		LUA_METHOD_DECL(SetDelayedDestroy)
		LUA_METHOD_DECL(IsMouseChildEnabled)
		LUA_METHOD_DECL(SetMouseChildEnabled)
		LUA_METHOD_DECL(FindSelectable)

		LUA_METHOD_DECL(SetSubControlText)
		LUA_METHOD_DECL(SetSubControlFixedHeight)
		LUA_METHOD_DECL(SetSubControlFixedWdith)
		LUA_METHOD_DECL(SetSubControlUserData)
		LUA_METHOD_DECL(GetSubControlText)
		LUA_METHOD_DECL(GetSubControlFixedHeight)
		LUA_METHOD_DECL(GetSubControlFixedWdith)
		LUA_METHOD_DECL(GetSubControlUserData)
		LUA_METHOD_DECL(FindSubControl)

		LUA_METHOD_DECL(GetScrollPos)
		LUA_METHOD_DECL(GetScrollRange)
		LUA_METHOD_DECL(SetScrollPos)
		LUA_METHOD_DECL(LineUp)
		LUA_METHOD_DECL(LineDown)
		LUA_METHOD_DECL(PageUp)
		LUA_METHOD_DECL(PageDown)
		LUA_METHOD_DECL(HomeUp)
		LUA_METHOD_DECL(EndDown)
		LUA_METHOD_DECL(LineLeft)
		LUA_METHOD_DECL(LineRight)
		LUA_METHOD_DECL(PageLeft)
		LUA_METHOD_DECL(PageRight)
		LUA_METHOD_DECL(HomeLeft)
		LUA_METHOD_DECL(EndRight)
		LUA_METHOD_DECL(EnableScrollBar)
		LUA_METHOD_DECL(GetVerticalScrollBar)
		LUA_METHOD_DECL(GetHorizontalScrollBar)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CContainerUI_h