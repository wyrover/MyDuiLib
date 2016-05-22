#ifndef _Lua_CActiveXUI_h
#define _Lua_CActiveXUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CActiveXUI, ActiveXUI, CActiveXUI, ControlUI, CControlUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetHostWindow)
		LUA_METHOD_DECL(IsDelayCreate)
		LUA_METHOD_DECL(SetDelayCreate)
		LUA_METHOD_DECL(CreateControl)
		LUA_METHOD_DECL(CreateControl2)
		//LUA_METHOD_DECL(GetControl)
		//LUA_METHOD_DECL(GetClisd)
		LUA_METHOD_DECL(SetModuleName)
		LUA_METHOD_DECL(GetModuleName)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CActiveXUI_h