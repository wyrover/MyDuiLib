#include "UIlib.h"
#include "RichEditUtil.h"

#include <comutil.h>

namespace DuiLib
{

	BSTR RichEdit_SysAllocString(LPCTSTR lpszStr)
	{
	#if defined(UNICODE) || defined(_UNICODE)
		return ::SysAllocString(lpszStr);
	#else
		return ::SysAllocString(_com_util::ConvertStringToBSTR(lpszStr));
	#endif
	}
	void RichEdit_Append(CDuiString& strText, BSTR bstr)
	{
	#if defined(UNICODE) || defined(_UNICODE)
		strText =  strText + bstr;
	#else
		strText = strText + _com_util::ConvertBSTRToString(bstr);
	#endif
	}

	UILIB_API void Replace(CDuiString& strText, const TCHAR * lpOldStr, const TCHAR * lpNewStr)
	{
		if (NULL == lpOldStr || NULL == lpNewStr)
			return ;

		strText.Replace(lpOldStr, lpNewStr);
	}

	UILIB_API HGLOBAL GlobalAllocByString(const char * lpszText, long nLen/* = -1*/)
	{
		if (NULL == lpszText)
			return NULL;

		if (-1 == nLen)
			nLen = strlen(lpszText);

		HGLOBAL hGlobal = ::GlobalAlloc(GHND, nLen + 4);
		if (hGlobal != NULL)
		{
			char * lpData = (char *)::GlobalLock(hGlobal);
			if (lpData != NULL)
			{
				memset(lpData, 0, nLen + 4);
				memcpy(lpData, lpszText, nLen);
				::GlobalUnlock(hGlobal);
			}
		}
		return hGlobal;
	}

	UILIB_API HGLOBAL GlobalAllocByString(const wchar_t * lpszText, long nLen/* = -1*/)
	{
		if (NULL == lpszText)
			return NULL;

		if (-1 == nLen)
			nLen = wcslen(lpszText);

		return GlobalAllocByString((const wchar_t *)lpszText, nLen * sizeof(wchar_t));
	}
	// 枚举系统字体回调函数
	int CALLBACK EnumSysFontProc(const LOGFONT *lpelf, const TEXTMETRIC *lpntm, DWORD dwFontType, LPARAM lParam)
	{
		if (dwFontType & TRUETYPE_FONTTYPE)
		{
			std::vector<CDuiString> * arrSysFont = (std::vector<CDuiString> *)lParam;
			if (arrSysFont != NULL)
			{
				for (int i = 0; i < (int)arrSysFont->size(); i++)
				{
					if ((*arrSysFont)[i] == lpelf->lfFaceName)
						return TRUE;
				}
				arrSysFont->push_back(lpelf->lfFaceName);
			}
		}

		return TRUE;
	}

	// 枚举系统字体
	BOOL EnumSysFont(std::vector<CDuiString> * arrSysFont)
	{
		if (NULL == arrSysFont)
			return FALSE;

		HDC hDC = ::GetDC(NULL);
		::EnumFontFamiliesEx(hDC, NULL, EnumSysFontProc, (LPARAM)arrSysFont, 0);
		::ReleaseDC(NULL, hDC);

		return TRUE;
	}
	
	////////////////////////////////////////////////////////////////////
	BOOL UILIB_API RichEdit_SetOleCallback(CRichEditUI* pRichUI, HWND hWnd)
	{
		IRichEditOleCallback2* pRichEditOleCallback2 = NULL;
		HRESULT hr = ::CoCreateInstance(CLSID_ImageOle, NULL, CLSCTX_INPROC_SERVER,
			__uuidof(IRichEditOleCallback2), (void**)&pRichEditOleCallback2);
		if (SUCCEEDED(hr))
		{
			pRichEditOleCallback2->SetNotifyHwnd(hWnd);
			ITextServices * pTextServices = pRichUI->GetTextServices();
			pRichEditOleCallback2->SetTextServices(pTextServices);
			pTextServices->Release();
			pRichUI->SetOleCallback(pRichEditOleCallback2);
			pRichEditOleCallback2->Release();
			return TRUE;
		}
		return FALSE;
	}
	void UILIB_API RichEdit_RegisterDragDrop(CRichEditUI* pRichUI, HWND hWnd)
	{
		IDropTarget *pdt = pRichUI->GetTxDropTarget();
		HRESULT hr = ::RegisterDragDrop(hWnd, pdt);
		pdt->Release();
	}
	UILIB_API IRichEditOle* RichEdit_GetOleInterface(HWND hWnd)
	{
		IRichEditOle *pRichEditOle = NULL;
		::SendMessage(hWnd, EM_GETOLEINTERFACE, 0, (LPARAM)&pRichEditOle);
		return pRichEditOle;
	}
	int UILIB_API RichEdit_GetWindowTextLength(HWND hWnd)
	{
		return ::GetWindowTextLength(hWnd);
	}
	int UILIB_API RichEdit_GetWindowText(HWND hWnd, LPTSTR lpszStringBuf, int nMaxCount)
	{
		return ::GetWindowText(hWnd, lpszStringBuf, nMaxCount);
	}
	int UILIB_API RichEdit_GetWindowText(HWND hWnd, CDuiString& strText)
	{
		int nLength;
		TCHAR * pszText;

		nLength = RichEdit_GetWindowTextLength(hWnd);
		pszText = new TCHAR[nLength+1];
		if (NULL == pszText)
			return 0;
		memset(pszText, 0, (nLength+1)*sizeof(TCHAR));
		nLength = RichEdit_GetWindowText(hWnd, pszText, nLength+1);
		strText = pszText;
		delete []pszText;

		return nLength;
	}
	int UILIB_API RichEdit_GetTextRange(HWND hWnd, CHARRANGE * lpchrg, CDuiString& strText)
	{
		strText = _T("");

		if (NULL == lpchrg || lpchrg->cpMax <= lpchrg->cpMin)
			return 0;

		LONG nLen = lpchrg->cpMax - lpchrg->cpMin;

#ifndef _UNICODE
		LPWSTR lpwStr = NULL;
		lpwStr = new WCHAR[nLen + 1];
		::ZeroMemory(lpwStr, (nLen + 1) * sizeof(WCHAR));

		TEXTRANGEW tr = { 0 };
		tr.chrg = *lpchrg;
		tr.lpstrText = lpwStr;

		int nRet = (int)::SendMessage(hWnd, EM_GETTEXTRANGE, 0, (LPARAM)&tr);

		ASSERT(!::IsBadStringPtrW(lpwStr,-1));
		int cchStr = ((int) wcslen(lpwStr) * 2) + 1;
		CHAR pstr[2048] = { 0 };
		if( pstr != NULL ) ::WideCharToMultiByte(::GetACP(), 0, lpwStr, -1, pstr, cchStr, NULL, NULL);

		strText.Assign(pstr);
		delete[]lpwStr;

		return nRet;
#else
		LPWSTR pText = NULL;
		pText = new WCHAR[nLen + 1];
		::ZeroMemory(pText, (nLen + 1) * sizeof(WCHAR));

		TEXTRANGEW tr = { 0 };
		tr.chrg = *lpchrg;
		tr.lpstrText = pText;

		int nRet = (int)::SendMessage(hWnd, EM_GETTEXTRANGE, 0, (LPARAM)&tr);

		strText = pText;		
		delete []pText;

		return nRet;
#endif // !_UNICODE

	}
	DWORD UILIB_API RichEdit_GetDefaultCharFormat(HWND hWnd, CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		return (DWORD)::SendMessage(hWnd, EM_GETCHARFORMAT, 0, (LPARAM)&cf);
	}
	BOOL UILIB_API RichEdit_SetDefaultCharFormat(HWND hWnd, CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		return (BOOL)::SendMessage(hWnd, EM_SETCHARFORMAT, 0, (LPARAM)&cf);
	}
	DWORD UILIB_API RichEdit_GetSelectionCharFormat(HWND hWnd, CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		return (DWORD)::SendMessage(hWnd, EM_GETCHARFORMAT, 1, (LPARAM)&cf);
	}
	BOOL UILIB_API RichEdit_SetSelectionCharFormat(HWND hWnd, CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		return (BOOL)::SendMessage(hWnd, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	}
	void UILIB_API RichEdit_ReplaceSel(HWND hWnd, LPCTSTR lpszNewText, BOOL bCanUndo /*= FALSE*/)
	{
		::SendMessage(hWnd, EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)lpszNewText);
	}
	void UILIB_API RichEdit_GetSel(HWND hWnd, LONG& nStartChar, LONG& nEndChar)
	{
		CHARRANGE cr = { 0, 0 };
		::SendMessage(hWnd, EM_EXGETSEL, 0, (LPARAM)&cr);
		nStartChar = cr.cpMin;
		nEndChar = cr.cpMax;
	}
	int UILIB_API RichEdit_SetSel(HWND hWnd, LONG nStartChar, LONG nEndChar)
	{
		CHARRANGE cr = { nStartChar, nEndChar };
		return (int)::SendMessage(hWnd, EM_EXSETSEL, 0, (LPARAM)&cr);
	}

	// 设置默认字体
	void UILIB_API RichEdit_SetDefFont(HWND hWnd, LPCTSTR lpFontName, int nFontSize,
		COLORREF clrText, BOOL bBold, BOOL bItalic,
		BOOL bUnderLine, BOOL bIsLink)
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(cf));
		RichEdit_GetDefaultCharFormat(hWnd, cf);

		if (lpFontName != NULL)					// 设置字体名称
		{
			cf.dwMask = cf.dwMask | CFM_FACE;
			_tcscpy(cf.szFaceName, lpFontName);
		}

		if (nFontSize > 0)						// 设置字体高度
		{
			cf.dwMask = cf.dwMask | CFM_SIZE;
			cf.yHeight = nFontSize * 20;
		}

		cf.dwMask |= CFM_COLOR | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_LINK;

		cf.crTextColor = clrText;				// 设置字体颜色
		cf.dwEffects &= ~CFE_AUTOCOLOR;

		if (bBold)								// 设置粗体
			cf.dwEffects |= CFE_BOLD;
		else
			cf.dwEffects &= ~CFE_BOLD;

		if (bItalic)							// 设置倾斜
			cf.dwEffects |= CFE_ITALIC;
		else
			cf.dwEffects &= ~CFE_ITALIC;

		if (bUnderLine)							// 设置下划线
			cf.dwEffects |= CFE_UNDERLINE;
		else
			cf.dwEffects &= ~CFE_UNDERLINE;

		if (bIsLink)							// 设置超链接
			cf.dwEffects |= CFE_LINK;
		else
			cf.dwEffects &= ~CFE_LINK;

		RichEdit_SetDefaultCharFormat(hWnd, cf);
	}
	// 设置默认字体名称和大小
	void UILIB_API RichEdit_SetDefFont(HWND hWnd, LPCTSTR lpFontName, int nFontSize)
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(cf));
		RichEdit_GetDefaultCharFormat(hWnd, cf);

		if (lpFontName != NULL)					// 设置字体名称
		{
			cf.dwMask = cf.dwMask | CFM_FACE;
			_tcscpy(cf.szFaceName, lpFontName);
		}

		if (nFontSize > 0)						// 设置字体高度
		{
			cf.dwMask = cf.dwMask | CFM_SIZE;
			cf.yHeight = nFontSize * 20;
		}

		RichEdit_SetDefaultCharFormat(hWnd, cf);
	}
	// 设置默认字体颜色
	void UILIB_API RichEdit_SetDefTextColor(HWND hWnd, COLORREF clrText)
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(cf));
		RichEdit_GetDefaultCharFormat(hWnd, cf);

		cf.dwMask = cf.dwMask | CFM_COLOR;
		cf.crTextColor = clrText;
		cf.dwEffects &= ~CFE_AUTOCOLOR;
		RichEdit_SetDefaultCharFormat(hWnd, cf);
	}
	// 设置默认超链接
	void UILIB_API RichEdit_SetDefLinkText(HWND hWnd, BOOL bEnable)	
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(cf));
		RichEdit_GetDefaultCharFormat(hWnd, cf);

		cf.dwMask = cf.dwMask | CFM_LINK;
		if (bEnable)							// 设置超链接
			cf.dwEffects |= CFE_LINK;
		else
			cf.dwEffects &= ~CFE_LINK;

		RichEdit_SetDefaultCharFormat(hWnd, cf);
	}
	// 设置字体
	void UILIB_API RichEdit_SetFont(HWND hWnd, LPCTSTR lpFontName, int nFontSize,
		COLORREF clrText, BOOL bBold, BOOL bItalic,
		BOOL bUnderLine, BOOL bIsLink)
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(cf));
		RichEdit_GetSelectionCharFormat(hWnd, cf);

		if (lpFontName != NULL)					// 设置字体名称
		{
			cf.dwMask = cf.dwMask | CFM_FACE;
			_tcscpy(cf.szFaceName, lpFontName);
		}

		if (nFontSize > 0)						// 设置字体高度
		{
			cf.dwMask = cf.dwMask | CFM_SIZE;
			cf.yHeight = nFontSize * 20;
		}

		cf.dwMask |= CFM_COLOR | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_LINK;

		cf.crTextColor = clrText;				// 设置字体颜色
		cf.dwEffects &= ~CFE_AUTOCOLOR;

		if (bBold)								// 设置粗体
			cf.dwEffects |= CFE_BOLD;
		else
			cf.dwEffects &= ~CFE_BOLD;

		if (bItalic)							// 设置倾斜
			cf.dwEffects |= CFE_ITALIC;
		else
			cf.dwEffects &= ~CFE_ITALIC;

		if (bUnderLine)							// 设置下划线
			cf.dwEffects |= CFE_UNDERLINE;
		else
			cf.dwEffects &= ~CFE_UNDERLINE;

		if (bIsLink)							// 设置超链接
			cf.dwEffects |= CFE_LINK;
		else
			cf.dwEffects &= ~CFE_LINK;

		RichEdit_SetSelectionCharFormat(hWnd, cf);
	}
	// 设置字体名称和大小
	void UILIB_API RichEdit_SetFont(HWND hWnd, LPCTSTR lpFontName, int nFontSize)
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(cf));
		RichEdit_GetSelectionCharFormat(hWnd, cf);

		if (lpFontName != NULL)					// 设置字体名称
		{
			cf.dwMask = cf.dwMask | CFM_FACE;
			_tcscpy(cf.szFaceName, lpFontName);
		}

		if (nFontSize > 0)						// 设置字体高度
		{
			cf.dwMask = cf.dwMask | CFM_SIZE;
			cf.yHeight = nFontSize * 20;
		}

		RichEdit_SetSelectionCharFormat(hWnd, cf);
	}
	// 设置字体颜色
	void UILIB_API RichEdit_SetTextColor(HWND hWnd, COLORREF clrText)	
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(cf));
		RichEdit_GetSelectionCharFormat(hWnd, cf);

		cf.dwMask = cf.dwMask | CFM_COLOR;
		cf.crTextColor = clrText;
		cf.dwEffects &= ~CFE_AUTOCOLOR;

		RichEdit_SetSelectionCharFormat(hWnd, cf);
	}
	// 设置超链接
	void UILIB_API RichEdit_SetLinkText(HWND hWnd, BOOL bEnable)
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(cf));
		RichEdit_GetSelectionCharFormat(hWnd, cf);

		cf.dwMask = cf.dwMask | CFM_LINK;
		if (bEnable)							// 设置超链接
			cf.dwEffects |= CFE_LINK;
		else
			cf.dwEffects &= ~CFE_LINK;

		RichEdit_SetSelectionCharFormat(hWnd, cf);
	}
	// 设置左缩进(单位:缇)
	BOOL UILIB_API RichEdit_SetStartIndent(HWND hWnd, int nSize)
	{
		PARAFORMAT2 pf2;
		memset(&pf2, 0, sizeof(pf2));
		pf2.cbSize = sizeof(PARAFORMAT2);
		pf2.dwMask = PFM_STARTINDENT;
		pf2.dxStartIndent = nSize;
		return (BOOL)::SendMessage(hWnd, EM_SETPARAFORMAT, 0, (LPARAM)&pf2);
	}
	// 插入表情图片
	BOOL UILIB_API RichEdit_InsertFace(HWND hWnd, LPCTSTR lpszFileName, int nFaceId,
		int nFaceIndex, COLORREF clrBg, BOOL bAutoScale, int nReservedWidth)
	{
		BSTR bstrFileName = NULL;
		IRichEditOle * pRichEditOle = NULL;
		IOleClientSite *pOleClientSite = NULL;
		IImageOle* pImageOle = NULL;
		IOleObject *pOleObject = NULL;
		REOBJECT reobject = {0};
		HRESULT hr = E_FAIL;

		if (NULL == lpszFileName || NULL == *lpszFileName)
			return FALSE;

		TCHAR cProtocol[16] = {0};
		_tcsncpy(cProtocol, lpszFileName, 7);
		if ((_tcsicmp(cProtocol, _T("http://")) != 0) && ::GetFileAttributes(lpszFileName) == 0xFFFFFFFF)
			return FALSE;

		bstrFileName = RichEdit_SysAllocString(lpszFileName);
		
		if (NULL == bstrFileName)
			return FALSE;

		pRichEditOle = RichEdit_GetOleInterface(hWnd);
		if (NULL == pRichEditOle)
			goto Ret0;

		hr = ::CoCreateInstance(CLSID_ImageOle, NULL, 
			CLSCTX_INPROC_SERVER, IID_IImageOle, (void**)&pImageOle);
		if (FAILED(hr))
			goto Ret0;

		hr = pImageOle->QueryInterface(IID_IOleObject, (void **)&pOleObject);
		if (FAILED(hr))
			goto Ret0;

		pRichEditOle->GetClientSite(&pOleClientSite);
		if (NULL == pOleClientSite)
			goto Ret0;

		pOleObject->SetClientSite(pOleClientSite);

		pImageOle->SetRichEditHwnd(hWnd);
		pImageOle->SetTextServices(NULL);
		pImageOle->SetTextHost(NULL);
		pImageOle->SetFaceId(nFaceId);
		pImageOle->SetFaceIndex(nFaceIndex);
		pImageOle->SetBgColor(clrBg);
		pImageOle->SetAutoScale(bAutoScale, nReservedWidth);
		pImageOle->LoadFromFile(bstrFileName);

		hr = ::OleSetContainedObject(pOleObject, TRUE);

		reobject.cbStruct = sizeof(REOBJECT);
		reobject.clsid    = CLSID_ImageOle;
		reobject.cp       = REO_CP_SELECTION;
		reobject.dvaspect = DVASPECT_CONTENT;
		reobject.dwFlags  = REO_BELOWBASELINE;
		reobject.poleobj  = pOleObject;
		reobject.polesite = pOleClientSite;
		reobject.dwUser   = 0;

		hr = pRichEditOle->InsertObject(&reobject);

	Ret0:
		if (pOleObject != NULL)
			pOleObject->Release();

		if (pImageOle != NULL)
			pImageOle->Release();

		if (pOleClientSite != NULL)
			pOleClientSite->Release();

		if (pRichEditOle != NULL)
			pRichEditOle->Release();

		if (bstrFileName != NULL)
			::SysFreeString(bstrFileName);

		return SUCCEEDED(hr);
	}
	// 获取文本
	void UILIB_API RichEdit_GetText(HWND hWnd, CDuiString& strText,IRichEdit_ImageStringHandle* handle/* = NULL*/)
	{
		REOBJECT reobject;
		LONG nFaceId = -1;
		CDuiString strOrgText;

		IRichEditOle * pRichEditOle = RichEdit_GetOleInterface(hWnd);
		if (NULL == pRichEditOle)
			return;

		CHARRANGE chrg = {0, RichEdit_GetWindowTextLength(hWnd)};
		RichEdit_GetTextRange(hWnd, &chrg, strOrgText);

		for (LONG i = 0; i < (int)strOrgText.GetLength(); i++)
		{
			memset(&reobject, 0, sizeof(REOBJECT));
			reobject.cbStruct = sizeof(REOBJECT);
			reobject.cp = i;
			HRESULT hr = pRichEditOle->GetObject(REO_IOB_USE_CP, &reobject, REO_GETOBJ_POLEOBJ);
			if(!SUCCEEDED(hr))
			{
				if(handle)
				{
					handle->MakeNormalString(strOrgText.Mid(i,1),strText);
				}
				else
				{
					strText.Append(strOrgText.Mid(i,1));
				}
			}
			else
			{
				if (NULL == reobject.poleobj)
					continue;

				if (CLSID_ImageOle == reobject.clsid)
				{
					IImageOle * pImageOle = NULL;
					hr = reobject.poleobj->QueryInterface(__uuidof(IImageOle), (void**)&pImageOle);
					if (SUCCEEDED(hr))
					{
						pImageOle->GetFaceId(&nFaceId);
						if (nFaceId != -1)
						{
							if(handle)
							{
								handle->MakeImageStringById(nFaceId,strText);
							}
						}
						else
						{
							BSTR bstrFileName = NULL;
							pImageOle->GetFileName(&bstrFileName);
							CDuiString s_path;
							RichEdit_Append(s_path, bstrFileName);
							::SysFreeString(bstrFileName);
							if(handle)
							{
								handle->MakeImageStringByFile(s_path,strText);
							}
						}

						pImageOle->Release();
					}
				}
				reobject.poleobj->Release();
			}
		}

		pRichEditOle->Release();
	}
	// 替换选中文本
	void UILIB_API RichEdit_ReplaceSel(HWND hWnd, LPCTSTR lpszNewText, LPCTSTR lpFontName,
		int nFontSize, COLORREF clrText, BOOL bBold, BOOL bItalic,
		BOOL bUnderLine, BOOL bIsLink, int nStartIndent, BOOL bCanUndo /*= FALSE*/)
	{
		long lStartChar = 0, lEndChar = 0;
		RichEdit_GetSel(hWnd, lStartChar, lEndChar);
		RichEdit_ReplaceSel(hWnd, lpszNewText, bCanUndo);
		lEndChar = lStartChar + _tcslen(lpszNewText);
		RichEdit_SetSel(hWnd, lStartChar, lEndChar);
		RichEdit_SetFont(hWnd, lpFontName, nFontSize, clrText, bBold, bItalic, bUnderLine, bIsLink);
		RichEdit_SetStartIndent(hWnd, nStartIndent);
		RichEdit_SetSel(hWnd, lEndChar, lEndChar);
	}
	BOOL UILIB_API RichEdit_GetImageOle(HWND hWnd, POINT pt, IImageOle** pImageOle)
	{
		IRichEditOle * pRichEditOle;
		REOBJECT reobject;
		HRESULT hr;
		BOOL bRet = FALSE;

		if (NULL == pImageOle)
			return FALSE;

		*pImageOle = NULL;

		pRichEditOle = RichEdit_GetOleInterface(hWnd);
		if (NULL == pRichEditOle)
			return FALSE;

		int nCount = pRichEditOle->GetObjectCount();
		for (int i = 0; i < nCount; i++)
		{
			memset(&reobject, 0, sizeof(REOBJECT));
			reobject.cbStruct = sizeof(REOBJECT);
			hr = pRichEditOle->GetObject(i, &reobject, REO_GETOBJ_POLEOBJ);
			if (S_OK == hr)
			{
				if (reobject.poleobj != NULL)
				{
					if (CLSID_ImageOle == reobject.clsid)
					{
						IImageOle * pImageOle2 = NULL;
						hr = reobject.poleobj->QueryInterface(__uuidof(IImageOle), (void**)&pImageOle2);
						reobject.poleobj->Release();
						if (SUCCEEDED(hr))
						{
							RECT rcObject = {0};
							hr = pImageOle2->GetObjectRect(&rcObject);
							if (SUCCEEDED(hr))
							{
								if (::PtInRect(&rcObject, pt))
								{
									*pImageOle = pImageOle2;
									bRet = TRUE;
									break;
								}
							}
							pImageOle2->Release();
						}
					}
					else
					{
						reobject.poleobj->Release();
					}
				}
			}
		}

		pRichEditOle->Release();

		return bRet;
	}


	UILIB_API IRichEditOle* RichEdit_GetOleInterface(ITextServices * pTextServices)
	{
		IRichEditOle *pRichEditOle = NULL;
		pTextServices->TxSendMessage(EM_GETOLEINTERFACE, 0, (LPARAM)&pRichEditOle, NULL);
		return pRichEditOle;
	}
	int UILIB_API RichEdit_GetWindowTextLength(ITextServices * pTextServices)
	{
		HRESULT lRes = 0;
		pTextServices->TxSendMessage(WM_GETTEXTLENGTH, 0, 0, &lRes);
		return (int)lRes;
	}
	int UILIB_API RichEdit_GetWindowText(ITextServices * pTextServices, LPTSTR lpszStringBuf, int nMaxCount)
	{
		HRESULT lRes = 0;
		pTextServices->TxSendMessage(WM_GETTEXT, nMaxCount, (LPARAM)lpszStringBuf, &lRes);
		return (int)lRes;
	}
	int UILIB_API RichEdit_GetWindowText(ITextServices * pTextServices, CDuiString& strText)
	{
		int nLength;
		TCHAR * pszText;

		nLength = RichEdit_GetWindowTextLength(pTextServices);
		pszText = new TCHAR[nLength+1];
		if (NULL == pszText)
			return 0;
		memset(pszText, 0, (nLength+1)*sizeof(TCHAR));
		nLength = RichEdit_GetWindowText(pTextServices, pszText, nLength+1);
		strText = pszText;
		delete []pszText;

		return nLength;
	}
	int UILIB_API RichEdit_GetTextRange(ITextServices * pTextServices, CHARRANGE * lpchrg, CDuiString& strText)
	{
		strText = _T("");

		if (NULL == lpchrg || lpchrg->cpMax <= lpchrg->cpMin)
			return 0;

		LONG nLen = lpchrg->cpMax - lpchrg->cpMin;
#ifndef _UNICODE
		LPWSTR lpwStr = NULL;
		lpwStr = new WCHAR[nLen + 1];
		::ZeroMemory(lpwStr, (nLen + 1) * sizeof(WCHAR));

		TEXTRANGEW tr = { 0 };
		tr.chrg = *lpchrg;
		tr.lpstrText = lpwStr;

		HRESULT lRes = 0;
		pTextServices->TxSendMessage(EM_GETTEXTRANGE, 0, (LPARAM)&tr, &lRes);

		ASSERT(!::IsBadStringPtrW(lpwStr,-1));
		int cchStr = ((int) wcslen(lpwStr) * 2) + 1;
		CHAR pstr[2048] = { 0 };
		if( pstr != NULL ) ::WideCharToMultiByte(::GetACP(), 0, lpwStr, -1, pstr, cchStr, NULL, NULL);

		strText.Assign(pstr);

		delete[]lpwStr;

		return (int)lRes;
#else
		LPWSTR pText = NULL;
		pText = new WCHAR[nLen + 1];
		::ZeroMemory(pText, (nLen + 1) * sizeof(WCHAR));
		
		TEXTRANGEW tr = { 0 };
		tr.chrg = *lpchrg;
		tr.lpstrText = pText;

		HRESULT lRes = 0;
		pTextServices->TxSendMessage(EM_GETTEXTRANGE, 0, (LPARAM)&tr, &lRes);

		strText = pText;
		delete[]pText;

		return (int)lRes;
#endif // !_UNICODE
	}
	DWORD UILIB_API RichEdit_GetDefaultCharFormat(ITextServices * pTextServices, CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		HRESULT lRes = 0;
		pTextServices->TxSendMessage(EM_GETCHARFORMAT, 0, (LPARAM)&cf, &lRes);
		return (DWORD)lRes;
	}
	BOOL UILIB_API RichEdit_SetDefaultCharFormat(ITextServices * pTextServices, CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		HRESULT lRes = 0;
		pTextServices->TxSendMessage(EM_SETCHARFORMAT, 0, (LPARAM)&cf, &lRes);
		return (BOOL)lRes;
	}
	DWORD UILIB_API RichEdit_GetSelectionCharFormat(ITextServices * pTextServices, CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		LRESULT lRes = 0;
		pTextServices->TxSendMessage(EM_GETCHARFORMAT, 1, (LPARAM)&cf, &lRes);
		return (DWORD)lRes;
	}
	BOOL UILIB_API RichEdit_SetSelectionCharFormat(ITextServices * pTextServices, CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		LRESULT lRes = 0;
		pTextServices->TxSendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf, &lRes);
		return (BOOL)lRes;
	}
	void UILIB_API RichEdit_ReplaceSel(ITextServices * pTextServices, LPCTSTR lpszNewText, BOOL bCanUndo/* = FALSE*/)
	{
#ifdef _UNICODE		
		pTextServices->TxSendMessage(EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)lpszNewText, 0);
#else
		int iLen = _tcslen(lpszNewText);
		LPWSTR lpText = new WCHAR[iLen + 1];
		::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
		::MultiByteToWideChar(CP_ACP, 0, lpszNewText, -1, (LPWSTR)lpText, iLen);
		pTextServices->TxSendMessage(EM_REPLACESEL, (WPARAM)bCanUndo, (LPARAM)lpText, 0);
		delete[] lpText;
#endif
	}
	void UILIB_API RichEdit_GetSel(ITextServices * pTextServices, LONG& nStartChar, LONG& nEndChar)
	{
		CHARRANGE cr = { 0, 0 };
		pTextServices->TxSendMessage(EM_EXGETSEL, 0, (LPARAM)&cr, NULL);
		nStartChar = cr.cpMin;
		nEndChar = cr.cpMax;
	}
	int UILIB_API RichEdit_SetSel(ITextServices * pTextServices, LONG nStartChar, LONG nEndChar)
	{
		CHARRANGE cr = { nStartChar, nEndChar };
		HRESULT lRes = 0;
		pTextServices->TxSendMessage(EM_EXSETSEL, 0, (LPARAM)&cr, &lRes);
		return (int)lRes;
	}

	// 设置默认字体
	void UILIB_API RichEdit_SetDefFont(ITextServices * pTextServices, LPCTSTR lpFontName,
		int nFontSize, COLORREF clrText, BOOL bBold,
		BOOL bItalic, BOOL bUnderLine, BOOL bIsLink)
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(cf));
		RichEdit_GetDefaultCharFormat(pTextServices, cf);

		if (lpFontName != NULL)					// 设置字体名称
		{
			cf.dwMask = cf.dwMask | CFM_FACE;
			_tcscpy(cf.szFaceName, lpFontName);
		}

		if (nFontSize > 0)						// 设置字体高度
		{
			cf.dwMask = cf.dwMask | CFM_SIZE;
			cf.yHeight = nFontSize * 20;
		}

		cf.dwMask |= CFM_COLOR | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_LINK;

		cf.crTextColor = clrText;				// 设置字体颜色
		cf.dwEffects &= ~CFE_AUTOCOLOR;

		if (bBold)								// 设置粗体
			cf.dwEffects |= CFE_BOLD;
		else
			cf.dwEffects &= ~CFE_BOLD;

		if (bItalic)							// 设置倾斜
			cf.dwEffects |= CFE_ITALIC;
		else
			cf.dwEffects &= ~CFE_ITALIC;

		if (bUnderLine)							// 设置下划线
			cf.dwEffects |= CFE_UNDERLINE;
		else
			cf.dwEffects &= ~CFE_UNDERLINE;

		if (bIsLink)							// 设置超链接
			cf.dwEffects |= CFE_LINK;
		else
			cf.dwEffects &= ~CFE_LINK;

		RichEdit_SetDefaultCharFormat(pTextServices, cf);
	}
	// 设置字体
	void UILIB_API RichEdit_SetFont(ITextServices * pTextServices, LPCTSTR lpFontName, int nFontSize,
		COLORREF clrText, BOOL bBold, BOOL bItalic, BOOL bUnderLine, BOOL bIsLink)
	{
		CHARFORMAT cf;
		memset(&cf, 0, sizeof(cf));
		RichEdit_GetSelectionCharFormat(pTextServices, cf);

		if (lpFontName != NULL)					// 设置字体名称
		{
			cf.dwMask = cf.dwMask | CFM_FACE;
			_tcscpy(cf.szFaceName, lpFontName);
		}

		if (nFontSize > 0)						// 设置字体高度
		{
			cf.dwMask = cf.dwMask | CFM_SIZE;
			cf.yHeight = nFontSize * 20;
		}

		cf.dwMask |= CFM_COLOR | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_LINK;

		cf.crTextColor = clrText;				// 设置字体颜色
		cf.dwEffects &= ~CFE_AUTOCOLOR;

		if (bBold)								// 设置粗体
			cf.dwEffects |= CFE_BOLD;
		else
			cf.dwEffects &= ~CFE_BOLD;

		if (bItalic)							// 设置倾斜
			cf.dwEffects |= CFE_ITALIC;
		else
			cf.dwEffects &= ~CFE_ITALIC;

		if (bUnderLine)							// 设置下划线
			cf.dwEffects |= CFE_UNDERLINE;
		else
			cf.dwEffects &= ~CFE_UNDERLINE;

		if (bIsLink)							// 设置超链接
			cf.dwEffects |= CFE_LINK;
		else
			cf.dwEffects &= ~CFE_LINK;

		RichEdit_SetSelectionCharFormat(pTextServices, cf);
	}
	// 设置左缩进(单位:缇)
	BOOL UILIB_API RichEdit_SetStartIndent(ITextServices * pTextServices, int nSize)
	{
		PARAFORMAT2 pf2;
		memset(&pf2, 0, sizeof(pf2));
		pf2.cbSize = sizeof(PARAFORMAT2);
		pf2.dwMask = PFM_STARTINDENT;
		pf2.dxStartIndent = nSize;
		HRESULT lRes = 0;
		pTextServices->TxSendMessage(EM_SETPARAFORMAT, 0, (LPARAM)&pf2, &lRes);
		return (BOOL)lRes;
	}
	// 插入表情图片
	BOOL UILIB_API RichEdit_InsertFace(ITextServices *pTextServices, ITextHost *pTextHost,
		LPCTSTR lpszFileName, int nFaceId, int nFaceIndex,
		COLORREF clrBg, BOOL bAutoScale, int nReservedWidth)
	{
		BSTR bstrFileName = NULL;
		IRichEditOle * pRichEditOle = NULL;
		IOleClientSite *pOleClientSite = NULL;
		IImageOle* pImageOle = NULL;
		IOleObject *pOleObject = NULL;
		REOBJECT reobject = {0};
		HRESULT hr = E_FAIL;

		if (NULL == pTextServices || NULL == pTextHost ||
			NULL == lpszFileName || NULL == *lpszFileName)
			return FALSE;

		TCHAR cProtocol[16] = {0};
		_tcsncpy(cProtocol, lpszFileName, 7);
		if ((_tcsicmp(cProtocol, _T("http://")) != 0) && ::GetFileAttributes(lpszFileName) == 0xFFFFFFFF)
			return FALSE;

		bstrFileName = RichEdit_SysAllocString(lpszFileName);
		if (NULL == bstrFileName)
			return FALSE;

		pTextServices->TxSendMessage(EM_GETOLEINTERFACE, 0, (LPARAM)&pRichEditOle, NULL);
		if (NULL == pRichEditOle)
			goto Ret0;

		hr = ::CoCreateInstance(CLSID_ImageOle, NULL,
			CLSCTX_INPROC_SERVER, IID_IImageOle, (void**)&pImageOle);
		if (FAILED(hr))
			goto Ret0;

		hr = pImageOle->QueryInterface(IID_IOleObject, (void **)&pOleObject);
		if (FAILED(hr))
			goto Ret0;

		pRichEditOle->GetClientSite(&pOleClientSite);
		if (NULL == pOleClientSite)
			goto Ret0;

		pOleObject->SetClientSite(pOleClientSite);

		pImageOle->SetTextServices(pTextServices);
		pImageOle->SetTextHost(pTextHost);
		pImageOle->SetFaceId(nFaceId);
		pImageOle->SetFaceIndex(nFaceIndex);
		pImageOle->SetBgColor(clrBg);
		pImageOle->SetAutoScale(bAutoScale, nReservedWidth);
		pImageOle->LoadFromFile(bstrFileName);

		hr = ::OleSetContainedObject(pOleObject, TRUE);

		reobject.cbStruct = sizeof(REOBJECT);
		reobject.clsid = CLSID_ImageOle;
		reobject.cp = REO_CP_SELECTION;
		reobject.dvaspect = DVASPECT_CONTENT;
		reobject.dwFlags = REO_BELOWBASELINE;
		reobject.poleobj = pOleObject;
		reobject.polesite = pOleClientSite;
		reobject.dwUser = 0;

		hr = pRichEditOle->InsertObject(&reobject);

	Ret0:
		if (pOleObject != NULL)
			pOleObject->Release();

		if (pImageOle != NULL)
			pImageOle->Release();

		if (pOleClientSite != NULL)
			pOleClientSite->Release();

		if (pRichEditOle != NULL)
			pRichEditOle->Release();

		if (bstrFileName != NULL)
			::SysFreeString(bstrFileName);

		return SUCCEEDED(hr);
	}
	// 获取文本
	void UILIB_API RichEdit_GetText(ITextServices * pTextServices, CDuiString& strText, IRichEdit_ImageStringHandle* handle)
	{
		REOBJECT reobject;
		LONG nFaceId = -1;
		CDuiString strOrgText;

		IRichEditOle * pRichEditOle = RichEdit_GetOleInterface(pTextServices);
		if (NULL == pRichEditOle)
			return;

		CHARRANGE chrg = {0, RichEdit_GetWindowTextLength(pTextServices)};
		
		RichEdit_GetTextRange(pTextServices, &chrg, strOrgText);
		
		for (LONG i = 0; i < (int)strOrgText.GetLength(); i++)
		{
			memset(&reobject, 0, sizeof(REOBJECT));
			reobject.cbStruct = sizeof(REOBJECT);
			reobject.cp = i;
			HRESULT hr = pRichEditOle->GetObject(REO_IOB_USE_CP, &reobject, REO_GETOBJ_POLEOBJ);
			if(!SUCCEEDED(hr))
			{
				if(handle)
				{
					handle->MakeNormalString(strOrgText.Mid(i,1),strText);
				}
				else
				{
					strText.Append(strOrgText.Mid(i,1));
				}
			}
			else
			{
				if (NULL == reobject.poleobj)
					continue;

				if (CLSID_ImageOle == reobject.clsid)
				{
					IImageOle * pImageOle = NULL;
					hr = reobject.poleobj->QueryInterface(__uuidof(IImageOle), (void**)&pImageOle);
					if (SUCCEEDED(hr))
					{
						pImageOle->GetFaceId(&nFaceId);
						if (nFaceId != -1)
						{
							if (handle)
							{
								handle->MakeImageStringById(nFaceId, strText);
							}
						}
						else
						{
							BSTR bstrFileName = NULL;
							pImageOle->GetFileName(&bstrFileName);
							CDuiString s_path;
							RichEdit_Append(s_path, bstrFileName);
							::SysFreeString(bstrFileName);
							handle->MakeImageStringByFile(s_path, strText);
						}

						pImageOle->Release();
					}
				}
				reobject.poleobj->Release();
			}
		}

		pRichEditOle->Release();
	}
	// 替换选中文本
	void UILIB_API RichEdit_ReplaceSel(ITextServices * pTextServices, LPCTSTR lpszNewText,
		LPCTSTR lpFontName, int nFontSize, COLORREF clrText,
		BOOL bBold, BOOL bItalic, BOOL bUnderLine, BOOL bIsLink,
		int nStartIndent, BOOL bCanUndo /*= FALSE*/)
	{
		long lStartChar = 0, lEndChar = 0;
		RichEdit_GetSel(pTextServices, lStartChar, lEndChar);
		RichEdit_ReplaceSel(pTextServices, lpszNewText, bCanUndo);
		lEndChar = lStartChar + _tcslen(lpszNewText);
		RichEdit_SetSel(pTextServices, lStartChar, lEndChar);
		RichEdit_SetFont(pTextServices, lpFontName, nFontSize, clrText, bBold, bItalic, bUnderLine, bIsLink);
		RichEdit_SetStartIndent(pTextServices, nStartIndent);
		RichEdit_SetSel(pTextServices, lEndChar, lEndChar);
	}
	BOOL UILIB_API RichEdit_GetImageOle(ITextServices * pTextServices, POINT pt, IImageOle** pImageOle)
	{
		IRichEditOle * pRichEditOle;
		REOBJECT reobject;
		HRESULT hr;
		BOOL bRet = FALSE;

		if (NULL == pImageOle)
			return FALSE;

		*pImageOle = NULL;

		pRichEditOle = RichEdit_GetOleInterface(pTextServices);
		if (NULL == pRichEditOle)
			return FALSE;

		int nCount = pRichEditOle->GetObjectCount();
		for (int i = 0; i < nCount; i++)
		{
			memset(&reobject, 0, sizeof(REOBJECT));
			reobject.cbStruct = sizeof(REOBJECT);
			hr = pRichEditOle->GetObject(i, &reobject, REO_GETOBJ_POLEOBJ);
			if (S_OK == hr)
			{
				if (reobject.poleobj != NULL)
				{
					if (CLSID_ImageOle == reobject.clsid)
					{
						IImageOle * pImageOle2 = NULL;
						hr = reobject.poleobj->QueryInterface(__uuidof(IImageOle), (void**)&pImageOle2);
						reobject.poleobj->Release();
						if (SUCCEEDED(hr))
						{
							RECT rcObject = { 0 };
							hr = pImageOle2->GetObjectRect(&rcObject);
							if (SUCCEEDED(hr))
							{
								if (::PtInRect(&rcObject, pt))
								{
									*pImageOle = pImageOle2;
									bRet = TRUE;
									break;
								}
							}
							pImageOle2->Release();
						}
					}
					else
					{
						reobject.poleobj->Release();
					}
				}
			}
		}

		pRichEditOle->Release();

		return bRet;
	}
	long UILIB_API RichEdit_GetTextLength(ITextServices* pTextServices, DWORD dwFlags /*= GTL_DEFAULT*/)
	{
		GETTEXTLENGTHEX textLenEx;
		textLenEx.flags = dwFlags;
#ifdef _UNICODE
		textLenEx.codepage = 1200;
#else
		textLenEx.codepage = CP_ACP;
#endif
		LRESULT lResult;
		pTextServices->TxSendMessage(EM_GETTEXTLENGTHEX, (WPARAM)&textLenEx, 0, &lResult);
		return (long)lResult;
	}
	int UILIB_API RichEdit_GetTextRange(ITextServices* pTextServices, long nStartChar, long nEndChar,CDuiString& s_text)
	{
		TEXTRANGEW tr = { 0 };
		tr.chrg.cpMin = nStartChar;
		tr.chrg.cpMax = nEndChar;
		LPWSTR lpText = NULL;
		lpText = new WCHAR[nEndChar - nStartChar + 1];
		::ZeroMemory(lpText, (nEndChar - nStartChar + 1) * sizeof(WCHAR));
		tr.lpstrText = lpText;
		LRESULT lResult;
		pTextServices->TxSendMessage(EM_GETTEXTRANGE, 0, (LPARAM)&tr, &lResult);
		s_text = (LPCWSTR)lpText;
		delete[] lpText;

		return (int)lResult;
	}
}


