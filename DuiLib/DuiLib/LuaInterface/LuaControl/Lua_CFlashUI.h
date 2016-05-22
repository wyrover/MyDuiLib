#ifndef _Lua_CFlashUI_h
#define _Lua_CFlashUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CFlashUI, FlashUI, CFlashUI, ActiveXUI, CActiveXUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetFlashEventHandler)
		LUA_METHOD_DECL(DoCreateControl)
		LUA_METHOD_DECL(get_ShockwaveFlash)
		LUA_METHOD_DECL(SetFlashUrl)
		LUA_METHOD_DECL(GetFlashUrl)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CFlashUI_h