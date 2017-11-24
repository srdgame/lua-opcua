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

#include "lua_opcua.h"

#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM==501
# define lua_pushglobaltable(L) lua_pushvalue(L, LUA_GLOBALSINDEX)
/*
** Adapted from Lua 5.2.0
*/
extern "C"
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

extern "C"
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

extern "C"
static int opcua_node_gc(lua_State *L)
{
	opcua_node_t *node = (opcua_node_t *)luaL_checkudata (L, 1, OPCUA_NODE);
	if (node != NULL) {
		/* Nullify structure fields. */
		luaL_unref (L, LUA_REGISTRYINDEX, node->env);
		node->env = LUA_NOREF;
		
		if (node->callback) {
			luaL_unref (L, LUA_REGISTRYINDEX, node->callback->callback);
			free(node->callback);
			node->callback = NULL;
		}
	}
	return 0;
}

#define VALID_NODE(L) \
	opcua_node_t *node = (opcua_node_t *)luaL_checkudata (L, 1, OPCUA_NODE); \
	if (!node) { \
		return visapi_failmsg(L, "Node Missing: ", "Null object");\
	}

extern "C"
static int opcua_node_get_id(lua_State *L)
{
	VALID_NODE(L);
	auto id = node->node.GetId();
	if (id.IsInteger()) {
		lua_pushinteger(L, id.GetIntegerIdentifier());
	}
	else if (id.IsString()) {
		lua_pushstring(L, id.GetStringIdentifier().c_str());
	}
	else if (id.IsGuid()) {
		auto guid = id.GetGuidIdentifier();
		lua_pushlstring(L, (char*)guid, sizeof(guid));
	}
	else if (id.IsBinary()) {
		auto bin = id.GetBinaryIdentifier();
		lua_pushlstring(L, (char*)&bin[0], bin.length());
	}
	else {
		return visapi_failmsg(L, "Node Id: ", "Unknown Type");\
	}
	return 1;
}

extern "C"
static int opcua_node_get_parent(lua_State *L)
{
	VALID_NODE(L);
	return opcua_create_node(L, NULL, 1, node->node);
}

extern "C"
static int opcua_node_get_children(lua_State *L)
{
	VALID_NODE(L);
	lua_newtable(L);
	auto children = node->node.GetChildren();
	for (int i = 0; i < children.length(); ++i) {
		opcua_create_node(L, NULL, 1, children[i]);
		lua_seti(L, -2, i);
	}
	
	return 1;
}

extern "C"
static int opcua_node_get_child(lua_State *L)
{
	VALID_NODE(L);
	if (lua_isstring(L, 2)) {
		auto browsename = luaL_checkstring(L, 2);
		return opcua_create_node(L, NULL, 1, node->node.GetChild(browsename));
	} else {
		//TODO:
		return 0;
	}
}

extern "C"
static int opcua_node_get_properties(lua_State *L)
{
	VALID_NODE(L);
	lua_newtable(L);
	auto children = node->node.GetProperties();
	for (int i = 0; i < children.length(); ++i) {
		opcua_create_node(L, NULL, 1, children[i]);
		lua_seti(L, -2, i);
	}
	
	return 1;
}

extern "C"
static int opcua_node_get_variables(lua_State *L)
{
	VALID_NODE(L);
	lua_newtable(L);
	auto children = node->node.GetVariables();
	for (int i = 0; i < children.length(); ++i) {
		opcua_create_node(L, NULL, 1, children[i]);
		lua_seti(L, -2, i);
	}
	
	return 1;
}

extern "C"
static int opcua_node_is_valid(lua_State *L)
{
	VALID_NODE(L);
	if (node->node.IsValid()) {
		lua_pushboolean(L, 1);
	} else {
		lua_pushboolean(L, 0);
	}
	return 1;
}

extern "C"
static int opcua_node_get_attribute(lua_State *L)
{
	VALID_NODE(L);
	int attr_id = luaL_checkinteger(L, 2);
	return opcua_create_datavalue(L, node->node.GetAttribute(attr_id));
}

extern "C"
static int opcua_node_set_attribute(lua_State *L)
{
	VALID_NODE(L);

	int attr_id = luaL_checkinteger(L, 2);
	opcua_datavalue_t *val = (opcua_datavalue_t *)luaL_checkudata (L, 3, OPCUA_DATAVALUE);
	if (!val) {
		return visapi_failmsg(L, "DataValue Missing: ", "Null object");
	}
	node->node.SetAttribute(attr_id, val);
	return 0;
}

extern "C"
static int opcua_node_get_access_level(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

extern "C"
static int opcua_node_set_access_level(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

extern "C"
static int opcua_node_get_description(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

extern "C"
static int opcua_node_set_description(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

extern "C"
static int opcua_node_get_node_class(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

extern "C"
static int opcua_node_set_node_class(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

extern "C"
static int opcua_node_get_user_access_level(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}


extern "C"
static int opcua_node_set_user_access_level(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

extern "C"
static const struct luaL_Reg node_object_funcs[] = {
	{ "__gc", opcua_node_gc },
	{ "get_id", opcua_node_get_id },
	{ "get_parent", opcua_node_get_parent },
	{ "get_children", opcua_node_get_children },
	{ "get_child", opcua_node_get_child },
	{ "get_properties", opcua_node_get_properties },
	{ "get_variables", opcua_node_get_variables },

	{ "is_valid", opcua_node_is_valid },

	{ "get_attribute", opcua_node_get_attribute },
	{ "set_attribute", opcua_node_set_attribute },
	{ "get_access_level", opcua_node_get_access_level },
	{ "set_access_level", opcua_node_set_access_level },
	{ "get_description", opcua_node_get_description },
	{ "set_description", opcua_node_set_description },
	{ "get_node_class", opcua_node_get_node_class },
	{ "set_node_class", opcua_node_set_node_class },
	{ "get_user_access_level", opcua_node_get_user_access_level },
	{ "set_user_access_level", opcua_node_set_user_access_level },
	/*
	{ "get_user_write_mask", opcua_node_get_user_write_mask },
	{ "set_user_write_mask", opcua_node_set_user_write_mask },
	{ "get_write_mask", opcua_node_get_write_mask },
	{ "set_write_mask", opcua_node_set_write_mask },
	{ "get_value", opcua_node_get_value },
	{ "set_value", opcua_node_set_value },
	{ "get_data_value", opcua_node_get_data_value },
	{ "set_data_value", opcua_node_set_data_value },

	{ "get_data_type", opcua_node_get_data_type },

	{ "call_method", opcua_node_call_method },
	{ "call_methods", opcua_node_call_methods },

	{ "add_nodes", opcua_node_add_nodes },
	{ "add_references", opcua_node_add_references },

	{ "add_folder", opcua_node_add_folder },
	{ "add_object", opcua_node_add_object },
	{ "add_variable", opcua_node_add_variable },
	{ "add_property", opcua_node_add_property },
	{ "add_method", opcua_node_add_method },
	*/

	{ NULL, NULL},
};

extern "C"
static int opcua_create_node (lua_State *L, callback_t* cb, int env, OpcUa::Node& node) {
	opcua_node_t *node = (opcua_node_t *)lua_newuserdata(L, sizeof(opcua_node_t));
	luaL_getmetatable (L, OPCUA_NODE);
	lua_setmetatable (L, -2);

	/* fill in structure */
	node->env = LUA_NOREF;
	node->node = node;
	node->callback = cb;
	lua_pushvalue(L, env);
	node->env = luaL_ref(L, LUA_REGISTRYINDEX);

	return 1;
}

extern "C"
static int lua_opcua_node_init_meta(lua_State *L)
{
	if (!luaL_newmetatable(L, VISAPI_CONN))
		return 0;
	luaL_setfuncs(L, node_object_funcs, 0);

	/* define metamethods */
	lua_pushliteral (L, "__index");
	lua_pushvalue (L, -2);
	lua_settable (L, -3);

	lua_pushliteral (L, "__tostring");
	lua_pushstring (L, VISAPI_CONN);
	lua_pushcclosure (L, opcua_node_tostring, 1);
	lua_settable (L, -3);

	lua_pushliteral (L, "__metatable");
	lua_pushliteral (L, "Lua-OpcUa: you're not allowed to get this metatable");
	lua_settable (L, -3);

	lua_pop(L, 1);

	return 1;
}

extern "C"
int luaopen_opcua_node(lua_State *L) {
{
	lua_opcua_node_init_meta(L);

	return 1;
}
