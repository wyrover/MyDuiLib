// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

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

#define  _CONSOLE
#define _VSOUTPUT

#include "LuaEntry.h"
using namespace DuiLib;
 #ifdef _DEBUG
 #   ifdef _UNICODE
 #       pragma comment(lib, "DuiLib_ud.lib")
 #   else
 #       pragma comment(lib, "DuiLib_d.lib")
 #   endif
 #else
 #   ifdef _UNICODE
 #       pragma comment(lib, "DuiLib_u.lib")
 #   else
 #       pragma comment(lib, "DuiLib.lib")
 #   endif
 #endif

//#ifdef _DEBUG
//#pragma comment( linker, "/subsystem:console /entry:wWinMainCRTStartup" )
//#endif
// ------------------------------------------------------------
// ---------------------- new and delete ----------------------
// ------------------------------------------------------------
// ---------------------------------------- operator new
inline void * operator new (size_t size, const char* file, const size_t line, const char* func)
{
	void *p = malloc(size);
	if (p == NULL) throw std::bad_alloc();

	DuiLib::DuiMemeryLooker::Instance()->_recordAlloc(p, size, file, line, func);

	return p;
}
// ---------------------------------------- operator new[]
inline void * operator new [](size_t size, const char* file, const size_t line, const char* func)
{
	void *p = malloc(size);
	if (p == NULL) throw std::bad_alloc();
	DuiLib::DuiMemeryLooker::Instance()->_recordAlloc(p, size, file, line, func);

	return p;
}
////inline void * operator new(size_t size)
////{
////	void *p = malloc(size);
////	if (p == NULL) throw std::bad_alloc();
////	DuiLib::DuiMemeryLooker::Instance()->_recordAlloc(p, size);
////
////	return p;
////}
////inline void * operator new[](size_t size)
////{
////	void *p = malloc(size);
////	if (p == NULL) throw std::bad_alloc();
////	DuiLib::DuiMemeryLooker::Instance()->_recordAlloc(p, size);
////
////	return p;
////}
// ---------------------------------------- operator delete
inline void operator delete (void * pointer, size_t size)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(pointer);
	free(pointer);
}
inline void operator delete(void* pointer)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(pointer);
	free(pointer);
}

inline void operator delete[](void* pointer)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(pointer);
	free(pointer);
}
// ---------------------------------------- operator delete[]
inline void operator delete[](void * pointer, size_t size)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(pointer);
	free(pointer);
}
inline void operator delete(void *p, size_t size, const char *file, const size_t line, const char* func)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(p);
	free(p);
}

inline void operator delete[](void *p, size_t size, const char *file, const size_t line, const char* func)
{
	DuiLib::DuiMemeryLooker::Instance()->_recordDealloc(p);
	free(p);
}


 #define MC_NEW  new(__FILE__, __LINE__,__FUNCTION__)
 #define new  MC_NEW