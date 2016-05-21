#include "LuaEntry.h"

#include REQUIRE_H(CFadeButtonUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CFadeButtonUI, New)
	{
		CFadeButtonUI  *ctrl = new CFadeButtonUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CFadeButtonUI, GetClassName)
	{
		CDuiString pstrText = CFadeButtonUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_CLASS_REG_IMPL(CFadeButtonUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "FadeButtonUI");

		luaL_newmetatable(l, "CFadeButtonUI");
		luaL_getmetatable(l, "CButtonUI");
		lua_setmetatable(l, -2);

		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");

		lua_pop(l, 1);
	}
}