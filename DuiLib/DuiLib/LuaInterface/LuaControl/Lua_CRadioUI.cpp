#include "LuaEntry.h"

#include REQUIRE_H(CRadioUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CRadioUI, New)
	{
		CRadioUI  *ctrl = new CRadioUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CRadioUI, GetClassName)
	{
		CDuiString pstrText = CRadioUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_CLASS_REG_IMPL(CRadioUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "RadioUI");

		luaL_newmetatable(l, "CRadioUI");
		luaL_getmetatable(l, "COptionUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
				
		lua_pop(l, 1);
	}
}