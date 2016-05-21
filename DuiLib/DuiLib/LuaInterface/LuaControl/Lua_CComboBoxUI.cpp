#include "LuaEntry.h"

#include REQUIRE_H(CComboBoxUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CComboBoxUI, New)
	{
		CComboBoxUI  *ctrl = new CComboBoxUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CComboBoxUI, GetClassName)
	{
		CDuiString pstrText = CComboBoxUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}


	LUA_METHOD_IMPL(CComboBoxUI,GetArrowImage)
	{
		try
		{
			CComboBoxUI* self;
			self = static_cast<CComboBoxUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetArrowImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCComboBoxUI::GetArrowImage"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CComboBoxUI,SetArrowImage)
	{
		try
		{
			CComboBoxUI* self;
			self = static_cast<CComboBoxUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			self->SetArrowImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCComboBoxUI::SetArrowImage"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CComboBoxUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "ComboBoxUI");

		luaL_newmetatable(l, "CComboBoxUI");
		luaL_getmetatable(l, "CComboUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "SetArrowImage", SetArrowImage },
			{ "GetArrowImage", GetArrowImage },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}