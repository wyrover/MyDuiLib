#include "LuaEntry.h"

#include REQUIRE_H(CDateTimeUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CDateTimeUI, New)
	{
		CDateTimeUI  *ctrl = new CDateTimeUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CDateTimeUI, GetClassName)
	{
		CDuiString pstrText = CDateTimeUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}


	LUA_METHOD_IMPL(CDateTimeUI,IsReadOnly)
	{
		try
		{
			CDateTimeUI* self;
			self = static_cast<CDateTimeUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsReadOnly() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCDateTimeUI::IsReadOnly"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CDateTimeUI,SetReadOnly)
	{
		try
		{
			CDateTimeUI* self;
			self = static_cast<CDateTimeUI*>(LuaStatic::CheckUserData(l, 1));
			bool bReadOnly = lua_toboolean(l,2) != 0;
			self->SetReadOnly(bReadOnly);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCDateTimeUI::SetReadOnly"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CDateTimeUI,UpdateText)
	{
		try
		{
			CDateTimeUI* self;
			self = static_cast<CDateTimeUI*>(LuaStatic::CheckUserData(l, 1));
			self->UpdateText();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCDateTimeUI::UpdateText"));
			return 0;
		}
	}
	/*
	LUA_METHOD_IMPL(CDateTimeUI,GetTime)
	{
		try
		{
			CDateTimeUI* self;
			self = static_cast<CDateTimeUI*>(LuaStatic::CheckUserData(l, 1));
			SYSTEMTIME tm = self->GetTime();
			//
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCDateTimeUI::GetTime"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CDateTimeUI,SetTime)
	{
		try
		{
			CDateTimeUI* self;
			self = static_cast<CDateTimeUI*>(LuaStatic::CheckUserData(l, 1));
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCDateTimeUI::SetTime"));
			return 0;
		}
	}*/

	LUA_CLASS_REG_IMPL(CDateTimeUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "DateTimeUI");

		luaL_newmetatable(l, "CDateTimeUI");
		luaL_getmetatable(l, "CLabelUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "SetReadOnly", SetReadOnly },
			{ "IsReadOnly", IsReadOnly },
			{ "UpdateText", UpdateText},
			//{ "GetTime", GetTime},
			//{ "SetTime", SetTime},
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}