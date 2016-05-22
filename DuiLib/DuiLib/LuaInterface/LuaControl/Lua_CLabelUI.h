#ifndef _Lua_CLabelUI_h
#define _Lua_CLabelUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CLabelUI, LabelUI, CLabelUI, ControlUI, CControlUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)

		LUA_METHOD_DECL(SetTextStyle)
		LUA_METHOD_DECL(GetTextStyle)
		LUA_METHOD_DECL(SetTextColor)
		LUA_METHOD_DECL(GetTextColor)
		LUA_METHOD_DECL(SetDisabledTextColor)
		LUA_METHOD_DECL(GetDisabledTextColor)
		LUA_METHOD_DECL(SetFont)
		LUA_METHOD_DECL(GetFont)
		LUA_METHOD_DECL(GetTextPadding)
		LUA_METHOD_DECL(SetTextPadding)
		LUA_METHOD_DECL(IsShowHtml)
		LUA_METHOD_DECL(SetShowHtml)

		LUA_METHOD_DECL(SetEnabledEffect)
		LUA_METHOD_DECL(GetEnabledEffect)
		LUA_METHOD_DECL(SetTransShadow)
		LUA_METHOD_DECL(GetTransShadow)
		LUA_METHOD_DECL(SetTransShadow1)
		LUA_METHOD_DECL(GetTransShadow1)
		LUA_METHOD_DECL(SetTransText)
		LUA_METHOD_DECL(GetTransText)
		LUA_METHOD_DECL(SetTransText1)
		LUA_METHOD_DECL(GetTransText1)
		LUA_METHOD_DECL(SetTransStroke)
		LUA_METHOD_DECL(GetTransStroke)
		LUA_METHOD_DECL(SetGradientLength)
		LUA_METHOD_DECL(GetGradientLength)
		LUA_METHOD_DECL(SetTextRenderingHintAntiAlias)
		LUA_METHOD_DECL(GetTextRenderingHintAntiAlias)
		LUA_METHOD_DECL(SetShadowOffset)
		LUA_METHOD_DECL(GetShadowOffset)
		LUA_METHOD_DECL(SetTextColor1)
		LUA_METHOD_DECL(GetTextColor1)
		LUA_METHOD_DECL(SetTextShadowColorA)
		LUA_METHOD_DECL(GetTextShadowColorA)
		LUA_METHOD_DECL(SetTextShadowColorB)
		LUA_METHOD_DECL(GetTextShadowColorB)
		LUA_METHOD_DECL(SetStrokeColor)
		LUA_METHOD_DECL(GetStrokeColor)
		LUA_METHOD_DECL(SetGradientAngle)
		LUA_METHOD_DECL(GetGradientAngle)
		LUA_METHOD_DECL(SetEnabledStroke)
		LUA_METHOD_DECL(GetEnabledStroke)
		LUA_METHOD_DECL(SetEnabledShadow)
		LUA_METHOD_DECL(GetEnabledShadow)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CLabelUI_h