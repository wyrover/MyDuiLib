#ifndef _Lua_CWebBrowserUI_h
#define _Lua_CWebBrowserUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CWebBrowserUI, WebBrowserUI, CWebBrowserUI, ActiveXUI, CActiveXUI)
	{
	public:
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetHomePage)
		LUA_METHOD_DECL(GetHomePage)
		LUA_METHOD_DECL(SetAutoNavigation)
		LUA_METHOD_DECL(IsAutoNavigation)
		LUA_METHOD_DECL(Navigate2)
		LUA_METHOD_DECL(Refresh)
		LUA_METHOD_DECL(Refresh2)
		LUA_METHOD_DECL(GoBack)
		LUA_METHOD_DECL(NavigateHomePage)
		LUA_METHOD_DECL(NavigateUrl)
		LUA_METHOD_DECL(DoCreateControl)

		LUA_CLASS_REG_DECL()
	};
}

#endif//_Lua_CWebBrowserUI_h