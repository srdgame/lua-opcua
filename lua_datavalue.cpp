
#include "lua_helpers.h"
#include "lua_opcua.h"

static int opcua_create_datavalue(lua_State *L, int env, const OpcUa::DataValue& value);

static int opcua_node_gc(lua_State *L)
{
	opcua_datavalue_t *dv = (opcua_datavalue_t *)luaL_checkudata (L, 1, OPCUA_DATAVALUE);
	if (dv != NULL) {
		/* Nullify structure fields. */
		luaL_unref (L, LUA_REGISTRYINDEX, dv->env);
		dv->env = LUA_NOREF;
	}
	return 0;
}

#define VALID_DATAVALUE(L) \
	opcua_datavalue_t *dv = (opcua_datavalue_t *)luaL_checkudata (L, 1, OPCUA_DATAVALUE); \
	if (!dv) { return lua_opcua_failmsg(L, "DataValue Missing: ", "Null object"); } \


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
		lua_pushlstring(L, (char*)&guid, sizeof(guid));
	}
	else if (id.IsBinary()) {
		auto bin = id.GetBinaryIdentifier();
		lua_pushlstring(L, (char*)&bin[0], bin.size());
	}
	else {
		return lua_opcua_failmsg(L, "Node Id: ", "Unknown Type");\
	}
	return 1;
}

static int opcua_node_get_browse_name(lua_State *L)
{
	VALID_NODE(L);

	auto name = node->node.GetBrowseName();
	char buf[256];
	sprintf (buff, "%d-%s", name.NamespaceIndex, name.Name.c_str());
	lua_pushstring(L, buf);

	return 1;
}

static int opcua_node_get_parent(lua_State *L)
{
	VALID_NODE(L);
	return opcua_create_node(L, 1, node->node);
}

static int opcua_node_get_children(lua_State *L)
{
	VALID_NODE(L);
	lua_newtable(L);
	auto children = node->node.GetChildren();
	for (unsigned i = 0; i < children.size(); ++i) {
		opcua_create_node(L, 1, children[i]);
		lua_seti(L, -2, i);
	}
	
	return 1;
}

static int opcua_node_get_child(lua_State *L)
{
	VALID_NODE(L);
	if (lua_isstring(L, 2)) {
		auto browsename = luaL_checkstring(L, 2);
		return opcua_create_node(L, 1, node->node.GetChild(browsename));
	} else {
		//TODO:
		return 0;
	}
}

static int opcua_node_get_properties(lua_State *L)
{
	VALID_NODE(L);
	lua_newtable(L);
	auto vlist = node->node.GetProperties();
	for (unsigned i = 0; i < vlist.size(); ++i) {
		opcua_create_node(L, 1, vlist[i]);
		lua_seti(L, -2, i);
	}
	
	return 1;
}

static int opcua_node_get_variables(lua_State *L)
{
	VALID_NODE(L);
	lua_newtable(L);
	auto vlist = node->node.GetVariables();
	for (unsigned i = 0; i < vlist.size(); ++i) {
		opcua_create_node(L, 1, vlist[i]);
		lua_seti(L, -2, i);
	}
	
	return 1;
}

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

static int opcua_node_get_attribute(lua_State *L)
{
	VALID_NODE(L);
	int attr_id = luaL_checkinteger(L, 2);
	return opcua_create_datavalue(L, 1, node->node.GetAttribute((OpcUa::AttributeId)attr_id));
}

static int opcua_node_set_attribute(lua_State *L)
{
	VALID_NODE(L);

	int attr_id = luaL_checkinteger(L, 2);
	opcua_datavalue_t *val = (opcua_datavalue_t *)luaL_checkudata (L, 3, OPCUA_DATAVALUE);
	if (!val) {
		return lua_opcua_failmsg(L, "DataValue Missing: ", "Null object");
	}
	node->node.SetAttribute((OpcUa::AttributeId)attr_id, val->value);
	return 0;
}

static int opcua_node_get_access_level(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

static int opcua_node_set_access_level(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

static int opcua_node_get_description(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

static int opcua_node_set_description(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

static int opcua_node_get_node_class(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

static int opcua_node_set_node_class(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

static int opcua_node_get_user_access_level(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}


static int opcua_node_set_user_access_level(lua_State *L)
{
	VALID_NODE(L);
	return 0;
}

static const struct luaL_Reg node_object_funcs[] = {
	{ "__gc", opcua_node_gc },
	{ "get_id", opcua_node_get_id },
	{ "get_browse_name", opcua_node_get_browse_name },
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

static int opcua_create_node (lua_State *L, int env, const OpcUa::Node& node) {
	opcua_node_t *p = (opcua_node_t *)lua_newuserdata(L, sizeof(opcua_node_t));
	luaL_getmetatable (L, OPCUA_NODE);
	lua_setmetatable (L, -2);

	/* fill in structure */
	p->env = LUA_NOREF;
	p->node = node;
	lua_pushvalue(L, env);
	p->env = luaL_ref(L, LUA_REGISTRYINDEX);

	return 1;
}

static int opcua_node_tostring (lua_State *L) {
	char buff[256];
	VALID_NODE(L);
	if (node->node.IsValid()) {
		auto name = node->node.GetBrowseName();
		sprintf (buff, "%d-%s", name.NamespaceIndex, name.Name.c_str());
	}
	else
		strcpy (buff, "closed");
	lua_pushfstring (L, "%s (%s)", lua_tostring(L,lua_upvalueindex(1)), buff);
	return 1;
}

static int lua_opcua_node_init_meta(lua_State *L)
{
	if (!luaL_newmetatable(L, OPCUA_NODE))
		return 0;
	luaL_setfuncs(L, node_object_funcs, 0);

	/* define metamethods */
	lua_pushliteral (L, "__index");
	lua_pushvalue (L, -2);
	lua_settable (L, -3);

	lua_pushliteral (L, "__tostring");
	lua_pushstring (L, OPCUA_NODE);
	lua_pushcclosure (L, opcua_node_tostring, 1);
	lua_settable (L, -3);

	lua_pushliteral (L, "__metatable");
	lua_pushliteral (L, "Lua-OpcUa: you're not allowed to get this metatable");
	lua_settable (L, -3);

	lua_pop(L, 1);

	return 1;
}

int luaopen_opcua_node(lua_State *L)
{
	lua_opcua_node_init_meta(L);

	return 1;
}
