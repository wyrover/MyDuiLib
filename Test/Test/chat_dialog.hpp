#ifndef CHATDIALOG_HPP
#define CHATDIALOG_HPP


#include "UIFriends.h"
#include "FaceList.h"

class CFontInfo				// 字体信息
{
public:
	CFontInfo(void);
	~CFontInfo(void);

public:
	int m_nSize;			// 字体大小
	COLORREF m_clrText;		// 字体颜色
	CDuiString m_strName;		// 字体名称
	BOOL m_bBold;			// 是否加粗
	BOOL m_bItalic;			// 是否倾斜
	BOOL m_bUnderLine;		// 是否带下划线
};

class ChatDialog : public CWin
	, public INotifyUI
	, public IDialogBuilderCallback
{
public:

	ChatDialog(const CDuiString& bgimage, DWORD bkcolor, const FriendListItemInfo& myselft_info, const FriendListItemInfo& friend_info);
	virtual ~ChatDialog();

public:

	LPCTSTR GetWindowClassName() const;
	CControlUI* CreateControl(LPCTSTR pstrClass);

	virtual void OnFinalMessage(HWND hWnd);
	virtual void InitWindow();

	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT ProcessWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	LRESULT OnFaceSelected(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRecvChatMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	// 插入表情图片
	BOOL _RichEdit_InsertFace(CRichEditUI* pRichEdit,
		LPCTSTR lpszFileName, int nFaceId, int nFaceIndex,
		COLORREF clrBg, BOOL bAutoScale, int nReservedWidth, int nIndent = 0);

	void _RichEdit_ReplaceSel(CRichEditUI * pRichEdit, LPCTSTR lpszNewText, BOOL bIsLink,
		int nStartIndent, BOOL bCanUndo = FALSE);

	void _RichEdit_GetText(CRichEditUI* pRichEdit, CDuiString& s_text);

	void AddMsgToRecvEdit(LPCTSTR lpText);

	void SetTextColor(DWORD dwColor);

    void SendMsg();

protected:	
	virtual CDuiString GetSkinPath();
	virtual CDuiString GetSkinFolder();
	virtual UILIB_RESOURCETYPE GetResourceType() const;

	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);

	void OnSendClcik();

	void OnCbo_SelChange(TNotifyUI& msg);
private:
	void FontStyleChanged();
	void OnPaste(LPCTSTR lpText);
private:	
	bool emotion_timer_start_;

	bool bold_;
	bool italic_;
	bool underline_;
	DWORD text_color_;
	DWORD font_size_;
	CDuiString font_face_name_;

	CDuiString bgimage_;
	DWORD bkcolor_;
	FriendListItemInfo myselft_;
	FriendListItemInfo friend_;


	CRichEditUI* m_pRichEditInput;
	CRichEditUI* m_pRichEditRecv;

	CFaceList* m_lpFaceList;
	CFontInfo m_fontInfo;
};

typedef  DuiLib::SharedPtr<ChatDialog> spChatDialogT;

#endif // CHARTDIALOG_HPP