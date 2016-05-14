#include "UIlib.h"
#include "UIUserControl.h"

namespace DuiLib
{
	template<typename T>
	LPCTSTR CUserControlUI<T>::GetClassName()
	{
		return _T("UserControlUI");
	}

	template<typename T>
	LPCTSTR CUserControlUI<T>::GetClass() const
	{
		return _T("UserControlUI");
	}

	template<typename T>
	CUserControlUI<T>::CUserControlUI(CPaintManagerUI* ppm)
	{
		ASSERT(ppm && _T("PaintManagerUI is null"));
		this->SetManager(ppm, this);
	}

	template<typename T>
	CUserControlUI<T>::~CUserControlUI()
	{}

	template<typename T>
	bool CUserControlUI<T>::CreateFromXML(STRINGorID xml, LPCTSTR type /* = NULL */)
	{
		CControlUI* pReturn = NULL;
		if (!m_builder.GetMarkup()->IsValid()) 
		{
			pReturn = m_builder.Create(xml, type, NULL, m_pManager, this);
		}
		else 
		{
			pReturn = m_builder.Create((UINT)0, m_pManager, this);
		}

		return pReturn != NULL;
	}

}