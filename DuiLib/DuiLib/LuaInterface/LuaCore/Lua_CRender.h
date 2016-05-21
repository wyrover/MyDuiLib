#ifndef _LuaCRender_H
#define _LuaCRender_H
#pragma once

namespace DuiLib
{
	LUA_CLASS(CRenderClip)
	{
	public:
		LUA_METHOD_DECL(isnil)
		LUA_METHOD_DECL(_gc)
		LUA_METHOD_DECL(_eq)
		LUA_METHOD_DECL(_tostring)
		LUA_METHOD_DECL(Delete)
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(GenerateClip)
		LUA_METHOD_DECL(GenerateRoundClip)
		LUA_METHOD_DECL(UseOldClipBegin)
		LUA_METHOD_DECL(UseOldClipEnd)

		LUA_METHOD_DECL(getRectItem)
		LUA_METHOD_DECL(getHDC)
		LUA_METHOD_DECL(getHRGN)
		LUA_METHOD_DECL(getOldHRGN)

		LUA_METHOD_DECL(setRectItem)
		LUA_METHOD_DECL(setHDC)
		LUA_METHOD_DECL(setHRGN)
		LUA_METHOD_DECL(setOldHRGN)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CRenderEngine)
	{
	public:
		LUA_METHOD_DECL(AdjustColor)
		LUA_METHOD_DECL(LoadBitmap)
		LUA_METHOD_DECL(LoadImage)
		LUA_METHOD_DECL(FreeImage)
		LUA_METHOD_DECL(DrawImage)
		LUA_METHOD_DECL(DrawImageString)
		LUA_METHOD_DECL(DrawColor)
		LUA_METHOD_DECL(DrawGradient)
		LUA_METHOD_DECL(DrawLine)
		LUA_METHOD_DECL(DrawRect)
		LUA_METHOD_DECL(DrawRoundRect)
		LUA_METHOD_DECL(DrawText)
		LUA_METHOD_DECL(DrawHtmlText)
		LUA_METHOD_DECL(GenerateBitmap)
		LUA_METHOD_DECL(GetTextSize)

		LUA_CLASS_REG_DECL()
	};
}

#endif//_LuaCRender_H