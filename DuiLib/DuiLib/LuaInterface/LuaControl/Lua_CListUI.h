#ifndef _Lua_CListUI_h
#define _Lua_CListUI_h
#pragma once


namespace DuiLib
{
	LUA_CLASS(CListUI)
	{
	public:
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetScrollSelect)
		LUA_METHOD_DECL(SetScrollSelect)
		LUA_METHOD_DECL(GetCurSel)
		LUA_METHOD_DECL(SelectItem)
		LUA_METHOD_DECL(GetSelCount)
		LUA_METHOD_DECL(GetHeader)
		LUA_METHOD_DECL(GetList)
		LUA_METHOD_DECL(GetListInfo)
		LUA_METHOD_DECL(EnsureVisible)
		LUA_METHOD_DECL(Scroll)
		LUA_METHOD_DECL(SetItemFont)
		LUA_METHOD_DECL(SetItemTextStyle)
		LUA_METHOD_DECL(SetItemTextPadding)
		LUA_METHOD_DECL(SetItemTextColor)
		LUA_METHOD_DECL(SetItemBkColor)
		LUA_METHOD_DECL(SetItemBkImage)
		LUA_METHOD_DECL(SetAlternateBk)
		LUA_METHOD_DECL(SetSelectedItemTextColor)
		LUA_METHOD_DECL(SetSelectedItemBkColor)
		LUA_METHOD_DECL(SetSelectedItemImage)
		LUA_METHOD_DECL(SetHotItemTextColor)
		LUA_METHOD_DECL(SetHotItemBkColor)
		LUA_METHOD_DECL(SetHotItemImage)
		LUA_METHOD_DECL(SetDisabledItemTextColor)
		LUA_METHOD_DECL(SetDisabledItemBkColor)
		LUA_METHOD_DECL(SetDisabledItemImage)
		LUA_METHOD_DECL(SetItemLineColor)
		LUA_METHOD_DECL(IsItemShowHtml)
		LUA_METHOD_DECL(SetItemShowHtml)
		LUA_METHOD_DECL(GetItemTextPadding)
		LUA_METHOD_DECL(GetItemTextColor)
		LUA_METHOD_DECL(GetItemBkColor)
		LUA_METHOD_DECL(GetItemBkImage)
		LUA_METHOD_DECL(IsAlternateBk)
		LUA_METHOD_DECL(GetSelectedItemTextColor)
		LUA_METHOD_DECL(GetSelectedItemBkColor)
		LUA_METHOD_DECL(GetSelectedItemImage)
		LUA_METHOD_DECL(GetHotItemTextColor)
		LUA_METHOD_DECL(GetHotItemBkColor)
		LUA_METHOD_DECL(GetHotItemImage)
		LUA_METHOD_DECL(GetDisabledItemTextColor)
		LUA_METHOD_DECL(GetDisabledItemBkColor)
		LUA_METHOD_DECL(GetDisabledItemImage)
		LUA_METHOD_DECL(GetItemLineColor)
		LUA_METHOD_DECL(SetMultiSelect)
		LUA_METHOD_DECL(IsMultiSelected)
		LUA_METHOD_DECL(SetMultiExpanding)
		LUA_METHOD_DECL(GetExpandedItem)
		LUA_METHOD_DECL(ExpandItem)
		LUA_METHOD_DECL(GetTextCallback)
		LUA_METHOD_DECL(SetTextCallback)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CListBodyUI)
	{
	public:
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CListHeaderUI)
	{
	public:
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		
		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CListHeaderItemUI)
	{
	public:
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(IsDragable)
		LUA_METHOD_DECL(SetDragable)
		LUA_METHOD_DECL(GetSepWidth)
		LUA_METHOD_DECL(SetSepWidth)
		LUA_METHOD_DECL(GetTextStyle)
		LUA_METHOD_DECL(SetTextStyle)
		LUA_METHOD_DECL(GetTextColor)
		LUA_METHOD_DECL(SetTextColor)
		LUA_METHOD_DECL(SetTextPadding)
		LUA_METHOD_DECL(GetTextPadding)
		LUA_METHOD_DECL(SetFont)
		LUA_METHOD_DECL(IsShowHtml)
		LUA_METHOD_DECL(SetShowHtml)
		LUA_METHOD_DECL(GetNormalImage)
		LUA_METHOD_DECL(SetNormalImage)
		LUA_METHOD_DECL(GetHotImage)
		LUA_METHOD_DECL(SetHotImage)
		LUA_METHOD_DECL(GetPushedImage)
		LUA_METHOD_DECL(SetPushedImage)
		LUA_METHOD_DECL(GetFocusedImage)
		LUA_METHOD_DECL(SetFocusedImage)
		LUA_METHOD_DECL(GetSepImage)
		LUA_METHOD_DECL(SetSepImage)
		LUA_METHOD_DECL(GetThumbRect)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CListElementUI)
	{
	public:
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetIndex)
		LUA_METHOD_DECL(SetIndex)
		LUA_METHOD_DECL(GetOwner)
		LUA_METHOD_DECL(SetOwner)
		LUA_METHOD_DECL(IsSelected)
		LUA_METHOD_DECL(Select)
		LUA_METHOD_DECL(IsExpanded)
		LUA_METHOD_DECL(Expand)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CListLabelElementUI)
	{
	public:
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CListTextElementUI)
	{
	public:
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetTextAt)
		LUA_METHOD_DECL(SetTextAt)
		LUA_METHOD_DECL(SetOwner)
		LUA_METHOD_DECL(GetLinkContent)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CListContainerElementUI)
	{
	public:		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetOwner)
		LUA_METHOD_DECL(SetOwner)
		LUA_METHOD_DECL(IsSelected)
		LUA_METHOD_DECL(Select)
		LUA_METHOD_DECL(IsExpanded)
		LUA_METHOD_DECL(Expand)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CListUI_h