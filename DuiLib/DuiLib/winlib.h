//库文件
#pragma once
#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <objbase.h>
#include <zmouse.h>
#include <exdisp.h>
#include <comdef.h>
#include <vector>
#include <sstream>
// TODO: 在此处引用程序需要的其他头文件
#ifndef _USE_DUILIB_
#define _USE_DUILIB_
#endif

#define _DEBUG 

#define  _CONSOLE
#define _VSOUTPUT
#include "lua.hpp"
#include "UIlib.h"
using namespace DuiLib;
 #ifdef _DEBUG
 #   ifdef _UNICODE
 #       pragma comment(lib, "../../lib/DuiLib_ud.lib")
 #   else
 #       pragma comment(lib, "../../lib/DuiLib_d.lib")
 #   endif
 #else
 #   ifdef _UNICODE
 #       pragma comment(lib, "..\\Lib\\DuiLib_u.lib")
 #   else
 #       pragma comment(lib, "..\\Lib\\DuiLib.lib")
 #   endif
 #endif

#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"comdlg32.lib")
#pragma comment(lib,"advapi32.lib")
#pragma comment(lib,"shell32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"oleaut32.lib")
#pragma comment(lib,"uuid.lib")
#pragma comment(lib,"odbc32.lib")
#pragma comment(lib,"odbccp32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"D:\Program Files (x86)\Lua\5.1\lib\lua5.1.lib")