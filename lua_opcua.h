#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>

#ifdef __cplusplus
}
#endif

#include <opc/ua/node.h>
#include <opc/ua/event.h>
#include <opc/ua/subscription.h>
#include <opc/ua/client/client.h>
#include <opc/ua/server/server.h>

#define OPCUA_CLIENT "LUA_OPCUA_CLIENT_KEY"
#define OPCUA_SERVER "LUA_OPCUA_SERVER_KEY"
#define OPCUA_NODE "LUA_OPCUA_NODE_KEY"
#define OPCUA_DATAVALUE "LUA_OPCUA_DATAVALUE_KEY"

typedef struct {
	lua_State* state;
	int callback;
} callback_t;

typedef struct {
	int env;
	OpcUa::DataValue value;	
} opcua_datavalue_t;

typedef struct {
	int env;
	OpcUa::Node node;	
} opcua_node_t;

typedef struct {
	int env;
	OpcUa::Event event;
} opcua_event_t;

typedef struct {
	int env;
	OpcUa::Subscription sub;
} opcua_sub_t;

typedef struct {
	int env;
	OpcUa::UaClient client;
} opcua_client_t;

typedef struct {
	int env;
	OpcUa::UaServer server;
} opcua_server_t;

