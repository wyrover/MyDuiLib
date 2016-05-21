#include "LuaEntry.h"

#include REQUIRE_H(CTextUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CTextUI, New)
	{
		CTextUI  *ctrl = new CTextUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CTextUI, GetClassName)
	{
		CDuiString pstrText = CTextUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}


	LUA_METHOD_IMPL(CTextUI,GetLinkContent)
	{
		try
		{
			CTextUI* self;
			self = static_cast<CTextUI*>(LuaStatic::CheckUserData(l, 1));
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
			DuiException(_T("LuaCTextUI::GetLinkContent"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CTextUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "TextUI");

		luaL_newmetatable(l, "CTextUI");
		luaL_getmetatable(l, "CLabelUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "GetLinkContent", GetLinkContent },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}