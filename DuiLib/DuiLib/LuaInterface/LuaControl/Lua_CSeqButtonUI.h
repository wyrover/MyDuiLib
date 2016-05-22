#ifndef _Lua_CSeqButtonUI_h
#define _Lua_CSeqButtonUI_h
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CSeqButtonUI, SeqButtonUI, CSeqButtonUI, ButtonUI, CButtonUI)
	{
	public:
		
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(SetSeqImages)
		LUA_METHOD_DECL(GetSeqImages)
		LUA_METHOD_DECL(SetTotalFrameCnt)
		LUA_METHOD_DECL(GetTotalFrameCnt)
		LUA_METHOD_DECL(IsAnimationing)

		LUA_CLASS_REG_DECL()
	};
}


#endif//_Lua_CSeqButtonUI_h