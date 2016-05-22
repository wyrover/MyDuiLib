#ifndef _Lua_CAnimControlUI_h
#define _Lua_CAnimControlUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CAnimControlUI, AnimControlUI, CAnimControlUI, LabelUI, CLabelUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetImages)
		LUA_METHOD_DECL(GetImages)
		LUA_METHOD_DECL(SetElapse)
		LUA_METHOD_DECL(GetElapse)
		LUA_METHOD_DECL(SetTotalFrameCnt)
		LUA_METHOD_DECL(GetTotalFrameCnt)
		LUA_METHOD_DECL(Start)
		LUA_METHOD_DECL(Stop)
		LUA_METHOD_DECL(IsRunning)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CAnimControlUI_h