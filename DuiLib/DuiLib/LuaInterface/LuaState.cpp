#include "LuaState.h"
#include "lauxlib.h"

namespace DuiLib
{
	LuaVar::LuaVar() : state(NULL), valueref(0) {}
	LuaVar::LuaVar(LuaState* state_, int ref) : state(state_), valueref(ref) {}
	LuaVar::LuaVar(lua_State* l, int ref) {}
	LuaVar::~LuaVar() {
		Dispose(false);
	}

	void LuaVar::Dispose()
	{
		Dispose(true);
		
	}

	void LuaVar::Dispose(bool disposeManagedResources)
	{
		if (valueref != 0)
		{
			
		}
	}

	lua_State* LuaVar::L() {
		return state->L;
	}
	int LuaVar::Ref() {
		return valueref;
	}

	void LuaVar::push(lua_State* l)
	{
		lua_getref(l, valueref);
	}

	int LuaVar::GetHashCode()
	{
		return 0;
	}
	bool LuaVar::Equals(IDisposable& obj)
	{
		return false;
	}

	bool LuaVar::operator ==(LuaVar& obj)
	{
		return false;
	}

	bool LuaVar::operator !=(LuaVar& obj)
	{
		return false;
	}

	//////////////////////////////////////////////////
	lua_State* LuaState::L = NULL;
	LuaState* LuaState::mainL = NULL;
	std::map<lua_State*, LuaState*> LuaState::statemap;
	lua_State* LuaState::oldptr = NULL;
	LuaState* LuaState::oldstate = NULL;
	LuaCFunction LuaState::errorFunc = NULL;

	bool LuaState::isMainThread() {
		return true;
	}

	void LuaState::Dispose()
	{
		Dispose(true);

	}

	void LuaState::Dispose(bool disposeManagedResources)
	{
		
	}

	int LuaState::GetHashCode()
	{
		return 0;
	}
	bool LuaState::Equals(IDisposable& obj)
	{
		return false;
	}

	LuaState* LuaState::get(lua_State* l)
	{
		if (l == oldptr)
			return oldstate;

		std::map<lua_State*, LuaState*>::const_iterator it = statemap.find(l);
		if (it != statemap.end())
		{
			oldptr = l;
			oldstate = it->second;
			return oldstate;
		}

		lua_getglobal(l, "__main_state");
		if (lua_isnil(l, -1))
		{
			lua_pop(l, 1);
			return NULL;
		}

		lua_State* nl = (lua_State*)lua_touserdata(l, -1);
		lua_pop(l, 1);
		if (nl != l)
			return get(nl);
		return NULL;
	}

	LuaState::LuaState()
	{
		mainThreadId = ::GetCurrentThreadId();
		l_ = luaL_newstate();
		statemap.insert(std::make_pair(l_, this));
		if (NULL == mainL)
			mainL = this;

		refQueue.clear();

	}
}

