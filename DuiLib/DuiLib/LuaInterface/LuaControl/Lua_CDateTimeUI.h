#ifndef _Lua_CDateTimeUI_h
#define _Lua_CDateTimeUI_h
#pragma once


namespace DuiLib
{
	LUA_CLASS(CDateTimeUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		//LUA_METHOD_DECL(GetTime)
		//LUA_METHOD_DECL(SetTime)
		LUA_METHOD_DECL(SetReadOnly)
		LUA_METHOD_DECL(IsReadOnly)
		LUA_METHOD_DECL(UpdateText)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CDateTimeUI_h