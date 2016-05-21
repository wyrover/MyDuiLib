#include "LuaEntry.h"

#include REQUIRE_H(CAnimControlUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CAnimControlUI, New)
	{
		CAnimControlUI  *ctrl = new CAnimControlUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CAnimControlUI, GetClassName)
	{
		CDuiString pstrText = CAnimControlUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_METHOD_IMPL(CAnimControlUI, SetImages)
	{
		try
		{
			CAnimControlUI* self;
			self = static_cast<CAnimControlUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			self->SetImages(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCAnimControlUI::SetImages"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CAnimControlUI, GetImages)
	{
		try
		{
			CAnimControlUI* self;
			self = static_cast<CAnimControlUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetImages();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCAnimControlUI::GetImages"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CAnimControlUI, SetElapse)
	{
		try
		{
			CAnimControlUI* self;
			self = static_cast<CAnimControlUI*>(LuaStatic::CheckUserData(l, 1));
			int uEllapse = lua_tointeger(l, 2);
			self->SetElapse(uEllapse);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCAnimControlUI::SetElapse"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CAnimControlUI, GetElapse)
	{
		try
		{
			CAnimControlUI* self;
			self = static_cast<CAnimControlUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l, self->GetElapse());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCAnimControlUI::GetElapse"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CAnimControlUI, SetTotalFrameCnt)
	{
		try
		{
			CAnimControlUI* self;
			self = static_cast<CAnimControlUI*>(LuaStatic::CheckUserData(l, 1));
			int uEllapse = lua_tointeger(l, 2);
			self->SetTotalFrameCnt(uEllapse);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCAnimControlUI::SetTotalFrameCnt"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CAnimControlUI, GetTotalFrameCnt)
	{
		try
		{
			CAnimControlUI* self;
			self = static_cast<CAnimControlUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l, self->GetTotalFrameCnt());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCAnimControlUI::GetTotalFrameCnt"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CAnimControlUI, Start)
	{
		try
		{
			CAnimControlUI* self;
			self = static_cast<CAnimControlUI*>(LuaStatic::CheckUserData(l, 1));
			self->Start();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCAnimControlUI::Start"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CAnimControlUI, Stop)
	{
		try
		{
			CAnimControlUI* self;
			self = static_cast<CAnimControlUI*>(LuaStatic::CheckUserData(l, 1));
			self->Stop();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCAnimControlUI::Stop"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CAnimControlUI, IsRunning)
	{
		try
		{
			CAnimControlUI* self;
			self = static_cast<CAnimControlUI*>(LuaStatic::CheckUserData(l, 1));
			lua_op_t<bool>::push_stack(l, self->IsRunning());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCAnimControlUI::IsRunning"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CAnimControlUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "AnimControlUI");

		luaL_newmetatable(l, "CAnimControlUI");
		luaL_getmetatable(l, "CLabelUI");
		lua_setmetatable(l, -2);

		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "SetImages", SetImages },
			{ "GetImages", GetImages },
			{ "SetElapse", SetElapse },
			{ "GetElapse", GetElapse },
			{ "SetTotalFrameCnt", SetTotalFrameCnt },
			{ "GetTotalFrameCnt", GetTotalFrameCnt },
			{ "Start", Start },
			{ "Stop", Stop },
			{ "IsRunning", IsRunning },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));

		lua_pop(l, 1);
	}
}