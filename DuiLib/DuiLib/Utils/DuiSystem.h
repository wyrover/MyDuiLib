#ifndef DuiSystem__h_
#define DuiSystem__h_
#pragma once

/*
* 类名：DuiSystem
* 作用：提供获取操作系统信息接口，单例模式。(暂时没有写全)
* 接口：
*/

namespace DuiLib
{
	#define DUI_VERSION	_T("2.1.0.1")
	#define DUI_COMMENT _T("Copyright (c) 2010-2015,\
duilib develop team(www.duilib.com) All rights reserved.")

	class UILIB_API DuiSystem : public Singleton<DuiSystem>
	{
		DECLARE_SINGLETON_CLASS(DuiSystem)
	public:
		DuiSystem();
		~DuiSystem();
	public:
		LPCTSTR GetVersion(){ return DUI_VERSION; }
		LPCTSTR GetComment(){ return DUI_COMMENT; }
	public:
		DWORD GetDllVersion(LPCTSTR lpszDllName);
		BOOL  IsWindow7();
		BOOL  IsVista();
		BOOL  IsAdmin();
		BOOL  IsWow64();

		WORD HKF2SDK(WORD mod);
		WORD SDK2HKF(WORD mod);
		BOOL OpenUrl(LPCTSTR lpUrl);
		BOOL ReStartApp(LPCTSTR lpCmd, BOOL isAdmin = FALSE);

		BOOL DllRegisterServer(LPCTSTR lpszFileName);
		BOOL DllUnregisterServer(LPCTSTR lpszFileName);
	protected:
		BOOL DllRegisterServer(LPCTSTR lpszFileName, BOOL bUnregister);
	private:
		
	};
}

#endif//DuiSystem__h_