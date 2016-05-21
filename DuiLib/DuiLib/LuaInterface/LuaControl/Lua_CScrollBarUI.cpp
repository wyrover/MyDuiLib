#include "LuaEntry.h"

#include REQUIRE_H(CScrollBarUI)

namespace DuiLib
{
	LUA_METHOD_IMPL(CScrollBarUI, New)
	{
		CScrollBarUI  *self = new CScrollBarUI();
		LuaStatic::AddObject2Lua(l, self, METATABLE_NAME(self));
		return 1;
	}

	LUA_METHOD_IMPL(CScrollBarUI, GetClassName)
	{
		CDuiString pstrText = CScrollBarUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetOwner)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CContainerUI* pOwner;
			pOwner = static_cast<CContainerUI*>(self->GetOwner());

			if (pOwner)
				LuaStatic::AddObject2Lua(l,pOwner, METATABLE_NAME(pOwner));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetOwner"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetOwner)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));

			CContainerUI* pOwner;
			pOwner = static_cast<CContainerUI*>(LuaStatic::CheckUserData(l, 2));

			self->SetOwner(pOwner);
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetOwner"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, IsHorizontal)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsHorizontal() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::IsHorizontal"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetHorizontal)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			bool bHorizontal = true;
			if(!lua_isnone(l,2))
				bHorizontal = lua_toboolean(l,2) != 0;
			self->SetHorizontal(bHorizontal);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetHorizontal"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetScrollRange)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetScrollRange());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetScrollRange"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetScrollRange)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));			
			self->SetScrollRange(lua_tointeger(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetScrollRange"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetScrollPos)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetScrollPos());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetScrollPos"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetScrollPos)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));			
			self->SetScrollPos(lua_tointeger(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetScrollPos"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetLineSize)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetLineSize());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetLineSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetLineSize)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));			
			self->SetLineSize(lua_tointeger(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetLineSize"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CScrollBarUI, GetShowButton1)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->GetShowButton1() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetShowButton1"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetShowButton1)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			bool bShow = true;
			if(!lua_isnone(l,2))
				bShow = lua_toboolean(l,2) != 0;
			self->SetShowButton1(bShow);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetShowButton1"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetButton1NormalImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetButton1NormalImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetButton1NormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetButton1NormalImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetButton1NormalImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetButton1NormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetButton1HotImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetButton1HotImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetButton1HotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetButton1HotImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetButton1HotImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetButton1HotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetButton1PushedImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetButton1PushedImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetButton1PushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetButton1PushedImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetButton1PushedImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetButton1PushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetButton1DisabledImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetButton1DisabledImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetButton1DisabledImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetButton1DisabledImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetButton1DisabledImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetButton1DisabledImage"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CScrollBarUI, GetShowButton2)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->GetShowButton2() ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetShowButton2"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetShowButton2)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			bool bShow = true;
			if(!lua_isnone(l,2))
				bShow = lua_toboolean(l,2) != 0;
			self->SetShowButton2(bShow);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetShowButton2"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetButton2NormalImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetButton2NormalImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetButton2NormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetButton2NormalImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetButton2NormalImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetButton2NormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetButton2HotImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetButton2HotImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetButton2HotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetButton2HotImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetButton2HotImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetButton2HotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetButton2PushedImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetButton2PushedImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetButton2PushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetButton2PushedImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetButton2PushedImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetButton2PushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetButton2DisabledImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetButton2DisabledImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetButton2DisabledImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetButton2DisabledImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetButton2DisabledImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetButton2DisabledImage"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CScrollBarUI, GetThumbNormalImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetThumbNormalImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetThumbNormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetThumbNormalImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetThumbNormalImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetThumbNormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetThumbHotImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetThumbHotImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetThumbHotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetThumbHotImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetThumbHotImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetThumbHotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetThumbPushedImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetThumbPushedImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetThumbPushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetThumbPushedImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetThumbPushedImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetThumbPushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetThumbDisabledImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetThumbDisabledImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetThumbDisabledImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetThumbDisabledImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetThumbDisabledImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetThumbDisabledImage"));
			return 0;
		}
	}

	LUA_METHOD_IMPL(CScrollBarUI, GetRailNormalImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetRailNormalImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetRailNormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetRailNormalImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetRailNormalImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetRailNormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetRailHotImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetRailHotImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetRailHotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetRailHotImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetRailHotImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetRailHotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetRailPushedImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetRailPushedImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetRailPushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetRailPushedImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetRailPushedImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetRailPushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetRailDisabledImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetRailDisabledImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetRailDisabledImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetRailDisabledImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetRailDisabledImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetRailDisabledImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetBkNormalImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetBkNormalImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetBkNormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetBkNormalImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetBkNormalImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetBkNormalImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetBkHotImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetBkHotImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetBkHotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetBkHotImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetBkHotImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetBkHotImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetBkPushedImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetBkPushedImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetBkPushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetBkPushedImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetBkPushedImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetBkPushedImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, GetBkDisabledImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetBkDisabledImage();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::GetBkDisabledImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CScrollBarUI, SetBkDisabledImage)
	{
		try
		{
			CScrollBarUI* self;
			self = static_cast<CScrollBarUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			self->SetBkDisabledImage(pstrText.GetData());
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCScrollBarUI::SetBkDisabledImage"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CScrollBarUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "New", New },
			{ "GetClassName", GetClassName },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "ScrollBarUI");

		luaL_newmetatable(l, "CScrollBarUI");
		luaL_getmetatable(l, "CControlUI");
		lua_setmetatable(l, -2);
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "GetOwner", GetOwner },
			{ "SetOwner", SetOwner },
			{ "IsHorizontal", IsHorizontal },
			{ "SetHorizontal", SetHorizontal },
			{ "GetScrollRange", GetScrollRange },
			{ "SetScrollRange", SetScrollRange },
			{ "GetScrollPos", GetScrollPos },
			{ "SetScrollPos", SetScrollPos },
			{ "GetLineSize", GetLineSize },
			{ "SetLineSize", SetLineSize },

			{ "GetShowButton1", GetShowButton1 },
			{ "SetShowButton1", SetShowButton1 },
			{ "GetButton1NormalImage", GetButton1NormalImage },
			{ "SetButton1NormalImage", SetButton1NormalImage },
			{ "GetButton1HotImage", GetButton1HotImage },
			{ "SetButton1HotImage", SetButton1HotImage },
			{ "GetButton1PushedImage", GetButton1PushedImage },
			{ "SetButton1PushedImage", SetButton1PushedImage },
			{ "GetButton1DisabledImage", GetButton1DisabledImage },
			{ "SetButton1DisabledImage", SetButton1DisabledImage },

			{ "GetShowButton2", GetShowButton2 },
			{ "SetShowButton2", SetShowButton2 },
			{ "GetButton2NormalImage", GetButton2NormalImage },
			{ "SetButton2NormalImage", SetButton2NormalImage },
			{ "GetButton2HotImage", GetButton2HotImage },
			{ "SetButton2HotImage", SetButton2HotImage },
			{ "GetButton2PushedImage", GetButton2PushedImage },
			{ "SetButton2PushedImage", SetButton2PushedImage },
			{ "GetButton2DisabledImage", GetButton2DisabledImage },
			{ "SetButton2DisabledImage", SetButton2DisabledImage },

			{ "GetThumbNormalImage", GetThumbNormalImage },
			{ "SetThumbNormalImage", SetThumbNormalImage },
			{ "GetThumbHotImage", GetThumbHotImage },
			{ "SetThumbHotImage", SetThumbHotImage },
			{ "GetThumbPushedImage", GetThumbPushedImage },
			{ "SetThumbPushedImage", SetThumbPushedImage },
			{ "GetThumbDisabledImage", GetThumbDisabledImage },
			{ "SetThumbDisabledImage", SetThumbDisabledImage },

			{ "GetRailNormalImage", GetRailNormalImage },
			{ "SetRailNormalImage", SetRailNormalImage },
			{ "GetRailHotImage", GetRailHotImage },
			{ "SetRailHotImage", SetRailHotImage },
			{ "GetRailPushedImage", GetRailPushedImage },
			{ "SetRailPushedImage", SetRailPushedImage },
			{ "GetRailDisabledImage", GetRailDisabledImage },
			{ "SetRailDisabledImage", SetRailDisabledImage },

			{ "GetBkNormalImage", GetBkNormalImage },
			{ "SetBkNormalImage", SetBkNormalImage },
			{ "GetBkHotImage", GetBkHotImage },
			{ "SetBkHotImage", SetBkHotImage },
			{ "GetBkPushedImage", GetBkPushedImage },
			{ "SetBkPushedImage", SetBkPushedImage },
			{ "GetBkDisabledImage", GetBkDisabledImage },
			{ "SetBkDisabledImage", SetBkDisabledImage },
		};

		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}