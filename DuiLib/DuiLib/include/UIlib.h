// Copyright (c) 2010-2011, duilib develop team(www.duilib.com).
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or 
// without modification, are permitted provided that the 
// following conditions are met.
//
// Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above 
// copyright notice, this list of conditions and the following
// disclaimer in the documentation and/or other materials 
// provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
// CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#if defined(UILIB_EXPORTS)
#if defined(_MSC_VER)
#define UILIB_API __declspec(dllexport)
#else
#define UILIB_API 
#endif
#else
#if defined(_MSC_VER)
#define UILIB_API __declspec(dllimport)
#else
#define UILIB_API 
#endif
#endif

#define UILIB_COMDAT __declspec(selectany)

#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */

#ifdef __GNUC__
// 怎么都没找到min，max的头文件-_-
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#endif

#ifndef __FILET__
#define __DUILIB_STR2WSTR(str)	L##str
#define _DUILIB_STR2WSTR(str)	__DUILIB_STR2WSTR(str)
#ifdef _UNICODE
#define __FILET__	_DUILIB_STR2WSTR(__FILE__)
#define __FUNCTIONT__	_DUILIB_STR2WSTR(__FUNCTION__)
#else
#define __FILET__	__FILE__
#define __FUNCTIONT__	__FUNCTION__
#endif
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stddef.h>
#include <richedit.h>
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>

#include "DuiType.h"

#include "IDuiObject.h"
#include "DuiEngine.h"
#include "Utils/IOBase.h"
#include "Utils/IOStream.h"
#include "Utils/ILogger.h"
#include "Utils/ILock.h"
#include "Utils/Singleton.h"
#include "Utils/SharedPtr.h"
#include "Utils/DuiSystem.h"
#include "Utils/Utils.h"
#include "Utils/UIDelegate.h"
#include "Utils/UIReflection.h"
#include "Core/UIMemLooker.h"
#include "Core/UIDefine.h"
#include "Core/UITrayIcon.h"
#include "Core/UIManager.h"
#include "Core/UIBase.h"
#include "Core/UIControl.h"
#include "Core/UIContainer.h"
#include "Core/UIMarkup.h"
#include "Core/UIDlgBuilder.h"
#include "Core/UIRender.h"
#include "Core/UITimer.h"
#include "Utils/IDuiWindow.h"
#include "Utils/Window.h"
#include "Utils/FileDialog.h"
#include "Utils/PathUtil.h"
#include "Utils/WebBrowserEventHandler.h"
#include "Utils/FlashEventHandler.h"
#include "Utils/UIUserControl.h"

#include "CommonInclude.h"
#include "ControlInclude.h"
#include "ExtendInclude.h"
#include "Utils/RichEditUtil.h"
//#include "LuaInclude.h"
#include "NetInclude.h"

extern HINSTANCE g_dllModule ;


#ifdef _USE_DUILIB_
#if defined(_DEBUG)
	#ifdef USE_STATIC_LIB
		#if defined(_UNICODE)
			#pragma comment(lib,"DuiLib_ud_s.lib")
		#else
			#pragma comment(lib,"DuiLib_d_s.lib")
		#endif
	#else
		#if defined(_UNICODE)
			#pragma comment(lib,"DuiLib_ud.lib")
		#else
			#pragma comment(lib,"DuiLib_d.lib")
		#endif
	#endif
#else
	#ifdef USE_STATIC_LIB
		#if defined(_UNICODE)
			#pragma comment(lib,"DuiLib_u_s.lib")
		#else
			#pragma comment(lib,"DuiLib_s.lib")
		#endif
	#else
		#if defined(_UNICODE)
			#pragma comment(lib,"DuiLib_u.lib")
		#else
			#pragma comment(lib,"DuiLib.lib")
		#endif
	#endif
#endif
#endif
