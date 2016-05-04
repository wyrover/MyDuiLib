sFullPath
sFullPath
sFullPath
#include "stdafx.h"
#include <windows.h>
#include <shellapi.h>

#include "chat_dialog.hpp"
#include "FaceSelDlg.h"
#include "json/DataParser.h"

#define RECV_MSG_ID   WM_USER + 1024

const TCHAR* const kTitleControlName = _T("apptitle");
const TCHAR* const kCloseButtonControlName = _T("BTN_CLOSE");
const TCHAR* const kMinButtonControlName = _T("BTN_MIN");
const TCHAR* const kMaxButtonControlName = _T("BTN_MAX");
const TCHAR* const kRestoreButtonControlName = _T("BTN_RESTORE");

const TCHAR* const kBackgroundControlName = _T("bg");

const TCHAR* const kLogoButtonControlName = _T("USER_LOGO");
const TCHAR* const kNickNameControlName = _T("NICK_NAME");
const TCHAR* const kDescriptionControlName = _T("description");

const TCHAR* const kFontButtonControlName = _T("BTN_FONT");
const TCHAR* const kFontbarControlName = _T("HLY_FONT");
const TCHAR* const kFontTypeControlName = _T("CBO_FONTNAME");
const TCHAR* const kFontSizeControlName = _T("CBO_FONTSIZE");
const TCHAR* const kBoldButtonControlName = _T("OPN_FONTBOLD");
const TCHAR* const kItalicButtonControlName = _T("OPN_FONTITALIC");
const TCHAR* const KUnderlineButtonControlName = _T("OPN_FONTUNDERLINE");
const TCHAR* const kColorButtonControlName = _T("OPN_FONTCOLOR");

const TCHAR* const kInputRichEditControlName = _T("REDIT_INPUT");
const TCHAR* const kViewRichEditControlName = _T("REDIT_OUTPUT");

const TCHAR* const kEmotionButtonControlName = _T("BTN_FACE");

const TCHAR* const kSendButtonControlName = _T("BTN_SEND");
const TCHAR* const kSendPICButtonControlName = _T("BTN_SENDPIC");

const int kEmotionRefreshTimerId = 1001;
const int kEmotionRefreshInterval = 150;

const dui_byte IMG_BEGIN = 0x20;
const dui_byte IMG_END = 0x25;

CFontInfo::CFontInfo(void)
{
	m_nSize = 9;
	m_clrText = RGB(0, 0, 0);
	m_strName = _T("宋体");
	m_bBold = FALSE;
	m_bItalic = FALSE;
	m_bUnderLine = FALSE;
}

CFontInfo::~CFontInfo(void)
{

}
class RichEdit_ImageStringHandleImp : public DuiLib::IRichEdit_ImageStringHandle
{
public:
	void _Replace(CDuiString& strText, const TCHAR * lpOldStr, const TCHAR * lpNewStr)
	{
		if (NULL == lpOldStr || NULL == lpNewStr)
			return ;

		strText.Replace(lpOldStr, lpNewStr);
	}
	virtual void MakeImageString(ImageString* pImageInfo, CDuiString& s_out)
	{
		if (NULL == pImageInfo)
		{
			return;
		}
		if (pImageInfo->nId > 0)
		{
			s_out += (TCHAR)IMG_BEGIN;
			TCHAR cText[2048] = { 0 };
			_stprintf(cText, _T("{img:[{id:%d,name:%s,tip:%s}]}"), pImageInfo->nId, pImageInfo->sName.GetData(), pImageInfo->sTip.GetData());
			s_out += cText;
			s_out += (TCHAR)IMG_END;
		}
		else if (pImageInfo->nIndex > 0)
		{
			s_out += (TCHAR)IMG_BEGIN;
			TCHAR cText[2048] = { 0 };
			_stprintf(cText, _T("{img:[{index:%d,name:%s,tip:%s}]}"), pImageInfo->nIndex, pImageInfo->sName.GetData(), pImageInfo->sTip.GetData());
			s_out += cText;
			s_out += (TCHAR)IMG_END;
		}
		else if (!pImageInfo->sFullPath.IsEmpty())
		{
			if (pImageInfo->bUrl)
			{
				s_out += (TCHAR)IMG_BEGIN;
				TCHAR cText[2048] = { 0 };
				_stprintf(cText, _T("{img:[{url:%s,name:%s,tip:%s}]}"), pImageInfo->sFullPath, pImageInfo->sName.GetData(), pImageInfo->sTip.GetData());
				s_out += cText;
				s_out += (TCHAR)IMG_END;
			}
			else
			{
				s_out += (TCHAR)IMG_BEGIN;
				TCHAR cText[2048] = { 0 };
				_stprintf(cText, _T("{img:[{file:%s,name:%s,tip:%s}]}"), pImageInfo->sFullPath, pImageInfo->sName.GetData(), pImageInfo->sTip.GetData());
				s_out += cText;
				s_out += (TCHAR)IMG_END;
			}
		}
	}
	virtual void MakeImageStringById(dui_uint nId, CDuiString& s_out)
	{
		s_out += (TCHAR)IMG_BEGIN;
		TCHAR cText[2048] = { 0 };
		_stprintf(cText, _T("{\'img\':[{\'id\':%d}]}"), nId);
		s_out += cText;
		s_out += (TCHAR)IMG_END;
	}
	virtual void MakeImageStringByFile(CDuiString& sFile, CDuiString& s_out)
	{
		 _Replace(sFile, _T("\\"), _T("/"));
		 s_out += (TCHAR)IMG_BEGIN;
		 TCHAR cText[2048] = { 0 };
		 _stprintf(cText, _T("{\'img\':[{\'file\':\'%s\'}]}"), sFile.GetData());
		s_out += cText;
		s_out += (TCHAR)IMG_END;
	}
	virtual void MakeImageStringByUrl(CDuiString& sUrl, CDuiString& s_out)
	{
		s_out += (TCHAR)IMG_BEGIN;
		TCHAR cText[2048] = { 0 };
		_stprintf(cText, _T("{\'img\':[{\'url\':\'%s\'}]}"), sUrl.GetData());
		s_out += cText;
		s_out += (TCHAR)IMG_END;
	}
	virtual void MakeNormalString(CDuiString& s_in, CDuiString& s_out)
	{
		s_out.Append(s_in);
	}
	virtual void PraseImageStringS(CDuiString& s_in, std::vector<RichEdit_Text>& t_out)
	{
		t_out.clear();
		size_t pos = 0;
		size_t beg = 0;
		CDuiString s_normal;
		for (; pos < s_in.GetLength();)
		{
			TCHAR ch = s_in[pos];
			if ((dui_byte)ch == IMG_BEGIN)
			{
				s_normal = s_in.Mid(beg, pos-beg);
				beg = pos;
				pos++;
				continue;
			}
			else if ((dui_byte)ch == IMG_END)
			{
				RichEdit_Text t;
				if (!s_normal.IsEmpty())
				{
					t.bImage = false;
					t.sText = s_normal;
					t_out.push_back(t);
				}

				t.bImage = true;
				t.sText = s_in.Mid(beg, pos-beg);
				t_out.push_back(t);

				pos++;
				beg = pos;
				continue;
			}
			else
			{
				pos++;
			}
		}
		if (beg < s_in.GetLength())
		{
			RichEdit_Text t;
			t.bImage = false;
			t.sText = s_in.Mid(beg);
			t_out.push_back(t);
		}
	}
	virtual bool PraseImageString(CDuiString& s_in, ImageString* p_out)
	{
		if (NULL == p_out)
			return false;
		Json::Reader reader;
		Json::Value value;
		CDuiString strJson = s_in;
		_Replace(strJson, _T("\'"), _T("\""));
		_Replace(strJson, _T("\t"), _T(""));
		
		if (!reader.parse(strJson.GetAString(), value) || value.isNull()) return false;

		
		Json::Value images = JsonParser::getValue<Json::Value>(value, "img");
		if (images.isNull()) return false;
		Json::Value image = JsonParser::getValue<Json::Value>(images, 0);
		int nId = JsonParser::getValue<int>(image, "id");
		std::string file = JsonParser::getValue<std::string>(image, "file");
		p_out->nId = nId;
		p_out->sFullPath.AssignString(file.c_str());
		return true;
	}
};

struct MsgText
{
	static dui_uint nIndex;
	TCHAR sText[2048];
};
dui_uint MsgText::nIndex = -1;
MsgText* NewMsgText(CDuiString& s_in)
{
	MsgText* pMsg = new MsgText;
	pMsg->nIndex = MsgText::nIndex + 1;
	memset(pMsg->sText, 0, 2048);
	_stprintf(pMsg->sText, _T("%s"), s_in.GetData());

	return pMsg;
}

void DelMsgText(MsgText* pMsg)
{
	if (pMsg)
	{
		delete pMsg;
	}
}


////////////////////////////////////////////////////////////////////////
ChatDialog::ChatDialog(const CDuiString& bgimage, DWORD bkcolor, const FriendListItemInfo& myselft_info, const FriendListItemInfo& friend_info)
: bgimage_(bgimage)
, bkcolor_(bkcolor)
, myselft_(myselft_info)
, friend_(friend_info)
, emotion_timer_start_(false)
, text_color_(0xFF000000)
, bold_(false)
, italic_(false)
, underline_(false)
, font_size_(12)
, font_face_name_(_T("微软雅黑"))
{
	m_pRichEditInput = NULL;
	m_pRichEditRecv = NULL;
	m_lpFaceList = NULL;
}

ChatDialog::~ChatDialog()
{
	if (m_lpFaceList)
		delete m_lpFaceList;
	m_lpFaceList = NULL;


	return;
}

void ChatDialog::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
	delete this;
}

LPCTSTR ChatDialog::GetWindowClassName() const
{
	return _T("ChatDialog");
}

CControlUI* ChatDialog::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

CDuiString ChatDialog::GetSkinPath()
{
	return CPaintManagerUI::GetInstancePath();
}
CDuiString ChatDialog::GetSkinFolder()
{
	return _T("richedit_test/skin");
}
UILIB_RESOURCETYPE ChatDialog::GetResourceType() const
{
	return UILIB_FILE;
}
LRESULT ChatDialog::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if defined(WIN32) && !defined(UNDER_CE)
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(m_hWnd) != bZoomed)
	{
		if (!bZoomed)
		{
			CControlUI* pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(kMaxButtonControlName));
			if( pControl ) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(kRestoreButtonControlName));
			if( pControl ) pControl->SetVisible(true);
		}
		else 
		{
			CControlUI* pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(kMaxButtonControlName));
			if( pControl ) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(kRestoreButtonControlName));
			if( pControl ) pControl->SetVisible(false);
		}
	}
#else
	return __super::OnSysCommand(uMsg, wParam, lParam, bHandled);
#endif

	return 0;
}

LRESULT ChatDialog::ProcessWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (FACE_CTRL_SEL == uMsg)
		return OnFaceSelected(uMsg, wParam, lParam, bHandled);
	else if (RECV_MSG_ID == uMsg)
		return OnRecvChatMsg(uMsg, wParam, lParam, bHandled);
	else if (uMsg == WM_NOTIFY && (EN_PASTE == ((LPNMHDR)lParam)->code))
	{
		ITextServices * pTextServices = m_pRichEditInput->GetTextServices();
		if (NULL == pTextServices) return FALSE;
		if ((UINT)pTextServices == ((LPNMHDR)lParam)->idFrom)
		{
			OnPaste(((NMRICHEDITOLECALLBACK *)lParam)->lpszText);
		}
		if (pTextServices != NULL)
			pTextServices->Release();
	}
	else if ((uMsg == WM_KEYDOWN) && (wParam == 'V') && (lParam & VK_CONTROL))//Ctrl+V
	{
		if (m_pRichEditInput != NULL && m_pRichEditInput->IsFocused())
		{
			m_pRichEditInput->Paste();
			if (IsClipboardFormatAvailable(CF_TEXT))
				m_pRichEditInput->PasteSpecial(CF_TEXT);
			else if (IsClipboardFormatAvailable(CF_BITMAP))
				m_pRichEditInput->PasteSpecial(CF_BITMAP);
		}
	}
	return __super::ProcessWindowMessage(uMsg, wParam, lParam, bHandled);
}

LRESULT ChatDialog::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return FALSE;
}

void ChatDialog::OnTimer(TNotifyUI& msg)
{}

void ChatDialog::OnExit(TNotifyUI& msg)
{
	Close();
}

void ChatDialog::InitWindow()
{
	m_pRichEditInput = static_cast<CRichEditUI*>(GetPaintMgr()->FindControl(kInputRichEditControlName));
	m_pRichEditRecv = static_cast<CRichEditUI*>(GetPaintMgr()->FindControl(kViewRichEditControlName));

	DuiLib::RichEdit_SetOleCallback(m_pRichEditRecv, m_hWnd);
	DuiLib::RichEdit_SetOleCallback(m_pRichEditInput, m_hWnd);

	DuiLib::RichEdit_RegisterDragDrop(m_pRichEditInput, m_hWnd);

	m_lpFaceList = new CFaceList;
	CDuiString strPath = _T("..\\Face\\FaceConfig.xml");
	m_lpFaceList->LoadConfigFile(strPath);

	CButtonUI* pLogo = static_cast<CButtonUI*>(GetPaintMgr()->FindControl(kLogoButtonControlName));
	pLogo->SetBkImage(friend_.logo);
	CLabelUI* pNick = static_cast<CLabelUI*>(GetPaintMgr()->FindControl(kNickNameControlName));
	pNick->SetText(friend_.nick_name);

}

void ChatDialog::OnPrepare(TNotifyUI& msg)
{
	TCHAR szBuf[MAX_PATH] = {0};

	CControlUI* background = GetPaintMgr()->FindControl(kBackgroundControlName);
	if (background != NULL)
	{
//#if defined(UNDER_WINCE)
//		_stprintf(szBuf, _T("file='%s' corner='600,200,1,1'"), bgimage_.c_str());
//#else
//		_stprintf_s(szBuf, MAX_PATH - 1, _T("file='%s' corner='600,200,1,1'"), bgimage_);
//#endif
//		background->SetBkImage(szBuf);
//		background->SetBkColor(bkcolor_);
	}

	CButtonUI* log_button = static_cast<CButtonUI*>(GetPaintMgr()->FindControl(kLogoButtonControlName));
	if (log_button != NULL)
	{
#if defined(UNDER_WINCE)
		_stprintf(szBuf, _T("%s"), friend_.logo.c_str());
#else
		_stprintf_s(szBuf, MAX_PATH - 1, _T("%s"), friend_.logo);
#endif
		log_button->SetNormalImage(szBuf);
	}

	CControlUI* nick_name = GetPaintMgr()->FindControl(kNickNameControlName);
	if (nick_name != NULL)
		nick_name->SetText(friend_.nick_name);

	CControlUI* desciption = GetPaintMgr()->FindControl(kDescriptionControlName);
	if (desciption != NULL)
		desciption->SetText(friend_.description);

	CContainerUI* pFontbar = static_cast<CContainerUI*>(GetPaintMgr()->FindControl(kFontbarControlName));
	if (pFontbar != NULL)
		pFontbar->SetVisible(false);
}

CDuiString GetCurrentTimeString()
{
	SYSTEMTIME time = {0};
	TCHAR szTime[MAX_PATH] = {0};
	::GetLocalTime( &time );
#if defined(UNDER_CE)
	_stprintf( szTime, _T("%04d年%02d月%02d日 %02d:%02d:%02d"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
#else
	_stprintf_s( szTime, MAX_PATH, _T("%04d年%02d月%02d日 %02d:%02d:%02d"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
#endif

	return szTime;
}

void ChatDialog::SendMsg()
{
	if (m_pRichEditInput == NULL) return;
	m_pRichEditInput->SetFocus();
	CDuiString sText = m_pRichEditInput->GetTextRange(0, m_pRichEditInput->GetTextLength());
    if( sText.IsEmpty() ) return;
	m_pRichEditInput->SetText(_T(""));

	if (m_pRichEditRecv == NULL) return;
    long lSelBegin = 0, lSelEnd = 0;
    CHARFORMAT2 cf;
    ZeroMemory(&cf, sizeof(CHARFORMAT2));
    cf.cbSize = sizeof(cf);
    cf.dwReserved = 0;
    cf.dwMask = CFM_COLOR | CFM_LINK | CFM_UNDERLINE | CFM_UNDERLINETYPE;
    cf.dwEffects = CFE_LINK;
    cf.bUnderlineType = CFU_UNDERLINE;
    cf.crTextColor = RGB(220, 0, 0);

	lSelEnd = lSelBegin = m_pRichEditRecv->GetTextLength();
	m_pRichEditRecv->SetSel(lSelEnd, lSelEnd);
	m_pRichEditRecv->ReplaceSel(_T("某人"), false);

	lSelEnd = m_pRichEditRecv->GetTextLength();
	m_pRichEditRecv->SetSel(lSelBegin, lSelEnd);
	m_pRichEditRecv->SetSelectionCharFormat(cf);

	lSelEnd = lSelBegin = m_pRichEditRecv->GetTextLength();
	m_pRichEditRecv->SetSel(lSelEnd, lSelEnd);
	m_pRichEditRecv->ReplaceSel(_T("说:\t2011-07-30 08:30:12\n"), false);
    cf.dwMask = CFM_COLOR;
    cf.crTextColor = RGB(0, 0, 0);
    cf.dwEffects = 0;
	lSelEnd = m_pRichEditRecv->GetTextLength();
	m_pRichEditRecv->SetSel(lSelBegin, lSelEnd);
	m_pRichEditRecv->SetSelectionCharFormat(cf);

    PARAFORMAT2 pf;
    ZeroMemory(&pf, sizeof(PARAFORMAT2));
    pf.cbSize = sizeof(pf);
    pf.dwMask = PFM_STARTINDENT;
    pf.dxStartIndent = 0;
	m_pRichEditRecv->SetParaFormat(pf);

	lSelEnd = lSelBegin = m_pRichEditRecv->GetTextLength();

	m_pRichEditRecv->SetSel(-1, -1);
	m_pRichEditRecv->ReplaceSel(sText.GetData(), false);

	m_pRichEditRecv->SetSel(-1, -1);
	m_pRichEditRecv->ReplaceSel(_T("\n"), false);

    cf.crTextColor = RGB(0, 0, 0);
	lSelEnd = m_pRichEditRecv->GetTextLength();
	m_pRichEditRecv->SetSel(lSelBegin, lSelEnd);
	m_pRichEditRecv->SetSelectionCharFormat(cf);

    ZeroMemory(&pf, sizeof(PARAFORMAT2));
    pf.cbSize = sizeof(pf);
    pf.dwMask = PFM_STARTINDENT;
    pf.dxStartIndent = 220;
	m_pRichEditRecv->SetParaFormat(pf);

	m_pRichEditRecv->EndDown();
}

void ChatDialog::Notify(TNotifyUI& msg)
{
	if (msg.sType.Compare(_T("timer")) != 0 && msg.pSender)
		VSOutput::Write(CDuiString::FormatString(_T("name:%s,type:%s\r\n"), msg.pSender->GetName().GetData(), msg.sType.GetData()));

	if (_tcsicmp(msg.sType, _T("windowinit")) == 0)
	{
		InitWindow();
		OnPrepare(msg);
	}
	else if (_tcsicmp(msg.sType, _T("killfocus")) == 0)
	{
	}
	else if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		if (_tcsicmp(msg.pSender->GetName(), kCloseButtonControlName) == 0)
		{
			OnExit(msg);
		}
		else if (_tcsicmp(msg.pSender->GetName(), kMinButtonControlName) == 0)
		{
#if defined(UNDER_CE)
			::ShowWindow(m_hWnd, SW_MINIMIZE);
#else
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
#endif
		}
		else if (_tcsicmp(msg.pSender->GetName(), kMaxButtonControlName) == 0)
		{
#if defined(UNDER_CE)
			::ShowWindow(m_hWnd, SW_MAXIMIZE);
			CControlUI* pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(kMaxButtonControlName));
			if( pControl ) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(kRestoreButtonControlName));
			if( pControl ) pControl->SetVisible(true);
#else
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
#endif
		}
		else if (_tcsicmp(msg.pSender->GetName(), kRestoreButtonControlName) == 0)
		{
#if defined(UNDER_CE)
			::ShowWindow(m_hWnd, SW_RESTORE);
			CControlUI* pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(kMaxButtonControlName));
			if( pControl ) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(GetPaintMgr()->FindControl(kRestoreButtonControlName));
			if( pControl ) pControl->SetVisible(false);
#else
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
#endif
		}
		else if (_tcsicmp(msg.pSender->GetName(), kFontButtonControlName) == 0)
		{
			CContainerUI* pFontbar = static_cast<CContainerUI*>(GetPaintMgr()->FindControl(kFontbarControlName));
			if (pFontbar != NULL)
				pFontbar->SetVisible(!pFontbar->IsVisible());
		}
		else if (_tcsicmp(msg.pSender->GetName(), kEmotionButtonControlName) == 0)
		{
			POINT pt = {0};
			CDuiRect rcEmotionBtn = msg.pSender->GetPos();
			CDuiRect rcWindow;
			GetWindowRect(&rcWindow);

			pt.y = rcWindow.top + rcEmotionBtn.top;
			pt.x = rcWindow.left + rcEmotionBtn.left;
			//emotion_list_window_.SelectEmotion(pt);
			CFaceSelDlg* pFaceDialog = new CFaceSelDlg();
			if (pFaceDialog == NULL)
				return;
			pFaceDialog->SetFaceList(m_lpFaceList);
#if defined(WIN32) && !defined(UNDER_CE)
			pFaceDialog->Create(m_hWnd, _T("FaceDialog"), UI_WNDSTYLE_FRAME | WS_POPUP, NULL, 0, 0, 0, 0);
#else
			pFaceDialog->Create(m_hWnd, _T("FaceDialog"), UI_WNDSTYLE_FRAME | WS_POPUP, NULL, 0, 0, 0, 0);
#endif

			pFaceDialog->CenterWindow();
			::ShowWindow(*pFaceDialog, SW_SHOW);
		}
		else if (_tcsicmp(msg.pSender->GetName(), kSendButtonControlName) == 0)
        {
			OnSendClcik();
            //SendMsg();
		}
		else if (_tcsicmp(msg.pSender->GetName(), kSendPICButtonControlName) == 0)
		{
			static LPCTSTR lpszFilter = _T("图像文件(*.bmp;*.jpg;*.jpeg;*.gif;*.png)\0*.bmp;*.jpg;*.jpeg;*.gif;*.png\0\0");;
			if (NULL == m_pRichEditInput)
				return;
			DuiLib::CFileDialog * pFileDlg = new DuiLib::CFileDialog();
			pFileDlg->SetFilter(lpszFilter);
			pFileDlg->SetParentWnd(m_hWnd);
			if (pFileDlg->ShowOpenFileDlg())
			{
				ITextServices * pTextServices = m_pRichEditInput->GetTextServices();
				ITextHost * pTextHost = m_pRichEditInput->GetTextHost();
				if (pTextServices != NULL && pTextHost != NULL)
				{
					BOOL bRet = DuiLib::RichEdit_InsertFace(pTextServices, pTextHost,
						pFileDlg->GetPathName(), -1, -1, RGB(255, 255, 255), TRUE, 40);

					if (pTextServices != NULL)
						pTextServices->Release();
					if (pTextHost != NULL)
						pTextHost->Release();
				}

				m_pRichEditInput->SetFocus();
			}
			delete pFileDlg;
		}
	}
    else if( _tcsicmp(msg.sType, _T("return")) == 0 ) 
    {
        if (_tcsicmp(msg.pSender->GetName(), kInputRichEditControlName) == 0)
        {
            SendMsg();
        }
    }
	else if (_tcsicmp(msg.sType, _T("timer")) == 0)
	{
		return OnTimer(msg);
	}
	else if (_tcsicmp(msg.sType, _T("selectchanged")) == 0)
	{
		if (_tcsicmp(msg.pSender->GetName(), kColorButtonControlName) == 0)
		{
			CContainerUI* pFontbar = static_cast<CContainerUI*>(GetPaintMgr()->FindControl(kFontbarControlName));
			if (pFontbar != NULL)
			{
				//POINT pt = {0};
				//CDuiRect rcFontbar = pFontbar->GetPos();
				//CDuiRect rcColorBtn = msg.pSender->GetPos();
				//CDuiRect rcWindow;
				//GetWindowRect(&rcWindow);

				//pt.y = rcWindow.top + rcFontbar.top;
				//pt.x = rcWindow.left + rcColorBtn.left + static_cast<LONG>(rcColorBtn.right - rcColorBtn.left / 2);
				////new CColorPicker(this, pt);
				static COLORREF rgbCustomColors[16] =
				{
					RGB(255, 255, 255), RGB(255, 255, 255),
					RGB(255, 255, 255), RGB(255, 255, 255),
					RGB(255, 255, 255), RGB(255, 255, 255),
					RGB(255, 255, 255), RGB(255, 255, 255),
					RGB(255, 255, 255), RGB(255, 255, 255),
					RGB(255, 255, 255), RGB(255, 255, 255),
					RGB(255, 255, 255), RGB(255, 255, 255),
					RGB(255, 255, 255), RGB(255, 255, 255),
				};

				CHOOSECOLOR cc = { 0 };
				cc.lStructSize = sizeof(cc);
				cc.lpCustColors = rgbCustomColors;
				cc.hwndOwner = m_hWnd;
				cc.Flags = CC_RGBINIT;

				BOOL bRet = ::ChooseColor(&cc);
				if (bRet)
				{
					text_color_ = cc.rgbResult;
					FontStyleChanged();
				}
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(), kBoldButtonControlName) == 0)
		{
			COptionUI* bold_button = static_cast<COptionUI*>(msg.pSender);
			if (bold_button != NULL)
			{
				bold_ = bold_button->IsSelected();
				FontStyleChanged();
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(), kItalicButtonControlName) == 0)
		{
			COptionUI* italic_button = static_cast<COptionUI*>(msg.pSender);
			if (italic_button != NULL)
			{
				italic_ = italic_button->IsSelected();
				FontStyleChanged();
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(), KUnderlineButtonControlName) == 0)
		{
			COptionUI* underline_button = static_cast<COptionUI*>(msg.pSender);
			if (underline_button != NULL)
			{
				underline_ = underline_button->IsSelected();
				FontStyleChanged();
			}
		}
	}
	else if (_tcsicmp(msg.sType, _T("itemselect")) == 0)
	{
		OnCbo_SelChange(msg);

		if (_tcsicmp(msg.pSender->GetName(), kFontTypeControlName) == 0)
		{
			CComboUI* font_type = static_cast<CComboUI*>(msg.pSender);
			if (font_type != NULL)
			{
				font_face_name_ = font_type->GetText();
				FontStyleChanged();
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(), kFontSizeControlName) == 0)
		{
			CComboUI* font_size = static_cast<CComboUI*>(msg.pSender);
			if (font_size != NULL)
			{
				font_size_ = _ttoi(font_size->GetText());
				FontStyleChanged();
			}
		}
	}
}

void ChatDialog::SetTextColor(DWORD dwColor)
{
	COptionUI* color_button = static_cast<COptionUI*>(GetPaintMgr()->FindControl(kColorButtonControlName));
	if (color_button != NULL)
	{
		color_button->Selected(false);
		if (dwColor != 0)
		{
			text_color_ = dwColor;
			FontStyleChanged();
		}
	}
}

LRESULT ChatDialog::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	try
	{
		ModifyStyle(WS_CAPTION, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		if (!RegisterSkin(_T("DlgChat.xml"), 0, this))
			return 0;

		GetPaintMgr()->AddNotifier(this);
		RECT rcClient;
		::GetClientRect(*this, &rcClient);
		::SetWindowPos(*this, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
			rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);
	}
	catch (...)
	{
		throw _T("ChatDialog::OnCreate");
	}
	return 0;
}

void ChatDialog::FontStyleChanged()
{
	m_fontInfo.m_bBold = bold_;
	m_fontInfo.m_bItalic = italic_;
	m_fontInfo.m_bUnderLine = underline_;
	m_fontInfo.m_nSize = font_size_;
	m_fontInfo.m_clrText = text_color_;
	m_fontInfo.m_strName = font_face_name_;

}


void ChatDialog::OnSendClcik()
{
	if (m_pRichEditInput == NULL) return;
	CDuiString s_text;

	s_text.Empty();
	_RichEdit_GetText(m_pRichEditInput, s_text);


	MsgText* pmsg = NewMsgText(s_text);

	PostMessage(RECV_MSG_ID, (WPARAM)pmsg);
	
	s_text.Empty();

	m_pRichEditInput->SetText(_T(""));
	m_pRichEditInput->SetFocus();
}


LRESULT ChatDialog::OnFaceSelected(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	if (m_pRichEditInput == NULL) return 0;

	CFaceInfo * lpFaceInfo = (CFaceInfo*)wParam;

	CDuiString sFacePath = CFaceCtrl::GetFaceFloder() + lpFaceInfo->m_strFileName;


	BOOL bRet = _RichEdit_InsertFace(m_pRichEditInput, sFacePath, lpFaceInfo->m_nId, lpFaceInfo->m_nIndex, RGB(255, 255, 255), TRUE, 40);

	return 0;
}

BOOL ChatDialog::_RichEdit_InsertFace(CRichEditUI* pRichEdit, LPCTSTR lpszFileName, int nFaceId, int nFaceIndex, COLORREF clrBg, BOOL bAutoScale, int nReservedWidth, int nIndent)
{
	ITextServices * pTextServices = pRichEdit->GetTextServices();
	ITextHost * pTextHost = pRichEdit->GetTextHost();

	DuiLib::RichEdit_SetStartIndent(pTextServices, nIndent);

	BOOL bRet = DuiLib::RichEdit_InsertFace(pTextServices, pTextHost, lpszFileName, nFaceId, nFaceIndex, clrBg, bAutoScale, nReservedWidth);
	if (pTextServices != NULL)
		pTextServices->Release();
	if (pTextHost != NULL)
		pTextHost->Release();

	return bRet;
}

void ChatDialog::_RichEdit_GetText(CRichEditUI* pRichEdit, CDuiString& s_text)
{
	RichEdit_ImageStringHandleImp* pHandle = new RichEdit_ImageStringHandleImp;
	ITextServices * pTextServices = pRichEdit->GetTextServices();
	DuiLib::RichEdit_GetText(pTextServices, s_text,pHandle);
	pTextServices->Release();
	delete pHandle;
}

LRESULT ChatDialog::OnRecvChatMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	MsgText* pmsg = (MsgText*)wParam;

	CDuiString s_text(pmsg->sText);

	AddMsgToRecvEdit(s_text);

	DelMsgText(pmsg);
	return 0;
}

void ChatDialog::OnPaste(LPCTSTR lpText)
{

	if (!IsClipboardFormatAvailable(CF_BITMAP))
	{
		DUI__Trace(_T("IsClipboardFormatAvailable() failed!\n"));
		return;
	}
	if (!OpenClipboard(NULL))
	{
		DUI__Trace(_T("OpenClipboard() failed!\n"));
		return;
	}
	HANDLE hMem = GetClipboardData(CF_BITMAP);
	ASSERT(hMem != NULL);

	HBITMAP hBMP = (HBITMAP)GlobalLock(hMem);
	if (!hBMP)
	{
		DUI__Trace(_T("GlobalLock() failed: %d!\n"), GetLastError());
		
	}
	//Do something here using hBMP
	GlobalUnlock(hMem);
	//Free the memory
	CloseClipboard();

	if (!OpenClipboard(NULL))
		return;
	hMem = GetClipboardData(CF_UNICODETEXT);
	if (hMem != NULL)
	{
		LPTSTR lpStr = (LPTSTR)GlobalLock(hMem);
		if (lpStr != NULL)
		{
			OutputDebugString(lpStr);
		}
		GlobalUnlock(hMem);
	}
	CloseClipboard();
	if (NULL == lpText || NULL == *lpText)
		return;
	m_pRichEditInput->EndDown();
}

void ChatDialog::_RichEdit_ReplaceSel(CRichEditUI * pRichEdit, LPCTSTR lpszNewText, BOOL bIsLink,
	int nStartIndent, BOOL bCanUndo)
{
	ITextServices * pTextServices = pRichEdit->GetTextServices();
	DuiLib::RichEdit_ReplaceSel(pTextServices, lpszNewText,
		m_fontInfo.m_strName,m_fontInfo.m_nSize, m_fontInfo.m_clrText, m_fontInfo.m_bBold, m_fontInfo.m_bItalic,m_fontInfo.m_bUnderLine, bIsLink, nStartIndent, bCanUndo);

	pTextServices->Release();
}
void ChatDialog::AddMsgToRecvEdit(LPCTSTR lpText)
{
	if (NULL == lpText || NULL == *lpText)
		return;

	m_pRichEditRecv->SetAutoURLDetect(true);

	CDuiString strTime = GetCurrentTimeString();

	ITextServices * pTextServices = m_pRichEditRecv->GetTextServices();
	DuiLib::RichEdit_SetSel(pTextServices, -1, -1);

	TCHAR cText[2048] = { 0 };
	_stprintf(cText, _T("%s("), _T("倚天"));

	RichEdit_ReplaceSel(pTextServices, cText,
		_T("宋体"), 9, RGB(0, 0, 255), FALSE, FALSE, FALSE, FALSE, 0);

	_stprintf(cText, _T("%u"), 43156150);
	RichEdit_ReplaceSel(pTextServices, cText,
		_T("宋体"), 9, RGB(0, 114, 193), FALSE, FALSE, TRUE, TRUE, 0);

	_stprintf(cText, _T(")  %s\r\n"), strTime.GetData());
	RichEdit_ReplaceSel(pTextServices, cText,
		_T("宋体"), 9, RGB(0, 0, 255), FALSE, FALSE, FALSE, FALSE, 0);

	RichEdit_ImageStringHandleImp* pHandle = new RichEdit_ImageStringHandleImp;
	std::vector<DuiLib::RichEdit_Text> t_out;
	CDuiString s_in(lpText);
	pHandle->PraseImageStringS(s_in, t_out);

	for (size_t it = 0; it < t_out.size(); ++it)
	{
		DuiLib::RichEdit_Text t = t_out[it];
		if (!t.bImage)
		{
			_RichEdit_ReplaceSel(m_pRichEditRecv, t.sText,FALSE, 300);
		}
		else
		{
			ImageString* pImageString = new ImageString;
			
			if (pHandle->PraseImageString(t.sText, pImageString) )
			{	
				if (pImageString->nId > 0)
				{
					CFaceInfo * lpFaceInfo = m_lpFaceList->GetFaceInfoById(pImageString->nId);
					if (lpFaceInfo)
					{

						CDuiString sFacePath = CFaceCtrl::GetFaceFloder() + lpFaceInfo->m_strFileName;


						BOOL bRet = _RichEdit_InsertFace(m_pRichEditRecv, sFacePath, lpFaceInfo->m_nId, lpFaceInfo->m_nIndex, RGB(255, 255, 255), TRUE, 40, 300);
					}
				}
				else if (pImageString->sFullPath.GetLength()>0)
				{
					//CDuiString sFacePath = CFaceCtrl::GetFaceFloder() + lpFaceInfo->m_strFileName;


					BOOL bRet = _RichEdit_InsertFace(m_pRichEditRecv, pImageString->sFullPath, 0, 0, RGB(255, 255, 255), TRUE, 40, 300);
				}
			}

			delete pImageString;
		}
	}

	delete pHandle;


	RichEdit_ReplaceSel(pTextServices, _T("\r\n"));
	RichEdit_SetStartIndent(pTextServices, 0);
	m_pRichEditRecv->EndDown();

	pTextServices->Release();
}

void ChatDialog::OnCbo_SelChange(TNotifyUI& msg)
{

}