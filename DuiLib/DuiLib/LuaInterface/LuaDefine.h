#ifndef Lua_Define_H
#define Lua_Define_H
#pragma once
#include <stdlib.h>
#include <string>
#include "lua.hpp"

namespace DuiLib
{
	typedef int(*LuaCFunction)(lua_State* l);

	struct LuaReg
	{
		const char* name;
		LuaCFunction func;
	};//end of LuaReg

	struct LuaArgs
	{
		const char* name;
		unsigned int v;
	};

#define  __string__(x)   #x

#define REQUIRE_H(name) \
	__string__(Lua_##name##.h)

	template<typename T>
	class LuaBase {
	public:
		static LuaReg methods[];
	};

#define LUA_CLASS(name, exportName, metaName, parentName, parentMeta) \
class NameWarpForLua_##name##_##exportName##_##metaName##_##parentName##_##parentMeta { \
	public: static const char* ExportName() { return #exportName; }  \
	public: static const char* MetaName() { return #metaName; }  \
	public: static const char* ParentExportName() { return #parentName; }  \
	public: static const char* ParentMetaName() { return #parentMeta; }  \
}; \
class Lua_##name : public NameWarpForLua_##name##_##exportName##_##metaName##_##parentName##_##parentMeta

#define LUA_METHOD_DECL(func) \
	static int func(lua_State* l);

#define LUA_METHOD_IMPL(name,func) \
	int Lua_##name::func(lua_State* l)

#define LUA_CLASS_REG_DECL() \
	static void Reg(lua_State* l);

#define LUA_CLASS_REG_IMPL(name) \
	void Lua_##name::Reg(lua_State* l)

#define LUA_CLASS_REG(name) \
	Lua_##name::Reg(l);
}


#endif//Lua_Define_H