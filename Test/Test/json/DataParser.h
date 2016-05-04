#ifndef __DATAPARSER_H
#define __DATAPARSER_H

#include "include/json.h"

template<typename T = Json::Value>
class CDataParser
{
public:
	typedef Json::Value          value_type;

	template<typename O>
	static void toValue(value_type& v,O& o);

	template<typename O>
	static void  getValue(value_type& v,const char* key,O& o)
	{
		assert(key);
		if(!v.isNull())
		{
			value_type theValue = v[key];
			if(!theValue.isNull())
				return toValue(theValue,o);
		}

		o = O();
	}

	template<typename O>
	static void  getValue(value_type& v, const int index, O& o)
	{
		assert(key);
		if (!v.isNull())
		{
			value_type theValue = v[index];
			if (!theValue.isNull())
				return toValue(theValue, o);
		}

		o = O();
	}

	template<typename O>
	static void getValue(value_type& v,const char* key,O& o,O def_o)
	{
		assert(key);
		if(!v.isNull())
		{
			value_type theValue = v[key];
			if(!theValue.isNull())
				return toValue(theValue,o);
		}

		o = def_o;
	}
	template<typename O>
	static void getValue(value_type& v, const int index, O& o, O def_o)
	{
		assert(key);
		if (!v.isNull())
		{
			value_type theValue = v[index];
			if (!theValue.isNull())
				return toValue(theValue, o);
		}

		o = def_o;
	}

	template<typename O>
	static O getValue(value_type& v,const char* key)
	{
		assert(key);
		O o = O();
		if(!v.isNull())
		{
			value_type theValue = v[key];
			if(!theValue.isNull())
				toValue(theValue,o);
		}
		return o;
	}

	template<typename O>
	static O getValue(value_type& v, const int key)
	{
		size_t index = (size_t)key;
		assert(index >= 0 && index <v.size());
		O o = O();
		if (!v.isNull())
		{
			value_type theValue = v[index];
			if (!theValue.isNull())
				toValue(theValue, o);
		}
		return o;
	}

	template<>
	static void toValue(value_type& v, value_type& o)
	{
		o = v;
	}

	template<>
	static void toValue(value_type& v,std::string& o)
	{
		o = v.asCString();
	}
	template<>
	static void toValue(value_type& v, std::wstring& o)
	{
		std::string str = v.asCString();
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
	static void toValue(value_type& v,int& o)
	{
		o = v.isInt() ? v.asInt() : atoi(v.asCString());
	}

	template<>
	static void toValue(value_type& v,unsigned& o)
	{
		o = v.isIntegral() ?  v.asUInt() : atoi(v.asCString());
	}

	template<>
	static void toValue(value_type& v,long& o)
	{
		o = v.isIntegral() ?  v.asInt(): atol(v.asCString());
	}

	template<>
	static void toValue(value_type& v,bool& o)
	{
		o = v.isIntegral() ? v.asBool() :  ("true" == v.asString());
	}
};

typedef CDataParser<Json::Value>   JsonParser;


#endif//__DATAPARSER_H