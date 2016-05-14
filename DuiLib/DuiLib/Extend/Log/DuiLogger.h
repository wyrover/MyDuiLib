#ifndef LOGGER_H_
#define LOGGER_H_
#pragma once

/*
    * 类名：DuiLogger
    * 作用：提供写日志功能，支持多线程，支持可变形参数操作，支持写日志级别的设置
    * 接口：
*/
namespace DuiLib
{
	class UILIB_API DuiLogger : public ILogger, public Singleton<DuiLogger>
    {
		DECLARE_SINGLETON_CLASS(DuiLogger)
    public:
		typedef DuiLogger            self_type;
#ifdef _UNICODE
		typedef wchar_t char_type;
		typedef std::wstring          string_type;
#else
		typedef char char_type;
		typedef std::string          string_type;
#endif
		
		enum Log_Level
		{
			SysLog = 0,
			InfoLog = 1,
			WarningLog = 2,
			ErrorLog = 3,
		};
		enum Log_Type
		{
			YEAR = 0,
			MONTH = 1,
			DAY = 2,
			HOUR = 3,
			MIN = 4,
			SECOND = 5,
		};
	public:
		virtual void flush();
		virtual void logMessage(const char* lpstrLog);
		virtual void logMessage(const wchar_t* lpstrLog);
		virtual void formatLog(const char_type* fmt, ...);
		virtual void formatLog(const char_type* srcfile, unsigned int line, Log_Level lvl, const char_type* lpstrLog, ...);

		void ConsoleToggle(bool bConsole) { _bConsole = bConsole; }
		void VSOutputToggle(bool bVsOutput) { _bVsOutput = bVsOutput; }
	public:
		void Init(const char_type* filename = _T("duilib.log"), Log_Level lev = Log_Level::InfoLog, Log_Type type = Log_Type::DAY, size_t maxSaveLogCnt = 3);
		
		DuiLogger();

		virtual ~DuiLogger();

		
		bool isValid()const { return _IsOpen(); }

	protected:
		DuiLogger(const self_type&){}
		self_type& operator = (const self_type&){ return *this; }

		template<typename charT>
		void _Vfprintf(const charT* fmt, va_list& va);
	private:
		void write(const wchar_t* lpstrLog);
		void write(const char* lpstrLog);
	private:
		bool                     _Open();
		void                     _Close();
		bool                     _IsOpen() const;
		unsigned long            _GetCurrentThreadID() const;
		void                     _ScanAllFiles(const string_type& rootPath, std::vector<string_type>& container, bool isRecursive = true);
		void                     _Clear();
	private:
		Log_Level                _level;
		Log_Type                 _type;
		size_t                   _maxSaveCnt;

		char_type				 _filename[512];
		char_type				 _timename[256];
        //日志文件
		IOBase *			     _pIO;
		//Lock
		ILock *  				 _pLock;
		//std
		bool					 _bConsole;
		//vsoutput
		bool                     _bVsOutput;
    };

#define  DuiLogInfo(fmt,...)  (DuiLogger::Instance()->formatLog(__FILET__,__LINE__,DuiLogger::Log_Level::InfoLog,fmt,##__VA_ARGS__))
#define  DuiLogWarning(fmt,...) (DuiLogger::Instance()->formatLog(__FILET__,__LINE__,DuiLogger::Log_Level::WarningLog,fmt,##__VA_ARGS__))
#define  DuiLogError(fmt,...) (DuiLogger::Instance()->formatLog(__FILET__,__LINE__,DuiLogger::Log_Level::ErrorLog,fmt,##__VA_ARGS__))
}
#endif
