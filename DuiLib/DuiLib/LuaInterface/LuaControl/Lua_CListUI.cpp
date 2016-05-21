#include "LuaEntry.h"

#include REQUIRE_H(CListUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CListUI, New)
	{
		CListUI  *ctrl = new CListUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CListUI, GetClassName)
	{
		CDuiString pstrText = CListUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_METHOD_IMPL(CListUI, GetScrollSelect)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->GetScrollSelect() ? 1: 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetScrollSelect"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetScrollSelect)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetScrollSelect(lua_toboolean(l,2) != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetScrollSelect"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetCurSel)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetCurSel());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetCurSel"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SelectItem)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			int iIndex = lua_tointeger(l,2);
			bool bTakeFocus = false;
			bool bSelected = true;
			if(!lua_isnone(l,3))
				bTakeFocus = lua_toboolean(l,3) != 0 ;
			if(!lua_isnone(l,4))
				bSelected = lua_toboolean(l,4) != 0;
			self->SelectItem(iIndex,bTakeFocus,bSelected);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SelectItem"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetSelCount)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetSelCount());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetSelCount"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetHeader)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			CListHeaderUI* pHeader = self->GetHeader();
			if (pHeader)
				LuaStatic::AddObject2Lua(l, pHeader, METATABLE_NAME(pHeader));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetHeader"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetList)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			CContainerUI* pList = self->GetList();
			if (pList)
				LuaStatic::AddObject2Lua(l, pList, METATABLE_NAME(pList));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetList"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetListInfo)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			TListInfoUI* pInfo = self->GetListInfo();
			if (pInfo)
				;//LuaStatic::AddObject2Lua(l, pInfo, METATABLE_NAME(pList));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetListInfo"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, EnsureVisible)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			self->EnsureVisible(lua_tointeger(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::EnsureVisible"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, Scroll)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			int dx = lua_tointeger(l,2);
			int dy = lua_tointeger(l,3);
			self->Scroll(dx,dy);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::EnsureVisible"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetItemFont)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetItemFont(lua_tointeger(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetItemFont"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetItemTextStyle)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetItemTextStyle(lua_tointeger(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetItemTextStyle"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetItemTextPadding)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			RECT rt = LuaStatic::ReadRectFromLua(l, 2);
			self->SetItemTextPadding(rt);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetItemTextPadding"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetItemTextColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCor = LuaStatic::ReadRGBAFromLua(l, 2);
			self->SetItemTextColor(dwCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetItemTextColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetItemBkColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCor = LuaStatic::ReadRGBAFromLua(l, 2);
			self->SetItemBkColor(dwCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetItemBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetItemBkImage)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetItemBkImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetItemBkImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetAlternateBk)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetAlternateBk(lua_toboolean(l,2) != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetItemBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetSelectedItemTextColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCor = LuaStatic::ReadRGBAFromLua(l, 2);
			self->SetSelectedItemTextColor(dwCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetSelectedItemTextColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetSelectedItemBkColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCor = LuaStatic::ReadRGBAFromLua(l, 2);
			self->SetSelectedItemBkColor(dwCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetSelectedItemBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetSelectedItemImage)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetSelectedItemImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetSelectedItemImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetHotItemTextColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCor = LuaStatic::ReadRGBAFromLua(l, 2);
			self->SetHotItemTextColor(dwCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetHotItemTextColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetHotItemBkColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCor = LuaStatic::ReadRGBAFromLua(l, 2);
			self->SetHotItemBkColor(dwCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetHotItemBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetHotItemImage)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetHotItemImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetHotItemImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetDisabledItemTextColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCor = LuaStatic::ReadRGBAFromLua(l, 2);
			self->SetDisabledItemTextColor(dwCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetDisabledItemTextColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetDisabledItemBkColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCor = LuaStatic::ReadRGBAFromLua(l, 2);
			self->SetDisabledItemBkColor(dwCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetDisabledItemBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetDisabledItemImage)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetDisabledItemImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetDisabledItemImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetItemLineColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCor = LuaStatic::ReadRGBAFromLua(l, 2);
			self->SetItemLineColor(dwCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetItemLineColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, IsItemShowHtml)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsItemShowHtml() ? 1: 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::IsItemShowHtml"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetItemShowHtml)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetItemShowHtml(lua_toboolean(l,2) != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetItemShowHtml"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetItemTextPadding)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRect2Lua(l, self->GetItemTextPadding());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetItemTextPadding"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetItemTextColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l, self->GetItemTextColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetItemTextColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetItemBkColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l, self->GetItemBkColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetItemBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetItemBkImage)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetItemBkImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetItemBkImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, IsAlternateBk)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			lua_op_t<bool>::push_stack(l, self->IsAlternateBk());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::IsAlternateBk"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetSelectedItemTextColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l, self->GetSelectedItemTextColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetSelectedItemTextColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetSelectedItemBkColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l, self->GetSelectedItemBkColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetSelectedItemBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetSelectedItemImage)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetSelectedItemImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetSelectedItemImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetHotItemTextColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l, self->GetHotItemTextColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetHotItemTextColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetHotItemBkColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l, self->GetHotItemBkColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetHotItemBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetHotItemImage)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetHotItemImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetHotItemImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetDisabledItemTextColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l, self->GetDisabledItemTextColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetDisabledItemTextColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetDisabledItemBkColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l, self->GetDisabledItemBkColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetDisabledItemBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetDisabledItemImage)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetDisabledItemImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetDisabledItemImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetItemLineColor)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l, self->GetItemLineColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetItemLineColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetMultiSelect)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetMultiSelect(lua_toboolean(l,2) != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetMultiSelect"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, IsMultiSelected)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsMultiSelected() ? 1: 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::IsMultiSelected"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetMultiExpanding)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetMultiExpanding(lua_toboolean(l,2) != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetMultiExpanding"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetExpandedItem)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetExpandedItem());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetExpandedItem"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, ExpandItem)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			int iIndex = lua_toboolean(l,2) != 0;
			bool bExpand = true;
			if(!lua_isnone(l,3))
				bExpand = lua_toboolean(l,3) != 0;
			self->ExpandItem(iIndex,bExpand);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::ExpandItem"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, GetTextCallback)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			//
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::GetExpandedItem"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListUI, SetTextCallback)
	{
		try
		{
			CListUI* self;
			self = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
			IListCallbackUI* pCallback = static_cast<IListCallbackUI*>(LuaStatic::CheckUserData(l, 2));
			self->SetTextCallback(pCallback);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListUI::SetTextCallback"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CListUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "ListUI");

		luaL_newmetatable(l, "CListUI");
		luaL_getmetatable(l, "CVerticalLayoutUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");

		static LuaReg MethodFuncs[] =
		{
			{ "GetScrollSelect", GetScrollSelect },
			{ "SetTextCallback", SetTextCallback },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
};

namespace DuiLib
{
	LUA_METHOD_IMPL(CListBodyUI, New)
	{
		CListUI* pOwner = static_cast<CListUI*>(LuaStatic::CheckUserData(l, 1));
		CListBodyUI  *self = new CListBodyUI(pOwner);
		LuaStatic::AddObject2Lua(l, self, METATABLE_NAME(self));
		return 1;
	}

	LUA_METHOD_IMPL(CListBodyUI, GetClassName)
	{
		CDuiString pstrText = CListBodyUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_CLASS_REG_IMPL(CListBodyUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "ListBodyUI");

		luaL_newmetatable(l, "CListBodyUI");
		luaL_getmetatable(l, "CVerticalLayoutUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
				
		lua_pop(l,1);
	}
};

namespace DuiLib
{
	LUA_METHOD_IMPL(CListHeaderUI, New)
	{
		CListHeaderUI  *self = new CListHeaderUI();
		LuaStatic::AddObject2Lua(l, self, METATABLE_NAME(self));
		return 1;
	}

	LUA_METHOD_IMPL(CListHeaderUI, GetClassName)
	{
		CDuiString pstrText = CListHeaderUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_CLASS_REG_IMPL(CListHeaderUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "ListHeaderUI");

		luaL_newmetatable(l, "CListHeaderUI");
		luaL_getmetatable(l, "CHorizontalLayoutUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
				
		lua_pop(l,1);
	}
};

namespace DuiLib
{
	LUA_METHOD_IMPL(CListHeaderItemUI, New)
	{
		CListHeaderItemUI  *self = new CListHeaderItemUI();
		LuaStatic::AddObject2Lua(l, self, METATABLE_NAME(self));
		return 1;
	}

	LUA_METHOD_IMPL(CListHeaderItemUI, GetClassName)
	{
		CDuiString pstrText = CListHeaderItemUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_METHOD_IMPL(CListHeaderItemUI, IsDragable)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsDragable() ? 1: 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::IsDragable"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetDragable)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetDragable(lua_toboolean(l,2) != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetDragable"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, GetSepWidth)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetSepWidth());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::GetSepWidth"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetSepWidth)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			int iWidth = lua_tointeger(l,2);
			self->SetSepWidth(iWidth);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetSepWidth"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, GetTextStyle)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetTextStyle());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::GetTextStyle"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetTextStyle)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			int iWidth = lua_tointeger(l,2);
			self->SetTextStyle(iWidth);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetTextStyle"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, GetTextColor)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l, self->GetTextColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::GetTextColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetTextColor)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			DWORD dwCor = LuaStatic::ReadRGBAFromLua(l, 2);
			self->SetTextColor(dwCor);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetTextColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetTextPadding)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			RECT rt = LuaStatic::ReadRectFromLua(l, 2);
			self->SetTextPadding(rt);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetTextPadding"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, GetTextPadding)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRect2Lua(l, self->GetTextPadding());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::GetTextPadding"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetFont)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			int iWidth = lua_tointeger(l,2);
			self->SetFont(iWidth);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetFont"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, IsShowHtml)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsShowHtml() ? 1: 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::IsShowHtml"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetShowHtml)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetShowHtml(lua_toboolean(l,2) != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetShowHtml"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, GetNormalImage)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetNormalImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::GetNormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetNormalImage)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetNormalImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetNormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, GetHotImage)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetHotImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::GetHotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetHotImage)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetHotImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetHotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, GetPushedImage)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetPushedImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::GetPushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetPushedImage)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetPushedImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetPushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, GetFocusedImage)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetFocusedImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::GetFocusedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetFocusedImage)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetFocusedImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetFocusedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, GetSepImage)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetSepImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::GetSepImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, SetSepImage)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetSepImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetSepImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListHeaderItemUI, GetThumbRect)
	{
		try
		{
			CListHeaderItemUI* self;
			self = static_cast<CListHeaderItemUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRect2Lua(l, self->GetThumbRect());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::GetThumbRect"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CListHeaderItemUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "ListHeaderItemUI");

		luaL_newmetatable(l, "CListHeaderItemUI");
		luaL_getmetatable(l, "CControlUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "IsDragable", IsDragable },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));		
		lua_pop(l,1);
	}
};

namespace DuiLib
{
	LUA_METHOD_IMPL(CListElementUI, New)
	{
		CListElementUI  *self = new CListElementUI();
		LuaStatic::AddObject2Lua(l, self, METATABLE_NAME(self));
		return 1;
	}

	LUA_METHOD_IMPL(CListElementUI, GetClassName)
	{
		CDuiString pstrText = CListElementUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_METHOD_IMPL(CListElementUI, GetIndex)
	{
		try
		{
			CListElementUI* self;
			self = static_cast<CListElementUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetIndex());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListElementUI::GetIndex"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListElementUI, SetIndex)
	{
		try
		{
			CListElementUI* self;
			self = static_cast<CListElementUI*>(LuaStatic::CheckUserData(l, 1));
			int iWidth = lua_tointeger(l,2);
			self->SetIndex(iWidth);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListHeaderItemUI::SetIndex"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListElementUI, GetOwner)
	{
		try
		{
			CListElementUI* self;
			self = static_cast<CListElementUI*>(LuaStatic::CheckUserData(l, 1));
			IListOwnerUI* pOwner;
			pOwner = static_cast<IListOwnerUI*>(self->GetOwner());

			if (pOwner)
			{
				CDuiString sName = pOwner->GetClass();
				LuaStatic::AddObject2Lua(l, pOwner, sName.GetAString());
			}
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListElementUI::GetOwner"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListElementUI, SetOwner)
	{
		try
		{
			CListElementUI* self;
			self = static_cast<CListElementUI*>(LuaStatic::CheckUserData(l, 1));

			CControlUI* pOwner;
			pOwner = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));

			self->SetOwner(pOwner);
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListElementUI::SetOwner"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListElementUI, IsSelected)
	{
		try
		{
			CListElementUI* self;
			self = static_cast<CListElementUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsSelected() ? 1: 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListElementUI::IsSelected"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListElementUI, Select)
	{
		try
		{
			CListElementUI* self;
			self = static_cast<CListElementUI*>(LuaStatic::CheckUserData(l, 1));
			bool bSelected = true;
			if(!lua_isnone(l,2))
				bSelected = lua_toboolean(l,2) != 0;
			self->Select(bSelected);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListElementUI::Select"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListElementUI, IsExpanded)
	{
		try
		{
			CListElementUI* self;
			self = static_cast<CListElementUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsExpanded() ? 1: 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListElementUI::IsExpanded"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListElementUI, Expand)
	{
		try
		{
			CListElementUI* self;
			self = static_cast<CListElementUI*>(LuaStatic::CheckUserData(l, 1));
			bool bExpand = true;
			if(!lua_isnone(l,2))
				bExpand = lua_toboolean(l,2) != 0;
			self->Expand(bExpand);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListElementUI::Expand"));
			return 0;
		}
	}
	LUA_CLASS_REG_IMPL(CListElementUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "ListElementUI");

		luaL_newmetatable(l, "CListElementUI");
		luaL_getmetatable(l, "CControlUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "GetIndex", GetIndex },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));		
		lua_pop(l,1);
	}
};

namespace DuiLib
{
	LUA_METHOD_IMPL(CListLabelElementUI, New)
	{
		CListLabelElementUI  *self = new CListLabelElementUI();
		LuaStatic::AddObject2Lua(l, self, METATABLE_NAME(self));
		return 1;
	}

	LUA_METHOD_IMPL(CListLabelElementUI, GetClassName)
	{
		CDuiString pstrText = CListLabelElementUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	
	LUA_CLASS_REG_IMPL(CListLabelElementUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "ListLabelElementUI");

		luaL_newmetatable(l, "CListLabelElementUI");
		luaL_getmetatable(l, "CListElementUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");

		lua_pop(l,1);
	}
};

namespace DuiLib
{
	LUA_METHOD_IMPL(CListTextElementUI, New)
	{
		CListTextElementUI  *self = new CListTextElementUI();
		LuaStatic::AddObject2Lua(l, self, METATABLE_NAME(self));
		return 1;
	}

	LUA_METHOD_IMPL(CListTextElementUI, GetClassName)
	{
		CDuiString pstrText = CListTextElementUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_METHOD_IMPL(CListTextElementUI, GetTextAt)
	{
		try
		{
			CListTextElementUI* self;
			self = static_cast<CListTextElementUI*>(LuaStatic::CheckUserData(l, 1));
			int iIndex = lua_tointeger(l,2);
			CDuiString pstrText = self->GetText(iIndex);

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListTextElementUI::GetTextAt"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListTextElementUI, SetTextAt)
	{
		try
		{
			CListTextElementUI* self;
			self = static_cast<CListTextElementUI*>(LuaStatic::CheckUserData(l, 1));
			int iIndex = lua_tointeger(l,2);
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText);

			self->SetText(iIndex, pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListTextElementUI::SetTextAt"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListTextElementUI, SetOwner)
	{
		try
		{
			CListTextElementUI* self;
			self = static_cast<CListTextElementUI*>(LuaStatic::CheckUserData(l, 1));

			CControlUI* pOwner;
			pOwner = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));

			self->SetOwner(pOwner);
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListTextElementUI::SetOwner"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListTextElementUI, GetLinkContent)
	{
		try
		{
			CListTextElementUI* self;
			self = static_cast<CListTextElementUI*>(LuaStatic::CheckUserData(l, 1));
			int iIndex = lua_tointeger(l,2);
			CDuiString* pStr = self->GetLinkContent(iIndex);
			if (pStr)
				lua_pushstring(l, pStr->GetAString().c_str());
			else
				lua_pushnil(l);

			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListTextElementUI::GetLinkContent"));
			return 0;
		}
	}
	
	LUA_CLASS_REG_IMPL(CListTextElementUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "ListTextElementUI");

		luaL_newmetatable(l, "CListTextElementUI");
		luaL_getmetatable(l, "CListLabelElementUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "GetTextAt", GetTextAt },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));		
		lua_pop(l,1);
	}
};

namespace DuiLib
{
	LUA_METHOD_IMPL(CListContainerElementUI, New)
	{
		CListContainerElementUI  *ctrl = new CListContainerElementUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CListContainerElementUI, GetClassName)
	{
		CDuiString pstrText = CListContainerElementUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}
	LUA_METHOD_IMPL(CListContainerElementUI, GetOwner)
	{
		try
		{
			CListContainerElementUI* self;
			self = static_cast<CListContainerElementUI*>(LuaStatic::CheckUserData(l, 1));
			IListOwnerUI* pOwner;
			pOwner = static_cast<IListOwnerUI*>(self->GetOwner());

			if (pOwner)
			{
				CDuiString sName = pOwner->GetClass();
				LuaStatic::AddObject2Lua(l, pOwner, sName.GetAString());
			}
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListContainerElementUI::GetOwner"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListContainerElementUI, SetOwner)
	{
		try
		{
			CListContainerElementUI* self;
			self = static_cast<CListContainerElementUI*>(LuaStatic::CheckUserData(l, 1));

			CControlUI* pOwner;
			pOwner = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));

			self->SetOwner(pOwner);
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListContainerElementUI::SetOwner"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListContainerElementUI, IsSelected)
	{
		try
		{
			CListContainerElementUI* self;
			self = static_cast<CListContainerElementUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsSelected() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListContainerElementUI::IsSelected"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListContainerElementUI, Select)
	{
		try
		{
			CListContainerElementUI* self;
			self = static_cast<CListContainerElementUI*>(LuaStatic::CheckUserData(l, 1));

			bool bSelect = true;
			if(!lua_isnone(l,2))
				bSelect = lua_toboolean(l,2) != 0;

			self->Select(bSelect);
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListContainerElementUI::Select"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListContainerElementUI, IsExpanded)
	{
		try
		{
			CListContainerElementUI* self;
			self = static_cast<CListContainerElementUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsExpanded() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCListContainerElementUI::IsExpanded"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CListContainerElementUI, Expand)
	{
		try
		{
			CListContainerElementUI* self;
			self = static_cast<CListContainerElementUI*>(LuaStatic::CheckUserData(l, 1));

			bool bExpand = true;
			if(!lua_isnone(l,2))
				bExpand = lua_toboolean(l,2) != 0;

			self->Expand(bExpand);
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCListContainerElementUI::Expand"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CListContainerElementUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "ListContainerElementUI");

		luaL_newmetatable(l, "CListContainerElementUI");
		luaL_getmetatable(l, "CContainerUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "GetOwner", GetOwner },
			{ "SetOwner", SetOwner },
			{ "IsSelected", IsSelected },
			{ "Select", Select },
			{ "IsExpanded", IsExpanded },
			{ "Expand", Expand },
		};

		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}
