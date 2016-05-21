#include "LuaEntry.h"

#include REQUIRE_H(CPaintManagerUI)

namespace DuiLib
{
	//static functions

	LUA_METHOD_IMPL(CPaintManagerUI, New)
	{
		CPaintManagerUI  *self = new CPaintManagerUI();
		LuaStatic::AddObject2Lua(l, self, METATABLE_NAME(self));
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetClassName)
	{
		CDuiString pstrText = CPaintManagerUI::GetClassName();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetInstance)
	{
		HINSTANCE hInst = CPaintManagerUI::GetInstance();
		if(hInst)
			LuaStatic::AddObject2Lua(l, hInst, "HINSTANCE");
		else
			lua_pushnil(l);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetInstancePath)
	{
		CDuiString pstrText = CPaintManagerUI::GetInstancePath();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetCurrentPath)
	{
		CDuiString pstrText = CPaintManagerUI::GetCurrentPath();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetResourceDll)
	{
		HINSTANCE hInst = CPaintManagerUI::GetResourceDll();
		if(hInst)
			LuaStatic::AddObject2Lua(l, hInst, "HINSTANCE");
		else
			lua_pushnil(l);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetResourcePath)
	{
		CDuiString pstrText = CPaintManagerUI::GetResourcePath();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetResourceZip)
	{
		CDuiString pstrText = CPaintManagerUI::GetResourceZip();
		lua_op_t<CDuiString>::push_stack(l, pstrText);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, IsCachedResourceZip)
	{
		lua_pushboolean(l,CPaintManagerUI::IsCachedResourceZip() ? 1 : 0);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetResourceZipHandle)
	{
		HANDLE hHandle = CPaintManagerUI::GetResourceDll();
		if(hHandle)
			LuaStatic::AddObject2Lua(l, hHandle, "HANDLE");
		else
			lua_pushnil(l);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetInstance)
	{
		HINSTANCE hInst = static_cast<HINSTANCE>(LuaStatic::CheckUserData(l, 1));
		CPaintManagerUI::SetInstance(hInst);
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetCurrentPath)
	{
		CDuiString pstrText;
		lua_op_t<CDuiString>::lua_to_value(l, 1, pstrText);
		CPaintManagerUI::SetCurrentPath(pstrText);
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetResourceDll)
	{
		HINSTANCE hInst = static_cast<HINSTANCE>(LuaStatic::CheckUserData(l, 1));
		CPaintManagerUI::SetResourceDll(hInst);
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetResourcePath)
	{
		CDuiString pstrText;
		lua_op_t<CDuiString>::lua_to_value(l, 1, pstrText);
		CPaintManagerUI::SetResourcePath(pstrText);
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetResourceZip)
	{
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetResourceZip2)
	{
		CDuiString pstrText;
		lua_op_t<CDuiString>::lua_to_value(l, 1, pstrText);
		bool bCachedResourceZip = false;
		if(lua_isboolean(l,2))
			bCachedResourceZip = lua_toboolean(l,2) != 0;
		CPaintManagerUI::SetResourceZip(pstrText.GetData(), bCachedResourceZip);
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetHSL)
	{
		short H,S,L;
		H = lua_tointeger(l,1);
		S = lua_tointeger(l,2);
		L = lua_tointeger(l,3);
		CPaintManagerUI::GetHSL(&H,&S,&L);
		lua_pushinteger(l,H);
		lua_pushinteger(l,S);
		lua_pushinteger(l,L);
		return 3;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetHSL)
	{
		bool bUseHSL = lua_toboolean(l,1) != 0;
		short H,S,L;
		H = lua_tointeger(l,2);
		S = lua_tointeger(l,3);
		L = lua_tointeger(l,4);
		CPaintManagerUI::SetHSL(bUseHSL,H,S,L);
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, ReloadSkin)
	{
		CPaintManagerUI::ReloadSkin();
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, LoadPlugin)
	{
		CDuiString pstrText;
		lua_op_t<CDuiString>::lua_to_value(l, 1, pstrText);
		lua_pushboolean(l, CPaintManagerUI::LoadPlugin(pstrText) ? 1 : 0);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetPlugins)
	{
		CStdPtrArray* pArr = CPaintManagerUI::GetPlugins();
		if (pArr)
			LuaStatic::AddObject2Lua(l, pArr, METATABLE_NAME(pArr));
		else
			lua_pushnil(l);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, PlayDuiSound)
	{
		CDuiString pstrText;
		lua_op_t<CDuiString>::lua_to_value(l, 1, pstrText);
		CPaintManagerUI::PlayDuiSound(pstrText);
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, MessageLoop)
	{
		CPaintManagerUI::MessageLoop();
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, TranslateMessage)
	{		
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, Term)
	{
		CPaintManagerUI::Term();
		return 0;
	}
	//methods
	LUA_METHOD_IMPL(CPaintManagerUI, isnil)
	{
		CPaintManagerUI* self;
		self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));

		lua_pushboolean(l, self == NULL ? 1 : 0);
		return 1;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, _gc)
	{	
		CPaintManagerUI* self;
		self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
		LuaStatic::RemoveObjectInLua(l);
		SafeDelete(self);
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, _eq)
	{
		try
		{
			CPaintManagerUI* left;
			left = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));

			CPaintManagerUI* right;
			right = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 2));

			lua_pushboolean(l, left == right ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::_eq"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, _tostring)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			if (self)
			{
				CDuiString str = CDuiString::FormatString(_T("%s(addr:%p)"), self->GetClass(), (void*)self);
				lua_pushstring(l, str.GetAString().c_str());
			}
			else
			{
				CDuiString str = CDuiString::FormatString(_T("%s(addr:%s)"), "PaintManagerUI", "nil");
				lua_pushstring(l, str.GetAString().c_str());
			}
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::_tostring"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, Delete)
	{
		CPaintManagerUI* self;
		self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
		LuaStatic::RemoveObjectInLua(l);
		SafeDelete(self);
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetClass)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText = self->GetClass();
			lua_op_t<CDuiString>::push_stack(l, pstrText);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetClass"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, Init)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			HWND hWnd = static_cast<HWND>(LuaStatic::CheckUserData(l, 2));
			self->Init(hWnd);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::Init"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, NeedUpdate)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->NeedUpdate();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::NeedUpdate"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, Invalidate)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			RECT rt = LuaStatic::ReadRectFromLua(l, 2);
			self->Invalidate(rt);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::Invalidate"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetPaintDC)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			HDC hPaintDC = self->GetPaintDC();
			if(hPaintDC)
				LuaStatic::AddObject2Lua(l, hPaintDC, "HDC");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetPaintDC"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetPaintWindow)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			HWND hWnd = self->GetPaintWindow();
			if(hWnd)
				LuaStatic::AddObject2Lua(l, hWnd, "HWND");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetPaintWindow"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetTooltipWindow)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			HWND hWnd = self->GetTooltipWindow();
			if(hWnd)
				LuaStatic::AddObject2Lua(l, hWnd, "HWND");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetTooltipWindow"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetMousePos)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WritePoint2Lua(l,self->GetMousePos());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetMousePos"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetClientSize)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteSize2Lua(l,self->GetClientSize());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetClientSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetInitSize)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteSize2Lua(l,self->GetInitSize());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetInitSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetInitSize)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			//SIZE sz = LuaStatic::ReadSizeFromLua(l,2);
			int cx = lua_tointeger(l,2);
			int cy = lua_tointeger(l,3);
			self->SetInitSize(cx,cy);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetInitSize"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetSizeBox)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRect2Lua(l,self->GetSizeBox());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetSizeBox"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetSizeBox)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			RECT rt = LuaStatic::ReadRectFromLua(l,2);
			self->SetSizeBox(rt);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetSizeBox"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetCaptionRect)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRect2Lua(l,self->GetCaptionRect());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetCaptionRect"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetCaptionRect)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			RECT rt = LuaStatic::ReadRectFromLua(l,2);
			self->SetCaptionRect(rt);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetCaptionRect"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetBottomCaptionRect)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRect2Lua(l,self->GetBottomCaptionRect());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetBottomCaptionRect"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetBottomCaptionRect)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			RECT rt = LuaStatic::ReadRectFromLua(l,2);
			self->SetBottomCaptionRect(rt);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetBottomCaptionRect"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetRoundCorner)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteSize2Lua(l,self->GetRoundCorner());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetRoundCorner"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetRoundCorner)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			//SIZE sz = LuaStatic::ReadSizeFromLua(l,2);
			int cx = lua_tointeger(l,2);
			int cy = lua_tointeger(l,3);
			self->SetRoundCorner(cx,cy);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetRoundCorner"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetMinInfo)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteSize2Lua(l,self->GetMinInfo());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetMinInfo"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetMinInfo)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			//SIZE sz = LuaStatic::ReadSizeFromLua(l,2);
			int cx = lua_tointeger(l,2);
			int cy = lua_tointeger(l,3);
			self->SetMinInfo(cx,cy);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetMinInfo"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetMaxInfo)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteSize2Lua(l,self->GetMaxInfo());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetMaxInfo"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetMaxInfo)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			//SIZE sz = LuaStatic::ReadSizeFromLua(l,2);
			int cx = lua_tointeger(l,2);
			int cy = lua_tointeger(l,3);
			self->SetMaxInfo(cx,cy);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetMaxInfo"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetTransparent)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetTransparent());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetTransparent"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetTransparent)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			int nOpacity = lua_tointeger(l,2);
			self->SetTransparent(nOpacity);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetTransparent"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetBackgroundTransparent)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetTransparent(lua_toboolean(l,2) != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetBackgroundTransparent"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, IsShowUpdateRect)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsShowUpdateRect() ? 1 :0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::IsShowUpdateRect"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetShowUpdateRect)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetShowUpdateRect(lua_toboolean(l,2) != 0);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetShowUpdateRect"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, UseParentResource)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CPaintManagerUI* pm = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l,2));
			lua_pushboolean(l,self->UseParentResource(pm) ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::UseParentResource"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetParentResource)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CPaintManagerUI* pm = self->GetParentResource();
			if (pm)
				LuaStatic::AddObject2Lua(l, pm, METATABLE_NAME(pm));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetParentResource"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetDefaultDisabledColor)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l,self->GetDefaultDisabledColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetDefaultDisabledColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetDefaultDisabledColor)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetDefaultDisabledColor(LuaStatic::ReadRGBAFromLua(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetDefaultDisabledColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetDefaultFontColor)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l,self->GetDefaultFontColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetDefaultFontColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetDefaultFontColor)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetDefaultFontColor(LuaStatic::ReadRGBAFromLua(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetDefaultFontColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetDefaultLinkFontColor)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l,self->GetDefaultLinkFontColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetDefaultLinkFontColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetDefaultLinkFontColor)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetDefaultLinkFontColor(LuaStatic::ReadRGBAFromLua(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetDefaultLinkFontColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetDefaultLinkHoverFontColor)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l,self->GetDefaultLinkHoverFontColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetDefaultLinkHoverFontColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetDefaultLinkHoverFontColor)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetDefaultLinkHoverFontColor(LuaStatic::ReadRGBAFromLua(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetDefaultLinkHoverFontColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetDefaultSelectedBkColor)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			LuaStatic::WriteRGBA2Lua(l,self->GetDefaultSelectedBkColor());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetDefaultSelectedBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetDefaultSelectedBkColor)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetDefaultSelectedBkColor(LuaStatic::ReadRGBAFromLua(l,2));
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetDefaultSelectedBkColor"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetDefaultFontInfo)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			TFontInfo* pFontInfo = self->GetDefaultFontInfo();
			if(pFontInfo)
				LuaStatic::AddObject2Lua(l, pFontInfo, "TFontInfo");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetDefaultFontInfo"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetDefaultFont)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			int nSize = lua_tointeger(l,3);
			bool bBold = lua_toboolean(l,4) != 0;
			bool bUnderline = lua_toboolean(l,5) != 0;
			bool bItalic = lua_toboolean(l,6) != 0;
			self->SetDefaultFont(pstrText, nSize, bBold, bUnderline, bItalic);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetDefaultFont"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetCustomFontCount)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushnumber(l,self->GetCustomFontCount());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetCustomFontCount"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddFont)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			int nSize = lua_tointeger(l,3);
			bool bBold = lua_toboolean(l,4) != 0;
			bool bUnderline = lua_toboolean(l,5) != 0;
			bool bItalic = lua_toboolean(l,6) != 0;
			HFONT hFont = self->AddFont(pstrText, nSize, bBold, bUnderline, bItalic);
			if (hFont)
				LuaStatic::AddObject2Lua(l, hFont, "HFONT");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AddFont"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddFontAt)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			int iIndex = lua_tointeger(l,2);
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText);
			int nSize = lua_tointeger(l,4);
			bool bBold = lua_toboolean(l,5) != 0;
			bool bUnderline = lua_toboolean(l,6) != 0;
			bool bItalic = lua_toboolean(l,7) != 0;
			HFONT hFont = self->AddFontAt(iIndex, pstrText, nSize, bBold, bUnderline, bItalic);
			if (hFont)
				LuaStatic::AddObject2Lua(l, hFont, "HFONT");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AddFontAt"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetFontByIndex)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			int iIndex = lua_tointeger(l,2);
			HFONT hFont = self->GetFont(iIndex);
			if (hFont)
				LuaStatic::AddObject2Lua(l, hFont, "HFONT");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetFontByIndex"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetFontByName)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			int nSize = lua_tointeger(l,3);
			bool bBold = lua_toboolean(l,4) != 0;
			bool bUnderline = lua_toboolean(l,5) != 0;
			bool bItalic = lua_toboolean(l,6) != 0;
			HFONT hFont = self->GetFont(pstrText, nSize, bBold, bUnderline, bItalic);
			if (hFont)
				LuaStatic::AddObject2Lua(l, hFont, "HFONT");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetFontByName"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, FindFont)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			HFONT hFont =  static_cast<HFONT>(LuaStatic::CheckUserData(l, 2));
			lua_pushboolean(l,self->FindFont(hFont) ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::FindFont"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, FindFont2)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			int nSize = lua_tointeger(l,3);
			bool bBold = lua_toboolean(l,4) != 0;
			bool bUnderline = lua_toboolean(l,5) != 0;
			bool bItalic = lua_toboolean(l,6) != 0;
			lua_pushboolean(l, self->FindFont(pstrText, nSize, bBold, bUnderline, bItalic) ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::FindFont2"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetFontIndex)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			HFONT hFont =  static_cast<HFONT>(LuaStatic::CheckUserData(l, 2));
			lua_pushinteger(l,self->GetFontIndex(hFont));
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetFontIndex"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetFontIndex2)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			int nSize = lua_tointeger(l,3);
			bool bBold = lua_toboolean(l,4) != 0;
			bool bUnderline = lua_toboolean(l,5) != 0;
			bool bItalic = lua_toboolean(l,6) != 0;
			lua_pushinteger(l, self->GetFontIndex(pstrText, nSize, bBold, bUnderline, bItalic));
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetFontIndex2"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveFont)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			HFONT hFont =  static_cast<HFONT>(LuaStatic::CheckUserData(l, 2));
			lua_pushboolean(l,self->RemoveFont(hFont) ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveFont"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveFontAt)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			int iIndex = lua_tointeger(l,2);
			lua_pushboolean(l,self->RemoveFontAt(iIndex) ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveFontAt"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveAllFonts)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->RemoveAllFonts();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveAllFonts"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetFontInfoAt)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			int iIndex = lua_tointeger(l,2);
			TFontInfo* pFontInfo = self->GetFontInfo(iIndex);
			if(pFontInfo)
				LuaStatic::AddObject2Lua(l, pFontInfo, "TFontInfo");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetFontInfoAt"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetFontInfo)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			HFONT hFont =  static_cast<HFONT>(LuaStatic::CheckUserData(l, 2));
			TFontInfo* pFontInfo = self->GetFontInfo(hFont);
			if(pFontInfo)
				LuaStatic::AddObject2Lua(l, pFontInfo, "TFontInfo");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetFontInfo"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetImage)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			const TImageInfo* pImageInfo = self->GetImage(pstrText);
			if (pImageInfo)
			{
				LuaStatic::AddObject2Lua(l, pImageInfo, "TImageInfo");
			}
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetImageEx)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			LPCTSTR type = NULL;
			if (lua_isstring(l, 3))
			{
				CDuiString pstrText2;
				lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText2);
				type = pstrText2.GetData();
			}
			DWORD mask = 0;
			if(lua_isnumber(l,4))
				mask = (DWORD)lua_tonumber(l,4);
			const TImageInfo* pImageInfo = self->GetImageEx(pstrText, type, mask);
			if(pImageInfo)
				LuaStatic::AddObject2Lua(l, pImageInfo, "TImageInfo");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetImageEx"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddImage)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			LPCTSTR type = NULL;
			if (lua_isstring(l, 3))
			{
				CDuiString pstrText2;
				lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText2);
				type = pstrText2.GetData();
			}
			DWORD mask = 0;
			if(lua_isnumber(l,4))
				mask = (DWORD)lua_tonumber(l,4);
			const TImageInfo* pImageInfo = self->AddImage(pstrText, type, mask);
			if(pImageInfo)
				LuaStatic::AddObject2Lua(l, pImageInfo, "TImageInfo");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AddImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddImageEx)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			HBITMAP hBitmap = static_cast<HBITMAP>(LuaStatic::CheckUserData(l, 3));
			int nW = lua_tointeger(l,4);
			int nH = lua_tointeger(l,5);
			bool bAlpha = lua_toboolean(l,6) != 0;
			const TImageInfo* pImageInfo = self->AddImage(pstrText, hBitmap, nW, nH, bAlpha);
			if(pImageInfo)
				LuaStatic::AddObject2Lua(l, pImageInfo, "TImageInfo");
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AddImageEx"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveImage)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			lua_pushboolean(l, self->RemoveImage(pstrText));
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveImage"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveAllImages)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->RemoveAllImages();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveAllImages"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, ReloadAllImages)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->ReloadAllImages();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::ReloadAllImages"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddDefaultAttributeList)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			CDuiString pstrText2;
			lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText2);
			self->AddDefaultAttributeList(pstrText, pstrText2);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AddDefaultAttributeList"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetDefaultAttributeList)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);

			CDuiString pstrText2 = self->GetDefaultAttributeList(pstrText);
			lua_op_t<CDuiString>::push_stack(l, pstrText2);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetDefaultAttributeList"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveDefaultAttributeList)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			lua_pushboolean(l, self->RemoveDefaultAttributeList(pstrText));
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveDefaultAttributeList"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetDefaultAttribultes)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CStdStringPtrMap pMap = self->GetDefaultAttribultes();
			LuaStatic::AddObject2Lua(l, &pMap, METATABLE_NAME(&pMap));
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetDefaultAttribultes"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveAllDefaultAttributeList)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->RemoveAllDefaultAttributeList();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveAllDefaultAttributeList"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddCustomStyle)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			CStdStringPtrMap* pMap = static_cast<CStdStringPtrMap*>(LuaStatic::CheckUserData(l, 3));
			self->AddCustomStyle(pstrText, pMap);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AddCustomStyle"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetCustomStyle)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			CDuiString pstrText2;
			lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText2);
			LPCTSTR pStyle = self->GetCustomStyle(pstrText, pstrText2);
			if(pStyle)
			{	
				CDuiString pstrText3(pStyle);
				lua_op_t<CDuiString>::push_stack(l, pstrText3);
			}
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetCustomStyle"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetCustomStyleMap)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			CStdStringPtrMap* pMap = self->GetCustomStyle(pstrText);
			if (pMap)
				LuaStatic::AddObject2Lua(l, pMap, METATABLE_NAME(pMap));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetCustomStyleMap"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveAllStyle)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->RemoveAllStyle();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveAllStyle"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AttachDialog)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			lua_pushboolean(l,self->AttachDialog(pControl) != 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AttachDialog"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, InitControls)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			CControlUI* pParent = NULL;
			if(!lua_isnone(l,3))
				pParent = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 3));
			lua_pushboolean(l,self->InitControls(pControl,pParent) != 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::InitControls"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, ReapObjects)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			self->ReapObjects(pControl);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::ReapObjects"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddOptionGroup)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 3));
			lua_pushboolean(l, self->AddOptionGroup(pstrText, pControl) ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AddOptionGroup"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetOptionGroup)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			CStdPtrArray* pArr = self->GetOptionGroup(pstrText);
			if(pArr)
				LuaStatic::AddObject2Lua(l,pArr,METATABLE_NAME(pArr));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetOptionGroup"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveOptionGroup)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 3));
			self->RemoveOptionGroup(pstrText, pControl);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveOptionGroup"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveAllOptionGroups)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->RemoveAllOptionGroups();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveAllOptionGroups"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetFocus)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = self->GetFocus();
			if(pControl)
				LuaStatic::AddObject2Lua(l,pControl,METATABLE_NAME(pControl));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetFocus"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetFocus)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			self->SetFocus(pControl);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetFocus"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetFocusNeeded)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			self->SetFocusNeeded(pControl);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetFocusNeeded"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetNextTabControl)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			bool bForward = true;
			if(lua_isboolean(l,2))
				bForward = lua_toboolean(l,2) != 0;
			self->SetNextTabControl(bForward);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetNextTabControl"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetTimer)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			int TimerID = lua_tointeger(l,3);
			int Elapse = lua_tointeger(l,4);
			lua_pushboolean(l,self->SetTimer(pControl,TimerID,Elapse) != 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetTimer"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, KillTimer)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			int TimerID = lua_tointeger(l,3);
			lua_pushboolean(l,self->KillTimer(pControl,TimerID) != 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::KillTimer"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, KillTimer2)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			self->KillTimer(pControl);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::KillTimer2"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveAllTimers)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->RemoveAllTimers();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveAllTimers"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetCapture)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->SetCapture();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetCapture"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, ReleaseCapture)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			self->ReleaseCapture();
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::ReleaseCapture"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, IsCaptured)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushboolean(l,self->IsCaptured() != 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::IsCaptured"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddNotifier)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			INotifyUI* pControl = static_cast<INotifyUI*>(LuaStatic::CheckUserData(l, 2));
			lua_pushboolean(l,self->AddNotifier(pControl) != 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AddNotifier"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveNotifier)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			INotifyUI* pControl = static_cast<INotifyUI*>(LuaStatic::CheckUserData(l, 2));
			lua_pushboolean(l,self->RemoveNotifier(pControl) != 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemoveNotifier"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SendNotify)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			TNotifyUI* pMsg = static_cast<TNotifyUI*>(LuaStatic::CheckUserData(l, 2));
			bool bAsync = false;
			if(lua_isboolean(l,3))
				bAsync = lua_toboolean(l,3) != 0;
			self->SendNotify(*pMsg,bAsync);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SendNotify"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SendNotify2)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText);
			WPARAM wParam = 0; LPARAM lParam = 0; bool bAsync = false;
			if(!lua_isnone(l,4))
				wParam = (WPARAM) luaL_optint(l, 4, 0);
			if(!lua_isnone(l,5))
				lParam = (LPARAM) luaL_optstring(l, 5, "");
			if(lua_isboolean(l,3))
				bAsync = lua_toboolean(l,6) != 0;

			self->SendNotify(pControl, pstrText, wParam, lParam, bAsync);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SendNotify2"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddPreMessageFilter)
	{
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemovePreMessageFilter)
	{
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddMessageFilter)
	{
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveMessageFilter)
	{
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetPostPaintCount)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			lua_pushinteger(l,self->GetPostPaintCount());
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetPostPaintCount"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddPostPaint)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			lua_pushboolean(l,self->AddPostPaint(pControl) ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AddPostPaint"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemovePostPaint)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			lua_pushboolean(l,self->RemovePostPaint(pControl) ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::RemovePostPaint"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, SetPostPaintIndex)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			int iIndex = lua_tointeger(l,3);
			lua_pushboolean(l,self->SetPostPaintIndex(pControl,iIndex) ? 1 : 0);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::SetPostPaintIndex"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddDelayedCleanup)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(l, 2));
			self->AddDelayedCleanup(pControl);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::AddDelayedCleanup"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, AddTranslateAccelerator)
	{
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, RemoveTranslateAccelerator)
	{
		return 0;
	}
	LUA_METHOD_IMPL(CPaintManagerUI, TranslateAccelerator)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::TranslateAccelerator"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetRoot)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pControl = self->GetRoot();
			if(pControl)
				LuaStatic::AddObject2Lua(l,pControl,METATABLE_NAME(pControl));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetRoot"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, FindControlByPoint)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			POINT pt = LuaStatic::ReadPointFromLua(l,2);
			CControlUI* pControl = self->FindControl(pt);
			if(pControl)
				LuaStatic::AddObject2Lua(l,pControl,METATABLE_NAME(pControl));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::FindControlByPoint"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, FindControlByName)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 2, pstrText);
			CControlUI* pControl = self->FindControl(pstrText);
			if(pControl)
				LuaStatic::AddObject2Lua(l,pControl,METATABLE_NAME(pControl));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::FindControlByName"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, FindSubControlByPoint)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pParent = static_cast<CControlUI*>(LuaStatic::CheckUserData(l,2));
			POINT pt = LuaStatic::ReadPointFromLua(l,3);
			CControlUI* pControl = self->FindSubControlByPoint(pParent,pt);
			if(pControl)
				LuaStatic::AddObject2Lua(l,pControl,METATABLE_NAME(pControl));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::FindSubControlByPoint"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, FindSubControlByName)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pParent = static_cast<CControlUI*>(LuaStatic::CheckUserData(l,2));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText);
			CControlUI* pControl = self->FindSubControlByName(pParent, pstrText);
			if(pControl)
				LuaStatic::AddObject2Lua(l,pControl,METATABLE_NAME(pControl));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::FindSubControlByName"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, FindSubControlByClass)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pParent = static_cast<CControlUI*>(LuaStatic::CheckUserData(l,2));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText);
			int iIndex = 0;
			if (lua_isnumber(l,4))
				iIndex = lua_tointeger(l,4);
			CControlUI* pControl = self->FindSubControlByClass(pParent, pstrText, iIndex);
			if(pControl)
				LuaStatic::AddObject2Lua(l,pControl,METATABLE_NAME(pControl));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::FindSubControlByClass"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, FindSubControlsByClass)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));
			CControlUI* pParent = static_cast<CControlUI*>(LuaStatic::CheckUserData(l,2));
			CDuiString pstrText;
			lua_op_t<CDuiString>::lua_to_value(l, 3, pstrText);
			CStdPtrArray* pControls = self->FindSubControlsByClass(pParent, pstrText);
			if(pControls)
				LuaStatic::AddObject2Lua(l,pControls,METATABLE_NAME(pControls));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::FindSubControlsByClass"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, GetSubControlsByClass)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));			
			CStdPtrArray* pControls = self->GetSubControlsByClass();
			if(pControls)
				LuaStatic::AddObject2Lua(l,pControls,METATABLE_NAME(pControls));
			else
				lua_pushnil(l);
			return 1;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::GetSubControlsByClass"));
			return 0;
		}
	}
	LUA_METHOD_IMPL(CPaintManagerUI, UsedVirtualWnd)
	{
		try
		{
			CPaintManagerUI* self;
			self = static_cast<CPaintManagerUI*>(LuaStatic::CheckUserData(l, 1));			
			bool bUsed = lua_toboolean(l,2) != 0;
			self->UsedVirtualWnd(bUsed);
			return 0;
		}
		catch (...)
		{
			DuiException(_T("LuaCPaintManagerUI::UsedVirtualWnd"));
			return 0;
		}
	}

	LUA_CLASS_REG_IMPL(CPaintManagerUI)
	{
		lua_newtable(l);
		static LuaReg StaticFuncs[] =
		{
			{ "GetClassName", GetClassName },
			{ "GetInstance", GetInstance },
			{ "GetInstancePath",GetInstancePath },
			{ "GetCurrentPath", GetCurrentPath},
			{ "GetResourceDll",GetResourceDll},
			{ "GetResourcePath",GetResourcePath},
			{ "GetResourceZip",GetResourceZip},
			{ "IsCachedResourceZip",IsCachedResourceZip},
			{ "GetResourceZipHandle",GetResourceZipHandle},
			{ "SetInstance",SetInstance},
			{ "SetCurrentPath",SetCurrentPath},
			{ "SetResourceDll",SetResourceDll},
			{ "SetResourcePath",SetResourcePath},
			{ "SetResourceZip",SetResourceZip},
			{ "SetResourceZip2",SetResourceZip2},
			{ "GetHSL",GetHSL},
			{ "SetHSL",SetHSL},
			{ "ReloadSkin",ReloadSkin},
			{ "LoadPlugin",LoadPlugin},
			{ "GetPlugins",GetPlugins},
			{ "MessageLoop",MessageLoop},
			{ "TranslateMessage",TranslateMessage},
			{ "Term",Term},
			{ "PlayDuiSound", PlayDuiSound },
			{ "New", New },
		};
		LuaStatic::LuaSetFuncsInTable(l, StaticFuncs, sizeof(StaticFuncs) / sizeof(StaticFuncs[0]));
		lua_setfield(l, -2, "PaintManagerUI");

		luaL_newmetatable(l, "CPaintManagerUI");
		
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		static LuaReg MethodFuncs[] =
		{
			{ "isnil",isnil },
			{ "__eq",_eq },
			{ "__gc",_gc },
			{ "__tostring", _tostring },
			{ "Delete",Delete},
			{ "GetClass", GetClass },
			{ "Init", Init },
			{ "NeedUpdate", NeedUpdate},
			{ "Invalidate", Invalidate},
			{ "GetPaintDC", GetPaintDC},
			{ "GetPaintWindow", GetPaintWindow},
			{ "GetTooltipWindow", GetTooltipWindow},
			{ "GetMousePos", GetMousePos},
			{ "GetClientSize", GetClientSize},
			{ "GetInitSize", GetInitSize},
			{ "SetInitSize", SetInitSize},
			{ "GetSizeBox", GetSizeBox},
			{ "SetSizeBox", SetSizeBox},
			{ "GetCaptionRect", GetCaptionRect},
			{ "SetCaptionRect", SetCaptionRect},
			{ "GetBottomCaptionRect", GetBottomCaptionRect},
			{ "SetBottomCaptionRect", SetBottomCaptionRect},
			{ "GetRoundCorner", GetRoundCorner},
			{ "SetRoundCorner", SetRoundCorner},
			{ "GetMinInfo", GetMinInfo},
			{ "SetMinInfo", SetMinInfo},
			{ "GetMaxInfo", GetMaxInfo},
			{ "SetMaxInfo", SetMaxInfo},
			{ "GetTransparent", GetTransparent},
			{ "SetTransparent", SetTransparent},
			{ "SetBackgroundTransparent", SetBackgroundTransparent},
			{ "IsShowUpdateRect", IsShowUpdateRect},
			{ "SetShowUpdateRect", SetShowUpdateRect},
			{ "UseParentResource", UseParentResource},
			{ "GetParentResource", GetParentResource},
			{ "GetDefaultDisabledColor", GetDefaultDisabledColor},
			{ "SetDefaultDisabledColor", SetDefaultDisabledColor},
			{ "GetDefaultFontColor", GetDefaultFontColor},
			{ "SetDefaultFontColor", SetDefaultFontColor},
			{ "GetDefaultLinkFontColor", GetDefaultLinkFontColor},
			{ "SetDefaultLinkFontColor", SetDefaultLinkFontColor},
			{ "GetDefaultLinkHoverFontColor", GetDefaultLinkHoverFontColor},
			{ "SetDefaultLinkHoverFontColor", SetDefaultLinkHoverFontColor},
			{ "GetDefaultSelectedBkColor", GetDefaultSelectedBkColor},
			{ "SetDefaultSelectedBkColor", SetDefaultSelectedBkColor},
			{ "GetDefaultFontInfo", GetDefaultFontInfo},
			{ "SetDefaultFont", SetDefaultFont},
			{ "GetCustomFontCount", GetCustomFontCount},
			{ "AddFont", AddFont},
			{ "AddFontAt", AddFontAt},
			{ "GetFontByIndex", GetFontByIndex},
			{ "GetFontByName", GetFontByName},
			{ "FindFont", FindFont},
			{ "FindFont2", FindFont2},
			{ "GetFontIndex", GetFontIndex},
			{ "GetFontIndex2", GetFontIndex2},
			{ "RemoveFont", RemoveFont},
			{ "RemoveFontAt", RemoveFontAt},
			{ "RemoveAllFonts", RemoveAllFonts},
			{ "GetFontInfoAt", GetFontInfoAt},
			{ "GetFontInfo", GetFontInfo},
			{ "GetImage", GetImage},
			{ "GetImageEx", GetImageEx},
			{ "AddImage", AddImage},
			{ "AddImageEx", AddImageEx},
			{ "RemoveImage", RemoveImage},
			{ "RemoveAllImages", RemoveAllImages},
			{ "ReloadAllImages", ReloadAllImages},
			{ "AddDefaultAttributeList", AddDefaultAttributeList},
			{ "GetDefaultAttributeList", GetDefaultAttributeList},
			{ "RemoveDefaultAttributeList", RemoveDefaultAttributeList},
			{ "GetDefaultAttribultes", GetDefaultAttribultes},
			{ "RemoveAllDefaultAttributeList", RemoveAllDefaultAttributeList},
			{ "AddCustomStyle", AddCustomStyle},
			{ "GetCustomStyle", GetCustomStyle},
			{ "GetCustomStyleMap", GetCustomStyleMap},
			{ "RemoveAllStyle", RemoveAllStyle},
			{ "AttachDialog", AttachDialog},
			{ "InitControls", InitControls},
			{ "ReapObjects", ReapObjects},
			{ "AddOptionGroup", AddOptionGroup},
			{ "GetOptionGroup", GetOptionGroup},
			{ "RemoveOptionGroup", RemoveOptionGroup},
			{ "RemoveAllOptionGroups", RemoveAllOptionGroups},
			{ "GetFocus", GetFocus},
			{ "SetFocus", SetFocus},
			{ "SetFocusNeeded", SetFocusNeeded},
			{ "SetNextTabControl", SetNextTabControl},
			{ "SetTimer", SetTimer},
			{ "KillTimer", KillTimer},
			{ "KillTimer2", KillTimer2},
			{ "RemoveAllTimers", RemoveAllTimers},
			{ "SetCapture", SetCapture},
			{ "ReleaseCapture", ReleaseCapture},
			{ "IsCaptured", IsCaptured},
			{ "AddNotifier", AddNotifier},
			{ "RemoveNotifier", RemoveNotifier},
			{ "SendNotify", SendNotify},
			{ "SendNotify2", SendNotify2},
			{ "AddPreMessageFilter", AddPreMessageFilter},
			{ "RemovePreMessageFilter", RemovePreMessageFilter},
			{ "AddMessageFilter", AddMessageFilter},
			{ "RemoveMessageFilter", RemoveMessageFilter},
			{ "GetPostPaintCount", GetPostPaintCount},
			{ "AddPostPaint", AddPostPaint},
			{ "RemovePostPaint", RemovePostPaint},
			{ "SetPostPaintIndex", SetPostPaintIndex},
			{ "AddDelayedCleanup", AddDelayedCleanup},
			{ "AddTranslateAccelerator", AddTranslateAccelerator},
			{ "RemoveTranslateAccelerator", RemoveTranslateAccelerator},
			{ "TranslateAccelerator", TranslateAccelerator},
			{ "GetRoot", GetRoot},
			{ "FindControlByPoint", FindControlByPoint},
			{ "FindControlByName", FindControlByName},
			{ "FindSubControlByPoint", FindSubControlByPoint},
			{ "FindSubControlByName", FindSubControlByName},
			{ "FindSubControlByClass", FindSubControlByClass},
			{ "FindSubControlsByClass", FindSubControlsByClass},
			{ "GetSubControlsByClass", GetSubControlsByClass},
			{ "UsedVirtualWnd", UsedVirtualWnd},
		};

		LuaStatic::LuaSetFuncsInTable(l, MethodFuncs, sizeof(MethodFuncs) / sizeof(MethodFuncs[0]));
		
		lua_pop(l, 1);
	}
}