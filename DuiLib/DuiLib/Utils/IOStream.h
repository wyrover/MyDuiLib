#ifndef _IOStream__h
#define _IOStream__h
#pragma once
#include <locale.h>

namespace DuiLib
{
	//interface of ostream
	class IOStream;
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief 自定义流运算符操作符类型
	 *
	 * 当该变量被流运算符输出到某流时，会调用该函数指针所指向的函数，参数为输出流。
	 */
	/* ----------------------------------------------------------------------------*/
	typedef IOStream& (*StreamSymbol_t)(IOStream& Target);
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief 输出流接口
	 * @attention 在继承类析构函数里必须调用flush。
	 */
	/* ----------------------------------------------------------------------------*/
	class UILIB_API IOStream
	{
	public:
		virtual IOStream& operator <<(int) = 0;
		virtual IOStream& operator <<(float) = 0;
		virtual IOStream& operator <<(wchar_t) = 0;
		virtual IOStream& operator <<(char) = 0;
		virtual IOStream& operator <<(wchar_t*) = 0;
		virtual IOStream& operator <<(char*) = 0;
		virtual IOStream& operator <<(void*) = 0;
		IOStream& operator <<(StreamSymbol_t v){return v(*this);}
		virtual void flush() = 0;
	};
	class UILIB_API OSTypeHelper
	{
	public:	

		template<typename param_type>
		static std::string getStr(param_type v)
		{
			std::string o;
			toValue(v, o);
			return o;
		}

		template<typename param_type>
		static std::wstring getStrW(param_type v)
		{
				std::wstring o;
				toValue(v, o);
				return o;
		}
	protected:
		template<typename param_type>
		static void toType(param_type v,std::string& o);	
	
		template<typename param_type>
		static void  toValue(param_type v,std::string& o)
		{
			return toType(v,o);
		}
	
		template<typename param_type>
		static void toType(param_type v, std::wstring& o);

		template<typename param_type>
		static void  toValue(param_type v, std::wstring& o)
		{
			return toType(v, o);
		}
		/////////////////////////////////////////////////////////
		template<>
		static void toType(int v,std::string& o)
		{
			char buf[MAX_PATH] = { 0 };
			sprintf_s(buf, "%d", v);
			o = std::string(buf);
		}
		
		template<>
		static void toType(long v, std::string& o)
		{
			char buf[MAX_PATH] = { 0 };
			sprintf_s(buf, "%d", v);
			o = std::string(buf);
		}
		
		template<>
		static void toType(float v, std::string& o)
		{
			char buf[MAX_PATH] = { 0 };
			sprintf_s(buf, "%f", v);
			o = std::string(buf);
		}
		
		template<>
		static void toType(char v,std::string& o)
		{
			o += v;
		}
		
		template<>
		static void toType(char* v,std::string& o)
		{
			o = std::string(v);
		}
		
		template<>
		static void toType(const char* v,std::string& o)
		{
			o = std::string(v);
		}
		template<>
		static void toType(void* v,std::string& o)
		{
			char buf[MAX_PATH] = { 0 };
			sprintf_s(buf, "%p", v);
			o = std::string(buf);
		}

		template<>
		static void toType(wchar_t* v, std::string& o)
		{
			setlocale(LC_ALL, "");
			std::wstring str(v);
#    if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN64__)
			int size = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
#	else
			size_t size = wcstombs(NULL, str.c_str(), 0);
#	endif

			std::string mbstr(size, wchar_t(0));
#    if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN64__)
			WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, const_cast<char*>(mbstr.c_str()), size, NULL, NULL);
#	else
			wcstombs(const_cast<char*>(mbstr.c_str()), const_cast<wchar_t*>(str.c_str()), (size + 1) * 4);
#	endif
			o = mbstr;
		}
		
		template<>
		static void toType(const wchar_t* v, std::string& o)
		{
			setlocale(LC_ALL, "");
			std::wstring str(v);
#    if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN64__)
			int size = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
#	else
			size_t size = wcstombs(NULL, str.c_str(), 0);
#	endif

			std::string mbstr(size, wchar_t(0));
#    if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN64__)
			WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, const_cast<char*>(mbstr.c_str()), size, NULL, NULL);
#	else
			wcstombs(const_cast<char*>(mbstr.c_str()), const_cast<wchar_t*>(str.c_str()), (size + 1) * 4);
#	endif
			o = mbstr;
		}

		////////////////////////////////////////////////////////
		template<>
		static void toType(int v, std::wstring& o)
		{
			std::string tmp;
			toType(v, tmp);
			return toType(tmp.c_str(), o);
		}

		template<>
		static void toType(long v, std::wstring& o)
		{
			std::string tmp;
			toType(v, tmp);
			return toType(tmp.c_str(), o);
		}

		template<>
		static void toType(float v, std::wstring& o)
		{
			std::string tmp;
			toType(v, tmp);
			return toType(tmp.c_str(), o);
		}
		template<>
		static void toType(char v, std::wstring& o)
		{
			std::string tmp;
			toType(v, tmp);
			return toType(tmp.c_str(), o);
		}

		template<>
		static void toType(wchar_t v, std::wstring& o)
		{
			o += v;
		}

		template<>
		static void toType(wchar_t* v, std::wstring& o)
		{
			o = std::wstring(v);
		}

		template<>
		static void toType(const wchar_t* v, std::wstring& o)
		{
			o = std::wstring(v);
		}
		template<>
		static void toType(void* v, std::wstring& o)
		{
			std::string tmp;
			toType(v, tmp);
			return toType(tmp.c_str(), o);
		}

		template<>
		static void toType(char* v, std::wstring& o)
		{
			setlocale(LC_ALL, "");
			std::string str(v);
#    if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN64__)
			int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0) - 1;
#	else
			size_t size = mbstowcs(NULL, str.c_str(), 0);
#	endif

			std::wstring wstr(size, wchar_t(0));
#    if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN64__)
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), const_cast<wchar_t*>(wstr.c_str()), size);
#	else
			mbstowcs(const_cast<wchar_t*>(wstr.c_str()), str.c_str(), size);
#	endif
			o = wstr;
		}

		template<>
		static void toType(const char* v, std::wstring& o)
		{
			setlocale(LC_ALL, "");
			std::string str(v);
#    if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN64__)
			int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0) - 1;
#	else
			size_t size = mbstowcs(NULL, str.c_str(), 0);
#	endif

			std::wstring wstr(size, wchar_t(0));
#    if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN64__)
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), const_cast<wchar_t*>(wstr.c_str()), size);
#	else
			mbstowcs(const_cast<wchar_t*>(wstr.c_str()), str.c_str(), size);
#	endif
			o = wstr;
		}

	};
	/* ----------------------------------------------------------------------------*/
	/**
	 * @brief 输出流产生器
	 *
	 * 用户可继承此类，重写output函数和flush（可选）函数来实现一个IOStream。
	 */
	/* ----------------------------------------------------------------------------*/
	class UILIB_API IOStreamMaker : public IOStream
	{
	public:
		virtual void output(const wchar_t* data){
			output(OSTypeHelper::getStr<const wchar_t*>(data).c_str());
		}
		virtual void output(const char* data) = 0;
		//保证operator<<(StreamSymbol_t)不被掩盖
		using IOStream::operator <<;
		virtual IOStream& operator <<(int v){
			output(OSTypeHelper::getStrW<int>(v).c_str());
			return *this;
		}
		virtual IOStream& operator <<(float v){
			output(OSTypeHelper::getStrW<float>(v).c_str());
			return *this;
		}
		virtual IOStream& operator <<(wchar_t v){
			output(OSTypeHelper::getStrW<wchar_t>(v).c_str());
			return *this;
		}
		virtual IOStream& operator <<(char v){
			output(OSTypeHelper::getStrW<char>(v).c_str());
			return *this;
		}
		virtual IOStream& operator <<(wchar_t* v){
			output(v);
			return *this;
		}
		virtual IOStream& operator <<(char* v){
			output(OSTypeHelper::getStrW<char*>(v).c_str());
			return *this;
		}
		virtual IOStream& operator <<(void* v){
			output(OSTypeHelper::getStrW<void*>(v).c_str());
			return *this;
		}
		////////////////////////////////////////////////////////////
		virtual IOStream& operator <<(const wchar_t* v){
			output(v);
			return *this;
		}
		virtual IOStream& operator <<(const char* v){
			output(OSTypeHelper::getStrW<const char*>(v).c_str());
			return *this;
		}
		virtual void flush(){}
	};
	
	class TestStream : public IOStreamMaker
	{
	public:
		TestStream() {	}
		void output(const char* data)
		{
			OutputDebugStringA(data);
			OutputDebugStringA("\n");
		}
	};
};


#endif//_IOStream__h