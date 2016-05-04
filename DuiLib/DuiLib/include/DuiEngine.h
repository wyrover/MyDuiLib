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
	protected:
		static LPCTSTR GetCurMode();
		static CDuiString GetCurMemoryFile();
	private:
		static DWORD dwMask;
	};
}


#endif//_DuiEngine_H