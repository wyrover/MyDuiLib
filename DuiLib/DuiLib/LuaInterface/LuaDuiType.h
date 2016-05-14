#ifndef _LuaDuiType_h
#define _LuaDuiType_h
#pragma once

#include "fflua/lua/fflua_register.h"
namespace ff
{
	template<>
	struct lua_op_t < DuiLib::CDuiString >
	{
		static void push_stack(lua_State* ls_, const DuiLib::CDuiString& arg_)
		{
			LPCTSTR d = arg_.GetData();
			lua_op_t<LPCTSTR>::push_stack(ls_, d);
		}

		static int get_ret_value(lua_State* ls_, int pos_, DuiLib::CDuiString& param_)
		{
			if (!lua_isstring(ls_, pos_))
			{
				return -1;
			}

			lua_pushvalue(ls_, pos_);
			size_t len = 0;
			const char* src = lua_tolstring(ls_, -1, &len);
			param_.Append(src);
			lua_pop(ls_, 1);

			return 0;

			return 0;
		}
		static int lua_to_value(lua_State* ls_, int pos_, DuiLib::CDuiString& param_)
		{
			size_t len = 0;
			const char* str = luaL_checklstring(ls_, pos_, &len);
			param_.Append(str);
			return 0;
		}
	};
	template<>
	struct lua_op_t < DuiLib::CDuiString& >
	{
		static void push_stack(lua_State* ls_, const DuiLib::CDuiString& arg_)
		{
			LPCTSTR d = arg_.GetData();
			lua_op_t<LPCTSTR>::push_stack(ls_, d);
		}

		static int get_ret_value(lua_State* ls_, int pos_, DuiLib::CDuiString& param_)
		{
			if (!lua_isstring(ls_, pos_))
			{
				return -1;
			}

			lua_pushvalue(ls_, pos_);
			size_t len = 0;
			const char* src = lua_tolstring(ls_, -1, &len);
			param_.Append(src);
			lua_pop(ls_, 1);

			return 0;

			return 0;
		}
		static int lua_to_value(lua_State* ls_, int pos_, DuiLib::CDuiString& param_)
		{
			size_t len = 0;
			const char* str = luaL_checklstring(ls_, pos_, &len);
			param_.Append(str);
			return 0;
		}
	};
	template<>
	struct lua_op_t <const DuiLib::CDuiString >
	{
		static void push_stack(lua_State* ls_, const DuiLib::CDuiString& arg_)
		{
			LPCTSTR d = arg_.GetData();
			lua_op_t<LPCTSTR>::push_stack(ls_, d);
		}

		static int get_ret_value(lua_State* ls_, int pos_, DuiLib::CDuiString& param_)
		{
			if (!lua_isstring(ls_, pos_))
			{
				return -1;
			}

			lua_pushvalue(ls_, pos_);
			size_t len = 0;
			const char* src = lua_tolstring(ls_, -1, &len);
			param_.Append(src);
			lua_pop(ls_, 1);

			return 0;

			return 0;
		}
		static int lua_to_value(lua_State* ls_, int pos_, DuiLib::CDuiString& param_)
		{
			size_t len = 0;
			const char* str = luaL_checklstring(ls_, pos_, &len);
			param_.Append(str);
			return 0;
		}
	};
	template<>
	struct lua_op_t <const DuiLib::CDuiString& >
	{
		static void push_stack(lua_State* ls_, const DuiLib::CDuiString& arg_)
		{
			LPCTSTR d = arg_.GetData();
			lua_op_t<LPCTSTR>::push_stack(ls_, d);
		}

		static int get_ret_value(lua_State* ls_, int pos_, DuiLib::CDuiString& param_)
		{
			if (!lua_isstring(ls_, pos_))
			{
				return -1;
			}

			lua_pushvalue(ls_, pos_);
			size_t len = 0;
			const char* src = lua_tolstring(ls_, -1, &len);
			param_.Append(src);
			lua_pop(ls_, 1);

			return 0;

			return 0;
		}
		static int lua_to_value(lua_State* ls_, int pos_, DuiLib::CDuiString& param_)
		{
			size_t len = 0;
			const char* str = luaL_checklstring(ls_, pos_, &len);
			param_.Append(str);
			return 0;
		}
	};
	template<>
	struct lua_op_t<SIZE>
	{
		static void push_stack(lua_State* ls_, const SIZE& arg_)
		{
			SIZE d = arg_;
			lua_op_t<SIZE*>::push_stack(ls_, &d);
		}

		static int get_ret_value(lua_State* ls_, int pos_, SIZE& param_)
		{
			return 0;
		}
		static int lua_to_value(lua_State* ls_, int pos_, SIZE& param_)
		{

			return 0;
		}
	};
	template<>
	struct lua_op_t < POINT >
	{
		static void push_stack(lua_State* ls_, const POINT& arg_)
		{
			POINT d = arg_;
			lua_op_t<POINT*>::push_stack(ls_, &d);
		}

		static int get_ret_value(lua_State* ls_, int pos_, POINT& param_)
		{
			return 0;
		}
		static int lua_to_value(lua_State* ls_, int pos_, POINT& param_)
		{

			return 0;
		}
	};
	template<>
	struct lua_op_t < RECT >
	{
		static void push_stack(lua_State* ls_, const RECT& arg_)
		{
			RECT d = arg_;
			lua_op_t<RECT*>::push_stack(ls_, &d);
		}

		static int get_ret_value(lua_State* ls_, int pos_, RECT& param_)
		{
			return 0;
		}
		static int lua_to_value(lua_State* ls_, int pos_, RECT& param_)
		{

			return 0;
		}
	};
	template<>
	struct lua_op_t < RECT& >
	{
		static void push_stack(lua_State* ls_, const RECT& arg_)
		{
			RECT d = arg_;
			lua_op_t<RECT*>::push_stack(ls_, &d);
		}

		static int get_ret_value(lua_State* ls_, int pos_, RECT& param_)
		{
			return 0;
		}
		static int lua_to_value(lua_State* ls_, int pos_, RECT& param_)
		{

			return 0;
		}
	};
	template<>
	struct lua_op_t <const RECT >
	{
		static void push_stack(lua_State* ls_, const RECT& arg_)
		{
			RECT d = arg_;
			lua_op_t<RECT*>::push_stack(ls_, &d);
		}

		static int get_ret_value(lua_State* ls_, int pos_, RECT& param_)
		{
			return 0;
		}
		static int lua_to_value(lua_State* ls_, int pos_, RECT& param_)
		{

			return 0;
		}
	};
	template<>
	struct lua_op_t <const RECT& >
	{
		static void push_stack(lua_State* ls_, const RECT& arg_)
		{
			RECT d = arg_;
			lua_op_t<RECT*>::push_stack(ls_, &d);
		}

		static int get_ret_value(lua_State* ls_, int pos_, RECT& param_)
		{
			return 0;
		}
		static int lua_to_value(lua_State* ls_, int pos_, RECT& param_)
		{

			return 0;
		}
	};
}

#endif//_LuaDuiType_h