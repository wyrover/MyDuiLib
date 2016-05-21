#ifndef _Lua_CTextUI_h
#define _Lua_CTextUI_h
#pragma once


namespace DuiLib
{
	LUA_CLASS(CTextUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetLinkContent)
		
		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CTextUI_h