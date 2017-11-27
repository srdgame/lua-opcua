#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WIN32 // MinGW
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include <dlfcn.h>
#include <unistd.h>
#else
#ifdef MINGW32_BUILD
#include <sys/time.h>
#include <sys/types.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <dlfcn.h>
#include <unistd.h>
#endif
// TODO: for win32 native
#endif

#ifdef __cplusplus
extern "C" {
#endif


#include <lua.h>
#include <lauxlib.h>

void ERROR_ABORT(int x, const char* s);
int lua_opcua_failmsg(lua_State *L, const char *err, const char *m);

#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM==501
# define lua_pushglobaltable(L) lua_pushvalue(L, LUA_GLOBALSINDEX)
/*
** Adapted from Lua 5.2.0
*/
void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup);
#endif


#ifdef __cplusplus
}
#endif
