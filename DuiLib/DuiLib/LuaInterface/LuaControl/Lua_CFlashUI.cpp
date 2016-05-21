#include "LuaEntry.h"

#include REQUIRE_H(CFlashUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CFlashUI, New)
	{
		CFlashUI  *ctrl = new CFlashUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CFlashUI, GetClassName)
	{
		CDuiString pstrText = CFlashUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}

	LUA_METHOD_IMPL(CFlashUI,SetFlashEventHandler)
	{
		try
		{
			CFlashUI* self;
			self = static_cast<CFlashUI*>(LuaStatic::CheckUserData(l, 1));
			//self->SetFlashEventHandler(lua_toboolean(l,2) != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCFlashUI::SetFlashEventHandler"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CFlashUI,DoCreateControl)
	{
		try
		{
			CFlashUI* self;
			self = static_cast<CFlashUI*>(LuaStatic::CheckUserData(l, 1));
			self->DoCreateControl();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCFlashUI::DoCreateControl"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CFlashUI,get_ShockwaveFlash)
	{
		try
		{
			CFlashUI* self;
			self = static_cast<CFlashUI*>(LuaStatic::CheckUserData(l, 1));
			IShockwaveFlash* pFlash = self->m_pFlash;
			if (pFlash)
			{
				//TODO:
			}
			else
			{
				lua_pushnil(l);
			}
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCFlashUI::get_ShockwaveFlash"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CFlashUI,SetFlashUrl)
	{
		try
		{
			CFlashUI* self;
			self = static_cast<CFlashUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetFlashUrl(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCFlashUI::SetFlashUrl"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CFlashUI,GetFlashUrl)
	{
		try
		{
			CFlashUI* self;
			self = static_cast<CFlashUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetFlashUrl();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCFlashUI::GetFlashUrl"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CFlashUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "FlashUI");

		luaL_newmetatable(l, "CFlashUI");
		luaL_getmetatable(l, "CActiveXUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "SetFlashEventHandler", SetFlashEventHandler },
			{ "DoCreateControl", DoCreateControl },
			{ "get_ShockwaveFlash", get_ShockwaveFlash },
			{ "SetFlashUrl", SetFlashUrl },
			{ "GetFlashUrl", GetFlashUrl },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}