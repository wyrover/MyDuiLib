#include "LuaEntry.h"

#include REQUIRE_H(CGifAnimUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CGifAnimUI, New)
	{
		CGifAnimUI  *ctrl = new CGifAnimUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CGifAnimUI, GetClassName)
	{
		CDuiString pstrText = CGifAnimUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_METHOD_IMPL(CGifAnimUI,SetGifImage)
	{
		try
		{
			CGifAnimUI* self;
			self = static_cast<CGifAnimUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetGifImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCGifAnimUI::SetGifImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CGifAnimUI,GetGifImage)
	{
		try
		{
			CGifAnimUI* self;
			self = static_cast<CGifAnimUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetGifImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCGifAnimUI::GetGifImage"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CGifAnimUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "GifAnimUI");

		luaL_newmetatable(l, "CGifAnimUI");
		luaL_getmetatable(l, "CLabelUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "GetGifImage", GetGifImage },
			{ "SetGifImage", SetGifImage },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}