#ifndef _Lua_CRadioUI_h
#define _Lua_CRadioUI_h
#pragma once


namespace DuiLib
{
	LUA_CLASS(CRadioUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		
		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CRadioUI_h