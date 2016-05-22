#ifndef _Lua_CSliderUI_h
#define _Lua_CSliderUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CSliderUI, SliderUI, CSliderUI, ContainerUI, CContainerUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetChangeStep)
		LUA_METHOD_DECL(SetChangeStep)
		LUA_METHOD_DECL(SetThumbSize)
		LUA_METHOD_DECL(GetThumbRect)
		LUA_METHOD_DECL(GetThumbImage)
		LUA_METHOD_DECL(SetThumbImage)
		LUA_METHOD_DECL(GetThumbHotImage)
		LUA_METHOD_DECL(SetThumbHotImage)
		LUA_METHOD_DECL(GetThumbPushedImage)
		LUA_METHOD_DECL(SetThumbPushedImage)
		
		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CSliderUI_h