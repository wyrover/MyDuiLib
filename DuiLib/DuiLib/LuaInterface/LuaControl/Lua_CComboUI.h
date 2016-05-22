#ifndef _Lua_CComboUI_h
#define _Lua_CComboUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CComboUI, ComboUI, CComboUI, ContainerUI, CContainerUI)
	{
	public:
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(New)
		//
		LUA_METHOD_DECL(GetDropBoxAttributeList)
		LUA_METHOD_DECL(SetDropBoxAttributeList)
		LUA_METHOD_DECL(GetDropBoxSize)
		LUA_METHOD_DECL(SetDropBoxSize)
		LUA_METHOD_DECL(GetCurSel)
		LUA_METHOD_DECL(SelectItem)
		LUA_METHOD_DECL(SetMultiSelect)
		LUA_METHOD_DECL(IsMultiSelected)
		LUA_METHOD_DECL(GetTextPadding)
		LUA_METHOD_DECL(SetTextPadding)
		LUA_METHOD_DECL(GetNormalImage)
		LUA_METHOD_DECL(SetNormalImage)
		LUA_METHOD_DECL(GetHotImage)
		LUA_METHOD_DECL(SetHotImage)
		LUA_METHOD_DECL(GetPushedImage)
		LUA_METHOD_DECL(SetPushedImage)
		LUA_METHOD_DECL(GetFocusedImage)
		LUA_METHOD_DECL(SetFocusedImage)
		LUA_METHOD_DECL(GetDisabledImage)
		LUA_METHOD_DECL(SetDisabledImage)
		LUA_METHOD_DECL(GetListInfo)
		LUA_METHOD_DECL(SetItemFont)
		LUA_METHOD_DECL(SetItemTextStyle)
		LUA_METHOD_DECL(GetItemTextPadding)
		LUA_METHOD_DECL(SetItemTextPadding)
		LUA_METHOD_DECL(GetItemTextColor)
		LUA_METHOD_DECL(SetItemTextColor)
		LUA_METHOD_DECL(GetItemBkColor)
		LUA_METHOD_DECL(SetItemBkColor)
		LUA_METHOD_DECL(GetItemBkImage)
		LUA_METHOD_DECL(SetItemBkImage)
		LUA_METHOD_DECL(IsAlternateBk)
		LUA_METHOD_DECL(SetAlternateBk)
		LUA_METHOD_DECL(GetSelectedItemTextColor)
		LUA_METHOD_DECL(SetSelectedItemTextColor)
		LUA_METHOD_DECL(GetSelectedItemBkColor)
		LUA_METHOD_DECL(SetSelectedItemBkColor)
		LUA_METHOD_DECL(GetSelectedItemImage)
		LUA_METHOD_DECL(SetSelectedItemImage)
		LUA_METHOD_DECL(GetHotItemTextColor)
		LUA_METHOD_DECL(SetHotItemTextColor)
		LUA_METHOD_DECL(GetHotItemBkColor)
		LUA_METHOD_DECL(SetHotItemBkColor)
		LUA_METHOD_DECL(GetHotItemImage)
		LUA_METHOD_DECL(SetHotItemImage)
		LUA_METHOD_DECL(GetDisabledItemTextColor)
		LUA_METHOD_DECL(SetDisabledItemTextColor)
		LUA_METHOD_DECL(GetDisabledItemBkColor)
		LUA_METHOD_DECL(SetDisabledItemBkColor)
		LUA_METHOD_DECL(GetDisabledItemImage)
		LUA_METHOD_DECL(SetDisabledItemImage)
		LUA_METHOD_DECL(GetItemLineColor)
		LUA_METHOD_DECL(SetItemLineColor)
		LUA_METHOD_DECL(IsItemShowHtml)
		LUA_METHOD_DECL(SetItemShowHtml)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CComboUI_h