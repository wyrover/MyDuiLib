#ifndef _Lua_CProgressUI_h
#define _Lua_CProgressUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CProgressUI, ProgressUI, CProgressUI, LabelUI, CLabelUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(IsHorizontal)
		LUA_METHOD_DECL(SetHorizontal)
		LUA_METHOD_DECL(IsStretchForeImage)
		LUA_METHOD_DECL(SetStretchForeImage)
		LUA_METHOD_DECL(GetMinValue)
		LUA_METHOD_DECL(SetMinValue)
		LUA_METHOD_DECL(GetMaxValue)
		LUA_METHOD_DECL(SetMaxValue)
		LUA_METHOD_DECL(GetValue)
		LUA_METHOD_DECL(SetValue)
		LUA_METHOD_DECL(GetForeImage)
		LUA_METHOD_DECL(SetForeImage)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CProgressUI_h