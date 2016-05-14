#include "LuaEntry.h"

#include "LuaCWindow.h"

namespace DuiLib
{
	CLuaWindow::CLuaWindow(LPCTSTR szName, UINT nStyle/* = CS_DBLCLKS*/)
		: szWindowName(szName), nClassStyle(nStyle),  CWin() {	}
	LPCTSTR CLuaWindow::GetWindowClassName() const { return szWindowName; }
	UINT CLuaWindow::GetClassStyle() const { return nClassStyle; }
	void CLuaWindow::OnFinalMessage(HWND hWnd)
	{
		PaintMgr()->RemovePreMessageFilter(this);
		PaintMgr()->RemoveNotifier(this);
		PaintMgr()->ReapObjects(PaintMgr()->GetRoot());
		
		if (CallLuaFuncBegin("OnFinalMessage"))
		{
			CallLuaFuncEnd(0);
		}
		this->SetValid(FALSE);
		this->UnTouchMsgTable();

		delete this;
	}
#pragma region RESOURCE_TYPE
	CDuiString CLuaWindow::GetSkinPath()
	{
		CLuaWindow* pThis = const_cast<CLuaWindow*>(this);
		if (pThis->CallLuaFuncBegin("GetSkinPath"))
		{
			pThis->CallLuaFuncEnd(0, 1);
			CDuiString sPath;
			lua_op_t<CDuiString>::get_ret_value(L(), -1, sPath);
			return sPath;
		}
		else
		{
			return _T("");
		}
	}
	CDuiString CLuaWindow::GetSkinFolder()
	{
		CLuaWindow* pThis = const_cast<CLuaWindow*>(this);
		if (pThis->CallLuaFuncBegin("GetSkinFolder"))
		{
			pThis->CallLuaFuncEnd(0, 1);
			CDuiString sPath;
			lua_op_t<CDuiString>::get_ret_value(L(), -1, sPath);
			return sPath;
		}
		else
		{
			return _T("");
		}
	}
	UILIB_RESOURCETYPE CLuaWindow::GetResourceType() const
	{
		CLuaWindow* pThis = const_cast<CLuaWindow*>(this);
		if (pThis->CallLuaFuncBegin("GetResourceType"))
		{
			pThis->CallLuaFuncEnd(0, 1);
			dui_int8 nRet = 1;
			lua_op_t<dui_int8>::get_ret_value(L(), -1, nRet);
			return (UILIB_RESOURCETYPE)(nRet);
		}
		else
		{
			return UILIB_RESOURCETYPE::UILIB_FILE;
		}
	}
	CDuiString CLuaWindow::GetZIPFileName() const
	{
		CLuaWindow* pThis = const_cast<CLuaWindow*>(this);
		if (pThis->CallLuaFuncBegin("GetZIPFileName"))
		{
			pThis->CallLuaFuncEnd(0, 1);
			CDuiString sZip;
			lua_op_t<CDuiString>::get_ret_value(L(), -1, sZip);
			return sZip;
		}
		else
		{
			return _T("");
		}
	}
	LPCTSTR CLuaWindow::GetResourceID() const
	{
		CLuaWindow* pThis = const_cast<CLuaWindow*>(this);
		if (pThis->CallLuaFuncBegin("GetResourceID"))
		{
			pThis->CallLuaFuncEnd(0, 1);
			CDuiString sID;
			lua_op_t<CDuiString>::get_ret_value(L(), -1, sID);
			return sID;
		}
		else
		{
			return _T("");
		}
	}
#pragma endregion RESOURCE_TYPE
	CPaintManagerUI* CLuaWindow::PaintMgr() const { return GetPaintMgr(); }

	void CLuaWindow::TouchMsgTable(int nLuaObjRef,int nLuaMsgRef)
	{
		mLuaObjRef = nLuaObjRef;
		mLuaMsgRef = nLuaMsgRef;
	}

	void CLuaWindow::UnTouchMsgTable()
	{
		luaL_unref(L(), LUA_REGISTRYINDEX,mLuaObjRef);
		luaL_unref(L(), LUA_REGISTRYINDEX,mLuaMsgRef);
	}

	lua_State* CLuaWindow::L() const { return LuaState::L; }

	bool CLuaWindow::onUIEvent(void* param)
	{
		if (CallLuaFuncBegin("OnUIEvent"))
		{
			const TEventUI* pEvent = static_cast<TEventUI*>(param);
			LuaStatic::AddObject2Lua(L(), pEvent, "TEventUI");
			CallLuaFuncEnd(1,1);
			bool ret = false;
			lua_op_t<bool>::get_ret_value(L(), -1, ret);
			return ret;
		}
		return false;
	}

	bool CLuaWindow::onUIDestroy(void* param)
	{
		if (CallLuaFuncBegin("OnUIDestroy"))
		{
			CControlUI* pEvent = static_cast<CControlUI*>(param);
			LuaStatic::AddObject2Lua(L(), pEvent, METATABLE_NAME(pEvent));
			CallLuaFuncEnd(1, 1);
			bool ret = false;
			lua_op_t<bool>::get_ret_value(L(), -1, ret);
			return ret;
		}
		return false;
	}

	void CLuaWindow::Notify(TNotifyUI &msg)
	{
		if (CallLuaFuncBegin("OnNotify"))
		{
			LuaStatic::AddObject2Lua(L(), &msg, "TNotifyUI");
			CallLuaFuncEnd(1);
		}
	}
	LRESULT CLuaWindow::MessageHandler(UINT msg, WPARAM wparam, LPARAM lparam, bool &handled)
	{
		if (!CallLuaFuncBegin("MessageHandler"))
		{
			goto done;
		}
		lua_pushinteger(L(), msg);
		lua_pushinteger(L(), wparam);
		lua_pushinteger(L(), lparam);
		CallLuaFuncEnd(3);
	done:
		handled = FALSE;
		return FALSE;
	}
	CControlUI * CLuaWindow::CreateControl(LPCTSTR pstrClass)
	{
		if (CallLuaFuncBegin("CreateControl"))
		{
			CDuiString pstrText(pstrClass);
			lua_op_t<CDuiString>::push_stack(L(), pstrText);
			CallLuaFuncEnd(1, 1);
			CControlUI* pControl = static_cast<CControlUI*>(LuaStatic::CheckUserData(L(), -1));
			return pControl;
		}
		else
		{
			return NULL;
		}
	}
	LPCTSTR CLuaWindow::GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
	{
		if (CallLuaFuncBegin("GetItemText"))
		{
			LuaStatic::AddObject2Lua(L(), pControl,METATABLE_NAME(pControl));
			lua_pushinteger(L(), iIndex);
			lua_pushinteger(L(), iSubItem);
			CallLuaFuncEnd(3);
		}
		return pControl->GetUserData();
	}

	void CLuaWindow::PushThis()
	{
		LuaStatic::AddObject2Lua(L(), this, "CLuaWindow");
	}

	LRESULT CLuaWindow::ProcessWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		__super::ProcessWindowMessage(uMsg, wParam, lParam, bHandled);
		if (!CallLuaFuncBegin("ProcessWindowMessage"))
		{
			goto done;
		}
		lua_op_t<dui_uint32>::push_stack(L(), uMsg);
		lua_op_t<dui_uint32>::push_stack(L(), wParam);
		lua_op_t<dui_int32>::push_stack(L(), lParam);

		CallLuaFuncEnd(3);
	done:
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT CLuaWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &handled)
	{
		__super::OnCreate(uMsg, wParam, lParam, handled);
		if (CallLuaFuncBegin("OnCreate"))
		{
			lua_pushinteger(L(), wParam);
			lua_pushinteger(L(), lParam);
			CallLuaFuncEnd(2, 0);

			handled = TRUE;
		}

		RECT rcClient;
		::GetClientRect(*this, &rcClient);
		::SetWindowPos(*this, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
			rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);

		CenterWindow();

		return TRUE;
	}

	LRESULT CLuaWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		__super::OnDestroy(uMsg, wParam, lParam, bHandled);
		if (CallLuaFuncBegin("OnDestroy"))
		{
			lua_pushinteger(L(), wParam);
			lua_pushinteger(L(), lParam);
			CallLuaFuncEnd(2, 0);

			bHandled = TRUE;
		}
		return TRUE;
	}

	LRESULT CLuaWindow::OnSysCommand(UINT msg, WPARAM wparam, LPARAM lparam, BOOL &handled)
	{
		LRESULT ret = __super::OnSysCommand(msg, wparam, lparam, handled);
		if (CallLuaFuncBegin("OnSysCommand"))
		{
			lua_pushinteger(L(), wparam);
			lua_pushinteger(L(), lparam);
			CallLuaFuncEnd(2, 0);
			handled = TRUE;
		}
		return ret;
	}

	bool CLuaWindow::CallLuaFuncBegin(const char* func)
	{
		return Lua::CallLuaPlusObjectBegin(mLuaMsgRef, mLuaObjRef, func);
	}

	void CLuaWindow::CallLuaFuncEnd(int nExternArgs, int nRets)
	{
		return Lua::CallLuaFuncEnd(1 + nExternArgs, nRets);
	}
}