#ifndef _Lua_CTileLayoutUI_h
#define _Lua_CTileLayoutUI_h
#pragma once


namespace DuiLib
{
	LUA_CLASS(CTileLayoutUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetItemSize)
		LUA_METHOD_DECL(SetItemSize)
		LUA_METHOD_DECL(GetColumns)
		LUA_METHOD_DECL(SetColumns)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CTileLayoutUI_h