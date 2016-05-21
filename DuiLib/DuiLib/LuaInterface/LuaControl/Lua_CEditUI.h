#ifndef _Lua_CEditUI_h
#define _Lua_CEditUI_h
#pragma once


namespace DuiLib
{
	LUA_CLASS(CEditUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetMaxChar)
		LUA_METHOD_DECL(GetMaxChar)
		LUA_METHOD_DECL(SetReadOnly)
		LUA_METHOD_DECL(IsReadOnly)
		LUA_METHOD_DECL(SetPasswordMode)
		LUA_METHOD_DECL(IsPasswordMode)
		LUA_METHOD_DECL(SetPasswordChar)
		LUA_METHOD_DECL(GetPasswordChar)
		LUA_METHOD_DECL(SetNumberOnly)
		LUA_METHOD_DECL(IsNumberOnly)
		LUA_METHOD_DECL(GetWindowStyls)
		LUA_METHOD_DECL(GetNormalImage)
		LUA_METHOD_DECL(SetNormalImage)
		LUA_METHOD_DECL(GetHotImage)
		LUA_METHOD_DECL(SetHotImage)
		LUA_METHOD_DECL(GetFocusedImage)
		LUA_METHOD_DECL(SetFocusedImage)
		LUA_METHOD_DECL(GetDisabledImage)
		LUA_METHOD_DECL(SetDisabledImage)
		LUA_METHOD_DECL(SetNativeEditBkColor)
		LUA_METHOD_DECL(GetNativeEditBkColor)
		LUA_METHOD_DECL(SetSel)
		LUA_METHOD_DECL(SetSelAll)
		LUA_METHOD_DECL(SetReplaceSel)
		LUA_METHOD_DECL(SetPrompt)
		LUA_METHOD_DECL(GetPrompt)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CEditUI_h