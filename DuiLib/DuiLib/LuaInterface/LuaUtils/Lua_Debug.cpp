#include "LuaEntry.h"
#include REQUIRE_H(Debug)

namespace DuiLib
{
	LUA_METHOD_IMPL(Debug, LuaAssert)
	{
		return 0;
	}

	LUA_CLASS_REG_IMPL(Debug)
	{
		
	}
}
