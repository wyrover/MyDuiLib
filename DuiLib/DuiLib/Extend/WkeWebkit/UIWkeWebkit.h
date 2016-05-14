#ifndef __UIWKEWEBKIT_H_
#define __UIWKEWEBKIT_H_
#pragma once
#include "wke.h"


namespace DuiLib
{
	///////////////////////////////////////////
	//网页加载状态改变的回调
	class IWkeWebkitLoadCallback
	{
	public:
		virtual void	OnLoadFailed() = 0;
		virtual void	OnLoadComplete() = 0;
		virtual void	OnDocumentReady() = 0;
	};
	///////////////////////////////////////////
	//网页标题、地址改变的回调
	class IWkeWebkitClientCallback
	{
	public:
		virtual void	OnTitleChange(const CDuiString& strTitle) = 0;
		virtual void	OnUrlChange(const CDuiString& strUrl) = 0;
	};

	class UILIB_API CWkeWebkitUI :
		public CControlUI,
		public wkeBufHandler
	{
	public:
		CWkeWebkitUI(void);
		~CWkeWebkitUI(void);
		static LPCTSTR GetClassName();
		static void WkeWebkit_Init();
		static void WkeWebkit_Shutdown();
		virtual void	onBufUpdated(const HDC hdc, int x, int y, int cx, int cy);
		virtual LPCTSTR	GetClass()const;
		virtual LPVOID	GetInterface(LPCTSTR pstrName);
		virtual void	DoEvent(TEventUI& event);
		virtual void	DoPaint(HDC hDC, const RECT& rcPaint);
		virtual void	SetPos(RECT rc);
		virtual void	DoInit();
		virtual void	SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		//////////////////////////////////////
		const	CDuiString& GetUrl()const;
		bool	CanGoBack() const;
		bool	GoBack();
		bool	CanGoForward() const;
		bool	GoForward();
		void	StopLoad();
		void	Refresh();
		wkeWebView	GetWebView();
		void	SetLoadCallback(IWkeWebkitLoadCallback* pCallback);
		IWkeWebkitLoadCallback* GetLoadCallback();
		void	Navigate(LPCTSTR lpUrl);
		void	LoadFile(LPCTSTR lpFile);
		void	LoadHtml(LPCTSTR lpHtml);
	protected:
		void	StartCheckThread();
		void	StopCheckThread();
		static	void OnTitleChange(const struct _wkeClientHandler* clientHandler, const wkeString title);
		static  void OnUrlChange(const struct _wkeClientHandler* clientHandler, const wkeString url);
	private:
		static int	m_bWebkitCount;
		static int  m_nTimerID;
		HANDLE		m_hCheckThread;
		CDuiString  m_strUrl;
		wkeWebView	m_pWebView;
		wkeClientHandler	m_ClientHandler;
		IWkeWebkitLoadCallback*		m_pLoadCallback;
		IWkeWebkitClientCallback*	m_pClientCallback;
	};
}

#endif//__UIWKEWEBKIT_H_