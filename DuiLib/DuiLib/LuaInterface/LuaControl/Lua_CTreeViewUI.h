#ifndef _Lua_CTreeViewUI_h
#define _Lua_CTreeViewUI_h
#pragma once


namespace DuiLib
{
	LUA_CLASS(CTreeNodeUI)
	{
	public:
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetVisibleTag)
		LUA_METHOD_DECL(GetVisibleTag)
		LUA_METHOD_DECL(SetItemText)
		LUA_METHOD_DECL(GetItemText)
		LUA_METHOD_DECL(CheckBoxSelected)
		LUA_METHOD_DECL(IsCheckBoxSelected)
		LUA_METHOD_DECL(IsHasChild)
		LUA_METHOD_DECL(GetTreeLevel)
		LUA_METHOD_DECL(AddChildNode)
		LUA_METHOD_DECL(SetParentNode)
		LUA_METHOD_DECL(GetParentNode)
		LUA_METHOD_DECL(GetCountChild)
		LUA_METHOD_DECL(SetTreeView)
		LUA_METHOD_DECL(GetTreeView)
		LUA_METHOD_DECL(GetChildNode)
		LUA_METHOD_DECL(SetVisibleFolderBtn)
		LUA_METHOD_DECL(GetVisibleFolderBtn)
		LUA_METHOD_DECL(SetVisibleCheckBtn)
		LUA_METHOD_DECL(GetVisibleCheckBtn)
		LUA_METHOD_DECL(SetItemTextColor)
		LUA_METHOD_DECL(GetItemTextColor)
		LUA_METHOD_DECL(SetItemHotTextColor)
		LUA_METHOD_DECL(GetItemHotTextColor)
		LUA_METHOD_DECL(SetSelItemTextColor)
		LUA_METHOD_DECL(GetSelItemTextColor)
		LUA_METHOD_DECL(SetSelItemHotTextColor)
		LUA_METHOD_DECL(GetSelItemHotTextColor)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CTreeViewUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(AddAt2)
		LUA_METHOD_DECL(SetItemCheckBox)
		LUA_METHOD_DECL(SetItemExpand)
		LUA_METHOD_DECL(SetVisibleFolderBtn)
		LUA_METHOD_DECL(GetVisibleFolderBtn)
		LUA_METHOD_DECL(SetVisibleCheckBtn)
		LUA_METHOD_DECL(GetVisibleCheckBtn)
		LUA_METHOD_DECL(SetItemMinWidth)
		LUA_METHOD_DECL(GetItemMinWidth)
		LUA_METHOD_DECL(SetItemHotTextColor)
		LUA_METHOD_DECL(SetSelItemTextColor)
		LUA_METHOD_DECL(SetSelItemHotTextColor)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CTreeViewUI_h