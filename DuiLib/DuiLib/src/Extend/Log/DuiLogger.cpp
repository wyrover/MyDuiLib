#include "stdafx.h"

#include <time.h>
#include <direct.h>
#include <algorithm>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#else
#include<pthread.h>
#include <sys/syscall.h>
#endif

namespace DuiLib
{
	const static DuiLogger::char_type* pLevel[] = { _T("Sys"), _T("Info"), _T("Warn"), _T("Error") };

	void DuiLogger::Init(const char_type* filename, Log_Level lev, Log_Type type, size_t maxSaveLogCnt)
	{
		std::locale::global(std::locale("chs"));
		assert(filename);
		string_type s(filename);
		std::replace(s.begin(), s.end(), _T('\\'), _T('/'));
		string_type::size_type index = s.find_last_of(_T('/'));
		string_type _dir, _name;
		if (std::string::npos != index)
		{
			_dir = s.substr(0, index + 1);
			_name = s.substr(index + 1);

			assert(!_dir.empty());
			assert(!_name.empty());

			if (!PathUtil::IsDirectoryExist(_dir.c_str()))
			{
				assert(PathUtil::CreateDirectory(_dir.c_str(), NULL));
			}
		}
		_pIO = NULL;	
		_level = lev;
		_type = type;
		_maxSaveCnt = maxSaveLogCnt;

		memset(_filename, 0, sizeof(_filename));
		_tcscpy(_filename, filename);

		memset(_timename, 0, sizeof(_timename));
		
		assert(_Open());
	}

	DuiLogger::DuiLogger()
		: _pIO(NULL)
		, _pLock(NULL)
		, _bConsole(false)
		, _bVsOutput(false)
	{
		if (NULL == _pLock)
			_pLock = LockHelper::newLock<critical_session>();

		assert(_pLock);

		CDuiString sLogName = PathUtil::GetCurAppName(FALSE);
		sLogName.Append(_T(".log"));
		Init(sLogName.GetData());
	}

	DuiLogger::~DuiLogger()
	{
		_Close();
		LockHelper::delLock(_pLock);
	}

	bool DuiLogger::_Open()
	{
		if (_IsOpen())
			return true;

		this->_Clear();

		_pIO = IOHelper::newIO<WinIO>();
		assert(_pIO);
		IOHelper IO(_pIO);
		/*if (IO.is_file_exists(_filename))
			IO.open(_filename, false);
			else */
#ifdef _UNICODE
		std::string filenameA = OSTypeHelper::getStr<wchar_t*>(_filename);
		IO.create(filenameA.c_str());
#else
		IO.create(_filename);
#endif

		int nErr = IO.get_lasterror();
		
		return _IsOpen();
	}
	void DuiLogger::_Close()
	{
		if (_IsOpen())
		{
			LockHelper lock(_pLock);
			{
				char_type szLogEnd[200] = _T("\r\n-----------------------------------LogEnd");
				this->write(szLogEnd);

				IOHelper IO(_pIO);
				IO.close();
				IOHelper::delIO(_pIO);
			}
		}
	}
	void DuiLogger::_Clear()
	{

	}
	bool DuiLogger::_IsOpen() const
	{
		if (!_pIO)
			return false;
		IOHelper IO(_pIO);
		return IO.is_open();
	}

	unsigned long DuiLogger::_GetCurrentThreadID() const
	{
#ifdef _WIN32
		return ::GetCurrentThreadId();
#else
		return (unsigned long)syscall(SYS_thread_selfid);
#endif
	}

	template<>
	void DuiLogger::_Vfprintf(const char* fmt, va_list& va)
	{
		char szBuffer[1025] = { 0 };
		int iRet = ::vsprintf(szBuffer, fmt, va);

		write(szBuffer);
	}

	template<>
	void DuiLogger::_Vfprintf(const wchar_t* fmt, va_list& va)
	{
		wchar_t szBuffer[1025] = { 0 };
		int iRet = ::vswprintf(szBuffer, fmt, va);

		write(szBuffer);
	}

	void DuiLogger::flush()
	{
		IOHelper IO(_pIO);
		IO.flush();
	}
	
	void DuiLogger::write(const char* lpstrLog)
	{
		IOHelper IO(_pIO);
		unsigned int nWrite = 0;
		unsigned int nLen = strlen(lpstrLog);
		IO.write(lpstrLog, nLen, &nWrite);

		if (_bVsOutput)
		{
			CDuiString s;
			s.AssignString(lpstrLog);
			VSOutput::Write(_T("%s"),s.GetData());
		}
		if (_bConsole)
		{
			CDuiString s;
			s.AssignString(lpstrLog);
			Console::Write(_T("%s"), s.GetData());
		}
	}

	void DuiLogger::write(const wchar_t* lpstrLog)
	{
		std::string s = OSTypeHelper::getStr<const wchar_t*>(lpstrLog);
		write(s.c_str());
	}

	void DuiLogger::logMessage(const char* lpstrLog)
	{
		this->write(lpstrLog);
	}

	void DuiLogger::logMessage(const wchar_t* lpstrLog)
	{
		this->write(lpstrLog);
	}

	void DuiLogger::formatLog(const char_type* fmt, ...)
	{
		assert(fmt);
		if (!fmt)
			return ;

		LockHelper lock(_pLock);
		{
			if (_IsOpen())
			{
				va_list va;
				va_start(va, fmt);
				this->_Vfprintf<char_type>(fmt, va);
				va_end(va);
			}
			this->flush();
		}
	}

	void DuiLogger::formatLog(const char_type* srcfile, unsigned int line, Log_Level lev, const char_type* fmt, ...)
	{
		assert(fmt);
		if (!fmt)
			return;

		if (lev < _level && SysLog != lev)
			return;

		LockHelper lock(_pLock);
		{
			if (!_IsOpen()) return;

			time_t t = time(NULL);
			tm* aTm = localtime(&t);

			char_type szTitle[2048] = { 0 };
			_stprintf(szTitle, _T("\r\n[%s][%-4d-%02d-%02d %02d:%02d:%02d][%lX][%s:%d]\r\n\t"),
				pLevel[lev],
				aTm->tm_year + 1900,
				aTm->tm_mon + 1,
				aTm->tm_mday,
				aTm->tm_hour,
				aTm->tm_min,
				aTm->tm_sec,
				_GetCurrentThreadID(),
				PathUtil::GetFileName(srcfile).GetData(),
				line);
						
			this->write(szTitle);
			if (this->_IsOpen())
			{
				va_list va;
				va_start(va, fmt);
				this->_Vfprintf<char_type>(fmt, va);
				va_end(va);
			}
			this->flush();
		}
	}
}