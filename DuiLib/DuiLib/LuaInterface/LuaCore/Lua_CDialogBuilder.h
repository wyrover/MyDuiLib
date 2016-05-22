#ifndef _LuaCDialogBuilder_H
#define _LuaCDialogBuilder_H
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CDialogBuilder, DialogBuilder, CDialogBuilder, DialogBuilder, CDialogBuilder)
	{
	public:
		LUA_METHOD_DECL(isnil)
		LUA_METHOD_DECL(_gc)
		LUA_METHOD_DECL(_eq)
		LUA_METHOD_DECL(_tostring)
		LUA_METHOD_DECL(Delete)
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetClass)
		LUA_METHOD_DECL(Create)
		LUA_METHOD_DECL(Create2)
		LUA_METHOD_DECL(GetMarkup)
		LUA_METHOD_DECL(GetLastErrorMessage)
		LUA_METHOD_DECL(GetLastErrorLocation)

		LUA_CLASS_REG_DECL()
	};
}

#endif//_LuaCDialogBuilder_H