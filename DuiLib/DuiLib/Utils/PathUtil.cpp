#include "UIlib.h"
#include "PathUtil.h"

namespace DuiLib
{

	// 获取应用程序执行路径
	CDuiString PathUtil::GetAppPath()
	{
		TCHAR szPath[MAX_PATH] = { 0 };

		::GetModuleFileName(NULL, szPath, MAX_PATH);

		CDuiString strPath = GetDirectoryName(szPath);
		_tcsncpy(szPath, strPath, MAX_PATH);
		

		return szPath;
	}

	CDuiString PathUtil::GetCurAppName(BOOL bNoExt)
	{
		TCHAR szPath[MAX_PATH] = { 0 };
		::GetModuleFileName(NULL, szPath, MAX_PATH);
		if (bNoExt)
			return GetFileNameWithoutExtension(szPath);
		else
			return GetFileName(szPath);
	}

	// 获取应用程序当前目录
	CDuiString PathUtil::GetCurDir()
	{
		TCHAR szCurDir[MAX_PATH] = { 0 };
		::GetCurrentDirectory(MAX_PATH, szCurDir);


		if (szCurDir[_tcslen(szCurDir) - 1] != _T('\\'))
			_tcscat(szCurDir, _T("\\"));

		return szCurDir;
	}

	// 获取当前系统的临时文件夹的路径
	CDuiString PathUtil::GetTempPath()
	{
		TCHAR szTempPath[MAX_PATH] = { 0 };

		::GetTempPath(MAX_PATH, szTempPath);

		if (szTempPath[_tcslen(szTempPath) - 1] != _T('\\'))
			_tcscat(szTempPath, _T("\\"));

		return szTempPath;
	}

	// 获取当前系统的临时文件夹的路径下的唯一命名的临时文件名(全路径)
	CDuiString PathUtil::GetTempFileName(LPCTSTR lpszFileName)
	{
		return GetRandomFileName(GetTempPath(), lpszFileName);
	}

	// 获取随机文件名(全路径)
	CDuiString PathUtil::GetRandomFileName(LPCTSTR lpszPath, LPCTSTR lpszFileName)
	{
		CDuiString strPath, strFileName, strExtFileName, strFullPath;
		TCHAR szBuf[MAX_PATH] = { 0 };

		if (!IsDirectoryExist(lpszPath))
			strPath = GetCurDir();
		else
			strPath = lpszPath;

		strFileName = GetFileNameWithoutExtension(lpszFileName);
		strExtFileName = GetExtension(lpszFileName);

		for (int i = 2; i < 10000; i++)
		{
			if (strExtFileName.IsEmpty())
			{
				strFullPath = strPath;
				strFullPath += strFileName;
				_stprintf(szBuf,  _T("%d"), i);

				strFullPath += szBuf;
			}
			else
			{
				strFullPath = strPath;
				strFullPath += strFileName;
				_stprintf(szBuf, _T("%d."), i);
				strFullPath += szBuf;
				strFullPath += strExtFileName;
			}

			if (!IsFileExist(strFullPath))
				return strFullPath;
		}

		return _T("");
	}

	// 检测指定路径是否目录
	BOOL PathUtil::IsDirectory(LPCTSTR lpszPath)
	{
		if (NULL == lpszPath || NULL == *lpszPath)
			return FALSE;

		DWORD dwAttr = ::GetFileAttributes(lpszPath);

		if ((dwAttr != 0xFFFFFFFF) && (dwAttr & FILE_ATTRIBUTE_DIRECTORY))
			return TRUE;
		else
			return FALSE;
	}

	// 检测指定文件是否存在
	BOOL PathUtil::IsFileExist(LPCTSTR lpszFileName)
	{
		if (NULL == lpszFileName || NULL == *lpszFileName)
			return FALSE;

		if (::GetFileAttributes(lpszFileName) != 0xFFFFFFFF)
			return TRUE;
		else
			return FALSE;
	}

	// 检测指定目录是否存在
	BOOL PathUtil::IsDirectoryExist(LPCTSTR lpszPath)
	{
		if (NULL == lpszPath || NULL == *lpszPath)
			return FALSE;

		DWORD dwAttr = ::GetFileAttributes(lpszPath);

		if ((dwAttr != 0xFFFFFFFF) && (dwAttr & FILE_ATTRIBUTE_DIRECTORY))
			return TRUE;
		else
			return FALSE;
	}

	BOOL PathUtil::CreateDirectory(LPCTSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
	{
		TCHAR cPathUtil[MAX_PATH] = { 0 };
		TCHAR cTmpPath[MAX_PATH] = { 0 };
		TCHAR * lpPos = NULL;
		TCHAR cTmp = _T('\0');

		if (NULL == lpPathName || NULL == *lpPathName)
			return FALSE;

		_tcsncpy(cPathUtil, lpPathName, MAX_PATH);

		for (int i = 0; i < (int)_tcslen(cPathUtil); i++)
		{
			if (_T('\\') == cPathUtil[i])
				cPathUtil[i] = _T('/');
		}

		lpPos = _tcschr(cPathUtil, _T('/'));
		while (lpPos != NULL)
		{
			if (lpPos == cPathUtil)
			{
				lpPos++;
			}
			else
			{
				cTmp = *lpPos;
				*lpPos = _T('\0');
				_tcsncpy(cTmpPath, cPathUtil, MAX_PATH);
				::CreateDirectory(cTmpPath, lpSecurityAttributes);
				*lpPos = cTmp;
				lpPos++;
			}
			lpPos = _tcschr(lpPos, _T('/'));
		}

		return TRUE;
	}
	BOOL PathUtil::IsPathValid(LPCTSTR lpszPath)
	{
		return TRUE;
	}
	CDuiString PathUtil::CombinePath(LPCTSTR lpszPath1, LPCTSTR lpszPath2)
	{
		CDuiString strPath1(lpszPath1);
		CDuiString strPath2(lpszPath2);

		strPath1.Replace(_T("\\"), _T("/"));
		strPath2.Replace(_T("\\"), _T("/"));

		int nLen1 = strPath1.GetLength();
		int nLen2 = strPath2.GetLength();
		if (strPath1[nLen1 - 1] == _T('/'))
			strPath1 = strPath1.Mid(0, nLen1 - 1);
		if (strPath2[0] == _T('/'))
			strPath2 = strPath2.Mid(1, nLen2 - 1);

		return strPath1 + _T("/") + strPath2;
	}
	// 获取指定路径的根目录信息
	CDuiString PathUtil::GetPathRoot(LPCTSTR lpszPath)
	{
		if (NULL == lpszPath || NULL == *lpszPath)
			return _T("");

		CDuiString strPath(lpszPath);

		strPath.Replace(_T("\\"), _T("/"));

		int nPos = strPath.Find(_T('/'));
		if (nPos != -1)
			strPath = strPath.Mid(0, nPos + 1);

		return strPath;
	}

	// 返回指定路径字符串的目录信息
	CDuiString PathUtil::GetDirectoryName(LPCTSTR lpszPath)
	{
		if (NULL == lpszPath || NULL == *lpszPath)
			return _T("");

		CDuiString strPath(lpszPath);

		strPath.Replace(_T("\\"), _T("/"));

		int nPos = strPath.ReverseFind(_T('/'));
		if (nPos != -1)
			strPath = strPath.Mid(0, nPos + 1);

		return strPath;
	}

	// 返回指定路径字符串的文件名和扩展名
	CDuiString PathUtil::GetFileName(LPCTSTR lpszPath)
	{
		if (NULL == lpszPath || NULL == *lpszPath)
			return _T("");

		CDuiString strPath(lpszPath);

		strPath.Replace(_T("\\"), _T("/"));

		int nPos = strPath.ReverseFind(_T('/'));
		if (nPos != -1)
			strPath = strPath.Mid(nPos + 1);

		return strPath;
	}

	// 返回不具有扩展名的路径字符串的文件名
	CDuiString PathUtil::GetFileNameWithoutExtension(LPCTSTR lpszPath)
	{
		if (NULL == lpszPath || NULL == *lpszPath)
			return _T("");

		CDuiString strPath(lpszPath);

		strPath.Replace(_T("\\"), _T("/"));

		int nPos = strPath.ReverseFind(_T('/'));
		if (nPos != -1)
			strPath = strPath.Mid(nPos + 1);

		nPos = strPath.ReverseFind(_T('.'));
		if (nPos != -1)
			strPath = strPath.Mid(0, nPos);

		return strPath;
	}

	// 返回指定的路径字符串的扩展名
	CDuiString PathUtil::GetExtension(LPCTSTR lpszPath)
	{
		if (NULL == lpszPath || NULL == *lpszPath)
			return _T("");

		CDuiString strPath(lpszPath);

		int nPos = strPath.ReverseFind(_T('.'));
		if (nPos != -1)
			strPath = strPath.Mid(nPos + 1);

		return strPath;
	}

	// 根据指定的相对路径获取绝对路径
	CDuiString PathUtil::GetFullPath(LPCTSTR lpszPath)
	{
		if (NULL == lpszPath || NULL == *lpszPath)
			return _T("");

		CDuiString strPath(lpszPath);

		strPath.Replace(_T("\\"), _T("/"));

		TCHAR cFirstChar = strPath.GetAt(0);
		TCHAR cSecondChar = strPath.GetAt(1);

		if (cFirstChar == _T('/'))
		{
			CDuiString strCurDir = GetAppPath();
			CDuiString strRootPath = GetPathRoot(strCurDir);
			return strRootPath + strPath;
		}
		else if (::IsCharAlpha(cFirstChar) && cSecondChar == _T(':'))
		{
			return strPath;
		}
		else
		{
			CDuiString strCurDir = GetAppPath();
			return strCurDir + strPath;
		}
	}

}