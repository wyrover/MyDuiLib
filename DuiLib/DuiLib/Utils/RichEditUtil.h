
#ifndef RichEditImp_H
#define RichEditImp_H
#pragma once
#include "Extend/ImgOle/IImageOle.h"

namespace DuiLib
{

	struct UILIB_API ImageString
	{
		dui_uint nId;
		dui_uint nIndex;
		dui_uint nWidth;
		dui_uint nHeight;
		dui_bool bUrl;

		CDuiString sFullPath;
		CDuiString sName;
		CDuiString sTip;
	};
	struct UILIB_API RichEdit_Text
	{
		dui_bool bImage;
		CDuiString sText;
	};
	class UILIB_API IRichEdit_ImageStringHandle
	{
	public:
		virtual void MakeImageString(ImageString* pImageInfo, CDuiString& s_out) = 0;
		virtual void MakeImageStringById(dui_uint nId, CDuiString& s_out) = 0;
		virtual void MakeImageStringByFile(CDuiString& sFile, CDuiString& s_out) = 0;
		virtual void MakeImageStringByUrl(CDuiString& sUrl, CDuiString& s_out) = 0;
		virtual void MakeNormalString(CDuiString& s_in, CDuiString& s_out) = 0;

		virtual void PraseImageStringS(CDuiString& s_in, std::vector<RichEdit_Text>& t_out) = 0;
		virtual bool PraseImageString(CDuiString& s_in, ImageString* p_out) = 0;
	};

	UILIB_API HGLOBAL GlobalAllocByString(const char * lpszText, long nLen = -1);
	UILIB_API HGLOBAL GlobalAllocByString(const wchar_t * lpszText, long nLen = -1);

	BOOL UILIB_API EnumSysFont(std::vector<CDuiString> * arrSysFont);	// 枚举系统字体
	UILIB_API void Replace(CDuiString& strText, const TCHAR * lpOldStr, const TCHAR * lpNewStr);
	////////////////////////////////////////////////////////////////////////////////
	BOOL UILIB_API RichEdit_SetOleCallback(CRichEditUI* pRichUI, HWND hWnd);
	void UILIB_API RichEdit_RegisterDragDrop(CRichEditUI* pRichUI, HWND hWnd);
	UILIB_API IRichEditOle* RichEdit_GetOleInterface(HWND hWnd);
	int UILIB_API RichEdit_GetWindowTextLength(HWND hWnd);
	int UILIB_API RichEdit_GetWindowText(HWND hWnd, LPTSTR lpszStringBuf, int nMaxCount);
	int UILIB_API RichEdit_GetWindowText(HWND hWnd, CDuiString& strText);
	int UILIB_API RichEdit_GetTextRange(HWND hWnd, CHARRANGE * lpchrg, CDuiString& strText);
	DWORD UILIB_API RichEdit_GetDefaultCharFormat(HWND hWnd, CHARFORMAT& cf);
	BOOL UILIB_API RichEdit_SetDefaultCharFormat(HWND hWnd, CHARFORMAT& cf);
	DWORD UILIB_API RichEdit_GetSelectionCharFormat(HWND hWnd, CHARFORMAT& cf);
	BOOL UILIB_API RichEdit_SetSelectionCharFormat(HWND hWnd, CHARFORMAT& cf);
	void UILIB_API RichEdit_ReplaceSel(HWND hWnd, LPCTSTR lpszNewText, BOOL bCanUndo = FALSE);
	void UILIB_API RichEdit_GetSel(HWND hWnd, LONG& nStartChar, LONG& nEndChar);
	int UILIB_API RichEdit_SetSel(HWND hWnd, LONG nStartChar, LONG nEndChar);

	void UILIB_API RichEdit_SetDefFont(HWND hWnd, LPCTSTR lpFontName, int nFontSize,	// 设置默认字体
		COLORREF clrText, BOOL bBold, BOOL bItalic,
		BOOL bUnderLine, BOOL bIsLink);
	void UILIB_API RichEdit_SetDefFont(HWND hWnd, LPCTSTR lpFontName, int nFontSize);	// 设置默认字体名称和大小
	void UILIB_API RichEdit_SetDefTextColor(HWND hWnd, COLORREF clrText);				// 设置默认字体颜色
	void UILIB_API RichEdit_SetDefLinkText(HWND hWnd, BOOL bEnable);					// 设置默认超链接
	void UILIB_API RichEdit_SetFont(HWND hWnd, LPCTSTR lpFontName, int nFontSize,		// 设置字体
		COLORREF clrText, BOOL bBold, BOOL bItalic,
		BOOL bUnderLine, BOOL bIsLink);
	void UILIB_API RichEdit_SetFont(HWND hWnd, LPCTSTR lpFontName, int nFontSize);	// 设置字体名称和大小
	void UILIB_API RichEdit_SetTextColor(HWND hWnd, COLORREF clrText);				// 设置字体颜色
	void UILIB_API RichEdit_SetLinkText(HWND hWnd, BOOL bEnable);						// 设置超链接
	BOOL UILIB_API RichEdit_SetStartIndent(HWND hWnd, int nSize);						// 设置左缩进(单位:缇)
	BOOL UILIB_API RichEdit_InsertFace(HWND hWnd, LPCTSTR lpszFileName, int nFaceId,	// 插入表情图片
		int nFaceIndex, COLORREF clrBg, BOOL bAutoScale, int nReservedWidth);
	void UILIB_API RichEdit_GetText(HWND hWnd, CDuiString& strText, IRichEdit_ImageStringHandle* handle = NULL);						// 获取文本
	void UILIB_API RichEdit_ReplaceSel(HWND hWnd, LPCTSTR lpszNewText, LPCTSTR lpFontName,	// 替换选中文本
		int nFontSize, COLORREF clrText, BOOL bBold, BOOL bItalic,
		BOOL bUnderLine, BOOL bIsLink, int nStartIndent, BOOL bCanUndo = FALSE);
	BOOL UILIB_API RichEdit_GetImageOle(HWND hWnd, POINT pt, IImageOle** pImageOle);


	UILIB_API IRichEditOle* RichEdit_GetOleInterface(ITextServices * pTextServices);
	int UILIB_API RichEdit_GetWindowTextLength(ITextServices * pTextServices);
	int UILIB_API RichEdit_GetWindowText(ITextServices * pTextServices, LPTSTR lpszStringBuf, int nMaxCount);
	int UILIB_API RichEdit_GetWindowText(ITextServices * pTextServices, CDuiString& strText);
	int UILIB_API RichEdit_GetTextRange(ITextServices * pTextServices, CHARRANGE * lpchrg, CDuiString& strText);
	DWORD UILIB_API RichEdit_GetDefaultCharFormat(ITextServices * pTextServices, CHARFORMAT& cf);
	BOOL UILIB_API RichEdit_SetDefaultCharFormat(ITextServices * pTextServices, CHARFORMAT& cf);
	DWORD UILIB_API RichEdit_GetSelectionCharFormat(ITextServices * pTextServices, CHARFORMAT& cf);
	BOOL UILIB_API RichEdit_SetSelectionCharFormat(ITextServices * pTextServices, CHARFORMAT& cf);
	void UILIB_API RichEdit_ReplaceSel(ITextServices * pTextServices, LPCTSTR lpszNewText, BOOL bCanUndo = FALSE);
	void UILIB_API RichEdit_GetSel(ITextServices * pTextServices, LONG& nStartChar, LONG& nEndChar);
	int UILIB_API RichEdit_SetSel(ITextServices * pTextServices, LONG nStartChar, LONG nEndChar);

	void UILIB_API RichEdit_SetDefFont(ITextServices * pTextServices, LPCTSTR lpFontName,		// 设置默认字体
		int nFontSize, COLORREF clrText, BOOL bBold,
		BOOL bItalic, BOOL bUnderLine, BOOL bIsLink);
	void UILIB_API RichEdit_SetFont(ITextServices * pTextServices, LPCTSTR lpFontName, int nFontSize,	// 设置字体
		COLORREF clrText, BOOL bBold, BOOL bItalic, BOOL bUnderLine, BOOL bIsLink);
	BOOL UILIB_API RichEdit_SetStartIndent(ITextServices * pTextServices, int nSize);			// 设置左缩进(单位:缇)
	BOOL UILIB_API RichEdit_InsertFace(ITextServices *pTextServices, ITextHost *pTextHost,	// 插入表情图片
		LPCTSTR lpszFileName, int nFaceId, int nFaceIndex,
		COLORREF clrBg, BOOL bAutoScale, int nReservedWidth);
	void UILIB_API RichEdit_GetText(ITextServices * pTextServices, CDuiString& strText, IRichEdit_ImageStringHandle* handle = NULL);			// 获取文本
	void UILIB_API RichEdit_ReplaceSel(ITextServices * pTextServices, LPCTSTR lpszNewText,	// 替换选中文本
		LPCTSTR lpFontName, int nFontSize, COLORREF clrText,
		BOOL bBold, BOOL bItalic, BOOL bUnderLine, BOOL bIsLink,
		int nStartIndent, BOOL bCanUndo = FALSE);
	BOOL UILIB_API RichEdit_GetImageOle(ITextServices * pTextServices, POINT pt, IImageOle** pImageOle);

	long UILIB_API RichEdit_GetTextLength(ITextServices* pTextServices, DWORD dwFlags = GTL_DEFAULT);
	int UILIB_API RichEdit_GetTextRange(ITextServices* pTextServices, long nStartChar, long nEndChar, CDuiString& s_text);

}


#endif//RichEditImp_H