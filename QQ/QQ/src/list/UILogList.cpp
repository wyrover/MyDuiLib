#include "stdafx.h"
#include "UISongList.hpp"
#include "../MainWindow/MainWindow.h"
#include "../tipinfo/DuiToolTip.h"

_LieBao_NameSpaceBegin

const int kListItemNormalHeight = 30;
const int kListItemSelectedHeight = 80;

CSongListUI::CSongListUI(CPaintManagerUI& paint_manager)
	
	: delay_deltaY_(0)
	, delay_number_(0)
	, delay_left_(0)
	, paint_manager_(paint_manager)
{
	SetItemShowHtml(true);
	m_iLastSel = -1;
	m_pItemTip = NULL;
}

CSongListUI::~CSongListUI()
{
	if(m_pItemTip)
		delete m_pItemTip;
}

bool CSongListUI::Add(CControlUI* pControl)
{
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)
		return false;

	return CListUI::Add(pControl);
}

bool CSongListUI::AddAt(CControlUI* pControl, int iIndex)
{
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)
		return false;

	return CListUI::AddAt(pControl, iIndex);
}

bool CSongListUI::Remove(CControlUI* pControl)
{
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)
		return false;

	return CListUI::Remove(pControl);
}
bool CSongListUI::RemoveAt(int iIndex)
{
	CControlUI* pControl = GetItemAt(iIndex);
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), _T("ListContainerElementUI")) != 0)
		return false;

	return CListUI::RemoveAt(iIndex);
}

void CSongListUI::RemoveAll()
{
	CListUI::RemoveAll();
}

void CSongListUI::DoEvent(TEventUI& event) 
{
	if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND)
	{
		if (m_pParent != NULL)
			m_pParent->DoEvent(event);
		else
			CVerticalLayoutUI::DoEvent(event);
		return;
	}

	if (event.Type == UIEVENT_TIMER && event.wParam == SCROLL_TIMERID)
	{
		if (delay_left_ > 0)
		{
			--delay_left_;
			SIZE sz = GetScrollPos();
			LONG lDeltaY =  (LONG)(CalculateDelay((double)delay_left_ / delay_number_) * delay_deltaY_);
			if ((lDeltaY > 0 && sz.cy != 0)  || (lDeltaY < 0 && sz.cy != GetScrollRange().cy ))
			{
				sz.cy -= lDeltaY;
				SetScrollPos(sz);
				return;
			}
		}
		delay_deltaY_ = 0;
		delay_number_ = 0;
		delay_left_ = 0;
		m_pManager->KillTimer(this, SCROLL_TIMERID);
		return;
	}
	if (event.Type == UIEVENT_SCROLLWHEEL)
	{
		LONG lDeltaY = 0;
		if (delay_number_ > 0)
			lDeltaY =  (LONG)(CalculateDelay((double)delay_left_ / delay_number_) * delay_deltaY_);
		switch (LOWORD(event.wParam))
		{
		case SB_LINEUP:
			if (delay_deltaY_ >= 0)
				delay_deltaY_ = lDeltaY + 8;
			else
				delay_deltaY_ = lDeltaY + 12;
			break;
		case SB_LINEDOWN:
			if (delay_deltaY_ <= 0)
				delay_deltaY_ = lDeltaY - 8;
			else
				delay_deltaY_ = lDeltaY - 12;
			break;
		}
		if
			(delay_deltaY_ > 100) delay_deltaY_ = 100;
		else if
			(delay_deltaY_ < -100) delay_deltaY_ = -100;

		delay_number_ = (DWORD)sqrt((double)abs(delay_deltaY_)) * 5;
		delay_left_ = delay_number_;
		m_pManager->SetTimer(this, SCROLL_TIMERID, 50U);
		return;
	}

	CListUI::DoEvent(event);
}
// bool IsItemControl(CControlUI* pUI)
// {
// 	try
// 	{
// 		if(pUI->IsName(_T("song_index")) ||
// 			pUI->IsName(_T("song_name"))||
// 			pUI->IsName(_T("item_collect"))||
// 			pUI->IsName(_T("item_delete"))||
// 			pUI->IsName(_T("item_timeContainer"))||
// 			pUI->IsName(_T("item_tab"))||
// 			pUI->IsName(_T("p_tab"))||
// 			pUI->IsName(_T("small_info"))||
// 			pUI->IsName(_T("item_timeContainer2"))||
// 			pUI->IsName(_T("big_info"))||					
// 			pUI->IsName(_T("album_info"))||
// 			pUI->IsName(_T("p_opinfo")))
// 			return true;
// 		return false;
// 	}
// 	catch (...)
// 	{
// 		return false;
// 	}
// }

static bool OnLogoButtonEvent(void* event) {
	try
	{
		CControlUI* pControl = ((TEventUI*)event)->pSender;
		CSongListUI* pList = NULL;
		if( pControl != NULL ) {
			if( 0 != _tcsicmp(pControl->GetUserData(),_T("song_item"))) return false;
			CControlUI* pUI = (CControlUI*)(pControl->GetTag());
			if(pUI)
			{
				DUI__Trace(pUI->GetClass());
				DUI__Trace(pUI->GetName());
			}
			if(!pUI) return false;
			if( 0 != _tcsicmp(pUI->GetClass(),_T("ListContainerElementUI")) ) return false;
			CListContainerElementUI* pListItem = (CListContainerElementUI*)(pControl->GetTag());
			if (pListItem)
			{
				if(pListItem->GetTag())
					pList = (CSongListUI*)(pListItem->GetTag());
				if (pList)
				{
					/*if( ((TEventUI*)event)->Type == UIEVENT_BUTTONDOWN ) 
					{
						if(pList->m_pItemTip!=NULL)
						{
							pList->m_pItemTip->Close(1);
							pList->m_pItemTip = NULL;
						}
					}*/
					/*else */if (((TEventUI*)event)->Type == UIEVENT_MOUSEHOVER||((TEventUI*)event)->Type == UIEVENT_MOUSEENTER)
					{
						if(pListItem->GetFixedHeight()==kListItemNormalHeight)
						{
							CSongListUI::array pItem = pList->GetItem(pList->GetItemIndex(pListItem));
							if (pItem._pTab/*&&pList->GetCurSel()!=pList->GetItemIndex(pListItem)*/)
							{
								pItem._pTab->SelectItem(1);
							}									
						}
						if(!(pControl->IsName(_T("item_collect"))||pControl->IsName(_T("item_delete"))))
						{					
							spSongInfo spSong = pList->SongInfo(pList->GetItemIndex(pListItem));					
							POINT pt;
							GetCursorPos(&pt);
							if(pList->m_pItemTip!=NULL)
							{
								pList->m_pItemTip->SetInfo(&spSong);
								pList->m_pItemTip->AdjustPostion(pt);
							}
							if(pList->m_pItemTip==NULL)
							{																	
								pList->m_pItemTip = new CItemTip(spSong);
								pList->m_pItemTip->InitToolTip(pt,&(pList->paint_manager_));
							}	
						}
					}
					else if(((TEventUI*)event)->Type == UIEVENT_MOUSELEAVE)
					{
						if(pListItem->GetFixedHeight()==kListItemNormalHeight)
						{
							CSongListUI::array pItem = pList->GetItem(pList->GetItemIndex(pListItem));
							if (pItem._pTab/*&&pList->GetCurSel()!=pList->GetItemIndex(pListItem)*/)
							{
								pItem._pTab->SelectItem(0);
							}
						}
						if(pList->m_pItemTip!=NULL)
						{
							pList->m_pItemTip->Close(1);
							pList->m_pItemTip = NULL;
						}
					}
				}
			}
		}
		return true;
	}
	catch (...)
	{
		return false;
	}
}

static bool OnLButtonDown(void* msg)
{
	CListContainerElementUI* pItem = static_cast<CListContainerElementUI*>(((TNotifyUI*)msg)->pSender);
	CSongListUI* pList = NULL;
	if (pItem)
	{
		pList = (CSongListUI*)(pItem->GetTag());
		if(pList)
		{
			_Debug(mci::ToString(pList->GetCurSel()));
			_Debug(_T("\r\n"));
			if (0 == ((TNotifyUI*)msg)->sType.Compare(_T("itemclick"))&&
				0 == ((TNotifyUI*)msg)->pSender->GetName().Compare(_T("listItem")))
			{
				_Debug(mci::ToString(pList->SongInfo(pList->GetItemIndex(pItem)).spSongPath.c_str()));
				_Debug(_T("\r\n"));
			}
		}
	}
	return true;
}
bool CSongListUI::AddNode(spSongInfo spSongInfoT)
{
	try
	{
		array* _pItem = new array;
		ASSERT(_pItem);

		int iCount = this->GetCount();
		CString sIndex;
		sIndex.Format(_T("%d"),iCount+1);

		CString sLogStr = _T("[ CSongListUI::AddNode(");
		sLogStr += sIndex;
		sLogStr += _T(",");
		sLogStr += mci::ToString(spSongInfoT.spSongPath.c_str());
		sLogStr += _T(")]");
		sLog(_T("[ CSongListUI::AddNode(%d,%s) ]"),iCount+1,mci::ToString(spSongInfoT.spSongPath.c_str()).GetString());

		CListContainerElementUI* pListElement = NULL;
		if( !m_dlgBuilder.GetMarkup()->IsValid() ) {
			pListElement = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create(_T("SongItem.xml"), (UINT)0, NULL, &paint_manager_));
		}
		else {
			pListElement = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create((UINT)0, &paint_manager_));
		}
		if (pListElement == NULL)
			return false;
		ASSERT(pListElement);
		pListElement->SetTag((UINT_PTR)this);
//		pListElement->OnNotify += MakeDelegate(&OnLButtonDown);
		
		_pItem->_pSongIndex = static_cast<CButtonUI*>(paint_manager_.FindSubControlByName(pListElement,_T("song_index")));
		_pItem->_pSongName = static_cast<CLabelUI*>(paint_manager_.FindSubControlByName(pListElement,_T("song_name")));
		_pItem->_pCollect = static_cast<CCheckBoxUI*>(paint_manager_.FindSubControlByName(pListElement,_T("item_collect")));
		_pItem->_pDelete = static_cast<CButtonUI*>(paint_manager_.FindSubControlByName(pListElement,_T("item_delete")));
		_pItem->_pTimeContainer = static_cast<CLabelUI*>(paint_manager_.FindSubControlByName(pListElement,_T("item_timeContainer")));
		_pItem->_pTab = static_cast<CTabLayoutUI*>(paint_manager_.FindSubControlByName(pListElement,_T("item_tab")));

		_pItem->_pAlbumImage = static_cast<CAlbumButtonUI*>(paint_manager_.FindSubControlByName(pListElement,_T("albumlogo")));
		_pItem->_pTimeContainer2 = static_cast<CLabelUI*>(paint_manager_.FindSubControlByName(pListElement,_T("item_timeContainer2")));
		_pItem->_pCollect2 = static_cast<CCheckBoxUI*>(paint_manager_.FindSubControlByName(pListElement,_T("item_collect2")));
		_pItem->_pShare = static_cast<CButtonUI*>(paint_manager_.FindSubControlByName(pListElement,_T("item_share")));
		_pItem->_pAlbumInfo = static_cast<CTextUI*>(paint_manager_.FindSubControlByName(pListElement,_T("album_info")));

		_pItem->_pHorUp = static_cast<CHorizontalLayoutUI*>(paint_manager_.FindSubControlByName(pListElement,_T("small_info")));
		_pItem->_pHorBottom = static_cast<CHorizontalLayoutUI*>(paint_manager_.FindSubControlByName(pListElement,_T("big_info")));

		ASSERT(_pItem->_pSongIndex);
		ASSERT(_pItem->_pSongName);
		ASSERT(_pItem->_pCollect);
		ASSERT(_pItem->_pDelete);
		ASSERT(_pItem->_pTimeContainer);
		ASSERT(_pItem->_pAlbumImage);
		ASSERT(_pItem->_pTimeContainer2);
		ASSERT(_pItem->_pCollect2);
		ASSERT(_pItem->_pShare);
		ASSERT(_pItem->_pAlbumInfo);
		ASSERT(_pItem->_pHorUp);
		ASSERT(_pItem->_pHorBottom);
		ASSERT(_pItem->_pTab);

		_pItem->_pSongIndex->SetTag((UINT_PTR)pListElement);
		_pItem->_pSongIndex->OnEvent += MakeDelegate(&OnLogoButtonEvent);
		
		_pItem->_pSongName->SetTag((UINT_PTR)pListElement);
		_pItem->_pSongName->OnEvent += MakeDelegate(&OnLogoButtonEvent);

		_pItem->_pCollect->SetTag((UINT_PTR)pListElement);
		_pItem->_pCollect->OnEvent += MakeDelegate(&OnLogoButtonEvent);
		_pItem->_pCollect->GetParent()->SetTag((UINT_PTR)pListElement);
		_pItem->_pCollect->GetParent()->OnEvent += MakeDelegate(&OnLogoButtonEvent);
		_pItem->_pDelete->SetTag((UINT_PTR)pListElement);
		_pItem->_pDelete->OnEvent += MakeDelegate(&OnLogoButtonEvent);

		_pItem->_pTimeContainer->SetTag((UINT_PTR)pListElement);
		_pItem->_pTimeContainer->OnEvent += MakeDelegate(&OnLogoButtonEvent);

		_pItem->_pTab->SetTag((UINT_PTR)pListElement);
		_pItem->_pTab->OnEvent += MakeDelegate(&OnLogoButtonEvent);

		_pItem->_pTab->GetParent()->SetTag((UINT_PTR)pListElement);
		_pItem->_pTab->GetParent()->OnEvent += MakeDelegate(&OnLogoButtonEvent);

		_pItem->_pHorUp->SetTag((UINT_PTR)pListElement);
		_pItem->_pHorUp->OnEvent += MakeDelegate(&OnLogoButtonEvent);

 		_pItem->_pTimeContainer2->SetTag((UINT_PTR)pListElement);
 		_pItem->_pTimeContainer2->OnEvent += MakeDelegate(&OnLogoButtonEvent);
 
		_pItem->_pTimeContainer2->GetParent()->SetTag((UINT_PTR)pListElement);
		_pItem->_pTimeContainer2->GetParent()->OnEvent += MakeDelegate(&OnLogoButtonEvent);

		_pItem->_pHorBottom->SetTag((UINT_PTR)pListElement);
		_pItem->_pHorBottom->OnEvent += MakeDelegate(&OnLogoButtonEvent);

 		_pItem->_pAlbumInfo->SetTag((UINT_PTR)pListElement);
 		_pItem->_pAlbumInfo->OnEvent += MakeDelegate(&OnLogoButtonEvent);
		_pItem->_pAlbumInfo->GetParent()->SetTag((UINT_PTR)pListElement);
		_pItem->_pAlbumInfo->GetParent()->OnEvent += MakeDelegate(&OnLogoButtonEvent);

 		_pItem->_pShare->GetParent()->SetTag((UINT_PTR)pListElement);
 		_pItem->_pShare->GetParent()->OnEvent += MakeDelegate(&OnLogoButtonEvent);
		////////////////////////////////////////////////////////////////////////////
		////
		_pItem->_pSongIndex->SetText(sIndex);
		_pItem->_pSongName->SetText(mci::ToString(spSongInfoT.spSongName.c_str()));
		_pItem->_pAlbumInfo->SetText(mci::ToString(spSongInfoT.spAlbumName.c_str()));
		_pItem->_pTimeContainer->SetText(mci::ToString(spSongInfoT.spSongTime.c_str()));
		CDuiString sTime = _T("00:00/");
		sTime += _pItem->_pTimeContainer->GetText().GetData();
		_pItem->_pTimeContainer2->SetText(sTime);
		_pItem->_pCollect2->SetUserData(_pItem->_pCollect2->GetText());
		pListElement->SetFixedHeight(kListItemNormalHeight);
		_pItem->_pHorBottom->SetVisible(false);


		_pSongList.push_back(spSongInfoT);

		if (!CListUI::Add(pListElement))
		{
			delete pListElement;
		}

		delete _pItem;
		return true;
	}
	catch(...)
	{
		throw L"CSongListUI::AddNode(spSongInfo spSongInfoT)";
	}
}
spSongInfo CSongListUI::PraseInfo(LPCTSTR spFilePath,const char* spPanelName)
{
	try
	{
		TID3InfoEx id3_info;
		spSongInfo spSongInfoT; 
		ZeroMemory(&spSongInfoT,sizeof(spSongInfoT));
		ZPlay* player = CreateZPlay();
		if(!player)		
			ASSERT(false);
		if(player->OpenFileW(spFilePath, sfAutodetect) == 0)
		{
			sLogError(_T("CSongListUI::PraseInfo : %s"),spFilePath);
			player->Release();

			spSongInfoT.spSongPath = std::string("");

			return spSongInfoT;
		}
		
		
		int iCount = this->GetCount()+1;
		if (player->LoadID3Ex(&id3_info,1))
		{
			spSongInfoT.spSongName       = std::string(id3_info.Title);
			spSongInfoT.spArtistName	 = std::string(id3_info.Artist);
			spSongInfoT.spAlbumName		 = std::string(id3_info.Album);

			DWORD dwMinSize;
			dwMinSize = WideCharToMultiByte(CP_ACP,NULL,spFilePath,-1,NULL,0,NULL,FALSE); //计算长度
			char *pathName= new char[dwMinSize+1];
			pathName[0] = 0x0;
			WideCharToMultiByte(CP_OEMCP,NULL,spFilePath,-1,pathName,dwMinSize,NULL,FALSE);
			spSongInfoT.spSongPath	     = std::string(pathName);
			delete []pathName;

			spSongInfoT.spLrcPath        = std::string("");
			spSongInfoT.spAlbumPath      = std::string("");
			spSongInfoT.spFileFormat     = std::string(mci::unicode_2_ansi(mci::rip_file_ext(spFilePath,true)).c_str());
			CString sSize;
			int MB = mci::get_file_size(spFilePath)/(1024*1024);
			int KB = (mci::get_file_size(spFilePath)-MB*1024*1024)/1024;

			sSize.Format(_T("文件大小：%d.%d M"),MB,KB);
			spSongInfoT.spFileSize       = mci::unicode_2_ansi(sSize);
			spSongInfoT.iFileStartPos    = 0;		
			spSongInfoT.iPlayCount       = 0;		
		}
		else
		{
			spSongInfoT.spSongName     = std::string("未知名称");
			spSongInfoT.spArtistName   = std::string("未知艺人");
			spSongInfoT.spAlbumName    = std::string("未知专辑");
			spSongInfoT.spSongPath     = std::string(mci::unicode_2_ansi(spFilePath));
			spSongInfoT.spLrcPath      = std::string("");
			spSongInfoT.spAlbumPath    = std::string("");
			spSongInfoT.spFileFormat   = mci::unicode_2_ansi(mci::rip_file_ext(spFilePath,true));
			CString sSize;
			int MB = mci::get_file_size(spFilePath)/(1024*1024);
			int KB = (mci::get_file_size(spFilePath)-MB*1024*1024)/1024;

			sSize.Format(_T("文件大小：%d.%d M"),MB,KB);
			spSongInfoT.spFileSize       = mci::unicode_2_ansi(sSize);
			spSongInfoT.iFileStartPos  = 0;		
			spSongInfoT.iPlayCount     = 0;		
		}
		TStreamInfo pInfo;
		player->GetStreamInfo(&pInfo);
		char* pbuf = new char[MAX_PATH];
		pbuf[0] = 0x0;
		sprintf_s(pbuf,MAX_PATH,"%02i:%02i",pInfo.Length.hms.minute,pInfo.Length.hms.second);
		spSongInfoT.spSongTime = std::string(pbuf);
		delete []pbuf;
		player->Release();
		return spSongInfoT;
	}
	catch(...)
	{
		throw L"CSongListUI::PraseInfo(LPCTSTR spFilePath)";
	}
}
bool CSongListUI::SelectItem(int iIndex, bool bTakeFocus,bool bSelected/* = true*/)
{
	if(iIndex<0||iIndex>=GetCount()) return false;
	m_iLastSel = GetCurSel();

	if (!__super::SelectItem(iIndex, bTakeFocus))
		return false;

	

	return true;
}
// void CSongListUI::DoPaint(HDC hDC, const RECT& rcPaint)
// {
// 	if(theApp->get_PlayListIndex() == theApp->get_UIArrar()._pListPanel->GetCurSel())
// 	{
// 		CControlUI* pControl = GetItemAt()
// 	}
// 	CListUI::DoPaint(hDC,rcPaint);
// }

CSongListUI::array CSongListUI::GetItem(int iIndex)
{
	ASSERT(iIndex>=0&&iIndex<this->GetCount());
	array pItem;
	CControlUI* pControl = GetItemAt(iIndex);
	if( pControl != NULL) {
		CListContainerElementUI* pListItem = static_cast<CListContainerElementUI*>(pControl);
		if ((pListItem != NULL))
		{
			pItem._pSongIndex = static_cast<CButtonUI*>(paint_manager_.FindSubControlByName(pListItem,_T("song_index")));
			pItem._pSongName = static_cast<CLabelUI*>(paint_manager_.FindSubControlByName(pListItem,_T("song_name")));
			pItem._pCollect = static_cast<CCheckBoxUI*>(paint_manager_.FindSubControlByName(pListItem,_T("item_collect")));
			pItem._pDelete = static_cast<CButtonUI*>(paint_manager_.FindSubControlByName(pListItem,_T("item_delete")));
			pItem._pTimeContainer = static_cast<CLabelUI*>(paint_manager_.FindSubControlByName(pListItem,_T("item_timeContainer")));
			pItem._pTab = static_cast<CTabLayoutUI*>(paint_manager_.FindSubControlByName(pListItem,_T("item_tab")));


			pItem._pAlbumImage = static_cast<CAlbumButtonUI*>(paint_manager_.FindSubControlByName(pListItem,_T("albumlogo")));
			pItem._pTimeContainer2 = static_cast<CLabelUI*>(paint_manager_.FindSubControlByName(pListItem,_T("item_timeContainer2")));
			pItem._pCollect2 = static_cast<CCheckBoxUI*>(paint_manager_.FindSubControlByName(pListItem,_T("item_collect2")));
			pItem._pShare = static_cast<CButtonUI*>(paint_manager_.FindSubControlByName(pListItem,_T("item_share")));
			pItem._pAlbumInfo = static_cast<CTextUI*>(paint_manager_.FindSubControlByName(pListItem,_T("album_info")));
			
			pItem._pHorUp = static_cast<CHorizontalLayoutUI*>(paint_manager_.FindSubControlByName(pListItem,_T("small_info")));
			pItem._pHorBottom = static_cast<CHorizontalLayoutUI*>(paint_manager_.FindSubControlByName(pListItem,_T("big_info")));

			ASSERT(pItem._pSongIndex);
			ASSERT(pItem._pSongName);
			ASSERT(pItem._pCollect);
			ASSERT(pItem._pDelete);
			ASSERT(pItem._pTimeContainer);
			ASSERT(pItem._pAlbumImage);
			ASSERT(pItem._pTimeContainer2);
			ASSERT(pItem._pCollect2);
			ASSERT(pItem._pShare);
			ASSERT(pItem._pHorUp);
			ASSERT(pItem._pHorBottom);	
		}
	}
	return pItem;
}
int CSongListUI::UpdateIndex(int iIndex)
{
	if(this->GetCount()<=0) return 0;
	ASSERT(iIndex>=0&&iIndex<=this->GetCount());
	int count = 0;
	for (int i=iIndex;i<this->GetCount();++i)
	{
		count ++;
		CSongListUI::array pItem = GetItem(i);
		pItem._pSongIndex->SetText(mci::ToString(i+1));
	}
	return count;
}
void CSongListUI::Update(int iSongIndex)
{
	if(iSongIndex<0) return ;
	if(GetCount()<=0) return ;
	CControlUI* pControl = NULL;
	CListContainerElementUI* pListItem = NULL;
	CSongListUI::array pItem;
	ZeroMemory(&pItem,sizeof(pItem));

	for (int i=0;i<GetCount();++i)
	{
		pControl = GetItemAt(i);
		ASSERT(pControl);
		pListItem = static_cast<CListContainerElementUI*>(pControl);
		ASSERT(pListItem);
		pItem = GetItem(i);
		ASSERT(pItem._pHorBottom);
		spSongInfo spSongInfoT;
		if(i == iSongIndex)
		{
			pItem._pHorBottom->SetVisible(true);
			pItem._pTab->SelectItem(1);
			pItem._pCollect->SetVisible(false);
			pListItem->SetFixedHeight(kListItemSelectedHeight);
			pListItem->SetBkColor(this->GetSelectedItemBkColor());
			pListItem->SetBkImage(this->GetSelectedItemImage());
			ASSERT(pItem._pSongName);
			CDuiString sNameInfo;
			spSongInfoT = SongInfo(iSongIndex);
			sNameInfo = mci::ToString(spSongInfoT.spSongName.c_str()) + _T(" - ");
			sNameInfo += mci::ToString(spSongInfoT.spArtistName.c_str());
			pItem._pSongName->SetText(sNameInfo);
		}else
		{
			pItem._pHorBottom->SetVisible(false);
			pItem._pTab->SelectItem(0);
			pItem._pCollect->SetVisible(true);
			pListItem->SetFixedHeight(kListItemNormalHeight);
			pListItem->SetBkColor(this->GetItemBkColor());
			pListItem->SetBkImage(this->GetItemBkImage());
			ASSERT(pItem._pSongName);
			spSongInfoT = SongInfo(i);
			pItem._pSongName->SetText(mci::ToString(spSongInfoT.spSongName.c_str()));
		}
	}
}
void CSongListUI::SetTimeUsed(int iIndex,LPCTSTR sTime)
{
	if(theApp->get_PlayListIndex() == theApp->get_UIArrar()._pListPanel->GetCurSel())
	{
		if(iIndex>=0&&iIndex<GetCount())
		{
			CSongListUI::array pItem = GetItem(iIndex);
			ASSERT(pItem._pTimeContainer2);
			pItem._pTimeContainer2->SetText(sTime);
		}
	}
}
void CSongListUI::Update(spSongInfo spSongInfoT)
{
	if(GetCount()<=0) return ;
	CControlUI* pControl = NULL;
	CListContainerElementUI* pListItem = NULL;
	CSongListUI::array pItem;
	ZeroMemory(&pItem,sizeof(pItem));

	for (int i=0;i<GetCount();++i)
	{
		pControl = GetItemAt(i);
		spSongInfo spSongInfoTmp = SongInfo(i);
		ASSERT(pControl);
		pListItem = static_cast<CListContainerElementUI*>(pControl);
		ASSERT(pListItem);
		pItem = GetItem(i);
		ASSERT(pItem._pHorBottom);
		if(spSongInfoT == spSongInfoTmp)
		{//同一首歌
			pItem._pHorBottom->SetVisible(true);
			pItem._pTab->SelectItem(1);
			pItem._pCollect->SetVisible(false);
			pListItem->SetFixedHeight(kListItemSelectedHeight);
			pListItem->SetBkColor(this->GetSelectedItemBkColor());
			pListItem->SetBkImage(this->GetSelectedItemImage());
			ASSERT(pItem._pSongName);
			CDuiString sNameInfo;

			sNameInfo = mci::ToString(spSongInfoTmp.spSongName.c_str()) + _T(" - ");
			sNameInfo += mci::ToString(spSongInfoTmp.spArtistName.c_str());
			pItem._pSongName->SetText(sNameInfo);
		}else
		{
			pItem._pHorBottom->SetVisible(false);
			pItem._pTab->SelectItem(0);
			pItem._pCollect->SetVisible(true);
			pListItem->SetFixedHeight(kListItemNormalHeight);
			pListItem->SetBkColor(this->GetItemBkColor());
			pListItem->SetBkImage(this->GetItemBkImage());
			ASSERT(pItem._pSongName);
			spSongInfoTmp = SongInfo(i);
			pItem._pSongName->SetText(mci::ToString(spSongInfoTmp.spSongName.c_str()));
		}
	}
}
void CSongListUI::RemoveSong(const int iIndex)
{
	if (iIndex>=0&&iIndex<_pSongList.size())
	{
		_pSongList.erase(_pSongList.begin()+iIndex);
	}
}
_LieBao_NameSpaceEnd