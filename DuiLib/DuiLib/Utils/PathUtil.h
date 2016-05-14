#ifndef PATHUTIL_H
#define PATHUTIL_H

namespace DuiLib
{
	class UILIB_API PathUtil
	{
	public:
		static CDuiString GetAppPath();	// 获取应用程序执行路径
		static CDuiString GetCurAppName(BOOL bNoExt = TRUE);//
		static CDuiString GetCurDir();	// 获取应用程序当前目录
		static CDuiString GetTempPath();	// 获取当前系统的临时文件夹的路径
		static CDuiString GetTempFileName(LPCTSTR lpszFileName);	// 获取当前系统的临时文件夹的路径下的唯一命名的临时文件名(全路径)
		static CDuiString GetRandomFileName(LPCTSTR lpszPath, LPCTSTR lpszFileName);	// 获取随机文件名(全路径)

		static BOOL IsDirectory(LPCTSTR lpszPath);	// 检测指定路径是否目录
		static BOOL IsFileExist(LPCTSTR lpszFileName);	// 检测指定文件是否存在
		static BOOL IsDirectoryExist(LPCTSTR lpszPath);	// 检测指定目录是否存在
		static BOOL CreateDirectory(LPCTSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
		static BOOL IsPathValid(LPCTSTR lpszPath); //路径是否合法

		static CDuiString CombinePath(LPCTSTR lpszPath1, LPCTSTR lpszPath2);//合并路径

		static CDuiString GetPathRoot(LPCTSTR lpszPath);	// 获取指定路径的根目录信息
		static CDuiString GetDirectoryName(LPCTSTR lpszPath);	// 返回指定路径字符串的目录信息
		static CDuiString GetFileName(LPCTSTR lpszPath); // 返回指定路径字符串的文件名和扩展名
		static CDuiString GetFileNameWithoutExtension(LPCTSTR lpszPath);	// 返回不具有扩展名的路径字符串的文件名
		static CDuiString GetExtension(LPCTSTR lpszPath);	// 返回指定的路径字符串的扩展名
		static CDuiString GetFullPath(LPCTSTR lpszPath);	// 根据指定的相对路径获取绝对路径

		
	};
}

#endif//PATHUTIL_H