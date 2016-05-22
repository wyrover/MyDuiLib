#include "LuaEntry.h"
#include REQUIRE_H(DuiEngine)

namespace DuiLib
{
	LUA_METHOD_IMPL(DuiEngine, ConsoleAndVsOutput)
	{
		DWORD dwMask = (DWORD)lua_tonumber(l,1);
		DuiEngine::ConsoleLogAndVsOutput(dwMask);
		return 0;
	}

	LUA_CLASS_REG_IMPL(DuiEngine)
	{
		lua_newtable(l);

		static LuaReg StaticFuncs[] =
		{
			{ "ConsoleAndVsOutput", ConsoleAndVsOutput },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));

		lua_setfield(l, -2, "DuiEngine");
	}

}