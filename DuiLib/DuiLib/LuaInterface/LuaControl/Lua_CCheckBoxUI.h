#ifndef _Lua_CCheckBoxUI_h
#define _Lua_CCheckBoxUI_h
#pragma once


namespace DuiLib
{
	LUA_CLASS(CCheckBoxUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetCheck)
		LUA_METHOD_DECL(GetCheck)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CCheckBoxUI_h