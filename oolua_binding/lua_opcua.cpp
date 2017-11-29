#include "types_stub.h"
#include "services_stub.h"
#include "node_stub.h"

extern "C"
int luaopen_opcua_node(lua_State *L)
{
	OOLUA::register_class<OpcUa::MessageId>(L);
	OOLUA::register_class<OpcUa::VariantType>(L);
	OOLUA::register_class<OpcUa::Variant>(L);
	OOLUA::register_class<OpcUa::Services>(L);
	OOLUA::register_class<OpcUa::Node>(L);

	return 1;
}
