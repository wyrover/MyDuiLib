#include "stdafx.h"

namespace DuiLib
{
	DWORD DuiEngine::dwMask = Invalid;

	BOOL DuiEngine::Initialize(DWORD nFlag)
	{
		dwMask = nFlag;
		HRESULT hr = ::OleInitialize(NULL);
		if (FAILED(hr))
			return FALSE;

		DuiLogger::Instance()->ConsoleToggle((dwMask & ConsoleOutput) != 0);
		DuiLogger::Instance()->VSOutputToggle((dwMask & VsOutput) != 0);
		if ((UseWke & dwMask) != 0)
		{
			CWkeWebkitUI::WkeWebkit_Init();
		}

		TCHAR szDuiLib[2048] = { 0 };
		_stprintf(szDuiLib, _T("\r\n\
------------------DuiLib----------------------\r\n\
Version: %s\r\n\
Comment: %s\r\n\
\r RunMode: %s\r\n\
\r Application: %s\r\n\
\r MemoryTracer: %s\r\n\
\r\n-----------------------------------LogBegin\r\n"),
DuiSystem::Instance()->GetVersion(),
DuiSystem::Instance()->GetComment(),
GetCurMode(), 
PathUtil::GetCurAppName(FALSE).GetData(),
GetCurMemoryFile().GetData());

		DuiLogger::Instance()->logMessage(szDuiLib);


		return TRUE;
	}

	BOOL DuiEngine::Unitialize()
	{
		if ((UseWke & dwMask) != 0)
		{
			CWkeWebkitUI::WkeWebkit_Shutdown();
		}
		::OleUninitialize();
		return TRUE;
	}

	LPCTSTR DuiEngine::GetCurMode()
	{
#ifdef _UNICODE
#ifdef _DEBUG
		return _T("Target = WIN32, CharSet = UNICODE, Mode = Debug");
#else
		return _T("Target = WIN32, CharSet = UNICODE, Mode = Release");
#endif
#else
#ifdef _DEBUG
		return _T("Target = WIN32, CharSet = MutiChar, Mode = Debug");
#else
		return _T("Target = WIN32, CharSet = MutiChar, Mode = Release");
#endif
#endif
	}

	CDuiString DuiEngine::GetCurMemoryFile()
	{
		return DuiMemeryLooker::Instance()->GetCurMemoryFile();
	}
}