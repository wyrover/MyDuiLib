#ifndef UIUserControl_H
#define UIUserControl_H
#pragma once

namespace DuiLib
{
	template<typename T = CListContainerElementUI>
	class UILIB_API CUserControlUI : public T
	{
	public:
		static LPCTSTR GetClassName();
		LPCTSTR GetClass() const;
	public:
		CUserControlUI(CPaintManagerUI* ppm);
		~CUserControlUI();
	public:
		bool CreateFromXML(STRINGorID xml,LPCTSTR type = NULL);
	private:
		CDialogBuilder m_builder;
	};
}

#endif//UIUserControl_H