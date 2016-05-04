#pragma once

#include "FaceCtrl.h"
#include "FaceList.h"

#define		FACE_CTRL_SEL		WM_USER + 1

class CFaceSelDlg : public IDuiWindow
{
public:
	CFaceSelDlg(void);
	~CFaceSelDlg(void);

public:
	LPCTSTR GetWindowClassName() const;	
	virtual void InitWindow();
	virtual CDuiString GetSkinPath();
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();

	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual void OnFinalMessage(HWND hWnd);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	void SetFaceList(CFaceList * lpFaceList);

protected:
	void Notify(TNotifyUI& msg);

private:
	CFaceCtrl * m_pFaceCtrl;
	CFaceList * m_lpFaceList;
};
