#include "types_stub.h"
#include "node_stub.h"

int luaopen_opcua_node(lua_State *L)
{
	OOLUA::register_class<OpcUa::MessageId>();
	OOLUA::register_class<OpcUa::VariantType>();
	OOLUA::register_class<OpcUa::Variant>();
	OOLUA::register_class<OpcUa::Node>();
}
