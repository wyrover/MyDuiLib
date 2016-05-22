#ifndef _DuiEngine_H
#define _DuiEngine_H

#pragma once

namespace DuiLib
{
	class UILIB_API DuiEngine
	{
	public:
		static BOOL Initialize(DWORD nFlag = 0);
		static BOOL Unitialize();
		static void ConsoleLogAndVsOutput(DWORD dwFlag);
		static BOOL ConsoleLog();
		static BOOL VsOutputLog();
	protected:
		static LPCTSTR GetCurMode();
		static CDuiString GetCurMemoryFile();
	private:
		static DWORD dwMask;
	};
}


#endif//_DuiEngine_H