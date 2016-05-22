#ifndef _LuaCMarkup_H
#define _LuaCMarkup_H
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CMarkup, Markup, CMarkup, Markup, CMarkup)
	{
	public:
		LUA_METHOD_DECL(isnil)
		LUA_METHOD_DECL(_gc)
		LUA_METHOD_DECL(_eq)
		LUA_METHOD_DECL(_tostring)
		LUA_METHOD_DECL(Delete)
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetClass)
		LUA_METHOD_DECL(Load)
		LUA_METHOD_DECL(LoadFromMem)
		LUA_METHOD_DECL(LoadFromFile)
		LUA_METHOD_DECL(Release)
		LUA_METHOD_DECL(IsValid)
		LUA_METHOD_DECL(SetPreserveWhitespace)
		LUA_METHOD_DECL(GetLastErrorMessage)
		LUA_METHOD_DECL(GetLastErrorLocation)
		LUA_METHOD_DECL(GetRoot)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CMarkupNode, MarkupNode, CMarkupNode, MarkupNode, CMarkupNode)
	{
	public:
		LUA_METHOD_DECL(isnil)
		LUA_METHOD_DECL(_gc)
		LUA_METHOD_DECL(_eq)
		LUA_METHOD_DECL(_tostring)
		LUA_METHOD_DECL(Delete)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GetClass)
		LUA_METHOD_DECL(GetParent)
		LUA_METHOD_DECL(GetSibling)
		LUA_METHOD_DECL(GetChild)
		LUA_METHOD_DECL(HasSiblings)
		LUA_METHOD_DECL(HasChildren)
		LUA_METHOD_DECL(GetName)
		LUA_METHOD_DECL(GetValue)
		LUA_METHOD_DECL(HasAttributes)
		LUA_METHOD_DECL(HasAttribute)
		LUA_METHOD_DECL(GetAttributeCount)
		LUA_METHOD_DECL(GetAttributeName)
		LUA_METHOD_DECL(GetAttributeValue1)
		LUA_METHOD_DECL(GetAttributeValue2)
		LUA_METHOD_DECL(GetAttributeValue3)
		LUA_METHOD_DECL(GetAttributeValue4)

		LUA_CLASS_REG_DECL()
	};
}

#endif//_LuaCMarkup_H