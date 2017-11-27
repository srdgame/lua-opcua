#include "lua_helpers.h"

void ERROR_ABORT(int x, const char* s) {
	fprintf(stderr, "%d : %s\n", x, s);
	exit(-1);
}

int lua_opcua_failmsg(lua_State *L, const char *err, const char *m) {
	lua_pushnil(L);
	lua_pushliteral(L, "VISTEK API: ");
	lua_pushstring(L, err);
	lua_pushstring(L, m);
	lua_concat(L, 3);
	return 2;
}


#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM==501
# define lua_pushglobaltable(L) lua_pushvalue(L, LUA_GLOBALSINDEX)
/*
** Adapted from Lua 5.2.0
*/
void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) {
	luaL_checkstack(L, nup, "too many upvalues");
	for (; l->name != NULL; l++) {	/* fill the table with given functions */
		int i;
		for (i = 0; i < nup; i++)	/* copy upvalues to the top */
			lua_pushvalue(L, -nup);
		lua_pushstring(L, l->name);
		lua_pushcclosure(L, l->func, nup);	/* closure with those upvalues */
		lua_settable(L, -(nup + 3));
	}
	lua_pop(L, nup);	/* remove upvalues */
}
#endif

static int traceback (lua_State *L) {
	if (!lua_isstring(L, 1))  /* 'message' not a string? */
		return 1;  /* keep it intact */
	lua_pushglobaltable(L);
	lua_getfield(L, -1, "debug");
	lua_remove(L, -2);
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		return 1;
	}
	lua_getfield(L, -1, "traceback");
	if (!lua_isfunction(L, -1)) {
		lua_pop(L, 2);
		return 1;
	}
	lua_pushvalue(L, 1);  /* pass error message */
	lua_pushinteger(L, 2);  /* skip this function and traceback */
	lua_call(L, 2, 1);  /* call debug.traceback */
	return 1;
}


void lua_opcua_check_callback(lua_State* L, conn_handle_t* data, int index)
{
	luaL_checktype(L, index, LUA_TFUNCTION);
	luaL_unref(L, LUA_REGISTRYINDEX, data->callback);
	lua_pushvalue(L, index);
	data->callback = luaL_ref(L, LUA_REGISTRYINDEX);
}

void lua_opcua_call_callback(lua_State* L, conn_handle_t* data, int nargs) {
	int ref = data->callback;
	if (ref == LUA_NOREF) {
		lua_pop(L, nargs);
	} else {
		// Get the traceback function in case of error
		lua_pushcfunction(L, traceback);
		// And insert it before the args if there are any.
		if (nargs) {
			lua_insert(L, -1 - nargs);
		}
		// Get the callback
		lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
		// And insert it before the args if there are any.
		if (nargs) {
			lua_insert(L, -1 - nargs);
		}

		if (lua_pcall(L, nargs, 0, -2 - nargs)) {
			fprintf(stderr, "Uncaught Error: %s\n", lua_tostring(L, -1));
			exit(-1);
		}
		// Remove the traceback function
		lua_pop(L, 1);
	}
}


