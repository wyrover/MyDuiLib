#ifndef ILogger_H
#define ILogger_H
#pragma once

namespace DuiLib
{
#define DUI_LOG_THRESHOLD   0
	/* ----------------------------------------------------------------------------*/
	/**
	* @brief 日志接口类
	*
	* 提供一个操作日志的接口，该类是操作系统无关的，而实现可能是操作系统相关的
	*/
	/* ----------------------------------------------------------------------------*/
	class UILIB_API ILogger
	{
	public:
		virtual void flush() = 0;
		
		virtual void logMessage(const char* lpstrLog) = 0;
		
		class Stream
			: public IOStreamMaker
		{
			ILogger* m_target;
		public:
			Stream(ILogger* target) : m_target(target){}

			void output(const char* lpstrLog){
				m_target->logMessage(lpstrLog);
			}
		};
		Stream stream(){ return Stream(this); }
	};

	class TestLogger : public ILogger
	{
	public:
		TestLogger(const char* name = "test.log"){
			fp = NULL;
			fopen_s(&fp,name, "wb");
		}
		virtual ~TestLogger(){
			if (fp)
			{
				fclose(fp);
				fp = NULL;
			}
		}
		virtual void flush() {
			if (fp) fflush(fp);
		}

		virtual void write(const char* lpstrLog) {
			std::string s = lpstrLog;
			fwrite(s.c_str(), s.size(), 1, fp);
		}
		void logMessage(const char* lpstrLog){
			write(lpstrLog);
		}
	private:
		FILE* fp;
	};

}


#endif//ILogger_H