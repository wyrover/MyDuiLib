#ifndef _LuaStruct_H
#define _LuaStruct_H
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(TNotifyUI, NotifyUI, TNotifyUI, NotifyUI, TNotifyUI)
	{
	public:
		LUA_METHOD_DECL(isnil)
		LUA_METHOD_DECL(_gc)
		LUA_METHOD_DECL(_eq)
		LUA_METHOD_DECL(_tostring)
		LUA_METHOD_DECL(Delete)
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(getType)
		LUA_METHOD_DECL(getVirtualWnd)
		LUA_METHOD_DECL(getSender)
		LUA_METHOD_DECL(getTimestamp)
		LUA_METHOD_DECL(getPtMouse)
		LUA_METHOD_DECL(getWParam)
		LUA_METHOD_DECL(getLParam)
		LUA_METHOD_DECL(setType)
		LUA_METHOD_DECL(setVirtualWnd)
		LUA_METHOD_DECL(setSender)
		LUA_METHOD_DECL(setTimestamp)
		LUA_METHOD_DECL(setPtMouse)
		LUA_METHOD_DECL(setWParam)
		LUA_METHOD_DECL(setLParam)
		LUA_METHOD_DECL(isType)
		LUA_METHOD_DECL(isControl)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(TFontInfo, FontInfo, TFontInfo, FontInfo, TFontInfo)
	{
	public:
		LUA_METHOD_DECL(isnil)
		LUA_METHOD_DECL(_gc)
		LUA_METHOD_DECL(_eq)
		LUA_METHOD_DECL(_tostring)
		LUA_METHOD_DECL(Delete)
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(getFont)
		LUA_METHOD_DECL(getFontName)
		LUA_METHOD_DECL(getSize)
		LUA_METHOD_DECL(getBold)
		LUA_METHOD_DECL(getUnderline)
		LUA_METHOD_DECL(getItalic)
		LUA_METHOD_DECL(getTextmetric)
		LUA_METHOD_DECL(setFont)
		LUA_METHOD_DECL(setFontName)
		LUA_METHOD_DECL(setSize)
		LUA_METHOD_DECL(setBold)
		LUA_METHOD_DECL(setUnderline)
		LUA_METHOD_DECL(setItalic)
		LUA_METHOD_DECL(setTextmetric)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(TImageInfo, ImageInfo, TImageInfo, ImageInfo, TImageInfo)
	{
	public:
		LUA_METHOD_DECL(isnil)
		LUA_METHOD_DECL(_gc)
		LUA_METHOD_DECL(_eq)
		LUA_METHOD_DECL(_tostring)
		LUA_METHOD_DECL(Delete)
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(getBitmap)
		LUA_METHOD_DECL(getX)
		LUA_METHOD_DECL(getY)
		LUA_METHOD_DECL(getAlphaChannel)
		LUA_METHOD_DECL(getResType)
		LUA_METHOD_DECL(getMask)
		LUA_METHOD_DECL(setBitmap)
		LUA_METHOD_DECL(setX)
		LUA_METHOD_DECL(setY)
		LUA_METHOD_DECL(setAlphaChannel)
		LUA_METHOD_DECL(setResType)
		LUA_METHOD_DECL(setMask)
		
		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(TEventUI, EventUI, TEventUI, EventUI, TEventUI)
	{
	public:
		LUA_METHOD_DECL(isnil)
		LUA_METHOD_DECL(_gc)
		LUA_METHOD_DECL(_eq)
		LUA_METHOD_DECL(_tostring)
		LUA_METHOD_DECL(Delete)
		LUA_METHOD_DECL(New)
		LUA_METHOD_DECL(getType)
		LUA_METHOD_DECL(getSender)
		LUA_METHOD_DECL(getTimestamp)
		LUA_METHOD_DECL(getPtMouse)
		LUA_METHOD_DECL(getChKey)
		LUA_METHOD_DECL(getKeyState)
		LUA_METHOD_DECL(getWParam)
		LUA_METHOD_DECL(getLParam)
		LUA_METHOD_DECL(setType)
		LUA_METHOD_DECL(setSender)
		LUA_METHOD_DECL(setTimestamp)
		LUA_METHOD_DECL(setPtMouse)
		LUA_METHOD_DECL(setChKey)
		LUA_METHOD_DECL(setKeyState)
		LUA_METHOD_DECL(setWParam)
		LUA_METHOD_DECL(setLParam)
		
		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(DuiLib, DuiLib, DuiLib, DuiLib, DuiLib)
	{
		LUA_METHOD_DECL(MsgBox)
		LUA_METHOD_DECL(TraceMsg)
		LUA_METHOD_DECL(QuitApp)
	public:
		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(MsgArgs, MsgArgs, MsgArgs, MsgArgs, MsgArgs)
	{
	public:
		LUA_CLASS_REG_DECL()
	};

	
	LUA_CLASS(EventMarco, EventMarco, EventMarco, EventMarco, EventMarco)
	{
	public:
		LUA_CLASS_REG_DECL()
	};
}

#endif//_LuaStruct_H