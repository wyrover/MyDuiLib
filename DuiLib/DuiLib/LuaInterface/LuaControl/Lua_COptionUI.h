#ifndef _Lua_COptionUI_h
#define _Lua_COptionUI_h
#pragma once


namespace DuiLib
{
	LUA_CLASS(COptionUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetSelectedImage)
		LUA_METHOD_DECL(SetSelectedImage)
		LUA_METHOD_DECL(SetSelectedTextColor)
		LUA_METHOD_DECL(GetSelectedTextColor)
		LUA_METHOD_DECL(GetSelectedHotImage)
		LUA_METHOD_DECL(SetSelectedHotImage)
		LUA_METHOD_DECL(GetSelectedPushedImage)
		LUA_METHOD_DECL(SetSelectedPushedImage)
		LUA_METHOD_DECL(GetGroup)
		LUA_METHOD_DECL(SetGroup)
		LUA_METHOD_DECL(IsSelected)
		LUA_METHOD_DECL(Selected)
		LUA_METHOD_DECL(SetNotFilterSelected)
		LUA_METHOD_DECL(IsNotFilterSelected)
		LUA_METHOD_DECL(SetSelectedToolTip)
		LUA_METHOD_DECL(GetSelectedToolTip)
		LUA_METHOD_DECL(SetNormalTooltip)
		LUA_METHOD_DECL(GetNormalTooltip)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_COptionUI_h