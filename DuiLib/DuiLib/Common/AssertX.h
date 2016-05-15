#ifndef __DUI_ASSERTX_H__
#define __DUI_ASSERTX_H__

#ifdef _MSC_VER
#pragma once
#endif

namespace DuiLib
{

#ifdef _UNICODE
	typedef wchar_t  local_char_type;
#else
	typedef char  local_char_type;
#endif

	// Assert function return values
	enum ErrRet
	{
		ERRRET_IGNORE = 0,
		ERRRET_CONTINUE,
		ERRRET_BREAKPOINT,
		ERRRET_ABORT
	};

	//- Global functions ----------------------------------------------------------
	UILIB_API ErrRet NotifyAssert(const local_char_type* condition, const local_char_type* fileName, int lineNumber, const local_char_type* formats, ...);


#if defined(_DEBUG) || defined(DEBUG)
	#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN64__)
        #define DuiAssertX(x, formats, ...) { \
		static bool _ignoreAssert = false; \
		if (!_ignoreAssert && !(x)) \
		{ \
			ErrRet _err_result = NotifyAssert(#x, __FILET__, __LINE__, formats, ##__VA_ARGS__); \
			if (_err_result == ERRRET_IGNORE) \
			{ \
				_ignoreAssert = true; \
			} \
			else if (_err_result == ERRRET_BREAKPOINT) \
			{ \
			__debugbreak(); \
			} \
		}}
	#else
		#define DuiAssertX(x, formats, ...) { \
		if (!(x)) \
		{ \
			CDuiString comment = CDuiString::FormatString(formats, ##__VA_ARGS__); \
			CDuiString msg; \
			if(!comment.IsEmpty()){ msg = CDuiString("Assert comment:") + comment + CDuiString("\n"); } \
#ifndef _UNICODE
			fprintf (stderr, _T("%s"), msg); \
#else
			fwprintf(stderr, _T("%s"), msg); \
#endif
			assert(x); \
			exit(-1);\
		}}

#	endif
#else
#		define DuiAssertX(x, formats, ...)
#endif

#if defined(_DEBUG) || defined(DEBUG)
#	define DuiAssert(x)		DuiAssertX(x, _T(""))
#else
#	define DuiAssert(x)
#endif
}

#endif
