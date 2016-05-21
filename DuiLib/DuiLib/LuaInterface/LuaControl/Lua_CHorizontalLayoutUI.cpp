#include "LuaEntry.h"

#include REQUIRE_H(CHorizontalLayoutUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CHorizontalLayoutUI, New)
	{
		CHorizontalLayoutUI  *ctrl = new CHorizontalLayoutUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CHorizontalLayoutUI, GetClassName)
	{
		CDuiString pstrText = CHorizontalLayoutUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_METHOD_IMPL(CHorizontalLayoutUI,SetSepWidth)
	{
		try
		{
			CHorizontalLayoutUI* self;
			self = static_cast<CHorizontalLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			int w = (int)lua_tointeger(l, 2);
			self->SetSepWidth(w);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCHorizontalLayoutUI::SetSepWidth"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CHorizontalLayoutUI,GetSepWidth)
	{
		try
		{
			CHorizontalLayoutUI* self;
			self = static_cast<CHorizontalLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			int w = self->GetSepWidth();
			lua_pushinteger(l,w);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCHorizontalLayoutUI::GetSepWidth"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CHorizontalLayoutUI,SetSepImmMode)
	{
		try
		{
			CHorizontalLayoutUI* self;
			self = static_cast<CHorizontalLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			bool bAuto = lua_toboolean(l, 2) != 0;
			self->SetSepImmMode(bAuto);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCHorizontalLayoutUI::SetSepImmMode"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CHorizontalLayoutUI,IsSepImmMode)
	{
		try
		{
			CHorizontalLayoutUI* self;
			self = static_cast<CHorizontalLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			bool bRet = self->IsSepImmMode();
			lua_pushboolean(l, bRet ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCHorizontalLayoutUI::IsSepImmMode"));
			return 0;
		}
	}	

	LUA_METHOD_IMPL(CHorizontalLayoutUI,GetThumbRect)
	{
		try
		{
			CHorizontalLayoutUI* self;
			self = static_cast<CHorizontalLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			bool bUseNew = false;
			if (!lua_isnone(l,2))
				bUseNew = lua_toboolean(l,2) != 0;
			RECT rt = self->GetThumbRect(bUseNew);

			LuaStatic::WriteRect2Lua(l, rt);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCHorizontalLayoutUI::GetThumbRect"));
			return 0;
		}
	}


	LUA_CLASS_REG_IMPL(CHorizontalLayoutUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "HorizontalLayoutUI");

		luaL_newmetatable(l, "CHorizontalLayoutUI");
		luaL_getmetatable(l, "CContainerUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "SetSepWidth", SetSepWidth },
			{ "GetSepWidth", GetSepWidth },
			{ "SetSepImmMode", SetSepImmMode },
			{ "IsSepImmMode", IsSepImmMode },
			{ "GetThumbRect", GetThumbRect },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}