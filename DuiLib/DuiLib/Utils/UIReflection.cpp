#include "UIlib.h"
#include "UIReflection.h"

namespace DuiLib
{

	//************************************
	// 函数名称: RegistDuiClass
	// 返回类型: void
	// 参数信息: string _duiClassName					类名
	// 参数信息: DuiInstanceFun _createDuiInstanceFun	注册的函数指针
	// 函数说明：类反射注册，若已经注册过，则直接返回
	//************************************
	void DuiObjectMap::RegisterDuiClass(LPCTSTR _duiClassName, DuiInstanceFun _createDuiInstanceFun)
	{
		if (GetDuiClassMaps().size() > 0 && GetDuiClassMaps().find(_duiClassName) != GetDuiClassMaps().end())
			return;

		GetDuiClassMaps()[_duiClassName] = _createDuiInstanceFun;
		DUITRACE(_T("RegisterDuiClass:预注册UI组建%s\r\n"), _duiClassName);
	}
	void* DuiObjectMap::createInstance(LPCTSTR _duiClassName)
	{
		if (GetDuiClassMaps().size() > 0 && GetDuiClassMaps().find(_duiClassName) == GetDuiClassMaps().end())
		{
			std::map<CDuiString, DuiInstanceFun>& mDuiClassMaps = GetDuiClassMaps();
			LPCTSTR str = _T("没有找到类对象：%s ,该对象类不是由DuiLib库注册的,请在外部调用CreateControl\r\n");
			DUITRACE(str, _duiClassName);
			DuiLogWarning(str, _duiClassName);
			return NULL;
		}
		else
		{
			return (GetDuiClassMaps()[_duiClassName])();
		}
	}
	std::map<CDuiString, DuiInstanceFun>& DuiObjectMap::GetDuiClassMaps()
	{
		static std::map<CDuiString, DuiInstanceFun> m_duiClassMaps;
		return m_duiClassMaps;
	}
	bool DuiObjectMap::isRegister(LPCTSTR _duiClassName)
	{
		if (GetDuiClassMaps().size() == 0 || GetDuiClassMaps().find(_duiClassName) == GetDuiClassMaps().end())
		{
			return false;
		}
		return true;
	}
}

