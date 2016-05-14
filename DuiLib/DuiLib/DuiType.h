#ifndef _DuiType_H
#define _DuiType_H
#pragma once

#include <sstream>
#include <vector>
#include <string>

namespace DuiLib
{

	/********************************************************************************

	Base integer types for all target OS's and CPU's

	UInt8            8-bit unsigned integer
	SInt8            8-bit signed integer
	UInt16          16-bit unsigned integer
	SInt16          16-bit signed integer
	UInt32          32-bit unsigned integer
	SInt32          32-bit signed integer
	UInt64          64-bit unsigned integer
	SInt64          64-bit signed integer

	*********************************************************************************/
	typedef unsigned char                   dui_uchar;
	typedef unsigned short                  dui_ushort;
	typedef unsigned int                    dui_uint;
	typedef unsigned long                   dui_ulong;

	typedef signed char                     dui_int8;
	typedef dui_uchar                       dui_uint8;
	typedef signed short                    dui_int16;
	typedef dui_ushort                      dui_uint16;

#ifdef __LP64__
	typedef signed int                      dui_int32;
	typedef dui_uint                        dui_uint32;
#else
	typedef signed long                     dui_int32;
	typedef unsigned long                   dui_uint32;
#endif

#if defined(_MSC_VER) && !defined(__MWERKS__) && defined(_M_IX86)
	typedef   signed __int64                dui_int64;
	typedef unsigned __int64                dui_uint64;
#else
	typedef   signed long long              dui_int64;
	typedef unsigned long long              dui_uint64;
#endif

	typedef unsigned int		dui_dword;
	typedef int					dui_bool;
	typedef unsigned char		dui_byte;
	typedef unsigned short		dui_word;

	typedef dui_uint8		dui_UTF8;
	typedef dui_uint32	    dui_UTF32;
//////////////////////////////////////////////////////////////////////////
	typedef std::string dui_String;
	typedef std::wstring dui_WString;
	typedef std::vector<dui_String> dui_StringArray;
	typedef std::stringstream	dui_StringStream;
	typedef dui_String dui_UTF8String;
	typedef std::basic_string<dui_UTF32, std::char_traits<dui_UTF32> >	dui_UTF32String;
	typedef char dui_char;
	typedef wchar_t dui_wchar;

#if defined(UNICODE) || defined(_UNICODE)
	typedef dui_WString dui_stdstring;
	typedef dui_wchar dui_stdchar;

	#define dui_strftime           wcsftime
	#define dui_strcat             wcscat      
	#define dui_fopen              _wfopen

	#define dui_sprintf            wsprintf
	#define dui_fprintf            fwprintf
	#define dui_strrchr            wcsrchr
	#define dui_strncpy            wcsncpy
	#define dui_strlen             wcslen
	#define dui_strcmp             wcscmp
	#define dui_strcpy             lstrcpy
	#define dui_vfprintf           vfwprintf
#else
	typedef dui_String dui_stdstring;
	typedef dui_char   dui_stdchar;

	#define dui_strftime           strftime
	#define dui_strcat             strcat
	#define dui_fopen              fopen

	#define dui_sprintf            sprintf_s
	#define dui_fprintf            fprintf
	#define dui_strrchr            strrchr
	#define dui_strncpy            strncpy
	#define dui_strlen             strlen
	#define dui_strcmp             strcmp
	#define dui_strcpy             strcpy
	#define dui_vfprintf           vfprintf
#endif//Unicode

};

namespace DuiLib
{
	class IDuiObject;

	class critical_session;
	template <class T>
	class SharedPtr;
	
	class DuiEngine;
	class DuiSystem;

	class STRINGorID;
	class CPoint;
	class CSize;
	class CDuiRect;
	class CStdPtrArray;
	class CStdValArray;
	class CDuiString;
	class CStdStringPtrMap;
	class CWaitCursor;
	class CVariant;
	class CDuiImage;
	class CDuiImageEx;
	class DuiMemeryLooker;

	class CDelegateBase;
	class CEventSource;

	class CNotifyPump;
	class CWindowWnd;
	class INotifyUI;
	class IMessageFilterUI;
	class ITranslateAccelerator;
	class CTooptip;
	class CPaintManagerUI;

	class CMarkup;
	class CMarkupNode;

	class IDialogBuilderCustomHandle;
	class IDialogBuilderCallback;
	class CDialogBuilder;

	class CRenderClip;
	class CRenderEngine;

	class CDuiTimerBase;
	class IDuiTimer;
	class CDuiTimer;
	class CTimerSource;

	class IDuiWindow;
	class CWin;

	class OSTypeHelper;
	class IOStreamMaker;
	class ILogger;
	class DuiLogger;
	class ILock;
	class LockHelper;


	class PathUtil;
	class CWebBrowserEventHandler;
	class CFlashEventHandler;

	class IUIAnimation;
	class CUIAnimation;

	class CUIAnim;
	class CUIAnimHelper;
	class CFadeAnimation;
	class CSeqAnimation;

	class CTrayIconUI;
	class CControlUI;
	class CContainerUI;
	class CChildLayoutUI;
	class CTileLayoutUI;
	class CHorizontalLayoutUI;
	class CVerticalLayoutUI;
	class CTabLayoutUI;
	class CAnimationTabLayoutUI;
	class CActiveXUI;
	class CLabelUI;
	class CTextUI;
	class CButtonUI;
	class CFadeButtonUI;
	class CAlbumButtonUI;
	class CAnimControlUI;
	class COptionUI;
	class CRadioUI;
	class CCheckBoxUI;
	class CFadeOptionUI;
	class CFadeCheckBoxUI;
	class CComboUI;
	class CComboBoxUI;
	class CEditUI;
	class CRichEditUI;
	class CDateTimeUI;
	class CFlashUI;
	class CGifAnimUI;
	class CHotKeyUI;
	class CProgressUI;
	class CSliderUI;
	class CScrollBarUI;
	class CListContainerElementUI;
	class CListBodyUI;
	class CListHeaderUI;
	class CListUI;
	class CTreeNodeUI;
	class CTreeViewUI;

	class CSeqButtonUI;
	class CWebBrowserUI;
};




#endif//_DuiType_H