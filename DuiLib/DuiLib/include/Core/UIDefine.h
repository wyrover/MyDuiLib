#ifndef _UIDefine_H
#define _UIDefine_H
#pragma once
//////////////BEGINÏûÏ¢Ó³Éäºê¶¨Òå////////////////////////////////////////////////////
///

namespace DuiLib
{
enum
{
	Invalid = 0 << 0,
	ConsoleOutput = 1 << 0,
	VsOutput = 1 << 1,
	UseWke = 1 << 2,


	ConsoleAndVsOutput = ConsoleOutput | VsOutput,
};


enum UILIB_RESOURCETYPE
{
	UILIB_FILE = 1,				// 来自磁盘文件
	UILIB_ZIP,						// 来自磁盘zip压缩包
	UILIB_RESOURCE,			// 来自资源
	UILIB_ZIPRESOURCE,	// 来自资源的zip压缩包
};
/////////////////////////////////////////////////////////////////////////////////////
//
#define UI_WNDSTYLE_CONTAINER  (0)
#define UI_WNDSTYLE_FRAME      (WS_VISIBLE | WS_OVERLAPPEDWINDOW)
#define UI_WNDSTYLE_CHILD      (WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#define UI_WNDSTYLE_DIALOG     (WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

#define UI_WNDSTYLE_EX_FRAME   (WS_EX_WINDOWEDGE)
#define UI_WNDSTYLE_EX_DIALOG  (WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)

#define UI_CLASSSTYLE_CONTAINER  (0)
#define UI_CLASSSTYLE_FRAME      (CS_VREDRAW | CS_HREDRAW)
#define UI_CLASSSTYLE_CHILD      (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)
#define UI_CLASSSTYLE_DIALOG     (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)


/////////////////////////////////////////////////////////////////////////////////////
//
#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)
#endif

#ifdef _DEBUG
#ifndef DUITRACE
#define DUITRACE DUI__Trace
#endif
#define DUITRACEMSG DUI__TraceMsg
#else
#ifndef DUITRACE
#define DUITRACE
#endif
#define DUITRACEMSG _T("")
#endif

void UILIB_API DUI__Trace(LPCTSTR pstrFormat, ...);
LPCTSTR UILIB_API DUI__TraceMsg(UINT uMsg);
/////////////////////////////////////////////////////////////////////////////////////
//
#define WM_EFFECTS		WM_USER+1680
#define WM_RELOADSTYLE	WM_USER+1681
#define WM_MOUSEINTRAYICON	WM_USER+1682
#define WM_MOUSEOUTTRAYICON	WM_USER+1683
/////////////////////////////////////////////////////////////////////////////////////
//
typedef enum EVENTTYPE_UI
{
	UIEVENT__ALL = 0,
	UIEVENT__FIRST = 1,
	UIEVENT__KEYBEGIN,
	UIEVENT_KEYDOWN,
	UIEVENT_KEYUP,
	UIEVENT_CHAR,
	UIEVENT_SYSKEY,
	UIEVENT__KEYEND,
	UIEVENT__MOUSEBEGIN,
	UIEVENT_MOUSEMOVE,
	UIEVENT_MOUSELEAVE,
	UIEVENT_MOUSEENTER,
	UIEVENT_MOUSEHOVER,
	UIEVENT_BUTTONDOWN,
	UIEVENT_BUTTONUP,
	UIEVENT_RBUTTONDOWN,
	UIEVENT_RBUTTONUP,
	UIEVENT_DBLCLICK,
	UIEVENT_RDBLCLICK,
	UIEVENT_CONTEXTMENU,
	UIEVENT_SCROLLWHEEL,
	UIEVENT__MOUSEEND,
	UIEVENT_KILLFOCUS,
	UIEVENT_SETFOCUS,
	UIEVENT_WINDOWSIZE,
	UIEVENT_SETCURSOR,
	UIEVENT_TIMER,
	UIEVENT_NOTIFY,
	UIEVENT_COMMAND,
	UIEVENT_RELOADSTYLE,
	UIEVENT__CUSTOMBEGIN,
	UIEVENT_TRAYICON,
	UIEVENT_MOUSEINTRAYICON,
	UIEVENT_MOUSEOUTTRAYICON,
	UIEVENT__CUSTOMEND,
	UIEVENT__LAST,
};

typedef enum EVENT_USER
{
	EVENT__ALL = WM_USER,
	EVENT_SOCKET,
	EVENT__LAST,
};
/////////////////////////////////////////////////////////////////////////////////////
//
// Flags for CControlUI::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004

// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_TOP_FIRST     0x00000008
#define UIFIND_ME_FIRST      0x80000000

// Flags for the CDialogLayout stretching
#define UISTRETCH_NEWGROUP   0x00000001
#define UISTRETCH_NEWLINE    0x00000002
#define UISTRETCH_MOVE_X     0x00000004
#define UISTRETCH_MOVE_Y     0x00000008
#define UISTRETCH_SIZE_X     0x00000010
#define UISTRETCH_SIZE_Y     0x00000020

// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_READONLY     0x00000020
#define UISTATE_CAPTURED     0x00000040

//////////////////////////////////////////////////////////////////////////
////
#define DUI_MSGTYPE_MAXMIN                   (_T("maxmin"))

#define DUI_MSGTYPE_MENU                   (_T("menu"))
#define DUI_MSGTYPE_LINK                   (_T("link"))

#define DUI_MSGTYPE_TIMER                  (_T("timer"))
#define DUI_MSGTYPE_CLICK                  (_T("click"))
#define DUI_MSGTYPE_RCLICK                  (_T("rclick"))
#define DUI_MSGTYPE_DBCLICK                (_T("dbclick"))
#define DUI_MSGTYPE_RDBCLICK                (_T("rdbclick"))

#define DUI_MSGTYPE_RETURN                 (_T("return"))
#define DUI_MSGTYPE_SCROLL                 (_T("scroll"))

#define DUI_MSGTYPE_DROPDOWN               (_T("dropdown"))
#define DUI_MSGTYPE_SETFOCUS               (_T("setfocus"))

#define DUI_MSGTYPE_KILLFOCUS              (_T("killfocus"))
#define DUI_MSGTYPE_ITEMCLICK 		   	   (_T("itemclick"))
#define DUI_MSGTYPE_TABSELECT              (_T("tabselect"))

#define DUI_MSGTYPE_ITEMSELECT 		   	   (_T("itemselect"))
#define DUI_MSGTYPE_ITEMEXPAND             (_T("itemexpand"))
#define DUI_MSGTYPE_WINDOWINIT             (_T("windowinit"))
#define DUI_MSGTYPE_BUTTONDOWN 		   	   (_T("buttondown"))
#define DUI_MSGTYPE_MOUSEENTER			   (_T("mouseenter"))
#define DUI_MSGTYPE_MOUSELEAVE			   (_T("mouseleave"))

#define DUI_MSGTYPE_TEXTCHANGED            (_T("textchanged"))
#define DUI_MSGTYPE_HEADERCLICK            (_T("headerclick"))
#define DUI_MSGTYPE_ITEMDBCLICK            (_T("itemdbclick"))
#define DUI_MSGTYPE_SHOWACTIVEX            (_T("showactivex"))

#define DUI_MSGTYPE_ITEMCOLLAPSE           (_T("itemcollapse"))
#define DUI_MSGTYPE_ITEMACTIVATE           (_T("itemactivate"))
#define DUI_MSGTYPE_VALUECHANGED           (_T("valuechanged"))

#define DUI_MSGTYPE_SELECTCHANGED 		   (_T("selectchanged"))
///////////////////////////////////////////////////////////////
///
//  4
#define  DUI_CTR_EDIT                            (_T("Edit"))
#define  DUI_CTR_LIST                            (_T("List"))
#define  DUI_CTR_TEXT                            (_T("Text"))

//5
#define  DUI_CTR_COMBO                           (_T("Combo"))
#define  DUI_CTR_LABEL                           (_T("Label"))
#define  DUI_CTR_FLASH							 (_T("Flash"))

//6
#define  DUI_CTR_BUTTON                          (_T("Button"))
#define  DUI_CTR_OPTION                          (_T("Option"))
#define  DUI_CTR_SLIDER                          (_T("Slider"))
#define  DUI_CTR_HOTKEY                          (_T("HotKey"))
//7
#define  DUI_CTR_CONTROL                         (_T("Control"))
#define  DUI_CTR_ACTIVEX                         (_T("ActiveX"))
#define  DUI_CTR_GIFANIM                         (_T("GifAnim"))

//8
#define  DUI_CTR_LISTITEM                        (_T("ListItem"))
#define  DUI_CTR_PROGRESS                        (_T("Progress"))
#define  DUI_CTR_RICHEDIT                        (_T("RichEdit"))
#define  DUI_CTR_CHECKBOX                        (_T("CheckBox"))
#define  DUI_CTR_COMBOBOX                        (_T("ComboBox"))
#define  DUI_CTR_DATETIME                        (_T("DateTime"))
#define  DUI_CTR_TREEVIEW                        (_T("TreeView"))
#define  DUI_CTR_TREENODE                        (_T("TreeNode"))

//9
#define  DUI_CTR_CONTAINER                       (_T("Container"))
#define  DUI_CTR_TABLAYOUT                       (_T("TabLayout"))
#define  DUI_CTR_SCROLLBAR                       (_T("ScrollBar"))
#define  DUI_CTR_SEPBUTTON                       (_T("SepButton"))
#define  DUI_CTR_WKEWEBKIT                       (_T("WbkWebkit"))

//10
#define  DUI_CTR_LISTHEADER                      (_T("ListHeader"))
#define  DUI_CTR_TILELAYOUT                      (_T("TileLayout"))
#define  DUI_CTR_WEBBROWSER                      (_T("WebBrowser"))
#define  DUI_CTR_FADEBUTTON					     (_T("FadeButton"))
#define  DUI_CTR_FADEOPTION				         (_T("FadeOption"))
//11
#define  DUI_CTR_CHILDLAYOUT                     (_T("ChildLayout"))
#define  DUI_CTR_LISTELEMENT                     (_T("ListElement"))
#define  DUI_CTR_ANIMCONTROL                     (_T("AnimControl"))
#define  DUI_CTR_ALBUMBUTTON					 (_T("AlbumButton"))

//12
#define  DUI_CTR_DIALOGLAYOUT                    (_T("DialogLayout"))
#define  DUI_CTR_FADECHECKBOX                    (_T("FadeCheckBox"))
//14
#define  DUI_CTR_VERTICALLAYOUT                  (_T("VerticalLayout"))
#define  DUI_CTR_LISTHEADERITEM                  (_T("ListHeaderItem"))

//15
#define  DUI_CTR_LISTTEXTELEMENT                 (_T("ListTextElement"))

//16
#define  DUI_CTR_HORIZONTALLAYOUT                (_T("HorizontalLayout"))
#define  DUI_CTR_LISTLABELELEMENT                (_T("ListLabelElement"))
#define  DUI_CTR_VERTICALLAYOUTEX                (_T("VerticalLayoutEx"))

//18
#define  DUI_CTR_ANIMATIONTABLAYOUT              (_T("AnimationTabLayout"))
#define  DUI_CTR_HORIZONTALLAYOUTEX              (_T("HorizontalLayoutEx"))
//20
#define  DUI_CTR_LISTCONTAINERELEMENT            (_T("ListContainerElement"))

/////////////////////////////////////////////////////////////////////////////////////
//
enum DuiSig
{
	DuiSig_end = 0, // [marks end of message map]
	DuiSig_lwl,     // LRESULT (WPARAM, LPARAM)
	DuiSig_vn,      // void (TNotifyUI)
};

class CControlUI;

// Structure for notifications to the outside world
typedef struct tagTNotifyUI 
{
	CDuiString sType;
	CDuiString sVirtualWnd;
	CControlUI* pSender;
	DWORD dwTimestamp;
	POINT ptMouse;
	WPARAM wParam;
	LPARAM lParam;
} TNotifyUI;

class CNotifyPump;
typedef void (CNotifyPump::*DUI_PMSG)(TNotifyUI& msg);  //Ö¸ÕëÀàÐÍ

union DuiMessageMapFunctions
{
	DUI_PMSG pfn;   // generic member function pointer
	LRESULT (CNotifyPump::*pfn_Notify_lwl)(WPARAM, LPARAM);
	void (CNotifyPump::*pfn_Notify_vn)(TNotifyUI&);
};

//////////////////////////////////////////////////////////////////////////

struct DUI_MSGMAP_ENTRY;
struct DUI_MSGMAP
{
#ifndef UILIB_STATIC
	const DUI_MSGMAP* (PASCAL* pfnGetBaseMap)();
#else
	const DUI_MSGMAP* pBaseMap;
#endif
	const DUI_MSGMAP_ENTRY* lpEntries;
};

//½á¹¹¶¨Òå
struct DUI_MSGMAP_ENTRY //¶¨ÒåÒ»¸ö½á¹¹Ìå£¬À´´æ·ÅÏûÏ¢ÐÅÏ¢
{
	CDuiString sMsgType;          // DUIÏûÏ¢ÀàÐÍ
	CDuiString sCtrlName;         // ¿Ø¼þÃû³Æ
	UINT       nSig;              // ±ê¼Çº¯ÊýÖ¸ÕëÀàÐÍ
	DUI_PMSG   pfn;               // Ö¸Ïòº¯ÊýµÄÖ¸Õë
};

//¶¨Òå
#ifndef UILIB_STATIC
#define DUI_DECLARE_MESSAGE_MAP()                                         \
private:                                                                  \
	static const DUI_MSGMAP_ENTRY _messageEntries[];                      \
protected:                                                                \
	static const DUI_MSGMAP messageMap;                                   \
	static const DUI_MSGMAP* PASCAL _GetBaseMessageMap();                 \
	virtual const DUI_MSGMAP* GetMessageMap() const;                      \

#else
#define DUI_DECLARE_MESSAGE_MAP()                                         \
private:                                                                  \
	static const DUI_MSGMAP_ENTRY _messageEntries[];                      \
protected:                                                                \
	static  const DUI_MSGMAP messageMap;				                  \
	virtual const DUI_MSGMAP* GetMessageMap() const;                      \

#endif


//»ùÀàÉùÃ÷¿ªÊ¼
#ifndef UILIB_STATIC
#define DUI_BASE_BEGIN_MESSAGE_MAP(theClass)                              \
	const DUI_MSGMAP* PASCAL theClass::_GetBaseMessageMap()               \
		{ return NULL; }                                                  \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
		{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
		{  &theClass::_GetBaseMessageMap, &theClass::_messageEntries[0] };\
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#else
#define DUI_BASE_BEGIN_MESSAGE_MAP(theClass)                              \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
		{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
		{  NULL, &theClass::_messageEntries[0] };                         \
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#endif


//×ÓÀàÉùÃ÷¿ªÊ¼
#ifndef UILIB_STATIC
#define DUI_BEGIN_MESSAGE_MAP(theClass, baseClass)                        \
	const DUI_MSGMAP* PASCAL theClass::_GetBaseMessageMap()               \
		{ return &baseClass::messageMap; }                                \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
		{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
		{ &theClass::_GetBaseMessageMap, &theClass::_messageEntries[0] }; \
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#else
#define DUI_BEGIN_MESSAGE_MAP(theClass, baseClass)                        \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
		{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
		{ &baseClass::messageMap, &theClass::_messageEntries[0] };        \
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#endif


//ÉùÃ÷½áÊø
#define DUI_END_MESSAGE_MAP()                                             \
	{ _T(""), _T(""), DuiSig_end, (DUI_PMSG)0 }                           \
};                                                                        \


//¶¨ÒåÏûÏ¢ÀàÐÍ--Ö´ÐÐº¯Êýºê
#define DUI_ON_MSGTYPE(msgtype, memberFxn)                                \
	{ msgtype, _T(""), DuiSig_vn, (DUI_PMSG)&memberFxn},                  \


//¶¨ÒåÏûÏ¢ÀàÐÍ--¿Ø¼þÃû³Æ--Ö´ÐÐº¯Êýºê
#define DUI_ON_MSGTYPE_CTRNAME(msgtype,ctrname,memberFxn)                 \
	{ msgtype, ctrname, DuiSig_vn, (DUI_PMSG)&memberFxn },                \


//¶¨ÒåclickÏûÏ¢µÄ¿Ø¼þÃû³Æ--Ö´ÐÐº¯Êýºê
#define DUI_ON_CLICK_CTRNAME(ctrname,memberFxn)                           \
	{ DUI_MSGTYPE_CLICK, ctrname, DuiSig_vn, (DUI_PMSG)&memberFxn },      \


//¶¨ÒåselectchangedÏûÏ¢µÄ¿Ø¼þÃû³Æ--Ö´ÐÐº¯Êýºê
#define DUI_ON_SELECTCHANGED_CTRNAME(ctrname,memberFxn)                   \
    { DUI_MSGTYPE_SELECTCHANGED,ctrname,DuiSig_vn,(DUI_PMSG)&memberFxn }, \


//¶¨ÒåkillfocusÏûÏ¢µÄ¿Ø¼þÃû³Æ--Ö´ÐÐº¯Êýºê
#define DUI_ON_KILLFOCUS_CTRNAME(ctrname,memberFxn)                       \
	{ DUI_MSGTYPE_KILLFOCUS,ctrname,DuiSig_vn,(DUI_PMSG)&memberFxn },     \


//¶¨ÒåmenuÏûÏ¢µÄ¿Ø¼þÃû³Æ--Ö´ÐÐº¯Êýºê
#define DUI_ON_MENU_CTRNAME(ctrname,memberFxn)                            \
	{ DUI_MSGTYPE_MENU,ctrname,DuiSig_vn,(DUI_PMSG)&memberFxn },          \


//¶¨ÒåÓë¿Ø¼þÃû³ÆÎÞ¹ØµÄÏûÏ¢ºê

  //¶¨ÒåtimerÏûÏ¢--Ö´ÐÐº¯Êýºê
#define DUI_ON_TIMER()                                                    \
	{ DUI_MSGTYPE_TIMER, _T(""), DuiSig_vn,(DUI_PMSG)&OnTimer },          \


///////////////////////////////////////////////////////////////////////////////////
#define WM_FUNC_DECLARE(func_name)	\
	virtual LRESULT func_name(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


#define DUI_DECLARE_WM_MSG_MAP()                                       \
	protected:                                                          \
	virtual LRESULT ProcessWinMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);  

#define DUI_IMPLAMENT_WM_MSG_MAP_BEGIN(theClass) \
	LRESULT theClass::ProcessWinMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)\
	{	\
		LRESULT lRes = 0; \
		switch (uMsg) \
		{ 
#define ON_WM_DUI_COMMOND(cmd, func)   \
		case cmd:	\
			lRes = func(uMsg, wParam, lParam, bHandled);	\
			break;
#define DUI_IMPLAMENT_WM_MSG_MAP_END() \
		case -1: \
		default: \
			break; \
		}\
		if (bHandled) return lRes;	\
		return __super::HandleMessage(uMsg, wParam, lParam);               \
	}
		



}// namespace DuiLib

#endif//_UIDefine_H