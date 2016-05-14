#include "UIlib.h"
#include "DuiSystem.h"

#include <Shlwapi.h>

namespace DuiLib
{
	DuiSystem::DuiSystem()
	{}
	DuiSystem::~DuiSystem()
	{}

	DWORD DuiSystem::GetDllVersion(LPCTSTR lpszDllName)
	{
		HINSTANCE hinstDll;
		DWORD dwVersion = 0;

		/* For security purposes, LoadLibrary should be provided with a fully-qualified
		path to the DLL. The lpszDllName variable should be tested to ensure that it
		is a fully qualified path before it is used. */
		hinstDll = ::LoadLibrary(lpszDllName);

		if (hinstDll)
		{
			DLLGETVERSIONPROC pDllGetVersion;
			pDllGetVersion = (DLLGETVERSIONPROC)GetProcAddress(hinstDll, "DllGetVersion");

			/* Because some DLLs might not implement this function, you must test for
			it explicitly. Depending on the particular DLL, the lack of a DllGetVersion
			function can be a useful indicator of the version. */

			if (pDllGetVersion)
			{
				DLLVERSIONINFO2 dvi;
				HRESULT hr;

				ZeroMemory(&dvi, sizeof(dvi));
				dvi.info1.cbSize = sizeof(dvi);

				hr = (*pDllGetVersion)(&dvi.info1);

				if (SUCCEEDED(hr))
				{
					dwVersion = MAKELONG(dvi.info1.dwMinorVersion, dvi.info1.dwMajorVersion);
				}
			}
			::FreeLibrary(hinstDll);
		}
		return dwVersion;
	}

	BOOL DuiSystem::IsWow64()
	{
		HMODULE hModule = GetModuleHandle(_T("kernel32"));
		if (!hModule) return FALSE;
		typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
		LPFN_ISWOW64PROCESS fnIsWow64Process;
		BOOL bIsWow64 = FALSE;
		fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(hModule, "IsWow64Process");
		if (NULL != fnIsWow64Process)
		{
			fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
		}
		return bIsWow64;
	}

	BOOL  DuiSystem::IsWindow7()
	{
		OSVERSIONINFO ovi = { sizeof(OSVERSIONINFO) };
		BOOL bRet = ::GetVersionEx(&ovi);
		return ((bRet != FALSE) && (ovi.dwMajorVersion == 6) && (ovi.dwMinorVersion >= 1));
	}
	BOOL  DuiSystem::IsVista()
	{
		OSVERSIONINFO ovi = { sizeof(OSVERSIONINFO) };
		BOOL bRet = ::GetVersionEx(&ovi);
		return ((bRet != FALSE) && (ovi.dwMajorVersion >= 6));
	}
	BOOL DuiSystem::IsAdmin()
	{
		BOOL bIsElevated = FALSE;
		HANDLE hToken = NULL;
		UINT16 uWinVer = LOWORD(GetVersion());
		uWinVer = MAKEWORD(HIBYTE(uWinVer), LOBYTE(uWinVer));

		if (uWinVer < 0x0600)
			return FALSE;

		if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
		{
			struct {
				DWORD TokenIsElevated;
			}te;
			DWORD dwReturnLength = 0;

			if (GetTokenInformation(hToken,/*TokenElevation*/(_TOKEN_INFORMATION_CLASS)20, &te, sizeof(te), &dwReturnLength)) {
				if (dwReturnLength == sizeof(te))
					bIsElevated = te.TokenIsElevated;
			}
			CloseHandle(hToken);
		}
		return bIsElevated;
	}

	WORD DuiSystem::HKF2SDK(WORD mod)
	{
		return ((mod & HOTKEYF_ALT) ? MOD_ALT : 0) \
			| ((mod & HOTKEYF_CONTROL) ? MOD_CONTROL : 0) \
			| ((mod & HOTKEYF_SHIFT) ? MOD_SHIFT : 0);
	}
	WORD DuiSystem::SDK2HKF(WORD mod)
	{
		return ((mod & MOD_ALT) ? HOTKEYF_ALT : 0) \
			| ((mod & MOD_CONTROL) ? HOTKEYF_CONTROL : 0) \
			| ((mod & MOD_SHIFT) ? HOTKEYF_SHIFT : 0);
	}

	BOOL DuiSystem::OpenUrl(LPCTSTR lpUrl)
	{
		ASSERT(lpUrl);
		SHELLEXECUTEINFO ShellInfo = { 0 };
		ShellInfo.cbSize = sizeof(ShellInfo);
		ShellInfo.hwnd = NULL;
		ShellInfo.lpVerb = _T("open");
		ShellInfo.lpFile = lpUrl;
		ShellInfo.nShow = SW_SHOWNORMAL;
		ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;

		return ::ShellExecuteEx(&ShellInfo);
	}

	BOOL DuiSystem::ReStartApp(LPCTSTR lpCmd, BOOL isAdmin/* = FALSE*/)
	{
		TCHAR s_exeFileName[MAX_PATH] = { 0 };
		DWORD n_result = ::GetModuleFileName(NULL, s_exeFileName, sizeof(TCHAR)* MAX_PATH);

		SHELLEXECUTEINFO ShellInfo = { 0 };
		ShellInfo.cbSize = sizeof(ShellInfo);
		ShellInfo.hwnd = NULL;
		ShellInfo.lpVerb = ((this->IsVista() && isAdmin) ? _T("runas") : _T("open"));
		ShellInfo.lpFile = s_exeFileName;
		ShellInfo.nShow = SW_SHOWNORMAL;
		ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShellInfo.lpParameters = lpCmd;

		return ::ShellExecuteEx(&ShellInfo);
	}

	BOOL DuiSystem::DllRegisterServer(LPCTSTR lpszFileName, BOOL bUnregister)
	{
		typedef HRESULT(WINAPI * FREG)();

		BOOL bRet = FALSE;

		HMODULE hDLL = ::LoadLibrary(lpszFileName);
		if (NULL == hDLL)
			return FALSE;

		CHAR * lpszFuncName;
		if (!bUnregister)
			lpszFuncName = "DllRegisterServer";
		else
			lpszFuncName = "DllUnregisterServer";

		FREG lpfunc = (FREG)::GetProcAddress(hDLL, lpszFuncName);
		if (lpfunc != NULL)
		{
			lpfunc();
			bRet = TRUE;
		}

		::FreeLibrary(hDLL);

		return bRet;
	}

	BOOL DuiSystem::DllRegisterServer(LPCTSTR lpszFileName)
	{
		return DllRegisterServer(lpszFileName, FALSE);
	}

	BOOL DuiSystem::DllUnregisterServer(LPCTSTR lpszFileName)
	{
		return DllRegisterServer(lpszFileName, TRUE);
	}
}