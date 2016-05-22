#ifndef _LUA_STATE_H
#define _LUA_STATE_H
#pragma once
#include "lua.h"
#include "UIlib.h"
#include <queue>
#include <map>
using namespace std;

namespace DuiLib
{
	typedef int(*LuaCFunction)(lua_State* l);

	class IDisposable
	{
		virtual void Dispose() = 0;
		virtual int GetHashCode() = 0;
		virtual bool Equals(IDisposable& obj) = 0;
	};

	class LuaState;
	class LuaVar : IDisposable
	{
	public:
		LuaVar();
		LuaVar(LuaState* state_, int ref);
		LuaVar(lua_State* l, int ref);

		~LuaVar();

		virtual void Dispose();
		void Dispose(bool disposeManagedResources);
		virtual int GetHashCode();
		virtual bool Equals(IDisposable& obj);
		virtual bool operator == (LuaVar& y);
		virtual bool operator != (LuaVar& y);

		lua_State* L();
		int Ref();

		void push(lua_State* l);
	protected:
		LuaState* state;
		int valueref;
	};

	class LuaThread : public LuaVar
	{
	public:
		LuaThread(lua_State* l, int ref) :
			LuaVar(l, ref) {}
	};

	class LuaFunction : public LuaVar
	{
	public:
		LuaFunction(LuaState* L, int ref) :
			LuaVar(L, ref) {}

		LuaFunction(lua_State* l, int ref) :
			LuaVar(l, ref) {}


	};

	class LuaState : public IDisposable
	{
	private:
		lua_State* l_;
		int mainThreadId;
	public:
		static lua_State* L;
	public:
		lua_State* Ls();
		bool isMainThread();
	public:
		virtual void Dispose();
		void Dispose(bool disposeManagedResources);
		virtual int GetHashCode();
		virtual bool Equals(IDisposable& obj);

		typedef void(*UnRefAction)(lua_State* l, int r);
		struct UnrefPair
		{
			UnRefAction act;
			int r;
		};

		std::deque<UnrefPair> refQueue;
		int PCallCSFunctionRef;

		static LuaState* mainL;
		static std::map<lua_State*, LuaState*> statemap;
		static lua_State* oldptr;
		static LuaState* oldstate;
		static LuaCFunction errorFunc;

		static LuaState* get(lua_State* l);
	public:
		LuaState();
	};

}

#endif//_LUA_STATE_H