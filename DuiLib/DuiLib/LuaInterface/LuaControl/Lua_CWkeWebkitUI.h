#ifndef _Lua_CWkeWebkitUI_h
#define _Lua_CWkeWebkitUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CWkeWebkitUI, WkeWebkitUI, CWkeWebkitUI, ControlUI, CControlUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(WkeWebkit_Init)
		LUA_METHOD_DECL(WkeWebkit_Shutdown)
		LUA_METHOD_DECL(SetURL)
		LUA_METHOD_DECL(SetFile)
		LUA_METHOD_DECL(RunJS)
		LUA_METHOD_DECL(SetClientHandler)
		LUA_METHOD_DECL(GoBack)
		LUA_METHOD_DECL(GoForward)
		LUA_METHOD_DECL(GoHome)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CWkeWebkitUI_h