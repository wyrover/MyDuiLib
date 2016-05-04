#include "stdafx.h"
#include "RichEditTest.h"
#include "chat_dialog.hpp"

CRichEditWnd::CRichEditWnd()
{

}
CRichEditWnd::~CRichEditWnd()
{

}
LPCTSTR CRichEditWnd::GetWindowClassName() const
{
	return _T("RichEditWnd");
}

CDuiString CRichEditWnd::GetSkinPath()
{
	return CPaintManagerUI::GetInstancePath();
}
CDuiString CRichEditWnd::GetSkinFolder()
{
	return _T("richedit_test/skin");
}
UILIB_RESOURCETYPE CRichEditWnd::GetResourceType() const
{
	return UILIB_FILE;
}

CControlUI* CRichEditWnd::CreateControl(LPCTSTR pstrClass)
{
	try
	{
		if (_tcscmp(pstrClass, _T("FriendList")) == 0)
			return new CFriendsUI(*(GetPaintMgr()));
	}
	catch (...)
	{
	}
	return NULL;
}
void CRichEditWnd::Notify(TNotifyUI &msg)
{
	if (msg.sType.Compare(_T("timer")) != 0 && msg.pSender)
		VSOutput::Write(CDuiString::FormatString(_T("name:%s,type:%s\r\n"), msg.pSender->GetName().GetData(), msg.sType.GetData()));
	if (msg.sType == _T("windowinit"))
	{
		OnInitWindow(msg);
	}
	else if (msg.sType == _T("click"))
	{
		OnClick(msg);
	}
	else if (msg.sType == _T("itemclick"))
	{
		OnItemClick(msg);
	}
	else if (msg.sType == _T("itemactivate"))
	{
		OnItemActive(msg);
	}
	else if (msg.sType.IsSame(_T("selectchanged")))
	{
		CAnimationTabLayoutUI* pLayout = static_cast<CAnimationTabLayoutUI*>(GetPaintMgr()->FindControl(_T("TAB_MAIN")));
		if (msg.pSender->IsName(_T("OPN_0")))
		{
			pLayout->SelectItem(0);
		}
		else if (msg.pSender->IsName(_T("OPN_1")))
		{
			pLayout->SelectItem(1);
		}
		else if (msg.pSender->IsName(_T("OPN_2")))
		{
			pLayout->SelectItem(2);
		}
		else if (msg.pSender->IsName(_T("OPN_3")))
		{
			pLayout->SelectItem(3);
		}
		else if (msg.pSender->IsName(_T("OPN_4")))
		{
			pLayout->SelectItem(4);
		}
	}

}
void CRichEditWnd::OnInitWindow(TNotifyUI& msg)
{
	UpdateFriendsList();
}
void CRichEditWnd::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
};
void CRichEditWnd::OnClick(TNotifyUI& msg)
{
	if (msg.pSender->IsName(_T("BTN_CLOSE")))
	{
		PostQuitMessage(0L);
		//SendMessage(WM_CLOSE, 0, 0);
	}
}
void CRichEditWnd::OnItemClick(TNotifyUI& msg)
{
	CAnimationTabLayoutUI* m_pTabSwitch = static_cast<CAnimationTabLayoutUI*>(GetPaintMgr()->FindControl(_T("TAB_MAIN")));
	if (m_pTabSwitch != NULL)
	{
		if (m_pTabSwitch->GetCurSel() == 0)
		{
			
		}
		else if (m_pTabSwitch->GetCurSel() == 1)
		{
			CFriendsUI* pFriendsList = static_cast<CFriendsUI*>(GetPaintMgr()->FindControl(_T("LIST_FRIEND")));
			if ((pFriendsList != NULL) && pFriendsList->GetItemIndex(msg.pSender) != -1)
			{
				if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
				{
					Node* node = (Node*)msg.pSender->GetTag();

					if (pFriendsList->CanExpand(node))
					{
						pFriendsList->SetChildVisible(node, !node->data().child_visible_);
					}
				}
			}
		}
	}
}
void CRichEditWnd::OnItemActive(TNotifyUI& msg)
{
	CAnimationTabLayoutUI* pTabControl = static_cast<CAnimationTabLayoutUI*>(GetPaintMgr()->FindControl(_T("TAB_MAIN")));
	if (pTabControl != NULL)
	{
		if (pTabControl->GetCurSel() == 1)
		{
			CFriendsUI* pFriendsList = static_cast<CFriendsUI*>(GetPaintMgr()->FindControl(_T("LIST_FRIEND")));
			if ((pFriendsList != NULL) && pFriendsList->GetItemIndex(msg.pSender) != -1)
			{
				if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0)
				{
					Node* node = (Node*)msg.pSender->GetTag();

					CControlUI* background = GetPaintMgr()->FindControl(_T("bg"));
					if (!pFriendsList->CanExpand(node) && (background != NULL))
					{
						FriendListItemInfo friend_info;

						for (std::vector<FriendListItemInfo>::const_iterator citer = friends_.begin(); citer != friends_.end(); ++citer)
						{
							if (_tcsicmp(citer->id, node->data().value) == 0)
							{
								friend_info = *citer;
								break;
							}
						}

						ChatDialog* pChatDialog = new ChatDialog(background->GetBkImage(), background->GetBkColor(), myself_info_, friend_info);
						if (pChatDialog == NULL)
							return;
#if defined(WIN32) && !defined(UNDER_CE)
						pChatDialog->Create(NULL, _T("ChatDialog"), UI_WNDSTYLE_FRAME | WS_POPUP, NULL, 0, 0, 0, 0);
#else
						pChatDialog->Create(NULL, _T("ChatDialog"), UI_WNDSTYLE_FRAME | WS_POPUP, NULL, 0, 0, 0, 0);
#endif

						pChatDialog->CenterWindow();
						::ShowWindow(*pChatDialog, SW_SHOW);
					}
				}
			}
		}
	}
}
LRESULT CRichEditWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	try
	{
		ModifyStyle(WS_CAPTION, WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		if (!RegisterSkin(_T("main.xml"), 0, this))
			return 0;

		GetPaintMgr()->AddNotifier(this);

		RECT rcClient;
		::GetClientRect(*this, &rcClient);
		::SetWindowPos(*this, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
			rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);
	}
	catch (...)
	{
		throw _T("CRichEditWnd::OnCreate");
	}
	return 0;
}
void CRichEditWnd::UpdateFriendsList()
{
	CFriendsUI* pFriendsList = static_cast<CFriendsUI*>(GetPaintMgr()->FindControl(_T("LIST_FRIEND")));
	if (pFriendsList != NULL)
	{
		if (!friends_.empty())
			friends_.clear();
		if (pFriendsList->GetCount() > 0)
			pFriendsList->RemoveAll();

		FriendListItemInfo item;

		item.id = _T("0");
		item.folder = true;
		item.empty = false;
		item.nick_name = _T("我的好友");

		Node* root_parent = pFriendsList->AddNode(item, NULL);
		friends_.push_back(item);

		item.id = _T("1");
		item.folder = false;
		item.logo = _T("user.png");
		item.nick_name = _T("tojen");
		item.description = _T("北国风光，千里冰封，万里雪飘");

		myself_info_ = item;

		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);

		item.id = _T("2");
		item.folder = false;
		item.logo = _T("users/175.png");
		item.nick_name = _T("achellies");
		item.description = _T("这个家伙很懒，什么也没留下。。。");
		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);

		item.id = _T("3");
		item.folder = false;
		item.logo = _T("users/176.png");
		item.nick_name = _T("wangchyz");
		item.description = _T("wangchyz@gmail.com");
		pFriendsList->AddNode(item, root_parent);
		friends_.push_back(item);

		for (int i = 0; i < 100; ++i)
		{
			item.id = CDuiString::FormatString(_T("%d"), 4 + i);
			item.folder = false;
			item.logo = CDuiString::FormatString(_T("users/%d.png"), (int)Math::RangeRandom(175, 264));
			item.nick_name = _T("duilib");
			item.description = _T("www.duilib.com");
			pFriendsList->AddNode(item, root_parent);
			friends_.push_back(item);
		}

		item.id = _T("3");
		item.folder = true;
		item.empty = false;
		item.nick_name = _T("企业好友");
		Node* root_parent2 = pFriendsList->AddNode(item, NULL);
		friends_.push_back(item);

		item.id = _T("4");
		item.folder = false;
		item.logo = CDuiString::FormatString(_T("users/%d.png"), (int)Math::RangeRandom(175, 264));
		item.nick_name = _T("腾讯企业QQ的官方展示号");
		item.description = _T("");
		pFriendsList->AddNode(item, root_parent2);
		friends_.push_back(item);

		item.id = _T("5");
		item.folder = true;
		item.empty = false;
		item.nick_name = _T("陌生人");
		Node* root_parent3 = pFriendsList->AddNode(item, NULL);
		friends_.push_back(item);


		item.id = _T("6");
		item.folder = true;
		item.empty = false;
		item.nick_name = _T("黑名单");
		Node* root_parent4 = pFriendsList->AddNode(item, NULL);
		friends_.push_back(item);
	}
}