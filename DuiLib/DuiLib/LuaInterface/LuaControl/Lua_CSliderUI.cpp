#include "LuaEntry.h"

#include REQUIRE_H(CSliderUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CSliderUI, New)
	{
		CSliderUI  *ctrl = new CSliderUI();
		LuaStatic::AddObject2Lua(l, ctrl, METATABLE_NAME(ctrl));
		return 1;
	}

	LUA_METHOD_IMPL(CSliderUI, GetClassName)
	{
		CDuiString pstrText = CSliderUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}
	LUA_METHOD_IMPL(CSliderUI, GetChangeStep)
	{
		try
		{
			CSliderUI* self;
			self = static_cast<CSliderUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetChangeStep());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCSliderUI::GetChangeStep"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CSliderUI, SetChangeStep)
	{
		try
		{
			CSliderUI* self;
			self = static_cast<CSliderUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetChangeStep(lua_tointeger(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCSliderUI::SetChangeStep"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CSliderUI, SetThumbSize)
	{
		try
		{
			CSliderUI* self;
			self = static_cast<CSliderUI*>(LuaStatic::CheckUserData(l, 1));
			SIZE sz = LuaStatic::ReadSizeFromLua(l, 2);
			self->SetThumbSize(sz);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCSliderUI::SetThumbSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CSliderUI, GetThumbRect)
	{
		try
		{
			CSliderUI* self;
			self = static_cast<CSliderUI*>(LuaStatic::CheckUserData(l, 1));
			RECT rt = self->GetThumbRect();

			LuaStatic::WriteRect2Lua(l, rt);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCSliderUI::GetThumbRect"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CSliderUI,SetThumbImage)
	{
		try
		{
			CSliderUI* self;
			self = static_cast<CSliderUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetThumbImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCSliderUI::SetThumbImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CSliderUI,GetThumbImage)
	{
		try
		{
			CSliderUI* self;
			self = static_cast<CSliderUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetThumbImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCSliderUI::GetThumbImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CSliderUI,SetThumbHotImage)
	{
		try
		{
			CSliderUI* self;
			self = static_cast<CSliderUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetThumbHotImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCSliderUI::SetThumbHotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CSliderUI,GetThumbHotImage)
	{
		try
		{
			CSliderUI* self;
			self = static_cast<CSliderUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetThumbHotImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCSliderUI::GetThumbHotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CSliderUI,SetThumbPushedImage)
	{
		try
		{
			CSliderUI* self;
			self = static_cast<CSliderUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetThumbPushedImage(pstrText);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCSliderUI::SetThumbPushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CSliderUI,GetThumbPushedImage)
	{
		try
		{
			CSliderUI* self;
			self = static_cast<CSliderUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetThumbPushedImage();

			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCSliderUI::GetThumbPushedImage"));
			return 0;
		}
	}


	LUA_CLASS_REG_IMPL(CSliderUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "SliderUI");

		luaL_newmetatable(l, "CSliderUI");
		luaL_getmetatable(l, "CProgressUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "GetChangeStep", GetChangeStep },
			{ "SetChangeStep", SetChangeStep },
			{ "SetThumbSize", SetThumbSize },
			{ "GetThumbRect", GetThumbRect },
			{ "GetThumbImage", GetThumbImage },
			{ "SetThumbImage", SetThumbImage },
			{ "GetThumbHotImage", GetThumbHotImage },
			{ "SetThumbHotImage", SetThumbHotImage },
			{ "GetThumbPushedImage", GetThumbPushedImage },
			{ "SetThumbPushedImage", SetThumbPushedImage },
		};
		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}