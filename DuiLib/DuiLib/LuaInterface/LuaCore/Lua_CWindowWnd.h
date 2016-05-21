#ifndef _LuaCWindowWnd_H
#define _LuaCWindowWnd_H
#pragma once

namespace DuiLib
{
	LUA_CLASS(CNotifyPump)
	{
	public:
		LUA_METHOD_DECL(AddVirtualWnd)
		LUA_METHOD_DECL(RemoveVirtualWnd)
		LUA_METHOD_DECL(NotifyPump)
		LUA_METHOD_DECL(LoopDispatch)

		LUA_CLASS_REG_DECL()
	};

	LUA_CLASS(CWindowWnd)
	{
	public:
		LUA_METHOD_DECL(GetClassName)
		LUA_METHOD_DECL(isnil)
		LUA_METHOD_DECL(_gc)
		LUA_METHOD_DECL(_eq)
		LUA_METHOD_DECL(_tostring)
		LUA_METHOD_DECL(Delete)
		
		LUA_METHOD_DECL(GetHWND)
		LUA_METHOD_DECL(RegisterWindowClass)
		LUA_METHOD_DECL(RegisterSuperclass)
		LUA_METHOD_DECL(Create)
		LUA_METHOD_DECL(Create2)
		LUA_METHOD_DECL(CreateDuiWindow)
		LUA_METHOD_DECL(Subclass)
		LUA_METHOD_DECL(Unsubclass)

		LUA_METHOD_DECL(ShowWindow)
		LUA_METHOD_DECL(ShowModal)
		LUA_METHOD_DECL(Close)
		LUA_METHOD_DECL(CenterWindow)

		LUA_METHOD_DECL(SetIcon)
		LUA_METHOD_DECL(SendMessage)
		LUA_METHOD_DECL(PostMessage)
		LUA_METHOD_DECL(ResizeClient)

		LUA_CLASS_REG_DECL()
	};
}

#endif//_LuaCWindowWnd_H