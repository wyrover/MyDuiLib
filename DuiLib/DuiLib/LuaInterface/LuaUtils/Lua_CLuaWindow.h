#ifndef _LuaWindowExport_H
#define _LuaWindowExport_H
#pragma once
#include "LuaDefine.h"

namespace DuiLib
{
	LUA_CLASS(CLuaWindow, LuaWindow, CLuaWindow, WindowWnd, CWindowWnd)
	{
	public:
			LUA_METHOD_DECL(New)

			LUA_METHOD_DECL(_tostring)
	
			LUA_METHOD_DECL(GetWindowClassName)
			LUA_METHOD_DECL(GetClassStyle)
			LUA_METHOD_DECL(GetStyle)
			LUA_METHOD_DECL(GetExStyle)
			LUA_METHOD_DECL(ModifyStyle)
			LUA_METHOD_DECL(ModifyStyleEx)

			LUA_METHOD_DECL(DestroyWindow)
			LUA_METHOD_DECL(MoveWindow)
			LUA_METHOD_DECL(MoveWindowEx)
			LUA_METHOD_DECL(MoveWindowToPoint)
			LUA_METHOD_DECL(SetWindowPos)
			LUA_METHOD_DECL(SetWindowPosEx)
			LUA_METHOD_DECL(ArrangeIconicWindows)

			LUA_METHOD_DECL(ForegroundWindow)
			LUA_METHOD_DECL(BringWindowToTop)
			LUA_METHOD_DECL(GetWindowRect)
			LUA_METHOD_DECL(GetClientRect)
			LUA_METHOD_DECL(ClientToScreenForPoint)
			LUA_METHOD_DECL(ClientToScreenForRect)
			LUA_METHOD_DECL(ScreenToClientForPoint)
			LUA_METHOD_DECL(ScreenToClientForRect)
			LUA_METHOD_DECL(MapWindowPoints)
			LUA_METHOD_DECL(MapWindowPoints2)
			LUA_METHOD_DECL(UpdateWindow)

			LUA_METHOD_DECL(SetRedraw)
			LUA_METHOD_DECL(Invalidate)
			LUA_METHOD_DECL(InvalidateRect)
			LUA_METHOD_DECL(ValidateRect)
			LUA_METHOD_DECL(InvalidateRgn)
			LUA_METHOD_DECL(ValidateRgn)
			LUA_METHOD_DECL(IsWindow)
			LUA_METHOD_DECL(IsIconic)
			LUA_METHOD_DECL(IsZoomed)
			LUA_METHOD_DECL(IsWindowEnabled)
			LUA_METHOD_DECL(EnableWindow)
			LUA_METHOD_DECL(IsWindowVisible)
			LUA_METHOD_DECL(IsWindowUnicode)
			LUA_METHOD_DECL(IsParentDialog)

			LUA_METHOD_DECL(SetTimer)
			LUA_METHOD_DECL(KillTimer)
			LUA_METHOD_DECL(SetActiveWindow)
			LUA_METHOD_DECL(SetCapture)
			LUA_METHOD_DECL(SetFocus)
			LUA_METHOD_DECL(IsChild)
			LUA_METHOD_DECL(GetTopLevelWindow)
			LUA_METHOD_DECL(GetTopLevelParent)
			LUA_METHOD_DECL(GetParent)
			LUA_METHOD_DECL(SetParent)
			LUA_METHOD_DECL(FlashWindow)
			LUA_METHOD_DECL(AnimateWindow)
			LUA_METHOD_DECL(FadeInOut)
			LUA_METHOD_DECL(ShakeWindow)
			LUA_METHOD_DECL(FindControl)
			LUA_METHOD_DECL(MsgBox)

			LUA_METHOD_DECL(SetHotKey)
			LUA_METHOD_DECL(GetHotKey)
			LUA_METHOD_DECL(IsMainThread)
			LUA_METHOD_DECL(GetWindowThreadID)
			LUA_METHOD_DECL(GetWindowProcessID)
			LUA_METHOD_DECL(GetFont)
			LUA_METHOD_DECL(SetWindowText)
			LUA_METHOD_DECL(GetWindowText)
			LUA_METHOD_DECL(GetWindowTextLength)
			LUA_METHOD_DECL(LoadIcon)
			LUA_METHOD_DECL(LoadIconEx)
			LUA_METHOD_DECL(SetIcon)
			LUA_METHOD_DECL(GetIcon)
			LUA_METHOD_DECL(RegisterSkin)
			LUA_METHOD_DECL(UnRegisterSkin)
			LUA_METHOD_DECL(GetTag)
			LUA_METHOD_DECL(SetTag)

			LUA_METHOD_DECL(ExistsSkinFile)
			LUA_METHOD_DECL(GetPaintMgr)
			LUA_METHOD_DECL(IsValid)
			LUA_METHOD_DECL(ControlFromPtr)

			LUA_METHOD_DECL(SetListCallback)
			LUA_METHOD_DECL(AddPreMessageFilter)
			LUA_METHOD_DECL(AddMessageFilter)
			LUA_METHOD_DECL(AddNotifier)
			LUA_METHOD_DECL(ListenUIEvent)
			LUA_METHOD_DECL(ListenUIDestroy)
			LUA_METHOD_DECL(TouchMsgTable)


			LUA_CLASS_REG_DECL()
	};
};

#endif//_LuaWindowExport_H