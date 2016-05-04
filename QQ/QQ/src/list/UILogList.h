
/***********************************************************
 *	FileName£ºUISongList.hpp
 *  Author  £ºDFn Li
 *  Timer   : 2013/3/2 14:24
 *  E-Mail  : libyyu@qq.com
 *  Comment : 
 *  Version : 1.0.0.1
 ***********************************************************/

#ifndef UISONGLIST_HPP
#define UISONGLIST_HPP


_LieBao_NameSpaceBegin

class CItemTip;

class CSongListUI : public CListUI
{
public:
	struct array
	{
		CButtonUI* _pSongIndex;
		CLabelUI*  _pSongName;
		CCheckBoxUI* _pCollect;
		CButtonUI* _pDelete;
		CLabelUI*  _pTimeContainer;

		CTabLayoutUI* _pTab;

		CAlbumButtonUI*  _pAlbumImage;
		CLabelUI*  _pTimeContainer2;
		CCheckBoxUI* _pCollect2;
		CButtonUI* _pShare;
		CTextUI* _pAlbumInfo;

		CHorizontalLayoutUI* _pHorUp;
		CHorizontalLayoutUI* _pHorBottom;
	};
	enum {SCROLL_TIMERID = 10};

	CSongListUI(CPaintManagerUI& paint_manager);

	~CSongListUI();

	bool Add(CControlUI* pControl);

	bool AddAt(CControlUI* pControl, int iIndex);

	bool Remove(CControlUI* pControl);

	bool RemoveAt(int iIndex);

	void RemoveAll();

	void DoEvent(TEventUI& event);
	bool AddNode(spSongInfo spSongInfoT);
	spSongInfo PraseInfo(LPCTSTR spFilePath,const char* spPanelName);
	bool SelectItem(int iIndex, bool bTakeFocus = false,bool bSelected = true);
	array GetItem(int iIndex);
	int  UpdateIndex(int iIndex);
	void Update(int iSongIndex);
	void Update(spSongInfo spSongInfoT);
	void SetTimeUsed(int iIndex,LPCTSTR sTime);
//	void DoPaint(HDC hDC, const RECT& rcPaint);
 	spSongInfo SongInfo(const int iIndex)const {return _pSongList[iIndex];}
	void SongInfo(spSongInfo spSong,const int iIndex){_pSongList[iIndex] = spSong;}
	void RemoveSong(const int iIndex);
	void Clear()
	{
		if(_pSongList.size()>0)
 			_pSongList.erase(_pSongList.begin(),_pSongList.end());
	}
	int m_iLastSel;
private:

	LONG	delay_deltaY_;
	DWORD	delay_number_;
	DWORD	delay_left_;

	

    CDialogBuilder m_dlgBuilder;

 	std::vector<spSongInfo> _pSongList;
public:
	CPaintManagerUI& paint_manager_;
	CItemTip* m_pItemTip;

};

_LieBao_NameSpaceEnd

#endif // UISONGLIST_HPP