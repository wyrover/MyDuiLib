#include "LuaEntry.h"

#include REQUIRE_H(CFadeOptionUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CFadeOptionUI, New)
	{
		CFadeOptionUI  *ctrl = new CFadeOptionUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CFadeOptionUI, GetClassName)
	{
		CDuiString pstrText = CFadeOptionUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_CLASS_REG_IMPL(CFadeOptionUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "FadeOptionUI");

		luaL_newmetatable(l, "CFadeOptionUI");
		luaL_getmetatable(l, "COptionUI");
		lua_setmetatable(l, -2);

		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");

		lua_pop(l, 1);
	}
}