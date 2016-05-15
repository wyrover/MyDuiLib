
#include "UIlib.h"
#include "IDuiWindow.h"

namespace DuiLib
{

//////////////////////////////////////////////////////////////////////////

DUI_BEGIN_MESSAGE_MAP(IDuiWindow,CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)
DUI_END_MESSAGE_MAP()

DUI_IMPLAMENT_WM_MSG_MAP_BEGIN(IDuiWindow)

DUI_IMPLAMENT_WM_MSG_MAP_END()


void IDuiWindow::OnFinalMessage( HWND hWnd )
{
	m_PaintManager.RemovePreMessageFilter(this);
	m_PaintManager.RemoveNotifier(this);
	m_PaintManager.ReapObjects(m_PaintManager.GetRoot());
	m_PaintManager.GetTrayObject().DeleteTrayIcon();
}

LRESULT IDuiWindow::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		Close();
		return TRUE;
	}

	return FALSE;
}

UINT IDuiWindow::GetClassStyle() const
{
	return CS_DBLCLKS;
}

CPaintManagerUI* IDuiWindow::GetPaintMgr()
{
	return &m_PaintManager;
}

#pragma region RESOURCE_TYPE
LPBYTE IDuiWindow::m_lpResourceZIPBuffer = NULL;
UILIB_RESOURCETYPE IDuiWindow::GetResourceType() const
{
	return UILIB_FILE;
}
CDuiString IDuiWindow::GetZIPFileName() const
{
	return _T("");
}
LPCTSTR IDuiWindow::GetResourceID() const
{
	return _T("");
}

CControlUI* IDuiWindow::CreateRoot()
{
	CDialogBuilder builder;

	CDuiString strResourcePath = PathUtil::CombinePath(GetSkinPath().GetData(), GetSkinFolder().GetData());
	m_PaintManager.SetCurResourcePath(strResourcePath.GetData());

	CControlUI* pRoot = NULL;

	switch (GetResourceType())
	{
	case UILIB_FILE:
		{
			pRoot = builder.Create(GetSkinFile().GetData(), (UINT)0, this, &m_PaintManager);
		}
		break;
	case UILIB_ZIP:
		{
			m_PaintManager.SetCurResourceZip(GetZIPFileName().GetData(), true);
			pRoot = builder.Create(GetSkinFile().GetData(), (UINT)0, this, &m_PaintManager);
		}
		break;
	case UILIB_RESOURCE:
		{
			pRoot = builder.Create(_ttoi(GetSkinFile().GetData()), _T("xml"), this, &m_PaintManager);
		}
		break;
	case UILIB_ZIPRESOURCE:
		{
			HINSTANCE hCurInst =  CPaintManagerUI::GetResourceDll();

			HRSRC hResource = ::FindResource(hCurInst, GetResourceID(), _T("ZIPRES"));
			if (hResource == NULL)
				return NULL;
			DWORD dwSize = 0;
			HGLOBAL hGlobal = ::LoadResource(hCurInst, hResource);
			if (hGlobal == NULL)
			{
	#if defined(WIN32) && !defined(UNDER_CE)
				::FreeResource(hResource);
	#endif
				return NULL;
			}
			dwSize = ::SizeofResource(hCurInst, hResource);
			if (dwSize == 0)
				return NULL;
			m_lpResourceZIPBuffer = new BYTE[dwSize];
			if (m_lpResourceZIPBuffer != NULL)
			{
				::CopyMemory(m_lpResourceZIPBuffer, (LPBYTE)::LockResource(hGlobal), dwSize);
			}
	#if defined(WIN32) && !defined(UNDER_CE)
			::FreeResource(hResource);
	#endif
			//m_PaintManager.SetResourceZip(m_lpResourceZIPBuffer, dwSize);

			pRoot = builder.Create(GetSkinFile().GetData(), (UINT)0, this, &m_PaintManager);
		}
	}

	ASSERT(pRoot && _T("加载资源文件失败"));
	if (pRoot == NULL)
	{
		MessageBox(NULL, _T("加载资源文件失败"), _T("Duilib"), MB_OK | MB_ICONERROR);
		ExitProcess(1);
		return NULL;
	}
	return pRoot;
}
#pragma endregion RESOURCE_TYPE
CControlUI* IDuiWindow::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT IDuiWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& /*bHandled*/)
{
	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return ResponseDefaultKeyEvent(wParam);
		default:
			break;
		}
	}
	return FALSE;
}

LRESULT IDuiWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

#if defined(WIN32) && !defined(UNDER_CE)
LRESULT IDuiWindow::OnNcActivate(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT IDuiWindow::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
// 	LPRECT pRect=NULL;
// 
// 	if ( wParam == TRUE)
// 	{
// 		LPNCCALCSIZE_PARAMS pParam = (LPNCCALCSIZE_PARAMS)lParam;
// 		pRect=&pParam->rgrc[0];
// 	}
// 	else
// 	{
// 		pRect=(LPRECT)lParam;
// 	}
// 
// 	if ( ::IsZoomed(m_hWnd))
// 	{	// 最大化时，计算当前显示器最适合宽高度
// 		MONITORINFO oMonitor = {};
// 		oMonitor.cbSize = sizeof(oMonitor);
// 		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
// 		CDuiRect rcWork = oMonitor.rcWork;
// 		CDuiRect rcMonitor = oMonitor.rcMonitor;
// 		rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);
// 
// 		pRect->right = pRect->left + rcWork.GetWidth();
// 		pRect->bottom = pRect->top + rcWork.GetHeight();
// 
// 		return WVR_REDRAW;
// 	}

	return 0;
}

LRESULT IDuiWindow::OnNcPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 0;
}

LRESULT IDuiWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	RECT rcCaption = m_PaintManager.GetCaptionRect();
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
			if( pControl && _tcsicmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
				_tcsicmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
				_tcsicmp(pControl->GetClass(), _T("TextUI")) != 0 )
				return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT IDuiWindow::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
	lpMMI->ptMaxPosition.x	= rcWork.left;
	lpMMI->ptMaxPosition.y	= rcWork.top;
	lpMMI->ptMaxSize.x		= rcWork.right;
	lpMMI->ptMaxSize.y		= rcWork.bottom;
	
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::OnMouseWheel(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}
#endif

LRESULT IDuiWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_PaintManager.GetRoundCorner();
#if defined(WIN32) && !defined(UNDER_CE)
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}
#endif
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == SC_CLOSE)
	{
		bHandled = TRUE;
		PostMessage(WM_CLOSE);
		return 0;
	}
#if defined(WIN32) && !defined(UNDER_CE)
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(m_hWnd) != bZoomed)
	{
		if (!bZoomed)
		{
			CControlUI* pRoot = m_PaintManager.GetRoot();
			m_PaintManager.SendNotify(pRoot, DUI_MSGTYPE_MAXMIN, 1);
		}
		else
		{
			CControlUI* pRoot = m_PaintManager.GetRoot();
			m_PaintManager.SendNotify(pRoot, DUI_MSGTYPE_MAXMIN, 0);
		}
	}
#else
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
#endif
	return lRes;
}

LRESULT IDuiWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	RECT rcClient;
	::GetClientRect(*this, &rcClient);
	::SetWindowPos(*this, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
		rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);

	m_PaintManager.Init(m_hWnd);
	m_PaintManager.AddPreMessageFilter(this);

	CControlUI* pRoot = this->CreateRoot();

	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);
//	m_PaintManager.SetBackgroundTransparent(TRUE);//modify by dfn.li 2013-8-31

	InitWindow();
	return 0;
}

LRESULT IDuiWindow::OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT IDuiWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg)
	{
	case WM_CREATE:			lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:			lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:		lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
#if defined(WIN32) && !defined(UNDER_CE)
	case WM_NCACTIVATE:		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:		lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO:	lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_MOUSEWHEEL:		lRes = OnMouseWheel(uMsg, wParam, lParam, bHandled); break;
#endif
	case WM_SIZE:			lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_CHAR:		lRes = OnChar(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:		lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	case WM_KEYDOWN:		lRes = OnKeyDown(uMsg, wParam, lParam, bHandled); break;
	case WM_KILLFOCUS:		lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); break;
	case WM_SETFOCUS:		lRes = OnSetFocus(uMsg, wParam, lParam, bHandled); break;
	case WM_LBUTTONUP:		lRes = OnLButtonUp(uMsg, wParam, lParam, bHandled); break;
	case WM_LBUTTONDOWN:	lRes = OnLButtonDown(uMsg, wParam, lParam, bHandled); break;
	case WM_MOUSEMOVE:		lRes = OnMouseMove(uMsg, wParam, lParam, bHandled); break;
	case WM_MOUSEHOVER:	lRes = OnMouseHover(uMsg, wParam, lParam, bHandled); break;
	default:				bHandled = FALSE; break;
	}
	if (bHandled) return lRes;

	lRes = HandleCustomMessage(uMsg, wParam, lParam, bHandled);
	if (bHandled) return lRes;

	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT IDuiWindow::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LONG IDuiWindow::GetStyle()
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;

	return styleValue;
}

void IDuiWindow::OnClick(TNotifyUI& msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
	if( sCtrlName == _T("closebtn") )
	{
		Close();
		return; 
	}
	else if( sCtrlName == _T("minbtn"))
	{ 
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); 
		return; 
	}
	else if( sCtrlName == _T("maxbtn"))
	{ 
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); 
		return; 
	}
	else if( sCtrlName == _T("restorebtn"))
	{ 
		SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); 
		return; 
	}
	return;
}

void IDuiWindow::Notify(TNotifyUI& msg)
{
	return CNotifyPump::NotifyPump(msg);
}
}