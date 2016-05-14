#ifndef UIReflection_h__
#define UIReflection_h__

#ifdef _MSC_VER
#pragma once
#endif

#include<string>
#include<map>
using namespace std;

namespace DuiLib
{
	typedef void* (*DuiInstanceFun)();
	class UILIB_API DuiObjectMap
	{
	private:
		DuiObjectMap(){};
	public:
		
		static void RegisterDuiClass(LPCTSTR _duiClassName, DuiInstanceFun _createDuiInstanceFun);
		static void* createInstance(LPCTSTR _duiClassName);
		static bool isRegister(LPCTSTR _duiClassName);
		static std::map<CDuiString, DuiInstanceFun>& GetDuiClassMaps();
	};

	template<typename T>
	class UILIB_API DelegatingObject 
	{
	public:
		DelegatingObject(LPCTSTR _duiClassName)
		{
			DuiObjectMap::RegisterDuiClass(_duiClassName, (DuiInstanceFun)&(DelegatingObject::CreateClassInstance));
		}

		static T* CreateClassInstance()
		{
			return static_cast<T*>(new T);
		}
	};

	template<class TObj>
	TObj CreateDuiInstance(LPCTSTR _DuiClassName){
		return static_cast<TObj>(DuiObjectMap::createInstance(_DuiClassName));
	}

#ifndef REGIST_DUICLASS
#define REGIST_DUICLASS(DuiObject) DelegatingObject<DuiObject> __class_##DuiObject( _T(#DuiObject) );
#endif
}

#endif // UIReflection_h__