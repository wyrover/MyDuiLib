#ifndef _LuaCoreInclude_h
#define _LuaCoreInclude_h
#pragma once

#include REQUIRE_H(Struct)
#include REQUIRE_H(CDialogBuilder)
#include REQUIRE_H(CMarkup)
#include REQUIRE_H(CPaintManagerUI)
#include REQUIRE_H(CRender)
#include REQUIRE_H(CWindowWnd)

namespace DuiLib
{
	class RegDuiCore2Lua
	{
	public:
		static void RegModule(lua_State* l)
		{
			LUA_CLASS_REG(TNotifyUI)
			LUA_CLASS_REG(TFontInfo)
			LUA_CLASS_REG(TImageInfo)
			LUA_CLASS_REG(TEventUI)
			LUA_CLASS_REG(EventMarco)
			LUA_CLASS_REG(MsgArgs)
			LUA_CLASS_REG(DuiLib)
			LUA_CLASS_REG(CDialogBuilder)
			LUA_CLASS_REG(CMarkup)
			LUA_CLASS_REG(CMarkupNode)
			LUA_CLASS_REG(CPaintManagerUI)
			LUA_CLASS_REG(CRenderClip)
			LUA_CLASS_REG(CRenderEngine)
			LUA_CLASS_REG(CNotifyPump)
			LUA_CLASS_REG(CWindowWnd)
		}
	};
}

#endif//_LuaCoreInclude_h