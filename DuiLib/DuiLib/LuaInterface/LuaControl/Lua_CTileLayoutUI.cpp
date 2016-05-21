#include "LuaEntry.h"

#include REQUIRE_H(CTileLayoutUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CTileLayoutUI, New)
	{
		CTileLayoutUI  *ctrl = new CTileLayoutUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CTileLayoutUI, GetClassName)
	{
		CDuiString pstrText = CTileLayoutUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}


	LUA_METHOD_IMPL(CTileLayoutUI,GetItemSize)
	{
		try
		{
			CTileLayoutUI* self;
			self = static_cast<CTileLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			SIZE sz = self->GetItemSize();
			LuaStatic::WriteSize2Lua(l, sz);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCTileLayoutUI::GetItemSize"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CTileLayoutUI,SetItemSize)
	{
		try
		{
			CTileLayoutUI* self;
			self = static_cast<CTileLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			SIZE sz = LuaStatic::ReadSizeFromLua(l, 2);
			self->SetItemSize(sz);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCTileLayoutUI::SetItemSize"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CTileLayoutUI,GetColumns)
	{
		try
		{
			CTileLayoutUI* self;
			self = static_cast<CTileLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			int w = self->GetColumns();
			lua_pushinteger(l,w);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCTileLayoutUI::GetColumns"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CTileLayoutUI,SetColumns)
	{
		try
		{
			CTileLayoutUI* self;
			self = static_cast<CTileLayoutUI*>(LuaStatic::CheckUserData(l, 1));
			int w = (int)lua_tointeger(l, 2);
			self->SetColumns(w);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCTileLayoutUI::SetColumns"));
			return 0;
		}
	}
	

	LUA_CLASS_REG_IMPL(CTileLayoutUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "TileLayoutUI");

		luaL_newmetatable(l, "CTileLayoutUI");
		luaL_getmetatable(l, "CContainerUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "GetItemSize", GetItemSize },
			{ "SetItemSize", SetItemSize },
			{ "GetColumns", GetColumns },
			{ "SetColumns", SetColumns },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}