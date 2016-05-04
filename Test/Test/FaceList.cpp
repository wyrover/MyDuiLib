#include "StdAfx.h"
#include "FaceList.h"

CFaceInfo::CFaceInfo(void)
{
	m_nId = -1;
	m_nIndex = -1;
	m_strTip = _T("");
	m_strFileName = _T("");
}

CFaceInfo::~CFaceInfo(void)
{

}

CFaceList::CFaceList(void)
{
	Reset();
}

CFaceList::~CFaceList(void)
{
	Reset();
}

void CFaceList::Reset()
{
// 	m_nWidth = 28;
// 	m_nHeight = 28;
// 	m_nZoomWidth = 86;
// 	m_nZoomHeight = 86;
// 	m_nCol = 15;
	m_nItemWidth = m_nItemHeight = 0;
	m_nZoomWidth = m_nZoomHeight = 0;
	m_nRow = m_nCol = 0;
	
	for (int i = 0; i < (int)m_arrFaceInfo.size(); i++)
	{
		CFaceInfo * lpFaceInfo = m_arrFaceInfo[i];
		if (lpFaceInfo != NULL)
			delete lpFaceInfo;
	}
	m_arrFaceInfo.clear();
}

BOOL CFaceList::LoadConfigFile(LPCTSTR lpszFileName)
{
	Reset();

	CMarkup xmlDoc;

	BOOL bRet = xmlDoc.LoadFromFile(lpszFileName);
	if (!bRet)
		return FALSE;

	CMarkupNode pRoot = xmlDoc.GetRoot();

	if (pRoot.IsValid())
	{
		m_nItemWidth = pRoot.GetAttributeInt(_T("item_width"));
		m_nItemHeight = pRoot.GetAttributeInt(_T("item_height"));
		m_nZoomWidth = pRoot.GetAttributeInt(_T("zoom_width"));
		m_nZoomHeight = pRoot.GetAttributeInt(_T("zoom_height"));
		m_nRow = pRoot.GetAttributeInt(_T("row"));
		m_nCol = pRoot.GetAttributeInt(_T("col"));

		CMarkupNode xmlSubNode = pRoot.GetChild(_T("face"));
		while (xmlSubNode.IsValid() && xmlSubNode.HasSiblings())
		{
			CFaceInfo * lpFaceInfo = new CFaceInfo;
			if (lpFaceInfo != NULL)
			{
				lpFaceInfo->m_nId = xmlSubNode.GetAttributeInt(_T("id"));
				lpFaceInfo->m_strTip = xmlSubNode.GetAttributeValue(_T("tip"));
				lpFaceInfo->m_strFileName = xmlSubNode.GetAttributeValue(_T("file"));
				m_arrFaceInfo.push_back(lpFaceInfo);
			}
			
			xmlSubNode = xmlSubNode.GetSibling();
		}
	}
	xmlDoc.Release();

	return TRUE;
}

CFaceInfo * CFaceList::GetFaceInfo(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_arrFaceInfo[nIndex])
		return m_arrFaceInfo[nIndex];
	else
		return NULL;
}

CFaceInfo * CFaceList::GetFaceInfoById(int nFaceId)
{
	for (int i = 0; i < (int)m_arrFaceInfo.size(); i++)
	{
		CFaceInfo * lpFaceInfo = m_arrFaceInfo[i];
		if (lpFaceInfo != NULL && lpFaceInfo->m_nId == nFaceId)
			return lpFaceInfo;
	}

	return NULL;
}

CFaceInfo * CFaceList::GetFaceInfoByIndex(int nFaceIndex)
{
	for (int i = 0; i < (int)m_arrFaceInfo.size(); i++)
	{
		CFaceInfo * lpFaceInfo = m_arrFaceInfo[i];
		if (lpFaceInfo != NULL && lpFaceInfo->m_nIndex == nFaceIndex)
			return lpFaceInfo;
	}

	return NULL;
}