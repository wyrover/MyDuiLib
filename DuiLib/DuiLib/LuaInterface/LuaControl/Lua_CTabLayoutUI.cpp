#include "LuaEntry.h"

#include REQUIRE_H(CTabLayoutUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CTabLayoutUI, New)
	{
		CTabLayoutUI  *ctrl = new CTabLayoutUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CTabLayoutUI, GetClassName)
	{
		CDuiString pstrText = CTabLayoutUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}


	LUA_METHOD_IMPL(CTabLayoutUI,GetCurSel)
	{
		try
		{
			CTabLayoutUI* self;
			self = static_cast<CTabLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			int w = self->GetCurSel();
			lua_pushinteger(l,w);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCTabLayoutUI::GetCurSel"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CTabLayoutUI,SelectItem)
	{
		try
		{
			CTabLayoutUI* self;
			self = static_cast<CTabLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			int w = (int)lua_tointeger(l, 2);
			self->SelectItem(w);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCTabLayoutUI::SelectItem"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CTabLayoutUI,SelectItem2)
	{
		try
		{
			CTabLayoutUI *self,*pControl;
			self = static_cast<CTabLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			pControl = static_cast<CTabLayoutUI*>(LuaStatic::CheckUserData(l, 2));
			self->SelectItem(pControl);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCTabLayoutUI::SelectItem2"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CTabLayoutUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "TabLayoutUI");

		luaL_newmetatable(l, "CTabLayoutUI");
		luaL_getmetatable(l, "CContainerUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "GetCurSel", GetCurSel },
			{ "SelectItem", SelectItem },
			{ "SelectItem2", SelectItem2 },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}